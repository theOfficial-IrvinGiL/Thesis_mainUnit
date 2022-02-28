// code for displaying interfaces that only has text/messages is written here: ⋙⋙

/**
 * Message: Main Unit
 */
void showMainUnit()
{
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(13, 25);
    display.println("MAIN UNIT");
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.display();
    delay(2000);
    display.clearDisplay();
}

/**
 * Message: Input Admin Passcode
 */
void showInputPasscodeMessage()
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 6);
    display.println("Input Administrator");
    display.setCursor(0, 15);
    display.println("Passcode: ");
    display.display();
}

/**
 * Message: The passcode you
 * have entered is not
 * registered in the
 * system...
 */
void displayInvalid_passcodeMSG()
{
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(2, 10);
    display.print("The passcode you");
    display.setCursor(7, 20);
    display.print("have entered is not");
    display.setCursor(12, 30);
    display.print("registered in the");
    display.setCursor(40, 40);
    display.print("system.");
    display.display();
}

/**
 *Message: MENU
 */
void admin_Menu()
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(20, 10);
    display.println("- - MENU - -");
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(5, 20);
    display.println("A. Register User");
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(5, 30);
    display.println("B. Delist User");
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(5, 40);
    display.println("C. View User List");
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(5, 50);
    display.println("D. Exit menu");
    display.display();
}

// sample bug
void sampleDisplay()
{
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(10, 10);
    display.println("> GREAT <");
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(5, 40);
    display.println("> THANKS <");
    display.display();
    delay(2000);
}