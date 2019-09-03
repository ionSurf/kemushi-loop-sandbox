#include <Speaker.hpp>

Speaker::Speaker() {
    this->__in_use  = false;
    this->__vol     = 255;
}
Speaker::Speaker( uint8_t pin) {
    this->__in_use  = false;
    this->__pin     = pin;
    this->__vol     = 255;
}

void Speaker::set_pin( uint8_t pin ) {
    this->__pin = pin;
}
uint8_t     Speaker::get_pin( ) {
    return this->__pin;
}
void        Speaker::set_volume( uint16_t  vol) {
    this->__vol = vol;
}
uint16_t    Speaker::get_volume() {
    return this->__vol;
}
bool        Speaker::is_busy() {
    return this->__in_use;
}
bool        Speaker::play_tone() {
}
bool        Speaker::stop() {
}