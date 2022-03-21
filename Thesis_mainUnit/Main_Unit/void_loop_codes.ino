// code for the void loop is written here...
void loop()
{
  // even-mode trigger statements
  if (digitalRead(registerButton) == HIGH)
  {
    register_mode = HIGH;
    delist_mode = LOW;
    listen_mode = LOW;
  }
  else if (digitalRead(delistButton) == HIGH)
  {
    delist_mode = HIGH;
    register_mode = LOW;
    listen_mode = LOW;
  }
  // else if (digitalRead(listenButton) == HIGH)
  // {
  //   delist_mode = LOW;
  //   register_mode = LOW;
  //   listen_mode = HIGH;
  // }

  // statement for dealing with function when button 1 is pressed
  if (register_mode == HIGH)
  {
    String msg = "Send Serial data to register contact.";
    showOLED(msg);

    unsigned long now_millis = millis();
    while ((millis() - now_millis) < 30000)
    {
      showOLED("Waiting for Serial Data!!!");
      if (Serial.available() != 0)
      {
        function_register();
        empty_serialMessages();
        register_mode = LOW;
        broadcast_mode = HIGH;
        break;
      }
    }

    /**
     * note: tried to revise the commented code below to function in a different way
     */

    // while (Serial.available() == 0)
    // {
    //   showOLED("Waiting for Serial Data!!!");
    // }
    // function_register();
    // empty_serialMessages();
    // register_mode = LOW;
    // broadcast_mode = HIGH;
  }

  // statement for dealing with function when button 2 is pressed
  else if (delist_mode == HIGH)
  {
    String msg = "Send Serial data to delist a contact.";
    showOLED(msg);
    while (Serial.available() == 0)
    {
      showOLED("Waiting for Serial Data!!!");
    }
    function_delist();
    empty_serialMessages();
    delist_mode = LOW;
  }

  /**
   * skip muna for now
   */
  else if (broadcast_mode == HIGH)
  {
    // put broadcast message here

    /**
     * direct the other boolean event triggers to be false
     */
    broadcast_mode == LOW;
    delist_mode = LOW;
    register_mode = LOW;
  }

  // default statement for the unit is listening mode
  // when all other mode is not set to HIGH
  else
  {
    showListeningMessage();
    RF_listenFunction();
  }
}
