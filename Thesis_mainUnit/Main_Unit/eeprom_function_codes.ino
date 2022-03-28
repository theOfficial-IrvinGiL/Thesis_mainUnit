//  codes that has eemprom related functions are written here: ⋙⋙⋙⋙

/**
   finds the eeprom address with empty values
*/
void clearMemory_portion(int target)
{
  for (int i = 0; i < 15; i++)
  {
    EEPROM.write(target, 0);
  }
}

/**
* void function to write the data received from serial to eeprom
*/
void update_eeprom(String cNumber)
{
  String bufferVar = processed_message[0];
  bufferVar += processed_message[1];
  char contact_array[15];
  for (int x = 0; x < sizeof(contact_array); x++)
  {
    contact_array[x] = bufferVar[x];
  }
  int emptyEEPROM = findEmpty_address();
  for (int y = 0; y < sizeof(contact_array); y++)
  {
    EEPROM.update(emptyEEPROM + y, contact_array[y]);
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
  while (counter < 500)
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
      counter += 15;
    }
  }
}

/**
* string function used to retrieve values from certain eeprom address
as indicated by the parameter
*/
String readStringFromEEPROM(int address)
{
  int len = 15;
  char data[len + 1];
  for (int i = 0; i < len; i++)
  {
    data[i] = EEPROM.read(address + i);
  }
  data[len] = '\0';
  return String(data);
}


