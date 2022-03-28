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
* generic function for displaying messages on 
the oled module
*/
void showOLED(String message) {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(2, 2);
  display.print(message);
  display.display();
  delay(2000);

}

/**
* function to show message
on listening mode
*/
void showListeningMessage() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(2, 2);
  display.print("Listening Mode . . . . .");
  display.display();

}
