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
    delay(4000);
    display.clearDisplay();
}

/**
 * Message: Input Admin Passcode
*/
void showInputPasscode()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 6);
  display.println("Input Admin Passcode: ");
  display.display();
}

/**
 * 
*/
