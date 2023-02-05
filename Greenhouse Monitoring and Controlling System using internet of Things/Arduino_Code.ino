/////////////////////////////////////////////////////////////////////////
//               Visvesvaraya Technological University                 //
//                         Main Project on                             //
//      "Greenhouse Monitoring and Controlling System using IoT"       //
//                                                                     //
//                             Done by                                 //
//                                                                     //
//                             D  G  M                                 //                 
//                             Student                                 //      
//       Department of Electronics and Communication Engineering       //
//                RajaRajeswari College of Engineeering                //
/////////////////////////////////////////////////////////////////////////

#include "DHT.h"
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>

const int DHTPIN1 = 14;
const int soilpin = 34;
const int ldrpin = 35;
const int relaypin1 = 32;//pump
const int relaypin2 = 33;//fan
const int relaypin3 = 23;//LED

#define FIREBASE_HOST "greenhousemonitoring-74379-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "VgytycWVgQpAsefHGP9o1aSWLziN6wmY5o1rxONo"
#define WIFI_SSID "Wireless Network" // input your home or public wifi name
#define WIFI_PASSWORD "123456789"

#define DHTTYPE DHT11
DHT dht1(DHTPIN1, DHTTYPE);

float h1, t1;
boolean stato;
String fireStatus;

void setup()
{
  Serial.begin(115200);
  delay(100);
  Serial.println("Welcome to");
  Serial.println("*******************************************************************");
  Serial.println("*              Visvesvaraya Technological University              *");
  Serial.println("*                         Main Project on                         *");
  Serial.println("*         'Greenhouse Monitoring and Controlling using IoT'       *");
  Serial.println("*                             Done by                             *");
  Serial.println("*                            D   G   M                            *");
  Serial.println("*                           Stduent of                            *");
  Serial.println("*      Department of Electronics and Communication Engineering    *");
  Serial.println("*                RajaRajeswari College of Engineering             *");
  Serial.println("*******************************************************************");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  delay(200);
  Serial.println();
  Serial.print("Connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  dht1.begin();
  pinMode(ldrpin, INPUT);
  pinMode(relaypin1, OUTPUT);
  pinMode(relaypin2, OUTPUT);
  pinMode(relaypin3, OUTPUT);
}

void temp()
{
  h1 = dht1.readHumidity();

  t1 = dht1.readTemperature();

  if (isnan(h1) || isnan(t1)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // print the result to Terminal
  Serial.print("Humidity1: ");
  Serial.print(h1);
  Serial.print("%\t");
  Firebase.setFloat("Humidity", h1);
  Serial.print("Temperature1: ");
  Serial.print(t1);
  Serial.println(" *C ");
  Firebase.setFloat("Temperature", t1);
  delay(1000);

  if (t1 > 25)
  {
    fanon();
  }
}

void fanon()
{
  digitalWrite(relaypin2, HIGH);
}

void fanoff()
{
  digitalWrite(relaypin2, LOW);
}

void soilread()
{
  float soilval = analogRead(soilpin);
  Serial.print("Moisture Value: ");
  Serial.println(soilval);
  Firebase.setFloat("Moisture", soilval);
  delay(500);
  if (soilval >= 2500)
  {
    pumpon();
  }
}

void pumpon()
{
  digitalWrite(relaypin1, HIGH);
}

void ldrread()
{
  stato = digitalRead(ldrpin);
  Firebase.setFloat("LDR", stato);
  if (stato == HIGH)
  {
    Serial.println("Light LOW");
    lighton();
  }
  else
  {
    Serial.println("Light HIGH");
    lightoff();
  }
}

void lighton()
{
  digitalWrite(relaypin3, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
}

void lightoff()
{
  digitalWrite(relaypin3, LOW);    // turn the LED off by making the voltage LOW
  delay(200);
}

void readfirebase() {
  fireStatus = Firebase.getString("STATUS");     // get ld status input from firebase
  Serial.println(fireStatus);
  if (fireStatus == "1")
  {
    pumpoff();
    delay(500);
  }
  else if (fireStatus == "2")
  {
    pumpon();
    delay(500);
  }
  else if (fireStatus == "3")
  {
    fanoff();
    delay(500);
  }
  else if (fireStatus == "4")
  {
    fanon();
    delay(500);
  }
  else if (fireStatus == "5")
  {
    lightoff();                        
    delay(500);
  }
  else if (fireStatus == "6")
  {
    lighton();
    delay(500);
  }
  else if (fireStatus == "0")
  {
    temp();
    soilread();
    ldrread();
    delay(500);
  }
  else
  {
    Serial.println("Wrong Credential!.");
  }
}

void loop()
{
  readfirebase();
}

// Note: Webpage is incomplete. Reason: Initially thought of using an Webpage to monitor and control the devices but then moved to an android application for better user experience, I have attached all these file as reference, anyone can built on top of it and make it functional.
// Android application is developed using MIT Appinventor and Google Firebase acting as a database server.
