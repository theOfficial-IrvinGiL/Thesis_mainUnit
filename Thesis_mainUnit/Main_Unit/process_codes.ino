// codes for the computation and calculation processs are written here: ⋙⋙

/**
 * process code for getting the input from the user and displaying it
 * on the OLED
 */
void getAdmin_input()
{
    char keyValue = customKeypad.getKey();

    if (keyValue)
    {
        Serial.println("above get admin access point");
        switch (keyValue)
        {
        case 'A':
            Serial.println("entered case A statement");

            if (validateAdmin_input(String(admin_input)) == true)
            {
                admin_Menu();

                requestAccess_mode = false;
                idle_mode = false;
                showAdmin_menu = true;
            }
            else
            {
                /**
                 *put error message display method here
                 */
                requestAccess_mode = false;
                idle_mode = true;
            }

            // variable reset codes
            set_CursorCollumn = 0;
            keyValue = 0x00;
            memset(admin_input, 0, sizeof(admin_input));

            break;
        case 'B':
            display.clearDisplay();
            break;
        default:
            if (fixed_numberOfInputs < sizeof(admin_input))
            {
                admin_input[fixed_numberOfInputs] = keyValue;
                displayChar_input(keyValue, set_CursorCollumn);
                fixed_numberOfInputs++;
                keyValue = 0x00;
                Serial.println("entered fix if statement");
            }
            Serial.println("entered default statement");
            break;
        }
        delay(1000);
    }
}

/**
 * determine if the user input is on the predefined admin codes
 */
bool validateAdmin_input(String inputValue)
{
    for (int x = 0; x < sizeof(predefined_adminPasscode); x++)
    {
        if (inputValue.equals(predefined_adminPasscode[x]))
        {
            return true;
        }
    }
    return false;
}

/**
 *  process method for registering new user
 */