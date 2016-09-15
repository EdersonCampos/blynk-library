/**************************************************************
 * This is a DEMO. You can use it only for development and testing.
 *
 * If you would like to add these features to your product,
 * please contact Blynk for Business:
 *
 *                    http://tiny.cc/BlynkB2B
 *
 **************************************************************/

volatile bool     g_buttonPressed = false;
volatile uint32_t g_buttonPressTime = -1;

void button_action(void)
{
  config_reset();
}

void button_change(void)
{
#if !(BOARD_BUTTON_ACTIVE_HIGH == true)
  g_buttonPressed = !digitalRead(BOARD_BUTTON_PIN);
#else
  g_buttonPressed = digitalRead(BOARD_BUTTON_PIN);
#endif

  if (g_buttonPressed) {
    DEBUG_PRINT("Hold the button to reset configuration...");
    g_buttonPressTime = millis();
  } else {
    uint32_t buttonHoldTime = millis() - g_buttonPressTime;
    if (buttonHoldTime >= BUTTON_HOLD_TIME_ACTION) {
      button_action();
    }
    g_buttonPressTime = -1;
  }
}

void button_init()
{
#if !(BOARD_BUTTON_ACTIVE_HIGH == true)
  pinMode(BOARD_BUTTON_PIN, INPUT_PULLUP);
#else
  pinMode(BOARD_BUTTON_PIN, INPUT);
#endif
  attachInterrupt(BOARD_BUTTON_PIN, button_change, CHANGE);
}

