#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int sensorPin = 2;

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED nu merge");
    for(;;);
  }

  display.clearDisplay();
}

void loop() {
  int value = analogRead(sensorPin);
  Serial.println(value);

  int percent = map(value, 1200, 1800, 100, 0);
  percent = constrain(percent, 0, 100);

  display.clearDisplay();
  display.setTextColor(WHITE);

  // 🔶 BARA SUS (zona galbena)
  int barWidth = map(percent, 0, 100, 0, 128);

  // contur bara
  display.drawRect(0, 0, 128, 12, WHITE);

  // umplere bara
  display.fillRect(0, 0, barWidth, 12, WHITE);

  // 🔵 MESAJ JOS
  display.setCursor(0, 30);

  if (percent < 40) {
    display.setTextSize(2);
    display.println("INTUNERIC!");
  } 
  else if (percent < 60) {
    display.setTextSize(2);
    display.println("SLAB");
  } 
  else if (percent < 80) {
    display.setTextSize(2);
    display.println("OK");
  } 
  else {
    display.setTextSize(2);
    display.println("FOARTE BUN");
  }

  display.display();
  delay(300);
}
