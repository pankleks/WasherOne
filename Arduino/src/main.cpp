// author: pankleks
// https://github.com/pankleks
// v1

#include <Arduino.h>
#include <Pin.h> // <-- all config settings are here
#include <EventLoop.h>
#include <Timer.h>
#include <Motor.h>

EVENT_LOOP;

Motor motor(MOTOR_ACC_MS);
Timer timer;

int taskId;
int mode; // 10 - wash setup, 11 - wash run, 20 - dry setup, 21 - dry run, 30 - cure setup, 31 - cure run

void setMode(int v)
{
  mode = v;

  int led = (mode / 10) - 1;
  for (int i = 0; i < 3; i++)
    digitalWrite(MODE_LED_PIN[i], i == led);
}

ISR(TIMER1_COMPA_vect)
{
  PORTD |= (1 << STEP_PIN);  // high
  PORTD &= ~(1 << STEP_PIN); // low
  OCR1A = motor.current;
}

void setMosfetPower(int percent)
{
  analogWrite(MOSFET_PIN, map(percent, 0, 100, 0, 255));
}

// wash
int washPhase;
int washCount;

void washSetup()
{
  setMode(10);
  timer.reset();
}

void washStop()
{
  elp.kill(taskId);
  motor.off();

  washSetup();
}

void washStart()
{
  setMode(11);

  motor.on(false, WASH_SLOW_N);
  motor.setTarget(WASH_FAST_N);

  washPhase = 0;
  timer.start();

  taskId = elp.interval(
      [](int count)
      {
        switch (washPhase)
        {
        case 0: // speeding up
          if (motor.atTarget)
            washPhase = 1;
          washCount = WASH_ONE_DIR_S;
          break;
        case 1: // const. high speed
          if (--washCount == 0)
          {
            washPhase = 2;
            motor.setTarget(WASH_SLOW_N);
          }
          break;
        case 2: // slowing down
          if (motor.atTarget)
          {
            washPhase = 0;
            motor.reverse(); // reverse dir and speed up
            motor.setTarget(WASH_FAST_N);
          }
          break;
        case 3:
          if (motor.atTarget)
            washStop(); // when slowed down -> stop
          break;
        }

        if (washPhase != 3 && timer.hasElapsed())
        {
          washPhase = 3;
          motor.setTarget(WASH_SLOW_N); // slow down before stop
        }
      },
      1000, true);
}

// dry
void drySetup()
{
  setMode(20);
  timer.reset();
}

void dryStop()
{
  setMosfetPower(0);

  elp.kill(taskId);
  motor.off();

  drySetup();
}

void dryStart()
{
  setMode(21);

  setMosfetPower(DRY_FAN_SPEED);

  motor.on(true, DRY_N);
  timer.start();

  taskId = elp.always(
      []()
      {
        if (timer.hasElapsed())
          dryStop();
      });
}

// cure
void cureSetup()
{
  setMode(30);
  timer.reset();
}

void cureStop()
{
  setMosfetPower(0);

  elp.kill(taskId);
  motor.off();

  cureSetup();
}

void cureStart()
{
  setMode(31);

  setMosfetPower(CURE_LED_POWER);

  motor.on(true, CURE_N);
  timer.start();

  taskId = elp.always(
      []()
      {
        if (timer.hasElapsed())
          cureStop();
      });
}

void setup()
{
  Serial.begin(9600);

  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(LOW_STEP_PIN, OUTPUT);
  pinMode(TIME_PIN, INPUT_PULLUP);
  pinMode(STOP_PIN, INPUT_PULLUP);
  pinMode(MODE_PIN, INPUT_PULLUP);
  pinMode(MOSFET_PIN, OUTPUT);

  display.setBrightness(6);

  // setup timer 1
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1 << CS12);  // prescalar = 256
  TCCR1B |= (1 << WGM12); // reset timer after match
  TCNT1 = 0;
  interrupts();

  elp.interval(
      [](int count)
      { motor.tick(); },
      100);

  elp.interval(
      [](int count)
      { timer.tick(); },
      1000);

  elp.pushButton(
      []()
      {
        switch (mode)
        {
        case 10:
        case 20:
        case 30:
          timer.increaseTarget();
          break;
        default:
          timer.extend();
          break;
        }
      },
      TIME_PIN);

  elp.pushButton(
      []()
      {
        switch (mode)
        {
        case 10:
          washStart();
          break;
        case 11:
          washStop();
          break;
        case 20:
          dryStart();
          break;
        case 21:
          dryStop();
          break;
        case 30:
          cureStart();
          break;
        case 31:
          cureStop();
          break;
        }
      },
      STOP_PIN);

  elp.pushButton(
      []()
      {
        switch (mode)
        {
        case 10:
          drySetup();
          break;
        case 20:
          cureSetup();
          break;
        case 30:
          washSetup();
          break;
        }
      },
      MODE_PIN);

  motor.off();
  washSetup();
}