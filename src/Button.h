#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

/* A class for debouncing a button. */
class Button {
  private:
  /* private vars */
  uint8_t pin;
  uint16_t timeoutDebounce;
  uint16_t timeoutDepressed;
  boolean triggeredState;
  unsigned long timeLastTriggered = 0;

  /* private methods */
  boolean isTimeoutExpired();

  public:
  /* public methods */
  Button(
    uint8_t _pin,
    uint16_t _timeoutDebounce,
    uint16_t _timeoutDepressed,
    boolean _triggeredState
  );
  void begin();
  boolean isPressed();
};

#endif
