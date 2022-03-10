// code for the void loop is written here...
void loop() {
  if (digitalRead(registerButton) == HIGH) {
    register_mode = HIGH;
    delist_mode = LOW;
    listen_mode = LOW;
  }
  else if (digitalRead(delistButton) == HIGH) {
    delist_mode = HIGH;
    register_mode = LOW;
    listen_mode = LOW;
  }
  else if (digitalRead(listenButton) == HIGH){
    delist_mode = LOW;
    register_mode = LOW;
    listen_mode = HIGH;
    }



  if (register_mode == HIGH) {
    String msg = "Send Serial data to register contact.";
    showOLED(msg);

    while (Serial.available() == 0) {
      showOLED("Waiting for Serial Data!!!");
    }
    function_register();
    empty_serialMessages();
    register_mode = LOW;
  }



  else if (delist_mode == HIGH) {
    String msg = "Send Serial data to delist a contact.";
    showOLED(msg);
    while (Serial.available() == 0) {
      showOLED("Waiting for Serial Data!!!");
    }
    function_delist();
    empty_serialMessages();
    delist_mode = LOW;
  }

  else {
    showNoMessage();

  }


}
