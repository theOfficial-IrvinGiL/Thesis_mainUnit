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
      showOLED(processed_message[count]);

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
    showOLED("The Serial message that you sent is unreadable by the system.");
  }
  else
  {
    update_eeprom(concat_message);
    showOLED("Data Registered Successfully!");
  }
}

/**
 * void function used to delist the user data processed from serial
 */
void function_delist()
{
  process_message();
  Serial.flush();
  if (processed_message[0] == "")
  {
    Serial.println("The Serial message that you sent is unreadable by the system.");
    showOLED("The Serial message that you sent is unreadable by the system.");
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
  process_message();

  String concat_message = processed_message[0];
  concat_message += processed_message[1];
  String eeprom_value;
  Serial.println(eeprom_value);
  unsigned int target_address = 0;

  unsigned int counter = 0;
  while (counter <= 300)
  {
    eeprom_value = String(readStringFromEEPROM(counter));
    Serial.println(eeprom_value);
    if (eeprom_value == concat_message)
    {
      target_address = x;
      showOLED("Data Delisted Successfully!");
      break;
    }
    else if (x >= 300)
    {
      showOLED("The Data you want to delist is not on the system!");
      target_address = x;
      break;
    }
  }

  for (unsigned int x = 0; x <= 300; x + 15)
  {
    eeprom_value = String(readStringFromEEPROM(x));
    Serial.println(eeprom_value);
    if (eeprom_value == concat_message)
    {
      target_address = x;
      showOLED("Data Delisted Successfully!");
      break;
    }
    else if (x >= 300)
    {
      showOLED("The Data you want to delist is not on the system!");
      target_address = x;
      break;
    }
    // else
    // {
    //   Serial.println("else");
    // }
  }
  Serial.println(target_address);
  clearMemory_portion(target_address);
}

// code for dealing with listening and data from the meter unit
void RF_listenFunction()
{
  radio.startListening(); // initialize radio start listening
  if (radio.available())
  {
    digitalWrite(relay_pin, HIGH); // turn relay HIGH
    delay(1000);                   // delay 1 sec to allow nano to boot up properly

    /**
     * read data from the rf radio buffer
     */
    char text[32] = "";
    radio.read(&text, sizeof(text));
    radio.stopListening();
    Serial.write(text, sizeof(text)); // write into serial sd card

    // turn indicator led on and off
    digitalWrite(indicator_led, HIGH);
    delay(500);
    digitalWrite(indicator_led, LOW);
    delay(500);
    digitalWrite(indicator_led, HIGH);
    delay(500);
    digitalWrite(indicator_led, LOW);

    radio.stopListening();
  }
  else // if there is no message picked on radio buffer, then turn indicator_led off
  {
    digitalWrite(indicator_led, LOW);
  }
}