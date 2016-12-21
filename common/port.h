#ifndef _PORT_H
#define _PORT_H

#include "util.h"

class Port {

    private:
        volatile uint8_t * _dir_reg;
        volatile uint8_t * _port_reg;
        uint8_t _pin;

    public:
        Port(volatile uint8_t * _dir_reg_v,
             volatile uint8_t * _port_reg_v,
             uint8_t _pin_v
                ) : _dir_reg(_dir_reg_v),
                    _port_reg(_port_reg_v),
                    _pin(_pin_v)
                    {}

        void setAsInput();
        void setAsOutput();
        void on();
        void off();
        void set(bool);
};

#endif
