

#include <SD.h>
char text[32];  
File myFile;

void store_toSD()
{
  // put your main code here, to run repeatedly:

  Serial.readBytes(text, 32);
  Serial.println(text);

  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  if (!SD.begin(10))
  {
    Serial.println("initialization failed!");
    while (1)
      ;
  }
  Serial.println("initialization done.");
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("Data.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile)
  {
    myFile.println(text);

    // close the file:
    myFile.close();
    //    Serial.println("done.");
    // readingSD();
  }
  else
  {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  SD.begin(10);
  // store_toSD();
}

void loop()
{
  if (Serial.available())
  {
    store_toSD();
    Serial.flush();
  }
}

/**
 * new I2C code here
 */
// Include Arduino Wire library for I2C
// #include <Wire.h>

// // Define Slave I2C Address
// #define SLAVE_ADDR 9

// // Define Slave answer size
// #define ANSWERSIZE 5

// char message[32];
// void setup()
// {
//   // put your setup code here, to run once:
//   Wire.begin(SLAVE_ADDR);

//   // Function to run when data received from master
//   Wire.onReceive(receiveEvent);

//   // Setup Serial Monitor
//   Serial.begin(9600);
// }

// void loop()
// {
//   // put your main code here, to run repeatedly:
// }

// // method to read the message if there is available
// void receiveEvent()
// {

//   // Read while data received
//   int index = 0;

//   while (Wire.available())
//   {
//     message[x] = Wire.read(); // read message on wire
//     index++;
//   }
//   store_toSD();
//   memset(message, 0, sizeof(message)); // clear message var
// }

// void store_toSD()
// {
//   // put your main code here, to run repeatedly:

//   // Serial.readBytes(text, 32);
//   // Serial.println(text);

//   // while (!Serial) {
//   //   ; // wait for serial port to connect. Needed for native USB port only
//   // }
//   if (!SD.begin(10))
//   {
//     Serial.println("initialization failed!");
//     while (1)
//       ;
//   }
//   Serial.println("initialization done.");
//   // open the file. note that only one file can be open at a time,
//   // so you have to close this one before opening another.
//   myFile = SD.open("energyData.txt", FILE_WRITE);
//   // if the file opened okay, write to it:
//   if (myFile)
//   {
//     myFile.println(message);

//     // close the file:
//     myFile.close();
//     //    Serial.println("done.");
//     // readingSD();
//   }
//   else
//   {
//     // if the file didn't open, print an error:
//     Serial.println("error opening test.txt");
//   }
// }
