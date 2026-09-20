#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int PITOT_PIN = 34;
const int MOSFET_PIN = 25;

void setup() {
  Serial.begin(115200);
  pinMode(MOSFET_PIN, OUTPUT);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {
  int rawADC = analogRead(PITOT_PIN);
  float voltage = (rawADC / 4095.0) * 3.3;
  
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Wind Tunnel Telemetry");
  display.setCursor(0, 20);
  display.printf("Raw ADC: %d\n", rawADC);
  display.printf("Voltage: %.2f V\n", voltage);
  display.display();

  analogWrite(MOSFET_PIN, 128); // 50% PWM test signal
  delay(100);
}