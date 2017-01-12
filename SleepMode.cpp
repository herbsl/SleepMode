
#include "SleepMode.h"

_SleepMode::_SleepMode() {
    _beforeCallback = 0;
    _afterCallback = 0;
};

_SleepMode::~_SleepMode() {};

void _SleepMode::before(callback_t callback) {
    _beforeCallback = callback;
}

void _SleepMode::after(callback_t callback) {
    _afterCallback = callback;
}

void _SleepMode::powerDown(uint32_t sleepTime, adc_t adc, bod_t bod) {
    period_t period;

    // align sleepTime
    _sleepTime = (sleepTime << 10) / 1000;

    if (_beforeCallback != 0) {
        _beforeCallback();
    }

    if (_sleepTime == -1) {
        LowPower.powerDown(SLEEP_FOREVER, adc, bod);
    }
    else {
        while (_sleepTime > 0) {
            period = getPeriod();
            LowPower.powerDown(period, adc, bod);
        }
    }

    if (_afterCallback != 0) {
        _afterCallback();
    }
}

period_t _SleepMode::getPeriod() {
    uint16_t periodSleepTime;

    if (_sleepTime <= 16) {
        _sleepTime = 0;

        return SLEEP_15MS;
    }

    for (uint8_t i = 9; i >= 0; --i) {
        periodSleepTime = 16 << i;

        if (_sleepTime >= periodSleepTime) {
            _sleepTime -= periodSleepTime;
          
            return (period_t)i;
        }
     }
}

_SleepMode SleepMode;
