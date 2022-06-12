#include "Arduino.h"
#include "NEMA23.h"

NEMA23::NEMA23 (int step, int dir)
{
    pinMode(step, OUTPUT);
    pinMode(dir, OUTPUT);

    this->pin_dir = dir;
    this->pin_step = step;

    this->bluetooth_val = 'S';

    this->state = 'S';

    this->_toLeft = 0;
    this->_toRight = 0;
}


void NEMA23::setInstr(void)
{
    if(Serial.available() > 0)
    {
      bluetooth_val = Serial.read();
    }
    
}

String NEMA23::getInstr(void)
{
    return String(bluetooth_val) + " " + String(bluetooth_val);
}

void NEMA23::controller(void)
{
    if(state == 'S' && state == 'S')
    {
        if(bluetooth_val == 'L' || bluetooth_val == 'G' || bluetooth_val == 'J')
        {
            digitalWrite(pin_dir, LOW);
            setStep();
            _toLeft++;
        }
        else if(bluetooth_val == 'R' || bluetooth_val == 'I' || bluetooth_val == 'H')
        {
            digitalWrite(pin_dir, HIGH);
            NEMA23::setStep();
            _toRight++;
        }
    }
    else if(state == 'L' || state == 'G' || state == 'J')
    {
        if(bluetooth_val == 'L' || bluetooth_val == 'G' || bluetooth_val == 'J')
        {
            if(_toLeft < 5)
            {
                digitalWrite(pin_dir, LOW);
                NEMA23::setStep();
                _toLeft++;
            }
        }
        else if(bluetooth_val == 'S')
        {
            digitalWrite(pin_dir, HIGH);
            NEMA23::initialPosition(_toLeft, _toRight);
            _toLeft = 0;
        }
    }
    else if(state == 'R' || state == 'I' || state == 'H')
    {
        if(bluetooth_val == 'R' || bluetooth_val == 'I' || bluetooth_val == 'H')
        {
            if(_toRight < 5)
            {
                digitalWrite(pin_dir, HIGH);
                setStep();
                _toRight++;
            }
        }
        else if(bluetooth_val == 'S')
        {
            digitalWrite(pin_dir, LOW);
            initialPosition(_toLeft, _toRight);
            _toRight = 0;
        }
    }
    state = bluetooth_val;
    delay(1);
}

void NEMA23::setStep(void)
{
    for(int i=0; i<10; i++)
    {
        digitalWrite(pin_step, HIGH);
        delay(1);
        digitalWrite(pin_step, LOW);
        delay(1);
    }
    delay(200);
}

void NEMA23::initialPosition(int L, int R)
{
    int x = max(L, R);
    for(int i=0; i<(x*10); i++)
    {
        digitalWrite(pin_step, HIGH);
        delay(1);
        digitalWrite(pin_step, LOW);
        delay(1);
    }
}
