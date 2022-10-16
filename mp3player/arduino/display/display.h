#ifndef DISPLAY_H
#define DISPLAY_H

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#include "freeserif.h"
#include "splash.h"
#include <Adafruit_SSD1306.h>
#include <Wire.h>

static inline float lerp(float from, float to, float weight) { return from + (to - from) * weight; }

namespace OLED {

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

inline void print(const String s) { oled.print(s); }
inline void println(const String s) { oled.println(s); }
inline void clear() { oled.clearDisplay(); }
inline void flush() { oled.display(); }

// Adafruit_GFX::drawBitmap(..., size_x, size_y). adds multiplication factors
void draw_bitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint8_t size_x,
                 uint8_t size_y) {
  int16_t i, j, byteWidth = (w + 7) / 8;

  for (j = 0; j < h; j++)
    for (i = 0; i < w; i++)
      if (pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7))) {
        if (size_x == 0 && size_y == 0)
          oled.drawPixel(x + i, y + j, color);
        else
          oled.drawRect(x + i * size_x, y + j * size_y, size_x, size_y, color);
      }
}

#define SPLASH_SCALE 2
#define SPLASH_BOTTOM (SCREEN_HEIGHT - SPLASH_SIZE) * (SPLASH_SCALE * SPLASH_SCALE)
#define SPLASH_MIDDLE SCREEN_WIDTH / SPLASH_SCALE - SPLASH_SIZE

void show_splash() {
  for (unsigned int c = 0; c < 2; c++) {
    for (unsigned int i = 0; i < 9; i++) {
      clear();
      const int16_t y_pos = lerp(SPLASH_BOTTOM, 0 - (SPLASH_SIZE * SPLASH_SCALE) - 30, (i + 1) / 10.);
      const int16_t x_pos = (rand() % 10 - 5) + SPLASH_MIDDLE;
      draw_bitmap(x_pos, y_pos, ships[i], SPLASH_SIZE, SPLASH_SIZE, WHITE, SPLASH_SCALE, SPLASH_SCALE);
      flush();
      delay(20);
    }
    delay(40);
  }
}

// boot oled
void begin() {
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.clearDisplay();
  oled.setFont(&FreeSerif9pt7b);
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 15);
  show_splash();
}

} // namespace OLED
#endif