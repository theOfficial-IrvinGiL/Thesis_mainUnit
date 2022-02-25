/**Notes and description
 * Predefined administrator passcodes:
 *  77351071
    27326699
    82736918
    61835240
    11808191
    12105460
    27651616
    65752500
    74198158
 *
 *
*/

// libraries
#include <Keypad.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <SPI.h>

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

Adafruit_SH1106 display(OLED_RESET);

#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    display.begin(SH1106_SWITCHCAPVCC, 0x3C);
    showMainUnit();
}

void loop()
{
start_point:
    char keyValue = customKeypad.getKey();

    if (keyValue)
    {
        switch (keyValue)
        {
        case 'A':
            requestAccess_mode = true;
            idle_mode = false;
            showInputPasscodeMessage();
            while (true)
            {
                if (keyValue)
                {
                    switch (keyValue)
                    {
                        if (fixed_numberOfInputs < 8)
                        {
                            displayChar_input(keyValue, set_CursorCollumn);
                            admin_input[fixed_numberOfInputs] = keyValue;
                            fixed_numberOfInputs++;
                        }
                    }
                }
            }

            break;
        default:
            break;
        }
    }
    else
    {
    }

    /**part of code where the main unit is receiving data from the
     * meter unit
     */
    if (idle_mode == true)
    {
    }
}
