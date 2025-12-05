/* A B按键使用示例
*/
#include <OneButton.h>

#define PIN_BUTTON_A P5
#define PIN_BUTTON_B P11

OneButton button_A(PIN_BUTTON_A);
OneButton button_B(PIN_BUTTON_B);

static void Clicked(void *param){
  OneButton *button = (OneButton *)param;
  if(button->pin() == PIN_BUTTON_A){
    Serial.println("Button A clicked.");
  }else if(button->pin() == PIN_BUTTON_B){
    Serial.println("Button B clicked.");
  }
}


void setup()
{
    Serial.begin(115200);

    /*设置按键点击回调函数*/
    button_A.attachClick(Clicked, &button_A);
    button_B.attachClick(Clicked, &button_B);
}

void loop()
{
    button_A.tick();
    button_B.tick();

    delay(10); /* let this time pass */
}
