#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

#define NEOPIXEL_PIN 2
#define NUM_LEDS 1
#define SHAKE_PIN   4
#define SHAKE_THRESHOLD 512
#define OFF 0
#define ON  1

CRGB leds[NUM_LEDS];
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, NEOPIXEL_PIN, NEO_GRBW + NEO_KHZ800);

bool state = 0;
uint8_t gHue = 0;
uint8_t gHueDelta = 3;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(SHAKE_PIN, INPUT);
  randomSeed(analogRead(1));
  FastLED.addLeds<NEOPIXEL, NEOPIXEL_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(0);
  FastLED.show();
  Serial.begin(9600); 
  delay(30);
}

// the loop function runs over and over again forever
void loop() {
  switch(state) {
    case OFF:
      if (digitalRead(SHAKE_PIN)) {
        Serial.println("Activating LED!");
        state = ON;
      }
      delay(200);
      break;
    case ON:
      leds[0].setHue(random(256));
      for(int i = 0; i < 255; i++ ) {
        FastLED.setBrightness(i);
        FastLED.show();
        delay(5);
      }
      for(int i = 0; i < 255; i++ ) {
        FastLED.setBrightness(255-i);
        FastLED.show();
        delay(5);
      }
      leds[0] = CRGB::Black; 
      FastLED.show();
      state = OFF;
      break;
  }    
}
