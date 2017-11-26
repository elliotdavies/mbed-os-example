#include "mbed.h"
#include "LCD_DISCO_F429ZI.h"
#include "TS_DISCO_F429ZI.h"

// Screen
LCD_DISCO_F429ZI lcd;
TS_DISCO_F429ZI ts;

// Send messages to PC for debugging
Serial pc(USBTX, USBRX);

InterruptIn userButton(USER_BUTTON);

DigitalOut led1(LED1);
DigitalOut led2(LED2);

#define buttonPressed 1

int flashLights = 0;
uint32_t backColor = LCD_COLOR_BLUE;

void setBackColor(uint32_t color) {
  lcd.Clear(color);
  lcd.SetBackColor(color);
  backColor = color;
}

void onUserButtonPress() {
  // Toggle flash
  flashLights = !flashLights;

  // Toggle back color
  if (backColor == LCD_COLOR_BLUE) {
    setBackColor(LCD_COLOR_RED);
  } else {
    setBackColor(LCD_COLOR_BLUE);
  }
}

int main() {
  // Turn LEDs off by default
  led1 = 0;
  led2 = 0;

  // Attach handler to button 'rise' event
  userButton.rise(&onUserButtonPress);

  // Default background
  setBackColor(LCD_COLOR_BLUE);

  // Set up variables for touchscreen
  TS_StateTypeDef TS_State;
  uint16_t x, y;
  uint8_t text[30];
  uint8_t status;

  // Get touchscreen size
  status = ts.Init(lcd.GetXSize(), lcd.GetYSize());

  while (1) {
    if (flashLights) {
      led1 = 1;
      wait(0.1);
      led2 = 1;
      wait(0.1);
      led1 = 0;
      wait(0.1);
      led2 = 0;
      wait(0.1);
    } else {
      led1 = 0;
      led2 = 0;
    }

    // Print out x,y coords when touchscreen is touched
    ts.GetState(&TS_State);
    if (TS_State.TouchDetected)
    {
      x = TS_State.X;
      y = TS_State.Y;
      sprintf((char*)text, "x=%d y=%d    ", x, y);
      lcd.DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);
    }
  }
}
