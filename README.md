# sentient
Code for Adam, the sentient robot

This Arduino code converts the incoming PWM servos signals from an RF receiver into other signals.

For example, it can change a servo value into stepper signals, or into different WS2812 LED colors.

The code uses pin 3 as INPUT and pin 10 as OUTPUT for driving the WS2812 RGB LED.

Connect one of the axis of the RF receiver to the Arduino: GND-GND(black), 5V-VIN(red), servo-pin3(orange). Note that this will actually power the RF receiver from the raw Arduino Vin (usually USB power)

Connect the WS2812 to the Arduino: DIN-pin10, GND-GND, 5V-Vcc (this will power the LED from the Arduino)
