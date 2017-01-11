#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 3
#define BUTTON_PIN 4
#define LEDNUM 24
#define DELAY   50
#define MAX_MODES 2

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LEDNUM, PIN, NEO_GRB + NEO_KHZ400);

int buttonState = 0; // g = 0 p = 1 y = 2
int ledPrint = 0;

void setup() {
  pixels.begin();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  int pressed = digitalRead(BUTTON_PIN);
  if (pressed == LOW) {
    ledPrint = 0;
    if (buttonState < MAX_MODES) {
      buttonState++;
    }
    else {
      buttonState = 0;
    }
  }

  if (ledPrint == 0) {
    for (int j=0; j < 256; j++) {
      for (int q=0; q < 3; q++) {
        for (int i=0; i < pixels.numPixels(); i = i+3) {
          if (buttonState == 0) {
            pixels.setPixelColor(i+q, 0, 255, 0);
          }
          if (buttonState == 1) {
            pixels.setPixelColor(i+q, 200, 0, 255);
          }
          if (buttonState == 2) {
            pixels.setPixelColor(i+q, 200, 255, 100);
          }
          /* if (buttonState == 3) { */
          /*   pixels.setPixelColor(i+q, Wheel( (i+j) % 255)); */
          /* } */
        }
      }
    }
    pixels.show();
    ledPrint = 1;
    delay(DELAY);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;

  if (WheelPos < 85) {
   return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }

  if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }

  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

