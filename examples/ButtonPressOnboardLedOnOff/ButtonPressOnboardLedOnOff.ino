#include <Arduino.h>
#include <Button.h>

#define GPIO_BUTTON 12                 // GPIO pin the button is connected to 
#define MS_TIMEOUT_DEBOUNCE 100.       // delay in ms between software button presses
#define MS_TIMEOUT_DEPRESS 100.        // time in ms the button must be depressed to register a software press
#define BUTTON_TRIGGER_STATE_LOW LOW   // the state the pin is in when the button is pressed

/* state variable(s) */
bool isLedOn = false;

/* create an instance of the button */
Button btn = Button(
    GPIO_BUTTON, // the GPIO pin that reads the button state
    MS_TIMEOUT_DEBOUNCE,
    MS_TIMEOUT_DEPRESS,
    BUTTON_TRIGGER_STATE_LOW
);

void setup() {
    // setup GPIO pins 
    pinMode(GPIO_BUTTON, INPUT_PULLUP); //
    pinMode(LED_BUILTIN, OUTPUT);

    // turn the onboard LED "off" to begin
    digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  if (btn.isPressed()) { // run `isPressed` on each loop to execute button timers
    // toggle LED state
    isLedOn = !isLedOn;
    // write state to the LED GPIO pin
    digitalWrite(LED_BUILTIN, isLedOn);
  }
}