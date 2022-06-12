#ifndef NEMA23_h
#define NEMA23_h

#include "Arduino.h"

class NEMA23
{
    public:
        NEMA23(int step, int dir);
        void controller(void);
        String getInstr(void);
        void setInstr(void);

    
    private:
        void setStep(void);
        void initialPosition(int L, int R);
        //output pin
        int pin_dir;
        int pin_step;

        //variable
        char bluetooth_val;
        char state;
        
        int _toLeft;
        int _toRight; 
};
#endif
