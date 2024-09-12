# ARDUINO NON-BLOCKING BUTTON

A non-blocking button library for Arduino devices with de-bounce and easy configuration.

## What does "non-blocking" mean?

With regard to this button logic, "non-blocking" means the button library doesn't use
the commonly used `delay` function which suspends the Arduino execution loop.f

## QUICK-START

Here is a quick-start guide. Checkout the Arduino examples for more.

### Usage Example (Turning the Onboard LED on/off)

```
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
```

## Functionality

### Pressing the button registers software presses

When the button is depressed longer than the configured depress timeout, a software press
is registered and the `isPressed()` method returns `true`.

After the button has been pressed, subsequent software presses will not be registered until
the configured number of debounce milliseconds has passed.

Once the configured debounce milliseconds have passed, a subsequent software press can be registered.

### Holding down sends repeat button presses

This particular button library is configured to register repeat software button presses when the
button is held down.

## How does it work?

To perform timing and wait operations, instead of suspending the Arduino execution loop,
which prevents other logic from happening and may interfere with functionality, this
button logic captures timestamps using the `millis()` function and compares time passed
against configured timeouts values.

## STEP-BY-STEP

### Include the Arduino Library

Include the library at the top of your Arduino sketch or import the library using
Sketch->Manage Libraries->Include Libary

```
#include <Button.h>
```

### (optional) Add Configuration constants

This step is optional, but adding configuration constants makes it easy to setup
multiple buttons to with the same debounce and depress timeout values.

However, you can set the debounce and depress timeouts individually per button instance, as needed.

```
#define GPIO_BUTTON 12                 // GPIO pin the button is connected to
#define MS_TIMEOUT_DEBOUNCE 100.       // delay in ms between software button presses
#define MS_TIMEOUT_DEPRESS 100.        // time in ms the button must be depressed to register a software press
#define BUTTON_TRIGGER_STATE_LOW LOW   // the state the pin is in when the button is pressed
```

### Declare a Button instance

To use the `Button` library, you must create a new instance of `Button` that is globally scoped (NOT inside `setup` or `loop`);

**IMPORTANT:**
Placing your `Button` declaration inside of `setup` or `loop` will NOT work.

```
/* create an instance of the button (with constants) */
Button btn = Button(
    GPIO_BUTTON, // the GPIO pin that reads the button state
    MS_TIMEOUT_DEBOUNCE,
    MS_TIMEOUT_DEPRESS,
    BUTTON_TRIGGER_STATE_LOW
);
```

**OR**

```
/* create an instance of the button (without constants) */
Button btn = Button(
    12, // the GPIO pin that reads the button state
    150, // 150ms debounce time
    100, // 100ms depress time
    LOW // state the button is in when it's triggered
);
```
