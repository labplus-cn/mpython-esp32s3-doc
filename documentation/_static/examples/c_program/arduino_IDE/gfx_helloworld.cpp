#include <Arduino.h>
#include "TFT_display.h"

image_fb_t fb;

void setup() {
  fb.buf = (uint8_t *)heap_caps_calloc(1, (320 * 172) * sizeof(uint16_t), MALLOC_CAP_8BIT | MALLOC_CAP_SPIRAM);
  fb.width = 320;
  fb.height = 172;
  fb.format = PIXFORMAT_RGB565;
  fb.len = (320 * 172) * sizeof(uint16_t);

  fb_gfx_fillRect(&fb, 10, 10, 300, 160, GUI_Green);
  fb_gfx_print(&fb, 20, 20, GUI_Red, "hello, world.");
  fb_gfx_drawFastHLine(&fb, 11, 111, 100, GUI_Blue);
  

  lcd_init();
  // lcd_draw_logo();
  lcd_show(fb.buf);
}

void loop() {
  // put your main code here, to run repeatedly:
}
