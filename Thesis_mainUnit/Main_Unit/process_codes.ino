// codes for the computation and calculation processs are written here: ⋙⋙
/**
 * Note:
 * - EEPROM is programmed to have a <= 300 address for the systems utilization
 */

void process_message()
{
  String message = "";
  short count = 0;
  while (Serial.available())
  {
    char value = Serial.read();
    if (value == ',')
    {
      processed_message = message;
      showOLED(processed_message, 1000);

      message = "";
      break;
    }
    else if (value == "") // break the loop if there is space on the serial data
    {
      break;
    }
    else
    {
      message += value;
    }
  }
}

/**
 * void function used to register the processed user data from serial
 */
void function_register()
{
  process_message();

  int empty_address = findEmpty_address();

  Serial.flush();
  if (processed_message == "")
  {
    Serial.println("The Serial message that you sent is unreadable by the system.");
    showOLED("The Serial message unreadable.", 2000);
    processed_message = "";
  }
  else
  {
    update_eeprom(processed_message);
    processed_message = "";
    showOLED("Data Registered Successfully!", 2000);
  }
  processed_message = "";
}

/**
 * void function used to delist the user data processed from serial
 */
void function_delist()
{
  process_message(); // process the serial data from the serial monitor
  Serial.flush();    // clears the serial buffer
  if (processed_message == "")
  {
    Serial.println("The Serial message that you sent is unreadable by the system.");
    showOLED("The Serial message that you sent is unreadable by the system.", 2000);
  }
  else
  {
    extract_delist();
  }
  processed_message = "";
}

/**
 * the working function of function_delist for deleting the specified user contact
 */
void extract_delist()
{
  process_message(); // process the serial data from the serial monitor

  String eeprom_value;
  // Serial.println(eeprom_value);
  unsigned int target_address = 0;

  unsigned int counter = 0;
  while (counter <= 300)
  {
    eeprom_value = String(readStringFromEEPROM(counter));
    // Serial.println(eeprom_value);
    if (eeprom_value == processed_message)
    {
      target_address = counter;
      showOLED("Data Delisted Successfully!", 2000);
      break;
    }
    else if (counter >= 100)
    {

      target_address = counter;
      break;
    }
    counter += 4;
  }
  /**
   * if data from serial is not on the system
   * then counter will reach 300
   */
  if (counter >= 300)
  {
    showOLED("The Data you want to delist is not on the system!", 2000);
    processed_message = "";
  }
  else
  {
    Serial.println(target_address);
    clearMemory_portion(target_address);
    processed_message = "";
  }
  // 1120,23568965233,
}

// under development
//  code for dealing with listening and data from the meter unit
void RF_listenFunction()
{
  unsigned long sdStart = 0;
  radio.startListening(); // initialize radio start listening
  if (radio.available())
  {

    // OLED_active = HIGH; // turn on the boolean trigger if there is data received
    sdStart = millis();
    char text[32] = "";
    radio.read(&text, 32); // get value from NRF

    showOLED(text, 3000);

    //  * write data for RF communications
    Serial.write(text, 32);
    radio.stopListening();

    showOLED("Data Received, Saving to SD...", 5000);

    // delay(10000);
    radio.flush_rx();
    // delay(3000);                      // delay for 5 seconds to allow nano to read and store data into sd card

    Serial.flush(); // to clear the serial buffer
    blink_LED();    // indicator if data recieved
    // oled_timestamp = millis();
    showOLED("Listening mode...", 5000);
  }
  else // if there is no message picked on radio buffer, then turn indicator_led off
  {

    display.clearDisplay();
    display.display();
    // oled_timestamp = millis();
  }
}

/**
 * function for broadcasting/updating user data to the meter unit
 * under development as of april 15, 2022
 */
void RF_broadcastFunction(String message)
{

  // unsigned long broadcastStart = millis();
  int messageLength = message.length();
  char data[messageLength];

  /**
     gets data from global message variable and copies it to data
     array for sending through RF
  */
  for (int x = 0; x < messageLength; x++)
  {
    data[x] = message[x];
  }

  radio.write(&data, sizeof(data)); // Sending the data
  delay(100);
}
