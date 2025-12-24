/* 创建一个简单的 slider示例
    * lvgl官方示例：
    *  - 在线文档: https://docs.lvgl.io/master/examples.html
    *  - 源码: https://github.com/lvgl/lvgl/tree/master/examples
*/

#include <TFT_display.h>

static lv_obj_t * label;
lv_obj_t * slider;
static int32_t slider_value = 30;

static void slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target_obj(e);
     Serial.println("hello");
    // lv_slider_set_value(slider, slider_value, LV_ANIM_OFF);
    // /*刷新slider进度文本值*/
    // lv_label_set_text_fmt(label, "%" LV_PRId32, lv_slider_get_value(slider));
    // lv_obj_align_to(label, slider, LV_ALIGN_OUT_TOP_MID, 0, -10);    /*slider 进度文本值始终在slider上部中间*/
}

void setup()
{
    Serial.begin(115200);
    TFT_display_init();

    /*屏幕上创建一个slider控件*/
    lv_obj_t * slider = lv_slider_create(lv_screen_active());
    lv_obj_set_width(slider, 200);                          /*设置宽度*/
    lv_obj_center(slider);                                  /*置于屏幕中间*/
    lv_slider_set_value(slider, slider_value, LV_ANIM_OFF); // 设置滑块初始值
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);     /*设置slider值改变时回调函数*/

    /*在slider上面创建一个显示进度的文本*/
    label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "30");
    lv_obj_align_to(label, slider, LV_ALIGN_OUT_TOP_MID, 0, -10);    /*文本居slider上部中间*/

    lv_obj_send_event(slider, LV_EVENT_VALUE_CHANGED, NULL);

}

void loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    delay(10); /* let this time pass */
}
