#include "Button.h"
#include <Arduino.h>

/* constructor */
Button::Button(
  uint8_t _pin,
  uint16_t _timeoutDebounce,
  uint16_t _timeoutDepressed,
  boolean _triggeredState
) {
  /* assign vars */
  pin = _pin;
  timeoutDebounce = _timeoutDebounce;
  timeoutDepressed = _timeoutDepressed;
  triggeredState = _triggeredState;

  /** Add the timeout period to the last pressed timestamp.
   * This prevents the button from being locked out on start */
  timeLastTriggered = millis() + timeoutDebounce;
}

boolean Button::isTimeoutExpired() {
  return (millis() - timeLastTriggered >= timeoutDebounce);
}

boolean Button::isPressed() {
  /* check if the timeout has passed */
  if (!isTimeoutExpired()) {
    /* timeout hasn't expired */
    return false;
  }

  /* timeout is expired, check button state */
  if (digitalRead(pin) != triggeredState) {
    /* button isn't in the triggered state */
    return false;
  }

  /* timeout expired and button in triggered state */
  
  /* record when the pin trigger was detected */
  unsigned long timePinTriggered = millis();

  /* hold logic while the pin is being triggered */
  /* verify the pin was held in a triggered state long enough */
  while (digitalRead(pin) == triggeredState && (millis() - timePinTriggered) < timeoutDepressed) {
    /* check if the pin stopped being triggered */
    if (digitalRead(pin) != triggeredState) {
      /* pin stop being triggered too soon */
      return false;
    }
  }

  /* timeout has expired, button was triggered long enough */
  
  /* record the latest triggered time */
  timeLastTriggered = millis();

  /* register the press */
  return true;
}