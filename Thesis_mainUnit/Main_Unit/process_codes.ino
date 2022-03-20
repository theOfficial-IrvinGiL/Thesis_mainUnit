// codes for the computation and calculation processs are written here: ⋙⋙

void empty_serialMessages() {
  for (int x = 0; x < sizeof(processed_message); x++) {
    processed_message[x] = "";
  }
}

void process_message() {
  String message = "";
  short count = 0;
  while (Serial.available()) {
    char value = Serial.read();
    if (value == ',') {
      processed_message[count] = message;
      showOLED(processed_message[count]);

      message = "";
      count++;
    }
    else {
      message += value;
    }
  }
}

void function_register() {
  process_message();

  int empty_address = findEmpty_address();
  String concat_message = processed_message[0];
  concat_message += processed_message[1];
  


  Serial.flush();
  if (processed_message[0] == "" ) {
    Serial.println("The Serial message that you sent is unreadable by the system.");
    showOLED("The Serial message that you sent is unreadable by the system.");

  }
  else {
    update_eeprom(concat_message);
    showOLED("Data Registered Successfully!");

  }


}

void function_delist() {
  process_message();
  Serial.flush();
  if (processed_message[0] == "" ) {
    Serial.println("The Serial message that you sent is unreadable by the system.");
    showOLED("The Serial message that you sent is unreadable by the system.");

  }
  else {
    extract_delist();
    if (Serial.available() == 0) {
      showOLED("Data Delisted Successfully!");

    }
  }
}


void extract_delist() {
  String concat_message = processed_message[0];
  concat_message += processed_message[1];
  String eeprom_value;
  unsigned int target_address = 0;

  for (unsigned long x = 0; x < EEPROM.length(); x + 15) {
    eeprom_value = String(readStringFromEEPROM(x));
    if (eeprom_value == concat_message) {
      target_address = x;
      break;
    }
    else if (x >= 500) {
      showOLED("The Data you want to delist is not on the system!");
      break;
    }
    else {
      Serial.println("else");
    }
  }
  Serial.println(target_address);
  clearMemory_portion(target_address);


}
