// codes for the computation and calculation processs are written here: ⋙⋙

// void RF_setupListen()
// {
//   // For NRF setup for listening
//   radio.begin();
//   radio.setAutoAck(false);
//   SPI.setClockDivider(SPI_CLOCK_DIV4);
//   radio.setRetries(15, 15);

//   radio.openReadingPipe(0, RF_addresses[1]); // Setting the address at which we will receive the data
//   radio.setPALevel(RF24_PA_MAX);
// }

// function for setting up broadcast function
// void RF_setupBroadcast()
// {

//   radio.setAutoAck(false);
//   SPI.setClockDivider(SPI_CLOCK_DIV4);
//   radio.setRetries(15, 15);
//   radio.openWritingPipe(RF_addresses[0]);
//   radio.setPALevel(RF24_PA_MAX);
//   radio.stopListening();
// }

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
      processed_message = message;
      showOLED(processed_message, 1000);

      message = "";
      count++;
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
  while (counter <= 100)
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
  if (counter >= 100)
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
    /**
     * write data into I2C communications
     */
    // toSD_I2C(text);
    Serial.write(text, 32);
    // Serial.println(String(text));
    radio.stopListening();

    showOLED("Data Received, Saving to SD...", 0);

    // delay(10000);

    // while (millis() - sdStart <= 5000) // write into serial sd card
    // {
    // Serial.write(text, sizeof(text));
    // }
    radio.flush_rx();
    // delay(3000);                      // delay for 5 seconds to allow nano to read and store data into sd card

    // delay(5000); // put a delay window for 3 seconds
    // digitalWrite(nanoSwitch, LOW);

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
void RF_broadcastFunction()
{
  showOLED("Broadcasting data!", 500);
  // RF_setupBroadcast(); // call setup function to set up sending features
  loadEEPROM_data(); // loads data from eeprom into a fixed array size of 20 indexes

  for (int x = 0; x < 20; x++)
  {
    if (eeprom_passcodes[x] == "")
    {
      break;
    }
    else
    {
      String passHolder = eeprom_passcodes[x];
      char text[4];
      for (int z = 0; z < passHolder.length(); z++)
      {
        text[z] = passHolder[z];
      }
      //  char text[] = eeprom_passcodes[x];
      radio.write(&text, sizeof(text));
    }
  }
}

/**
 * method to send the data into the arduino via I2C communication
 */
// void toSD_I2C(String message)
// {
//   int mess_lenght = message.length();
//   char data[mess_lenght];
//   for (int x = 0; x < mess_lenght; x++)
//   {
//     data[x] = message[x];
//   }
//   // Write a charatre to the Slave
//   Wire.beginTransmission(SLAVE_ADDR);
//   Wire.write(data);
//   Wire.endTransmission();
// }
