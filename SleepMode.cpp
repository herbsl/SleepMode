
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

void _SleepMode::powerDown(uint32_t ms, adc_t adc, bod_t bod) {
    period_t period;

    ms = (ms << 10) / 1000;

    if (_beforeCallback != 0) {
        _beforeCallback();
    }

    if (ms == -1) {
        LowPower.powerDown(SLEEP_FOREVER, adc, bod);
    }
    else {
        while (ms > 0) {
            period = getPeriod(&ms);
            LowPower.powerDown(period, adc, bod);
        }
    }

    if (_afterCallback != 0) {
        _afterCallback();
    }
}

period_t _SleepMode::getPeriod(uint32_t *ms) {
    uint16_t sleep;

    if (*ms <= 16) {
        *ms = 0;
        return SLEEP_15MS;
    }

    for (uint8_t i = 9; i >= 0; --i) {
        if (*ms >= sleep) {
            *ms -= sleep;

            return (period_t)i;
        }
     }
}

_SleepMode SleepMode;
