

//librabry declarations
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <EEPROM.h>
#include <nRF24L01.h>
#include <RF24.h>


//keep in case of *determining_size_of_array problem
// #define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])

// pin and address definition
#define OLED_RESET 4
#define SCREEN_ADDRESS 0x3C

//component object declarations
Adafruit_SH1106 display(OLED_RESET);
RF24 radio(9, 10); // CE, CSM
const byte RF_address [][6] = {"00001", "00002"}; //Setting the two addresses. One for transmitting and one for receiving

/**
 * 00001 - meter unit >> main unit
 * 00002 - main unit >> meter unit
 */

//misc code from oled example
#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif


//definition of pushbuttons
#define registerButton 35
#define delistButton 33
#define listenButton 31
#define indicator_led A0

//variable declarations = = = = = = = = = = =

String processed_message = "";

/**
*these modes are used in conjuction to the options choosen by the user by pressing the buttons
*/
boolean register_mode = false;
boolean delist_mode = false;
boolean broadcast_mode = false;
boolean listen_mode = false;

// array used to hold loaded data from the eeprom memory
String eeprom_passcodes [20]; //limitted for 20 user passcodes
// String sendThis_to [] = {"benjie", "mark neil", "irvin"};
//reset function


//setup code
/**
* note: the loop code is separated for organize and clealiness purposes
*/
void setup() {

  Wire.begin();
  Serial.begin(9600);
  display.begin(SH1106_SWITCHCAPVCC, 0x3C); //  for OLED module component


  radio.begin();
  radio.setAutoAck(false);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  radio.setRetries(15, 15);

  //radio.openWritingPipe(RF_addresses[1]);  //Setting the address at which we will send the data
  radio.openReadingPipe(1, RF_address[0]);  //Setting the address at which we will receive the data
  radio.openWritingPipe(RF_address[1]);   // setting the address on which to send the data
  radio.setPALevel(RF24_PA_MAX);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.

  

  //set up defined button values as input
  pinMode(registerButton, INPUT);
  pinMode(delistButton, INPUT);
  pinMode(listenButton, INPUT);
  pinMode(indicator_led, OUTPUT);

  showMainUnit();   // display text message
  blink_LED();      //blink indicator LED
  showOLED("Listening mode...", 2000);

}




void (*resetFunc) (void) = 0; //reset function

