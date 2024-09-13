# ARDUINO NON-BLOCKING BUTTON

A non-blocking button library for Arduino devices with de-bounce and easy configuration,
that does **NOT** use `delay` function which suspends the Arduino execution loop.

## API REFERENCE

### `Button` - constructor

#### Description

Used to construct a new instance of the `Button`.

#### Syntax

```
Button btn = Button(
    pin,
    timeoutDebounce,
    timeoutDepressed,
    triggeredState
);
```

#### Parameters

|          Parameter | Description                                                                 |
| -----------------: | --------------------------------------------------------------------------- |
|              `pin` | the GPIO pin the hardware button is connected to.                           |
|  `timeoutDebounce` | debounce delay time in ms between software presses.                         |
| `timeoutDepressed` | time in ms the hardware button must be pressed to trigger a software press. |
|   `triggeredState` | state the GPIO pin is in when the hardware button is depressed.             |

### `isPressed()` - instance method, returns `boolean`

#### Description

Returns `true` when a software button press has been detected.

To register a software button press,
the hardware button must be depressed for `timeoutDepressed` milliseconds.

When the hardware button is held down continuously, software button presses will be detected
with `timeoutDebounce` milliseconds wait time in between software button presses.

**Important:** - the `isPressed()` method _must_ be run frequently to detect hardware presses,
for best results, run `isPressed()` on every loop.

## Examples

### Usage Example (Turning the onboard LED on an Arduino UNO on/off)

```
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
