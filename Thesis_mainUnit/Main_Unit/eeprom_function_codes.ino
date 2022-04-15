//  codes that has eemprom related functions are written here: ⋙⋙⋙⋙

/**
   function for clearing the designated address on eeprom memory
*/
void clearMemory_portion(int target)
{
  for (int i = 0; i < 4; i++)
  {
    EEPROM.write(target + i, 0); // write zero on the target address
  }
}

/**
 * void function to write the data received from serial to eeprom
 */
void update_eeprom(String user_passcode)
{
  // String bufferVar = processed_message[0];
  // bufferVar += processed_message[1];
  char passcode_array[4];
  for (int x = 0; x < sizeof(passcode_array); x++)
  {
    passcode_array[x] = user_passcode[x];
  }
  int emptyEEPROM = findEmpty_address();
  for (int y = 0; y < sizeof(passcode_array); y++)
  {
    EEPROM.update(emptyEEPROM + y, passcode_array[y]);
  }
}

/**
 * void function to write to a empty memory slot on the eeprom
 */
int findEmpty_address()
{
  unsigned long emptyAddress = 0;
  unsigned long counter = 0;

  /**
  *adds the values on several eeprom memory address and identify if it
  an empty slot
  */
  while (counter < 100)
  {
    unsigned short var = short(EEPROM.read(counter));
    unsigned short var1 = short(EEPROM.read(counter + 1));
    unsigned short var2 = short(EEPROM.read(counter + 2));
    unsigned short var3 = short(EEPROM.read(counter + 3));

    unsigned short readVar = var + var1 + var2 + var3;
    if (readVar <= 0)
    {
      return counter;
      break;
    }
    else
    {
      counter += 4;
    }
  }
}

/**
* string function used to retrieve values from certain eeprom address
as indicated by the parameter
*/
String readStringFromEEPROM(int address)
{
  int len = 4;
  char data[len + 1];
  for (int i = 0; i < len; i++)
  {
    data[i] = EEPROM.read(address + i);
  }
  data[len] = '\0';
  return String(data);
}

/**
 * function to load the passcodes from eeprom ready for broadcasting
 * to the meter unit for updating/deleting purposes
 */
void loadEEPROM_data()
{
  int arrayIndex = 0;
  int eepromCounter = 0;
  // loads the existing passcode data from the eeprom
  for (int x = 0; x < sizeof(eeprom_passcodes); x++)
  {
    String this_passcode = readStringFromEEPROM(eepromCounter);
    if (this_passcode != "")
    {
      eeprom_passcodes[arrayIndex] = this_passcode;
      arrayIndex++;
    }

    eepromCounter += 4;
  }
  // marks the end of the loop; indicated by putting a value of "A"
  for (int y = 0; y < sizeof(eeprom_passcodes); y++)
  {
    if (eeprom_passcodes[y] == "") // a blank value on the array is detected, the index is given a value of "A"
    {
      eeprom_passcodes[y] = "A"; // the value "A" will be the indicator of the end of the data stream
      break;
    }
  }
}