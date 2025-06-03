#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <FirebaseESP8266.h>
#include <DIYables_IRcontroller.h>
#include <ESP8266WiFi.h>

#define url "https://dht11-9aca0-default-rtdb.firebaseio.com"
#define TOKEN "I5fAerwYcyQrGqZ5x4JzA2v8QPQ0f2lQwXYBbJl2"
#define DHTPIN 11
#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);
DIYables_IRcontroller_17 ir(12, 200);

const char* ssid = "EdNet";
const char* password = "Hauwei@123";

FirebaseAuth auth;
FirebaseData data;
FirebaseConfig config;

int led = 13;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("WiFi connected");

  config.database_url = url;
  config.signer.tokens.legacy_token = TOKEN;
  Firebase.begin(&config, &auth);

  ir.begin();
  pinMode(led, OUTPUT);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.print("ꄣSmart Home");
  lcd.setCursor(0, 1);
  lcd.print(" Automation ꄣ");
  delay(3000);
  lcd.clear();
}

void loop() {
  Key17 key = ir.getKey();
  remmote(key);
  interNet();
  displayOff();
}

void remmote(Key17 key) {
  if (key != Key17::NONE) {
    switch (key) {
      case Key17::KEY_OK:
        digitalWrite(led, HIGH);
        break;
      default:
        break;
    }
  }
}

void displayOff() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(hum);
  lcd.print("%");

  delay(2000);
  lcd.clear();
}

void interNet() {
  if (WiFi.status() == WL_CONNECTED) {
    if (Firebase.getString(data, "/status")) {
      String value = data.stringData();
      digitalWrite(led, value == "true" ? HIGH : LOW);
    }

    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    Firebase.setFloat(data, "/Temperature", temp);
    Firebase.setFloat(data, "/Humidity", hum);
  } else {
    Serial.println("Network disconnected");
  }

  delay(1000);
}
