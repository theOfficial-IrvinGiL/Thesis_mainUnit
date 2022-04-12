// code for displaying interfaces that only has text/messages is written here: ⋙⋙

//NRF data Recieved Data Indicator
void blink_LED()
{
//  unsigned long timestampLED = millis();
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(indicator_led, HIGH);
    delay(50);
    digitalWrite(indicator_led, LOW);
    delay(50);
  }
//  while (millis() - timestampLED <= 1500) {
//    digitalWrite(indicator_led, HIGH);
//    delay(80);
//    digitalWrite(indicator_led, LOW);
//    
//  }
}

/**
   Message: Main Unit
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
  generic function for displaying messages on
  the oled module
*/
void showOLED(String message, int delayCount) {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(2, 2);
  display.print(message);
  display.display();
  delay(delayCount);

}

/**
  function to show message
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
