#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <EEPROM.h>

#include <nRF24L01.h>
#include <RF24.h>



#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])

#define OLED_RESET 4
#define SCREEN_ADDRESS 0x3C


Adafruit_SH1106 display(OLED_RESET);
RF24 radio(9, 10); // CE, CSM
const byte RF_addresses [][6] = {"00001", "00002"}; //Setting the two addresses. One for transmitting and one for receiving


#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

#define registerButton 35
#define delistButton 33
#define listenButton 31

//variable declarations

String processed_message[] = {"", ""};
boolean register_mode = false;
boolean delist_mode = false;
boolean broadcast_mode = false;
boolean listen_mode = false;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);

  radio.begin();
  radio.openWritingPipe(RF_addresses[1]);  //Setting the address at which we will send the data
  radio.openReadingPipe(1, RF_addresses[0]);  //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MAX);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.

  radio.setAutoAck(false);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  radio.setRetries(15, 15);

  pinMode(registerButton, INPUT);
  pinMode(delistButton, INPUT);

}
