// code for the void loop is written here...

void loop()
{

  /**
   * conditional statement for handling detection of buttons
   */
  if (digitalRead(registerButton) == HIGH)
  {
    register_mode = HIGH;
    delist_mode = LOW;
    broadcast_mode = LOW;
    listen_mode = LOW;
  }
  else if (digitalRead(delistButton) == HIGH)
  {
    register_mode = LOW;
    delist_mode = HIGH;
    broadcast_mode = LOW;
    listen_mode = LOW;
  }

  // event handling conditional statements
  if (register_mode == HIGH)
  {
    unsigned long thisMilis = millis();
    // write functions to deal with registering new data here
    while ((millis() - thisMilis) <= 20000)
    {
      if (Serial.available() != 0)
      {
        /**
          calls function on process_codes
           to handle process
          of registering new user da
        */
        function_register();

        // write code for broadcast here
        break;
      }
      else
      {
        showOLED("Register: Waiting for data!", 2000);
      }
    }

    // set register mode back into LOW before exiting
    register_mode = LOW;
  }
  else if (delist_mode == HIGH)
  {
    unsigned long thisMilis = millis();
    // write functions to deal with registering new data here
    while ((millis() - thisMilis) <= 20000)
    {
      if (Serial.available() != 0)
      {
        /**
          calls function on process_codes to handle process
          of registering new user da
        */
        function_delist();

        // write code for broadcast here
        RF_broadcastFunction();

        break;
      }
      else
      {
        showOLED("Delist: Waiting for data!", 2000);
      }
    }

    // set delist mode back into LOW before exiting
    delist_mode = LOW;
  }
  /**
     default listening mode
  */
  else
  {
    // call the radio listening function
    RF_listenFunction();
    delay(500);
  }
}
