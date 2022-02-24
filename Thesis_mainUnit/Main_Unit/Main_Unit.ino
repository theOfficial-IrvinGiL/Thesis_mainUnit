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

// code for sd card component
#include <SD.h>
File myFile;

// code for defining the size of the Array
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

#define OLED_RESET 4
#define SCREEN_ADDRESS 0x3C
const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {A0, A1, A2, A3};

// object instantiation for the OLED display
Adafruit_SH1106 display(OLED_RESET);

#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

// object instantiation for the keypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// variable declarations are coded here
// for getting administrator passcode
char admin_input[8];
short admin_fixedInput = 0;

unsigned short setCursorCollumn = 0; // used as reference point for the cursor when writting

char contact_input[11];
char passcode_input[4];

int addressOnEEPROM = 0;
short fixedNumberOfInputs = 0;
char codeFromEEPROM[4];
String predefined_adminpass[] = {"77351071", "27326699", "82736918", "61835240"};

/**
variables  used for identifying different modes for execution
*/
boolean accessGranted = true;

// void showUserDelist() {
//   display.setTextSize(1);
//   display.setCursor(0, 2);
//   display.println("Enter contact number to delist:");
//   display.setCursor(32, 32);
//   display.println("XXXXXXXXXXX");
//   display.display();
// }

// void showDelistedMsg() {
//   display.setTextSize(1);
//   display.setCursor(18, 20);
//   display.println("Contact Delisted");
//   display.setCursor(30, 32);
//   display.println("Successfully");
//   display.display();
// }

// void showDelisteErrorMsg() {
//   display.setTextSize(1);
//   display.setCursor(2, 12);
//   display.println("The Contact that you");
//   display.setCursor(6, 25);
//   display.println ("have entered is not");
//   display.setCursor(11, 38);
//   display.println ("Registered on the");
//   display.setCursor(45, 51);
//   display.println ("System.");
//   display.display();
// }

// method codes for displaying interface into the oled module
// method to show "Main Unit" message on display
void showMainUnit()
{
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(10, 28);
  display.print("Main Unit");
  display.display();
  delay(4000);
  display.clearDisplay();
}

// method to show the "input admin passcode" on display
void showInputPasscode()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 6);
  display.println("Input Admin Passcode: ");
  display.display();
}
// method for showing characters from user input
void displayChar_input(char input, short setcursor_Collumn)
{
  display.setTextSize(2);
  display.setCursor(setcursor_Collumn, 30);
  display.println(input);
  display.display();
}
// method to promp register user function


void showRegisterUser()
{
  display.setTextSize(1);
  display.setCursor(0, 2);
  display.println("Contact Number:");
  display.setCursor(0, 47);
  display.println("A - Enter");
  display.setCursor(0, 57);
  display.println("B - Clear");
  display.display();
}

// method to show menu to display
void showMenu()
{
  display.setTextSize(1);
  display.setCursor(0, 8);
  display.println("         MENU                              A - Register User     B - Delist User      C - View Users List  D - Control Mode");
  display.display();

  // get user choice
  char keyValue = customKeypad.getKey();
  if (keyValue)
  {
    switch (keyValue)
    {
    // register user
    case 'A':
      break;

    // delist user
    case 'B':
      break;

    // view user list
    case 'C':
      break;

    // operate on control mode
    case 'D':
      break;
    }
  }
}

// method to show passcode of the new registered user
void showRegisteredMsg(String new_passcode)
{
  display.setTextSize(1);
  display.setCursor(0, 2);
  display.println("Your Passcode is:");
  display.setTextSize(2);
  display.setCursor(37, 22);
  display.println(new_passcode);
  display.setTextSize(1);
  display.setCursor(0, 49);
  display.println("You have 20 seconds  to save this code.");
  display.display();
}

/** = = = = = = main code starts here = = = = = == */

void setup()
{
  Wire.begin();
  Serial.begin(9600);

  display.begin(SH1106_SWITCHCAPVCC, 0x3C);

  showMainUnit();
  delay(2000);
}

// int contactNumber [];
// int fixedContactNumber = 0;

void loop()
{
start_Point:
  char keyValue = customKeypad.getKey();
  showInputPasscode();

  while (true)
  {
    if (accessGranted = true)
    {
      char keyValue = customKeypad.getKey();
      if (keyValue)
      {
        switch (keyValue)
        {
        case 'A':
          // loop to look and compare values obtained from user to the predefined admin passcodes
          for (int x = 0; x < 10; x++)
          {
            String str_admin = admin_input;
            // determine if the user input stored in array is equal to one to the contents in the adminpass array
            if (str_admin.compareTo(predefined_adminpass[x]) == 1)
            {
              showMenu();
            }
          }

          break;

        case 'B':
          break;

        default:
          // first method for user input entry, number input from user for administrator authentication
          if (admin_fixedInput < sizeof(admin_input))
          {
            admin_input[admin_fixedInput] = keyValue;
            admin_fixedInput++;

            // display the user input into the oled
            displayChar_input(keyValue, setCursorCollumn);
            setCursorCollumn += 12;
          }
          break;
        }
      }
    }
    else
    {
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
