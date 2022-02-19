#define STEP_PIN 8  // A4988 step
#define STEP_PORT PORTB // see which PORT register is controlling STEP_PIN
#define STEP_PORT_BIT 0 // see which bit in PORT register is controlling STEP_PIN

#define DIR_PIN 7   // A4988 dir
#define ENABLE_PIN 12   // A4988 enable

#define MODE_BUTTON_PIN 5
#define TIME_BUTTON_PIN A5
#define STOP_BUTTON_PIN A4

#ifndef STEP_MODE_PINS
#define STEP_MODE_PINS
const byte STEP_MODE_PIN[] = {11, 10, 9};
#endif

#define CLK_PIN A3  // lcd display CLK
#define DIO_PIN A2  // lcd display DIO
#define MOSFET_PIN 6 // only 3, 5, 6, 9, 10, 11 support pwm

#ifndef MODE_PINS
#define MODE_PINS
const byte MODE_LED_PIN[] = {2, 3, 4};  // these are the micro-step control pins of A4988
#endif

#define MAX_T 90 * 60 // max time in sec.
#define MIN_T 2 * 60  // min time in sec.

#define MOTOR_ACC_MS 5000   // motor should accelerate to target speed within this time (ms)

// wash works at half-step
#define WASH_SLOW_N 150   // motor min speed
#define WASH_FAST_N 30    // motor max speed
#define WASH_ONE_DIR_S 30 // seconds between direction change

// dry and cure works at sixteenth step
#define DRY_N 1000       // motor speed at drying
#define DRY_FAN_SPEED 50 // dry fan speed %

#define CURE_N 1000        // motor speed at curing
#define CURE_LED_POWER 100 // cure led power %
