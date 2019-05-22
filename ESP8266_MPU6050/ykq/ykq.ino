/*        原力小车遥控程序      
MPU6050           ESP8266
vin—————————vin
gnd—————————gnd
scl—————————D1
sda—————————D2
*/





#include <Wire.h>
#include <MPU6050.h>
#include <ESP8266WiFi.h>
const char* ssid = "Voyager";//←这里引号里面的是要链接的WiFi（这里改主程序也必须改成一样的(*^_^*)）
const char* host = "192.168.1.1";
String light_get;  

MPU6050 mpu;
int test=0;
int tesx=0;
void setup() 
{
  Serial.begin(115200);

  Serial.println("启动");
 delay(10);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("无法获取到数据");
    delay(500);
  }
}

void loop()
{
  Vector normAccel = mpu.readNormalizeAccel();
  int pitch = (atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
  int roll = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;

  
  if(pitch>30 && pitch<38){
      test=1;
      Serial.println("前进");
    
    }else if( pitch>4&&pitch<15){
      test=2;
        Serial.println("后退"); 
        
      }else if(roll>5&&roll<15){
        test=3;
          Serial.println("向左"); 
           
        }else if(roll<50&&roll>40){
          test=4;
            Serial.println("向右"); 
             
          }else{
            test=5;
            Serial.println("停止"); 
            }
  

 
light_get = "/opera?opera="+String(test);
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
    Serial.println("Cannot Request" + * host);
    return;
  }
    client.print(String("GET ") + light_get + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    while(client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }

   
    

/*
  // Output
  Serial.print(" 俯仰轴 = ");
  Serial.print(pitch);
  Serial.print(" 横滚轴 = ");
  Serial.print(roll);
  
  Serial.println();
*/
  delay(50);
}
