// code for displaying user input into the OLED is written here: ⋙⋙

/**
 * displays user input when the system asks for admin passcode for access
 */
void displayChar_input(char input, short setcursor_Collumn)
{
    display.setTextSize(2);
    display.setCursor(setcursor_Collumn, 30);
    display.println(input);
    display.display();
    set_CursorCollumn += 12;
}