#include "LM35.hpp"


LM35::LM35( short pin ) {
    this->__pin = pin;
    this->__min_refresh_lapse = 1000;
    pinMode( pin, OUTPUT );

    this->__mode = CELSIUS;
}

void LM35::set_mode( temp_mode_t mode ) {
    this->__mode = mode;
}

float LM35::update_value() {
    this->__last_value = 0;
    switch( __mode ) {
        case CELSIUS: 
            //return (float(analogRead( __pin ))*5/(1023))/0.01;
            this->__last_value = (analogRead(__pin)/ 2048.0) * 3300 * 0.1 - 14;
            break;
        case FARENHEIT:
            //return (((float(analogRead( __pin ))*5/(1023))/0.01)*1.8)+32;
            this->__last_value = ((analogRead(__pin)/ 2048.0) * 3300 * 0.1 - 14)*1.8 + 32;
            break;
        case KELVIN:
            //return ((float(analogRead( __pin ))*5/(1023))/0.01)+273;
            this->__last_value = ((analogRead(__pin)/ 2048.0) * 3300 * 0.1 - 14)*.001;
            break;
    }
    return __last_value;
}

float LM35::get_temp() {
    //RawValue = analogRead(analogIn);
    //Voltage = (RawValue / 2048.0) * 3300; // 5000 to get millivots.
    //tempC = Voltage * 0.1;

    return this->__last_value;
}