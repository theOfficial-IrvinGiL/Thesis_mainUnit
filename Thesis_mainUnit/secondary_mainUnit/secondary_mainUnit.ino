
#include <SD.h>
char text[32];
File myFile;

//sample

void store_toSD() {
  // put your main code here, to run repeatedly:

  Serial.readBytes(text, 32);
  Serial.println(text);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  if (!SD.begin(10)) {
    // Serial.println("initialization failed!");
    while (1);
  }
  // Serial.println("initialization done.");
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("bayotka.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    myFile.println(text);

    // close the file:
    myFile.close();
    // Serial.println("done.");
 
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SD.begin(10);

  
}

void loop() {
  if (Serial.available())
  {
    store_toSD();
    Serial.flush(); // flushes/empty the contents of the serial buffer 
  }
}
