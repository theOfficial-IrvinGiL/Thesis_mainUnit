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
    // radio.stopListening(); // turn off radio listening when any button is pressed
  }
  else if (digitalRead(delistButton) == HIGH)
  {
    register_mode = LOW;
    delist_mode = HIGH;
    // radio.stopListening();
  }

  // event handling conditional statements
  if (register_mode == HIGH)
  {
    unsigned long thisMilis = millis();
    // write functions to deal with registering new data here
    while ((millis() - thisMilis) <= 10000)
    {
      if (Serial.available() != 0)
      {
        /**
          calls function on process_codes
           to handle process
          of registering new user da
        */
        radio.stopListening();
        function_register();

        // write code for broadcast here
        showOLED("Broadcasting data!", 500);
        for (int x = 0; x < 20; x++)
        {
          String send_pass = readStringFromEEPROM(x * 4);
          if (send_pass != "")
          {
            RF_broadcastFunction(send_pass);
            delay(100);
          }
          else
          {
            break;
          }
        }
        for (int x = 0; x < 20; x++)
        {
          RF_broadcastFunction("A");
        } // end of broadcast here
        break;
      }
      else
      {
        showOLED("Register: Waiting for data!", 2000);
      }
    }
    // display.clearDisplay();
    // display.display();

    blink_LED();

    showOLED("Listening mode...", 5000);
    // set register mode back into LOW before exiting
    register_mode = LOW;
    // digitalWrite(nanoSwitch, HIGH);
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
        showOLED("Broadcasting data!", 500);
        // write code for broadcast here
        showOLED("Broadcasting data!", 500);
        for (int x = 0; x < 20; x++)
        {
          String send_pass = readStringFromEEPROM(x * 4);
          if (send_pass != "")
          {
            RF_broadcastFunction(send_pass);
            delay(100);
          }
          else
          {
            break;
          }
        }
        for (int x = 0; x < 20; x++)
        {
          RF_broadcastFunction("A");
        } // end of broadcast here

        break;
      }
      else
      {
        showOLED("Delist: Waiting for data!", 2000);
      }
    }
    blink_LED();
    showOLED("Listening mode...", 5000);
    // set delist mode back into LOW before exiting
    delist_mode = LOW;
    // digitalWrite(nanoSwitch, HIGH);
  }
  /**
     default listening mode
  */
  else
  {

    RF_listenFunction(); // call the rf listening function
    delay(2000);
  }
}
