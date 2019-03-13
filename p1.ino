//ppm Parts Per Million also called milligrams per liter(mg/L)
//#include <DHT.h>  // Including library for dht
#include <ESP8266WiFi.h>
//*********Host calling password and Key*************
String apiKey = "5LT88P7AWUH52CYX"; 
const char *ssid = "Hotspot"; 
const char *pass = "1234567890";
const char* server = "api.thingspeak.com";
//#define DHTPIN 0         
//DHT dht(DHTPIN, DHT11);
WiFiClient client;
void setup() 
{

Serial.begin(115200);
delay(10);
Serial.println("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, pass);
while (WiFi.status() != WL_CONNECTED)
{
  delay(500);
  Serial.print(".");
}
  Serial.println("");
  Serial.println("WiFi connected");
}
void loop() {
    //float h = dht.readHumidity();
    //float t = dht.readTemperature();
    float m = analogRead(A0);

    if (isnan(m))
      {
        Serial.println("Failed to read from MQ-5 sensor!");
        return;
       }
 /*   if (isnan(h) || isnan(t)) 
      {
        Serial.println("Failed to read from DHT sensor!");
        return;
       }*/
      
         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
              {  
                   String postStr = apiKey;
                    postStr +="&field2=";
                    postStr += String(m);
                    /*postStr +="&field3=";
                    postStr += String(t);
                    postStr +="&field4=";
                    postStr += String(h);*/
                    postStr += "\r\n\r\n";
                   
                    client.print("POST /update HTTP/1.1\n");
                    client.print("Host: api.thingspeak.com\n");
                    client.print("Connection: close\n");
                    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                    client.print("Content-Type: application/x-www-form-urlencoded\n");
                    client.print("Content-Length: ");
                    client.print(postStr.length());
                    client.print("\n\n");
                    client.print(postStr);
                    Serial.print("AQI ");
                    Serial.print(m);
                    Serial.println(" Send to SSEC Server.");
 
                    /*Serial.print("Temperature: ");
                    Serial.print(t);
                    Serial.print(" degrees Celcius, Humidity: ");
                    Serial.print(h);*/
                    Serial.println("%. Send to Thingspeak.");          
                }
}
