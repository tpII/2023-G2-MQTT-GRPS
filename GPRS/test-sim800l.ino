#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(1000);
  updateSerial();
  mySerial.println("AT+SAPBR=3,1,\"APN\",\"internet\"");
  delay(1000);
  updateSerial();
  mySerial.println("AT+SAPBR=1,1");
  delay(5000);
  updateSerial();
  mySerial.println("AT+SAPBR=2,1");
  delay(2000);
  updateSerial();
  mySerial.println("AT+HTTPINIT");
  delay(1000);
  updateSerial();
  mySerial.println("AT+HTTPPARA=\"CID\",1");
  delay(1000);
  updateSerial();
  mySerial.println("AT+HTTPPARA=\"URL\",\"http://jsonplaceholder.typicode.com/posts/1\"");  // Reemplaza con tu URL
  delay(1000);
  updateSerial();
  mySerial.println("AT+HTTPACTION=0");
  delay(15000);  // Espera más tiempo si es necesario
  updateSerial();
  mySerial.println("AT+HTTPREAD");
  delay(10000);
  updateSerial();
  mySerial.println("AT+HTTPTERM");
  delay(1000);
  updateSerial();
  mySerial.println("AT+SAPBR=0,1");
  delay(1000);
  updateSerial();
}

void loop()
{
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
