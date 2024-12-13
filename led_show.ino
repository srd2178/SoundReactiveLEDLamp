#include <Adafruit_NeoPixel.h>

#define MIC_PIN 2  
#define LED_PIN 17  
#define NUM_LEDS 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);

  strip.begin();
  strip.show(); 

  pinMode(MIC_PIN, INPUT);
}

void loop() {
  // Reads sound level from microphone
  int soundLevel = analogRead(MIC_PIN);
  Serial.println(soundLevel);

  // Map the sound level to a range of hues (went with violet)
  uint16_t hue = map(soundLevel, 0, 2800, 43690, 54613);

  // Map the sound level to a range of brightness
  uint8_t brightness = map(soundLevel, 0, 2800, 5, 255); 

  // Set brightness for each LED using hue and dynamically calculated brightness
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.ColorHSV(hue, 255, brightness)); 
  }
  strip.show();

  delay(100);
}
