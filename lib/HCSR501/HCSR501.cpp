#include <HCSR501.hpp>

HCSR501::HCSR501() : Sensor() { }

HCSR501::HCSR501( uint8_t pin ) : Sensor( PIRI_MIN_REFRESH_LAPSE, PIRI_MAX_REFRESH_LAPSE ) {
    this->__pin = pin;
    pinMode(__pin, INPUT_PULLUP);
}

void HCSR501::update_value() {
    this->__last_value = ( digitalRead( __pin ) == HIGH ) ? true : false;
}

bool HCSR501::has_presence() {
    this->__last_value = ( digitalRead( __pin ) == HIGH ) ? true : false;
    return __last_value;
}

void HCSR501::print_value() {
    String piri_output = "PIR presence is: ";

    Serial.print( piri_output);
  ( this->has_presence() ) ? Serial.println( "true" ) : Serial.println( "false" );
}