/** Notes and description
Predefined administrator passcodes:
  77351071
  27326699
  82736918
  61835240
  11808191
  12105460
  27651616
  65752500
  74198158
  91741377

Keys:
  A - Enter
  B - clear



*/

#include <Keypad.h> // for keypad
#include <SPI.h>    // for oled
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <SPI.h> // for sdcard
#include <SD.h>
File myFile;

// code for defining the size of the Array
#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])

#define OLED_RESET 4
#define SCREEN_ADDRESS 0x3C
const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {A0, A1, A2, A3};

//object instantiation for the OLED display
Adafruit_SH1106 display(OLED_RESET);

#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

//object instantiation for the keypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
#define relayPin 6 //used for the relay pin

//variable declarations are coded here
  //for getting administrator passcode
  char admin_input[8];
  short admin_fixedInput = 0;
  
  char contact_input[11]; keeping 
  int addressOnEEPROM = 0;
  short setCursor_column = 0;
  short fixedNumberOfInputs = 0;
  char codeFromEEPROM[4];
  String adminpass [] = {"77351071", "27326699", "82736918", "61835240", "11808191", "12105460","27651616", "65752500", "74198158", "91741377"};

/** 
variables used in for the displaying the user 
input for getting the admin passcode
*/
short setCursorColumn_adminInput = 0;




void showMainUnit() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(4, 10);
  display.print("Main Unit");
  display.display();
  delay(4000);
  display.clearDisplay();
}

void sdCARD(String writeThis_toSD) {
  Serial.begin(9600);
  while (!Serial) {
  // wait for  serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
  while (1);
  }
  Serial.println("initialization done.");
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println(writeThis_toSD);
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

//method for prompting and asking for user input
void showInputPasscode() {
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Input Administration Passcode: ");
  display.display();
}

//show user input on oled
void showsUser_input(char key) {
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(setCursor_column, 15);
  display.print(key);
  setCursor_column += 12;
  display.display();
}

//
void showMessage(String message) {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(4, 10);
  display.print(message);
  display.display();
  delay(4000);
  display.clearDisplay();
}

//method for getting the administrator passcode
void getAdmin_passcode(){
  //loop for getting input from keypad
  while (true){
      char keyValue = customKeypad.getKey();
      if (keyValue) {
        switch (keyValue) {
          case 'A':
          
          break;
            
          case 'B':

          break;

          case 'C':
          
          break;
          default:
            if (fixedNumberOfInputs < 11) {
              user_input[fixedNumberOfInputs] = keyValue;
              showsUser_input(keyValue);
              keyValue = 0x00;
              fixedNumberOfInputs++;
            }
            break; 

        }
      }
  }
}




/** = = = = = = main code starts here = = = = = == */

void setup() {
  Wire.begin();
  Serial.begin(9600);

  display.begin(SH1106_SWITCHCAPVCC, 0x3C);

  showMainUnit();
  pinMode(relayPin, OUTPUT);
}


int contactNumber [];
int fixedContactNumber = 0;

void loop() {
 start_Point:

 char keyValue = customKeypad.getKey();
 if (keyValue){
   switch (keyValue){
     case 'A':
     //loop to look and compare values obtained from user to the predefined admin passcodes
     for(int x = 0; x < 10; x++){
       //determine if the user input stored in array is equal to one to the contents in the adminpass array
        if(contact_input.compareTo(adminpass[x]) == 1){

        }
     }
      
     break;

     case 'B':
     break;

     default:
     //first method for user input entry, number input from user for administrator authentication
      if (fixedNumberOfInputs < sizeof(contact_input)){
        contact_input[fixedNumberOfInputs] = keyValue;
        fixedNumberOfInputs++;
      }
     break;
   }
 }



}
  // //goto point
  // clearScreen:

  // showInputPasscode();
  // char keyValue = customKeypad.getKey();
  // if (keyValue) {
  //   switch (keyValue) {
  //     case 'A':
  //         display.setTextColor(WHITE);
  //         display.setTextSize(2);
  //         display.setCursor(4, 10);
  //         display.print("Enter Contact Number: ");
  //         display.setCursor(50, 10)
  //         display.print("A. Enter     B. Clear")
  //         display.setCursor(15, 10)
  //         display.display();
  //         delay(4000);
  //         display.clearDisplay();
  //         display.display();
  //         keyValue = 0x00;

  //             char keyValue = customKeypad.getKey();
  //               if (keyValue) {
  //                 switch (keyValue) {
  //                   case 'A': 
  //                     display.setTextColor(WHITE);
  //                     display.setTextSize(2);
  //                     display.setCursor(4, 10);
  //                     display.print("Proceed to generate code");
  //                     display.display();
  //                     delay(2000);
  //                     display.clearDisplay();
  //                     display.display();
  //                     keyValue = 0x00;
  //                   case 'B': 
  //                     display.clearDisplay();
  //                     setCursor_column = 0;
  //                     keyValue = 0x00;
  //                     memset(contact_input, 0, sizeof(contact_input));
  //                     fixedContactNumber = 0;
  //                     goto clearScreen;
  //                   break;

  //                 default:
  //                   if (fixedContactNumber < 11) {
  //                   contact_input[fixedContactNumber] = keyValue;
  //                   showsUser_input(keyValue);
  //                   keyValue = 0x00;
  //                   fixedContactNumber++;
  //                 }
  //                 break;
  //       break;

  //     case 'B':
  //         if (fixedNumberOfInputs < 10) {
  //         display.setTextColor(WHITE);
  //         display.setTextSize(2);
  //         display.setCursor(4, 10);
  //         display.print("Error");
  //         display.display();
  //         delay(4000);
  //         display.clearDisplay();
  //         display.display();
  //         keyValue = 0x00;
  //       }
  //       else {
          
          
  //         goto clearScreen;
  //         break;
  //       default:
  //         if (fixedNumberOfInputs < 11) {
  //           user_input[fixedNumberOfInputs] = keyValue;
  //           showsUser_input(keyValue);
  //           keyValue = 0x00;
  //           fixedNumberOfInputs++;
  //         }
  //         break;
        
  //     case 'C':
  //           display.setTextColor(WHITE);
  //           display.setTextSize(2);
  //           display.setCursor(4, 10);
  //           display.display();
            
  //           for(int x = 0; x <(EEPROM.read(0)); x++){
  //           String retrievedString = readStringFromEEPROM(eepromAddress);
  //           if retrievedString.length() == 11{
  //               display.print(retrievedString)
  //           }
            
  //           delay(4000);
  //           display.clearDisplay();
  //           display.display();
  //           keyValue = 0x00;

// ---------------------------------------------E-N-D--------------------------------------
  // display.clearDisplay();
  //       setCursor_column = 0;
  //       keyValue = 0x00;
  //       memset(user_input, 0, sizeof(user_input));
  //       fixedNumberOfInputs = 0;
  //       goto clearScreen;