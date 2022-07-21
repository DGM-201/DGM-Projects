//You can use any text editor to code and save it in whichever extension you want e.g .py,.txt,.c,.html,.css,.js etc but the encoding format should be UTF-8 
//Main Code which controls the NodeMCU and its interfaced Sensors

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SFE_BMP180.h>
#include <Wire.h>
 
#include "Webpage.h" //Our HTML webpage contents with javascripts, Note: it should be named as "Webpage.h"
#include "DHTesp.h" //DHT11 Library for ESP
 
#define LED 2 //On board LED
#define DHTpin 14 //D5 of NodeMCU is GPIO14
#define ALTITUDE 1655.0 // Altitude in meters
 
SFE_BMP180 pressure; 
DHTesp dht;
 
//SSID and Password of your WiFi router
const char* ssid = "BMECSRDGMKTJ";
const char* password = "BMECSRDGMKTJ";
 
ESP8266WebServer server(80); //Server on port 80
 
void handleRoot() {
String s = MAIN_page; //Read HTML contents
server.send(200, "text/html", s); //Send web page
}
 
float humidity, temperature;
 
void handleADC() {
char status;
double T,P,p0,a;
double Tdeg, Tfar, phg, pmb;
 
status = pressure.startTemperature();
if (status != 0)
{
// Wait for the measurement to complete:
delay(status);
status = pressure.getTemperature(T);
if (status != 0)
{
// Print out the measurement:
Serial.print("Temperature: ");
Serial.print(T,2);
Tdeg = T;
Serial.print(" deg C, ");
Tfar = (9.0/5.0)*T+32.0;
Serial.print((9.0/5.0)*T+32.0,2);
Serial.println(" deg F");
 
status = pressure.startPressure(3);
if (status != 0)
{
// Wait for the measurement to complete:
delay(status);
status = pressure.getPressure(P,T);
if (status != 0)
{
// Print out the measurement:
Serial.print("Absolute Pressure: ");
Serial.print(P,2);
pmb = P;
Serial.print(" mb, ");
phg = P*0.0295333727;
Serial.print(P*0.0295333727,2);
Serial.println(" in Hg(Mercury)");
 
p0 = pressure.sealevel(P,ALTITUDE); // we're at 1655 meters (Boulder, CO)
Serial.print("Relative (Sea-Level) Pressure: ");
Serial.print(p0,2);
Serial.print(" mb, ");
Serial.print(p0*0.0295333727,2);
Serial.println(" in Hg");
 
a = pressure.altitude(P,p0);
Serial.print("Computed Altitude: ");
Serial.print(a,0);
Serial.print(" meters, ");
Serial.print(a*3.28084,0);
Serial.println(" feet");
}
else Serial.println("Error while retrieving pressure measurement\n");
}
else Serial.println("Error when starting pressure measurement\n");
}
else Serial.println("Error while retrieving temperature measurement\n");
}
else Serial.println("Error when starting temperature measurement\n");
 
 
int Rain = analogRead(A0);
char* rain;
{
if(Rain<300){
  rain = "Heavy Rain";
 }
 else if(Rain<512){
  rain = "Moderate Rain";
 }
 else{
  rain = "No Rain";
 }
}
 
//Create JSON data
String data = "{\"Rain\":\""+String(rain)+"\",\"Pressuremb\":\""+String(pmb)+"\",\"Pressurehg\":\""+String(phg)+"\", \"Temperature\":\""+ String(temperature) +"\", \"Humidity\":\""+ String(humidity) +"\"}";
 
digitalWrite(LED,!digitalRead(LED)); //Toggle LED on data request ajax
server.send(200, "text/plane", data); //Send ADC value, temperature and humidity JSON to client ajax request
 
delay(dht.getMinimumSamplingPeriod());
 
humidity = dht.getHumidity();
temperature = dht.getTemperature();
 
Serial.print("Humidity:");
Serial.println(humidity);
Serial.print("Temperature:");
Serial.println(temperature); //dht.toFahrenheit(temperature));
Serial.print("Rain:");
Serial.println(rain);
}
 
void setup()
{
Serial.begin(115200);
Serial.println();
 
// dht11 Sensor
 
dht.setup(DHTpin, DHTesp::DHT11); //for DHT11 Connect DHT sensor to GPIO 17
pinMode(LED,OUTPUT);
 
//BMP180 Sensor
if (pressure.begin())
Serial.println("BMP180 init success");
else
{
Serial.println("BMP180 init fail\n\n");
while(1); // Pause forever.
}
 
WiFi.begin(ssid, password); //Connect to your WiFi router
Serial.println("");
 
// Wait for connection
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
 
//If connection successful show IP address in serial monitor
Serial.println("");
Serial.print("Connected to ");
Serial.println(ssid);
Serial.print("IP address: ");
Serial.println(WiFi.localIP()); //IP address assigned to your ESP
 
server.on("/", handleRoot); //Which routine to handle at root location. This is display page
server.on("/readADC", handleADC); //This page is called by java Script AJAX
 
server.begin(); //Start server
Serial.println("HTTP Server Started");
}
 
void loop()
{
server.handleClient(); //Handle client requests
}