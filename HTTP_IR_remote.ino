#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <IRremoteESP8266.h>
#include <IRsend.h>

IRsend IRsender(4);
ESP8266WebServer server(80);

//=============================================
//                Server setup
//=============================================
void connectToWifi(){
  WiFi.begin("AgapeDaKing","kormoRan");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("Connecting to WiFi network...");
    }
  Serial.println("Server IP address: ");
  Serial.print(WiFi.localIP());
} 

void rootPath(){
  server.send(200, "text/plain", "Hello világ!");
  
}
//=============================================
//                IR raw datas
//=============================================
uint16_t Hitachi_Power[71] = {8944, 4444,  576, 1644,  576, 1644,  568, 1652,  568, 566,  544, 568,  542, 566,  544, 566,  544, 1648,  572, 1648,  574, 562,  548, 1646,  576, 560,  550, 560,  540, 570,  540, 1652,  570, 566,  544, 1650,  572, 1648,  574, 1646,  574, 562,  548, 1644,  576, 560,  550, 560,  540, 568,  542, 568,  544, 566,  542, 566,  544, 1650,  572, 566,  544, 1648,  574, 1646,  574, 1646,  576, 40918,  8940, 2212,  576};
uint16_t Epson_Power[135] = {9036, 4472,  602, 1658,  606, 1652,  600, 532,  600, 530,  600, 530,  600, 532,  600, 530,  602, 1658,  606, 1654,  610, 522,  610, 1650,  604, 528,  604, 1656,  608, 524,  608, 1650,  602, 530,  602, 528,  604, 528,  602, 530,  602, 528,  604, 1656,  606, 524,  608, 524,  608, 1652,  602, 1656,  608, 1652,  602, 1658,  604, 1654,  608, 524,  608, 1650,  604, 1656,  608, 524,  606, 40958,  9036, 4470,  602, 1656,  608, 1652,  600, 530,  600, 530,  600, 530,  602, 528,  602, 528,  602, 1656,  608, 1652,  602, 530,  602, 1656,  608, 524,  606, 1652,  600, 530,  600, 1658,  606, 526,  606, 526,  606, 526,  606, 526,  606, 526,  606, 1652,  600, 530,  600, 530,  600, 1660,  604, 1654,  610, 1650,  604, 1656,  606, 1652,  600, 532,  600, 1660,  604, 1654,  608, 524,  608}; 
//=============================================
//                IR Commands
//=============================================
void IR_Toggle(int projectorID){
  switch(projectorID){
    case 0:
      IRsender.sendRaw(Hitachi_Power, 71, 38);
      Serial.println("Hitachi powering on/off");
        break;
    case 1:
      IRsender.sendRaw(Epson_Power, 135, 38);
      Serial.println("Epson powering on/off");
        break;
    default:
        break;
    }
}





void setup() {
  Serial.begin(9600);
  connectToWifi();
  server.on("/",rootPath);
  server.begin();
  IRsender.begin();
}

void loop() {
   server.handleClient();
   char input = Serial.read();
   switch(input){
    case 'a':
        IR_Toggle(0);
        Serial.println("Hitachi");
        break;
    case 'b':
        IR_Toggle(1);
        Serial.println("Epson");
        break;
    default:
        break;
    }
}
