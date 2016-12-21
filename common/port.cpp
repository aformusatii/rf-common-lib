#include "Port.h"

void Port::setAsInput() {
    _in(_pin, *_dir_reg);
}

void Port::setAsOutput() {
    _out(_pin, *_dir_reg);
}

void Port::on() {
    _on(_pin, *_port_reg);
}

void Port::off() {
    _off(_pin, *_port_reg);
}

void Port::set(bool v) {
    if (v) {
        _on(_pin, *_port_reg);
    } else {
        _off(_pin, *_port_reg);
    }
}
