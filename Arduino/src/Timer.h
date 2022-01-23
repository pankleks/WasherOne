#include <Pin.h>
#include <TM1637Display.h>

TM1637Display display(CLK_PIN, DIO_PIN);

class Timer
{
    int _lastDumpT = -1;
    int _left;
    int _target;
    bool _started = false;

    void dump(int t)
    {
        if (_lastDumpT == t)
            return;

        display.showNumberDecEx(t / 60, 0b01000000, false, 2, 0);
        display.showNumberDec(t % 60, true, 2, 2);
        _lastDumpT = t;
    }

public:
    int getTarget()
    {
        return _target;
    }

    void increaseTarget()
    {
        if (_target < 60 * 10)
            _target += 60 * 2;
        else if (_target < 60 * 30)
            _target += 60 * 5;
        else
            _target += 60 * 10;

        if (_target > 60 * MAX_T)
            _target = 60 * 2;

        dump(_target);
    }

    void extend()
    {
        if (_started)
        {
            _left += 60 * 5;
            if (_left > 60 * MAX_T)
                _left = 60 * MAX_T;
            dump(_left);
        }
    }

    void reset(int target)
    {
        _target = target > 60 * 2 && (target % 60 == 0) ? target : 60 * 2;
        _started = false;
        dump(_target);
    }

    void start()
    {
        _left = _target;
        _started = true;
        dump(_target);
    }

    void tick()
    {
        if (_started)
        {
            _left -= 1;
            dump(_left);
        }
    }

    bool hasElapsed()
    {
        if (_left == 0)
        {
            _started = false;
            return true;
        }
        return false;
    }
};