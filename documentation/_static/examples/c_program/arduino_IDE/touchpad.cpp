#include <Arduino.h>
#include <driver/touch_pad.h>
#include <esp32-hal-touch.h>

bool p_touched = false;
bool y_touched = false;
bool t_touched = false;
bool h_touched = false;
bool o_touched = false;
bool n_touched = false;
void gotTouch_p(){
  p_touched = true;
}
void gotTouch_y(){
  y_touched = true;
}
void gotTouch_t(){
  t_touched = true;
}
void gotTouch_h(){
  h_touched = true;
}
void gotTouch_o(){
  o_touched = true;
}
void gotTouch_n(){
  n_touched = true;
}
void setup() {
  delay(1000);
  Serial.begin(9600);
  touchAttachInterrupt(P, gotTouch_p, 4500);
  touchAttachInterrupt(Y, gotTouch_y, 4500);
  touchAttachInterrupt(T, gotTouch_t, 4500);
  touchAttachInterrupt(H, gotTouch_h, 4500);
  touchAttachInterrupt(O, gotTouch_o, 4500);
  touchAttachInterrupt(N, gotTouch_n, 4500);
}
void loop() {
  // Serial.println(touchRead(9)); 
  if(p_touched){
    Serial.println("pad P touched.");
    p_touched = false;
  }
  if(y_touched){
    Serial.println("pad Y touched.");
    y_touched = false;
  }
  if(t_touched){
    Serial.println("pad T touched.");
    t_touched = false;
  }
  if(h_touched){
    Serial.println("pad H touched.");
    h_touched = false;
  }
  if(o_touched){
    Serial.println("pad O touched.");
    o_touched = false;
  }
  if(n_touched){
    Serial.println("pad N touched.");
    n_touched = false;
  }
  delay(200);
}
