#include "HardwarePlatform.h"

/* ======================================================= */
void HardwarePlatform::initIO() {
}

void HardwarePlatform::initSPI() {
}

void HardwarePlatform::csn(uint8_t value) {
}

void HardwarePlatform::ce(uint8_t value) {
}

uint8_t HardwarePlatform::spiTransfer(uint8_t tx_) {
	return 0;
}

void HardwarePlatform::delayMicroseconds(uint64_t micros) {
}

void HardwarePlatform::delayMilliseconds(uint64_t milisec) {
}
