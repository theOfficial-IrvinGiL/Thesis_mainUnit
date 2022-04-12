/**
*Note: This tab is where declartion and library instantiations
are written and also where the void set up is located.
*/

// librabry declarations
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

// component object declarations
Adafruit_SH1106 display(OLED_RESET);
RF24 radio(9, 10);                                 // CE, CSN
const byte RF_addresses[][6] = {"00001", "00002"}; // Setting the two addresses. One for (receiving , transmitting)
int indicator_led = 00;

// misc code from oled example
#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

// definition of pushbuttons
#define registerButton 35
#define delistButton 33
// #define listenButton 31
#define nanoSwitch 4     // note include relay for cutting off the power to the arduino nano when not in use
#define indicator_led A0 // note: add indicator led for the main unit schematic design

// variable declarations

String processed_message[] = {"", ""};

/**
 *these modes are used in conjuction to the options choosen by the user by pressing the buttons
 */
boolean register_mode = false;
boolean delist_mode = false;
boolean broadcast_mode = false;
boolean listen_mode = true; // listen_mode is set to high by default at end of each reboot

char userdata_eeprom[500];

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

  RF_setupListen();             // You can set it as minimum or maximum depending on the distance between the transmitter and receiver.

  // set unano_switch button values as input
  pinMode(registerButton, INPUT);
  pinMode(delistButton, INPUT);

  // pinMode(listenButton, INPUT);
  pinMode(nanoSwitch, OUTPUT);
  pinMode(indicator_led, OUTPUT);
  blink_LED();
  showMainUnit(); // display *Main unit message at the first boot up

 
}
