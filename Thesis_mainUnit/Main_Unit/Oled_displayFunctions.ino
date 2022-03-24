//code for oled functions are written here
void intro_message(){
    display.display();
    display.clearDisplay();
    display.setCursor(2,2);
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.print("Initializing: Main unit!");
    display.display();
    delay(2000);


}
void showText_OLED(String text){
    display.display();
    display.clearDisplay();
    display.setCursor(2,2);
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.print(text);
    display.display();
    delay(2000);


}