#include <Arduino.h>
#include <Pin.h>

class Motor
{
    int _target;
    int _delta;
    int _accT; // in ms
    bool _dir = false;

public:
    int current;
    bool atTarget;

    Motor(int accT)
    {
        _accT = accT;
    }

    void setTarget(int n)
    {
        _target = n;
        _delta = (float)100 / _accT * abs(_target - current);
        atTarget = false;
    }

    // 100ms
    void tick()
    {
        if (current < _target)
        {
            current += _delta;
            if (current > _target)
                current = _target;
        }
        else if (current > _target)
        {
            current -= _delta;
            if (current < _target)
                current = _target;
        }
        else
            atTarget = true;
    }

    void on(bool lowStep, int target)
    {
        _dir = false;
        digitalWrite(ENABLE_PIN, false);
        digitalWrite(DIR_PIN, _dir);
        digitalWrite(LOW_STEP_PIN, lowStep);        

        current = _target = target;
        atTarget = true;   

        TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
        OCR1A = target;             
    }

    void reverse()
    {
        _dir = !_dir;
        digitalWrite(DIR_PIN, _dir);
    }

    void off()
    {
        digitalWrite(ENABLE_PIN, true);
        
        TIMSK1 &= ~(1 << OCIE1A);   // disable timer compare interrupt
    }
};
