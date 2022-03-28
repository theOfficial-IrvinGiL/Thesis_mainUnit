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


void showOLED(String message) {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(2, 2);
  display.print(message);
  display.display();
  delay(2000);

}
void showListeningMessage() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(2, 2);
  display.print("Listening Mode . . . . .");
  display.display();

}
// void showWrongPass() {
//   display.clearDisplay();
//   display.setTextColor(WHITE);
//   display.setTextSize(1);
//   display.setCursor(2, 2);
//   display.print("Wrong Password!!");
//   display.display();

// }
