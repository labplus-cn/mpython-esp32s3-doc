/* 创建一个简单的 label示例
    * lvgl官方示例：
    *  - 在线文档: https://docs.lvgl.io/master/examples.html
    *  - 源码: https://github.com/lvgl/lvgl/tree/master/examples
*/

#include <TFT_display.h>

void setup()
{
    Serial.begin( 115200 );
    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
    Serial.println( LVGL_Arduino );

    TFT_display_init();

    lv_obj_t *label = lv_label_create( lv_screen_active() );
    lv_label_set_text( label, "Hello Arduino, I'm LVGL!" );
    lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );
}

void loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    delay(5); /* let this time pass */
}
