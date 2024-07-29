#define BLYNK_TEMPLATE_ID "TMPL3ShcgBWDO"
#define BLYNK_TEMPLATE_NAME "Weather Monitoring System"
#define BLYNK_AUTH_TOKEN "iVp-nSFei6xqrM5CP0rw5MrGBESY57GU"

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include<DHT_U.h>
#include<Adafruit_Sensor.h>
#include <SFE_BMP180.h>

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define rain A0
#define light D0

char ssid[] = "Ajinn"; //Enter your WIFI name
char pass[] = "ajincherian"; //Enter your WIFI password
char auth[] = "iVp-nSFei6xqrM5CP0rw5MrGBESY57GU"; //Enter your Auth token


DHT dht(D3, DHT11); //(DHT sensor pin,sensor type)
BlynkTimer timer;

//SFE_BMP180 bmp;
double T, P;
char status;

void setup() {
  Serial.begin(9600);
  //bmp.begin();
  pinMode(light, INPUT);

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  dht.begin();

  timer.setInterval(100L, DHT11sensor);
  timer.setInterval(100L, rainSensor);
  //timer.setInterval(100L, pressure);
  timer.setInterval(100L, LDRsensor);
}

void DHT11sensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
}

void rainSensor() {
  int value = analogRead(rain);
  value = map(value, 0, 1024, 0, 100);
  Blynk.virtualWrite(V2, value);
}

void LDRsensor() {
  bool value = digitalRead(light);
  if (value == 0) {
    WidgetLED LED(V4);
    LED.on();
  } else {
    WidgetLED LED(V4);
    LED.off();
  }
}

void loop() {
  Blynk.run();
  timer.run();
}