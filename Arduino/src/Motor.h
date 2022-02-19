#include <Arduino.h>
#include <Pin.h>

class Motor
{
    int _target;
    float _delta;
    int _accT; // in ms
    bool _dir = false;

public:
    float current;
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
        digitalWrite(STEP_MODE_PIN[0], true);        
        digitalWrite(STEP_MODE_PIN[1], lowStep);        
        digitalWrite(STEP_MODE_PIN[2], lowStep);       

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
