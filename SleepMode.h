#ifndef _SLEEP_MODE_H
#define _SLEEP_MODE_H

#include <LowPower.h>
#include "Arduino.h"

typedef void (*callback_t)(void);

class _SleepMode {
    public:
        _SleepMode();
        ~_SleepMode();

        void before(callback_t callback);
        void after(callback_t callback);
        void powerDown(uint32_t sleepTime, adc_t adc = ADC_OFF, bod_t bod = BOD_OFF);

    private:
        period_t getPeriod();

        uint32_t _sleepTime;

        callback_t _beforeCallback; 
        callback_t _afterCallback; 
};

extern _SleepMode SleepMode;

#endif
