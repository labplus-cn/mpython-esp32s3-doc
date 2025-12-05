/**
 * Brief	A library for controlling ws2812 in esp32 platform.
 * Author	ZhentaoLin
 * Url    https://github.com/Zhentao-Lin/ESP32_WS2812_Lib
 * Date		2024-09-02
 */
#include "ESP32_WS2812_Lib.h"

#define LEDS_COUNT 3
#define LEDS_PIN   P7
#define CHANNEL    0

ESP32_WS2812 strip = ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);

void setup() {
  strip.begin();
  strip.setBrightness(20);
}

void loop() {
  for (int j = 0; j < 255; j += 2) {
    for (int i = 0; i < strip.getLedCount(); i++) {
      strip.setLedColorData(i, strip.Wheel((i * 256 / strip.getLedCount() + j) & 255));
    }
    strip.show();
    delay(10);
  }
}