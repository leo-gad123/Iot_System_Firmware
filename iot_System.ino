/*
Author : "leoGad"
project-Name: "Iot System Firmware"
Date: 30/05/2025
Email-Address:hakizimanaleogad@gmail.com
https://github.com/leo-gad123/Iot_System_Firmware  
*/
#include<DHT.h>
#include<LiquidCrystal_I2C.h>
#include<FirebaseESP8266.h>
#include<DIYables_IRcontroller.h>
#include<ESP8266WiFi.h>
#define url "leo.firebase"
#define TOKEN "" 
LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht(11,11);
String wifi ="EdNet";
String pass ="Hauwei@123";
FirebaseAuth auth;
FirebaseData data;
FirebaseConfig config;
int led =13;
DIYables_IRcontroller_17 ir(12,200);
void setup(){
 
  Serial.begin(96000);
  WiFi.begin(wifi,pass);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
  }
  Serial.print("Wifi connected");
  fireBaseInit();
  ir.begin();
  pinMode(led,OUTPUT);
  dht.begin();
  lcd.init();
  lcd.print("ꄣSmart Home Automationꄣ");
  delay(3000);
  lcd.clear();
}

void fireBaseInit(){
  config.host=url;
  config.signer.tokens.legacy_token=TOKEN;
  Firebase.begin(&config, &auth);
}

void loop(){
   Key17 key=ir.getKey();
  interNet();
 if(key!=Key17::NONE){
  switch(key){
     case Key17::KEY_OK:
     bool value = (key==Key17::KEY_OK)?1:0;
     digitalWrite(led,value);
     break;
  }
 }
displayOff();
}

void displayOff(){
 lcd.print("ꄣTemp:");
 lcd.print(dht.readTemperature());
 lcd.print("c");
 lcd.print("ꄣHum:");
 lcd.print(dht.readHumidity());
 lcd.print("%");
 delay(1000);
 lcd.clear();
}

void interNet(){
   while(WiFi.status() == WL_CONNECTED){
if(Firebase.getString(data,"/status")){
  String value=data.stringData();
  if(value=="true"){
  digitalWrite(led,1);
  }
  else{
    digitalWrite(led,0);
  }
}
else{
  Serial.print("data not recieved ???????");
}
if(Firebase.setFloat(data,"/Temperature: ",dht.readTemperature())){
  Serial.print("data sent successfully");
}
else{
  Serial.print("Error??????");
}
if(Firebase.setFloat(data,"/Humidity: ",dht.readHumidity())){
  Serial.print("data sent successfully");
}
else{
  Serial.print("Error 🼴🼴 🼴🼴🼴🼴 🼴🼴🼴 🼴🼴🼴");
}
 }
}
// Thank you for using this firmware
most requirement of loRa is Wifi
