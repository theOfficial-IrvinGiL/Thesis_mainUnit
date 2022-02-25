// code for displaying interfaces that only has text/messages is written here: ⋙⋙

/**
 * Message: Main Unit
 */
void showMainUnit()
{
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(20, 10);
    display.println(" MAIN ");
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(20, 40);
    display.println(" UNIT ");
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
    display.println("Input Admin Passcode: ");
    display.display();
}

/**
 *Message: MENU
 */
void Menu()
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
    display.println("D. Switch To Control Mode");
    display.display();
}