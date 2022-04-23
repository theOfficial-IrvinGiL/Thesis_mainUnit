
/**
*Note: This tab is where declartion and library instantiations
are written and also where the void set up is located.
*/

// library instantiations

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <EEPROM.h>
#include <nRF24L01.h>
#include <RF24.h>

// keep in case of *determining_size_of_array problem
// #define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

#define OLED_RESET 4
#define SCREEN_ADDRESS 0x3C

/**
* declarations for I2C communications
*/
#define SLAVE_ADDR 9  // Define Slave I2C Address
#define ANSWERSIZE 5  // Define Slave answer size

// component object declarations
Adafruit_SH1106 display(OLED_RESET);
RF24 radio(9, 10); // CE, CSN
// Setting the two addresses.
const byte meterTOmain_address[6] = "00001";
const byte mainTOmeter_address[6] = "00002";
/**
 * 00001 - meter unit >> main unit
 * 00002 - main unit >> meter unit
 */

int indicator_led = 00;

// misc code from oled example
#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

// <<<<<<< experimental_branch
// definition of pushbuttons
#define registerButton 35 // object definition for the register button
#define delistButton 33   //  object definition for the delist button
// #define nanoSwitch A6      // note include relay for cutting off the power to the arduino nano when not in use
#define indicator_led A0  // note: add indicator led for the main unit schematic design


// variable declarations
String processed_message = ""; // global variable to house the processed serial message

/**
 *these modes are used in conjuction to the options choosen by the user by pressing the buttons
 */
boolean register_mode = false; // mode triggered when the register button is pressed
boolean delist_mode = false;   // mode triggered when the delist button is pressed
boolean listen_mode = true;    // listen_mode is set to high by default at end of each reboot

// variable declarations for dealing with updating/delisting user data on the main and meter unit
String eeprom_passcodes[20]; // serve as array storage of passcodes registered on eeprom

// setup code
/**

 * note: the loop code is separated for organize and clealiness purposes
 */
void setup()
{

  Wire.begin();
  Serial.begin(9600);
  display.begin(SH1106_SWITCHCAPVCC, 0x3C); //  for OLED module component
  display.clearDisplay();


  radio.begin();
  radio.setAutoAck(false);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  radio.setRetries(15, 15);
  radio.setPALevel(RF24_PA_MAX);
  radio.openReadingPipe(0, meterTOmain_address);
  

  // set the switch button values as input
  pinMode(registerButton, INPUT);
  pinMode(delistButton, INPUT);

  // pinMode(nanoSwitch, OUTPUT);
  pinMode(indicator_led, OUTPUT);
  blink_LED();
  showMainUnit(); // display *Main unit message at the first boot up
  //  digitalWrite(nanoSwitch, HIGH);
}

