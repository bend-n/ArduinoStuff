#ifndef DISPLAY_H
#define DISPLAY_H

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#include "../math.h"
#include "freeserif.hpp"
#include "splash.hpp"
#include <Adafruit_SSD1306.h>
#include <Wire.h>
namespace OLED {

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

inline void print(const String s) { oled.print(s); }
inline void println(const String s) { oled.println(s); }
inline void clear() { oled.clearDisplay(); }
inline void flush() { oled.display(); }

// Adafruit_GFX::drawBitmap(..., size_x, size_y). adds multiplication factors
void draw_bitmap(const int8_t x, const int8_t y, const uint8_t *bitmap, const int8_t w, const int8_t h,
                 const uint16_t color, const uint8_t size_x, const uint8_t size_y) {
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

static constexpr uint8_t SPLASH_SCALE = 2;
static constexpr uint8_t SPLASH_BOTTOM = SCREEN_HEIGHT + (SPLASH_SIZE * SPLASH_SCALE);
static constexpr uint8_t SPLASH_MIDDLE = SCREEN_WIDTH / SPLASH_SCALE - SPLASH_SIZE;

static constexpr uint8_t splash_step = SPLASH_BOTTOM - lerp(SPLASH_BOTTOM, 0 - (SPLASH_SIZE * SPLASH_SCALE), 0.1);
static constexpr int8_t SPLASH_TOP = -splash_step - (SPLASH_SIZE * SPLASH_SCALE);

void show_splash() {
  int8_t x_pos = SPLASH_MIDDLE;
  for (uint8_t i = 0; i < 100; i++) {
    clear();
    const int8_t y_pos = lerp(SPLASH_BOTTOM, SPLASH_TOP, (i + 1) / 100.0);
    x_pos = clamp(x_pos + (rand() % 4 - 2), SPLASH_MIDDLE - 50, SPLASH_MIDDLE + 50);
    draw_bitmap(x_pos, y_pos, ships[wrapi(i, 0, 8)], SPLASH_SIZE, SPLASH_SIZE, WHITE, SPLASH_SCALE, SPLASH_SCALE);
    flush();
    delay(20);
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