// codes for the computation and calculation processs are written here: ⋙⋙

void RF_setupListen()
{
  // For NRF setup for listening
  radio.begin();
  radio.setAutoAck(false);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  radio.setRetries(15, 15);

  radio.openReadingPipe(0, RF_addresses[1]); // Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MAX);
}

// function for setting up broadcast function
void RF_setupBroadcast()
{

  radio.setAutoAck(false);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  radio.setRetries(15, 15);
  radio.openWritingPipe(address[0]);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
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
  radio.startListening(); // initialize radio start listening
  if (radio.available())
  {
    blink_LED(); // indicator if data recieved

    char text[32] = "";
    radio.read(&text, sizeof(text)); // get value from NRF
    radio.stopListening();

    showOLED("Data Received, Saving to SD...", 0);

    digitalWrite(nanoSwitch, HIGH);
    Serial.write(text, sizeof(text)); // write into serial sd card
    delay(5000);                      // delay for 5 seconds to allow nano to read and store data into sd card

    radio.stopListening();
    digitalWrite(nanoSwitch, LOW);
    delay(3000); // put a delay window for 3 seconds

    Serial.flush(); // to clear the serial buffer
  }
  else // if there is no message picked on radio buffer, then turn indicator_led off
  {
    digitalWrite(indicator_led, LOW);
    showOLED("Listening mode...", 2000);
  }
}

/**
 * function for broadcasting/updating user data to the meter unit
 * under development as of april 15, 2022
 */
void RF_broadcastFunction()
{
  showOLED("Broadcasting data!", 500);
  RF_setupBroadcast(); // call setup function to set up sending features
  loadEEPROM_data();   // loads data from eeprom into a fixed array size of 20 indexes

  for (int x = 0; x < 20; x++)
  {
    if (eeprom_passcodes[x] == "")
    {
      break;
    }
    const char text[] = eeprom_passcodes[x];
    radio.write(&text, sizeof(text));
  }
}
