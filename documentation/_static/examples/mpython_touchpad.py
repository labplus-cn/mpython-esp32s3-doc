from mpython import *

def on_touchpad_p_pressed(_):
    print('p')

touchpad_p.event_pressed = on_touchpad_p_pressed

def on_touchpad_y_pressed(_):
    print('y')

touchpad_y.event_pressed = on_touchpad_y_pressed

def on_touchpad_t_pressed(_):
    print('t')

touchpad_t.event_pressed = on_touchpad_t_pressed

def on_touchpad_h_pressed(_):
    print('h')

touchpad_h.event_pressed = on_touchpad_h_pressed

def on_touchpad_n_pressed(_):
    print('n')

touchpad_n.event_pressed = on_touchpad_n_pressed

def on_touchpad_o_pressed(_):
    print('o')

touchpad_o.event_pressed = on_touchpad_o_pressed
