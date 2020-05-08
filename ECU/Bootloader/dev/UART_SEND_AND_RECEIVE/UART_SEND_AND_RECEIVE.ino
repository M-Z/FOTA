#include <SoftwareSerial.h>

SoftwareSerial Sim8001(2, 3); // RX, TX

static void sendCMND (char* cmnd) {
  Sim8001.write(cmnd);
  Sim8001.write("\r\n");
  while(Sim8001.available()== 0);
  Serial.write(Sim8001.read());
  Serial.write('\n');
}

void setup() {
  Serial.begin(9600);
  Sim8001.begin(9600);
  while (!Serial);
  while (!Sim8001);
  Serial.println("Started...");
  return;
  sendCMND("AT");
  sendCMND("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  sendCMND("AT+SAPBR=1,1");
  sendCMND("AT+HTTPINIT");
  sendCMND("AT+HTTPSSL=1");
  sendCMND("AT+HTTPPARA=\"CID\",1");
  sendCMND("AT+HTTPPARA=\"REDIR\",1");
  sendCMND("AT+HTTPPARA=\"URL\",\"fota2020.herokuapp.com/switchStatus\"");
  sendCMND("AT+HTTPACTION=0");
}

void loop() {

  if (Sim8001.available()) {
    Serial.write(Sim8001.read());
  }

  if (Serial.available()) {
    Sim8001.write(Serial.read());
  }
}
