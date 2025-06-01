/*
  Author : "leogad"
  email: "hakizimanaleogad@gmail.com"
*/
#include<DHT.h>
#include<LiquidCrystal_I2C.h>
#include<FirebaseESP8266.h>
#include<DIYables_IRcontroller.h>
#include<ESP8266WiFi.h>
#define url ""
#define TOKEN "" 
LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht(11,11);// you can use own  base on your choice
String wifi ="EdNet";// can be modified
String pass ="Hauwei@123";
FirebaseAuth auth;
FirebaseData data;
FirebaseConfig config;
int led =13;
DIYables_IRcontroller_17 ir(12,200);
void setup(){
  lcd.init();
  Serial.begin(96000);
  WiFi.begin(wifi,pass);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
  }
  Serial.print("Wifi connected");
  config.host=url;
  config.signer.tokens.legacy_token=TOKEN;
  Firebase.begin(&config, &auth);
  ir.begin();
  pinMode(led,OUTPUT);
  dht.begin();
  lcd.print("Smart Home");
}
void loop(){
   Key17 key=ir.getKey();
  internet();
 if(key!=Key17::NONE){
  switch(key){
     case Key17::KEY_OK:
     bool value = (key==Key17::KEY_OK)?1:0;
     digitalWrite(led,value);
     break;
  }
 }
 lcd.print("Temp:");
 lcd.print(dht.readTemperature());
 lcd.print("c");
 lcd.print("Hum:");
 lcd.print(dht.readHumidity());
 lcd.print("%");
 delay(1000);
 lcd.clear();
}
void internet(){
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
