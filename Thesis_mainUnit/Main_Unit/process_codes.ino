// codes for the computation and calculation processs are written here: ⋙⋙

/**
 * void function to clear the array contents of #processed_message
 */
void empty_serialMessages()
{
  for (int x = 0; x < sizeof(processed_message); x++)
  {
    processed_message[x] = "";
  }
}

/**
 * void function to process the serial data message sent from the android through serial
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
      processed_message[count] = message;
      showOLED(processed_message[count], 2000);

      message = "";
      count++;
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
  String concat_message = processed_message[0];
  concat_message += processed_message[1];

  Serial.flush();
  if (processed_message[0] == "")
  {
    Serial.println("The Serial message that you sent is unreadable by the system.");
    showOLED("The Serial message unreadable.", 2000);
    empty_serialMessages();
  }
  else
  {
    update_eeprom(concat_message);
    empty_serialMessages();
    showOLED("Data Registered Successfully!", 2000);
  }
}

/**
 * void function used to delist the user data processed from serial
 */
void function_delist()
{
  process_message(); // process the serial data from the serial monitor
  Serial.flush();    // clears the serial buffer
  if (processed_message[0] == "")
  {
    Serial.println("The Serial message that you sent is unreadable by the system.");
    showOLED("The Serial message that you sent is unreadable by the system.", 2000);
  }
  else
  {
    extract_delist();
  }
}

/**
 * the working function of function_delist for deleting the specified user contact
 */
void extract_delist()
{
  process_message(); // process the serial data from the serial monitor

  String concat_message = processed_message[0];
  concat_message += processed_message[1];
  String eeprom_value;
  // Serial.println(eeprom_value);
  unsigned int target_address = 0;

  unsigned int counter = 0;
  while (counter <= 300)
  {
    eeprom_value = String(readStringFromEEPROM(counter));
    Serial.println(eeprom_value);
    if (eeprom_value == concat_message)
    {
      target_address = counter;
      showOLED("Data Delisted Successfully!", 2000);
      break;
    }
    else if (counter >= 300)
    {

      target_address = counter;
      break;
    }
    counter += 15;
  }
  /**
   * if data from serial is not on the system
   * then counter will reach 300
   */
  if (counter >= 300)
  {
    showOLED("The Data you want to delist is not on the system!", 2000);
    empty_serialMessages();
  }
  else
  {
    Serial.println(target_address);
    clearMemory_portion(target_address);
    empty_serialMessages();
  }
  // 1120,23568965233,
}

// under development
//  code for dealing with listening and data from the meter unit
void RF_listenFunction()
{
  radio.startListening(); // initialize radio start listening
  if (radio.available())
  {
    digitalWrite(indicator_led, HIGH); // turn on indicator led
    /**
     * read data from the rf radio buffer
     */
    char text[32] = "";
    radio.read(&text, sizeof(text)); // get value from NRF
    radio.stopListening();

    showOLED("Data Received, Saving to SD...", 0);

    digitalWrite(nanoSwitch, HIGH);
    Serial.write(text, sizeof(text)); // write into serial sd card
    delay(1000);
    
    radio.stopListening();
    digitalWrite(nanoSwitch, LOW);
    digitalWrite(indicator_led, LOW); // turn off indicator led

    Serial.flush(); // to clear the serial buffer
  }
  else // if there is no message picked on radio buffer, then turn indicator_led off
  {
    digitalWrite(indicator_led, LOW);
    showOLED("Listening mode...", 2000);
  }
}
