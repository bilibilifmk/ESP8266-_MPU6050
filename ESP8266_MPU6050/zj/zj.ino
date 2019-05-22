/*        原力小车主机程序      
L298N             ESP8266
in1—————————D5
in2—————————D6
in3—————————D7
in4—————————D8
vcc—————————12v
5v—————————vcc
GND—————————GND
*/


#include <FS.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
IPAddress apIP(192, 168, 1, 1);
ESP8266WebServer server (80);

void setup() {
  WiFi.softAP("Voyager");
  Serial.begin (115200);
  Serial.println("Loading...");  
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
 
  Serial.println(WiFi.localIP());
  server.begin();
  server.on("/",abc);
  server.on("/opera", opera);
pinMode(D5, OUTPUT);
pinMode(D6, OUTPUT);
pinMode(D7, OUTPUT);
pinMode(D8, OUTPUT);


  
}


void abc(){
  File file = SPIFFS.open("/index.html", "r");
server.streamFile(file, "text/html");
  file.close();
}

void opera() {
  String parm = server.arg("opera");
 
  Serial.println(parm);
  if(parm=="1"){
    digitalWrite(D5, HIGH); //in1 正
    digitalWrite(D6, LOW); //in2反
    
    digitalWrite(D7, HIGH); //in3 正
    digitalWrite(D8, LOW); //in3反
    
    }if(parm=="2"){
      digitalWrite(D5, LOW); //in1 正
    digitalWrite(D6, HIGH); //in2反
    
    digitalWrite(D7, LOW); //in3 正
    digitalWrite(D8, HIGH); //in3反
      }if(parm=="3"){
        digitalWrite(D5, HIGH); //in1 正
    digitalWrite(D6, LOW); //in2反
    
    digitalWrite(D7, LOW); //in3 正
    digitalWrite(D8, HIGH); //in3反
        }if(parm=="4"){
    digitalWrite(D5, LOW); //in1 正
    digitalWrite(D6, HIGH); //in2反
    
    digitalWrite(D7, HIGH); //in3 正
    digitalWrite(D8, LOW); //in3反
          }if(parm=="5"){
    digitalWrite(D5, LOW); //in1 正
    digitalWrite(D6, LOW); //in2反
    
    digitalWrite(D7, LOW); //in3 正
    digitalWrite(D8, LOW); //in3反
            }
  
  
 
server.send(200, "text/plain", "ok");
}

void loop() {
  server.handleClient();
      delay(10);
}
