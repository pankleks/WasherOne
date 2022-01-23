#define STEP_PIN 2
#define DIR_PIN 3
#define ENABLE_PIN 7
#define TIME_PIN 5
#define STOP_PIN 4
#define MODE_PIN 6
#define LOW_STEP_PIN 8
#define CLK_PIN 10
#define DIO_PIN 9
#define MOSFET_PIN 11 // only 3, 5, 6, 9, 10, 11 support pwm

#ifndef MODE_PINS
#define MODE_PINS
const byte MODE_LED_PIN[] = {A1, A2, A3};
#endif

#define MAX_T 90

#define MOTOR_ACC_MS 6000

#define WASH_SLOW_N 150   // motor min speed
#define WASH_FAST_N 30    // motor max speed
#define WASH_ONE_DIR_S 30 // seconds between direction change

#define DRY_N 1000       // motor speed at drying
#define DRY_FAN_SPEED 50 // dry fan speed %

#define CURE_N 1000        // motor speed at curing
#define CURE_LED_POWER 100 // cure led power %

#if STEP_PIN > 7
#error "Step pin should be D0 to D7"
#endif
