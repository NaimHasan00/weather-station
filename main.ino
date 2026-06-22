// hello. It's a test and simple Weather Station project made by Naim Hasan. Thanks for watching!
#include <U8g2lib.h>
#include <Wire.h>
#include <DHT.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastRead = 0;
const unsigned long interval = 120000;

float temp = 0;
float hum = 0;

void drawScreen() {
  char tempStr[10];
  char humStr[10];

  dtostrf(temp, 2, 0, tempStr);
  dtostrf(hum, 2, 0, humStr);
  strcat(tempStr, "C");
  strcat(humStr, "%");

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_logisoso24_tf);

  String mainText = String(tempStr) + " " + String(humStr);

  int w = u8g2.getUTF8Width(mainText.c_str());
  int x = (128 - w) / 2;

  u8g2.drawUTF8(x, 40, mainText.c_str());
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(32,50,"Naim Hasan");

  u8g2.sendBuffer();
}

void setup() {
  u8g2.begin();
  dht.begin();

  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(20, 30, "Starting...");
  u8g2.sendBuffer();

  delay(2000);
}

void loop() {
  unsigned long now = millis();

  if (now - lastRead >= interval || lastRead == 0) {
    lastRead = now;

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      temp = -1;
      hum = -1;
    } else {
      temp = t;
      hum = h;
    }

    drawScreen();
  }
}
