#define SERVO_INPUT_PIN 3

#include <Adafruit_NeoPixel.h>
#define LED_PIN 10
Adafruit_NeoPixel pixels(1, LED_PIN, NEO_GRB + NEO_KHZ800);

#include <Stepper.h>
#define STEPS_PER_REVOLUTION 20
// initialize the stepper library on pins 8 through 11:
//Stepper myStepper(STEPS_PER_REVOLUTION, 8, 9, 10, 11);

void setup()
{
  //myStepper.setSpeed(2000);

  // initialize the serial port:
  Serial.begin(9600);
  pinMode(SERVO_INPUT_PIN, INPUT);
  
  pixels.begin(); // This initializes the NeoPixel library.
}

#define LED_OFF 0
#define LED_WHITE 1
#define LED_WHITE_BREATH 2
#define LED_RED 3
#define LED_RED_BLINK 4
#define LED_BLUE 5

static int state = 0;

void setState(int newState)
{
  switch (newState)
  {
  default:
    newState = LED_OFF;
    // fall through
  case LED_OFF:
    pixels.setPixelColor(0, pixels.Color(0,0,0));
    break;
  case LED_WHITE:
    pixels.setPixelColor(0, pixels.Color(255,255,255));
    break;
  case LED_WHITE_BREATH:
    //pixels.setPixelColor(0, pixels.Color(255,100,0));
    break;
  case LED_RED:
    pixels.setPixelColor(0, pixels.Color(255,0,0));
    break;
  case LED_RED_BLINK:
    //pixels.setPixelColor(0, pixels.Color(255,0,0));
    break;
  case LED_BLUE:
    pixels.setPixelColor(0, pixels.Color(0,0,255));
    break;
  }

  pixels.show();
  state = newState;
}

void update()
{
  if (state == LED_WHITE_BREATH)
  {
    static long last_millis = 0;
    static char d = 3;
    long m = millis();
    int w = (m - last_millis)>>2;
    if (d < 0) w = 255 - w;
    if (w<0) { w=-w; d=-d; last_millis = m; }
    else if (w>255) { w=510-w; d=-d; last_millis = m; }
    pixels.setPixelColor(0, pixels.Color(w,w,w));
    pixels.show();
  }
  else if (state == LED_RED_BLINK)
  {
    int r = (millis()&0x400)?255:0;
    pixels.setPixelColor(0, pixels.Color(r,0,0));
    pixels.show();    
  }
}

void loop()
{  
  // The servos pulses are 50Hz at different duty cycles,
  // ranging from ~1ms to ~2ms, 5% resp. 10% duty cycle.
  int i = pulseIn(SERVO_INPUT_PIN, LOW, 20000);
  Serial.println(i);

  static int previous = 1000;
  
  //myStepper.step((i - previous)*1.5f);
  if (previous < 1300 && i > 1700)
    setState(state + 1);
        
  update();
    
  previous = i;
}

