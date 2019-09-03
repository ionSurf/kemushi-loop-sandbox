#include <SR04.hpp>

SR04::SR04() : Sensor() {
    this->__mode = MILIMETERS;
    this->__last_value = 0;

    this->__threshold_val = 0;
    this->__is_above_threshold = false;
};

SR04::SR04( uint8_t t_pin, uint8_t e_pin ) : Sensor() {
    this->__e_pin = e_pin;
    this->__t_pin = t_pin;

    this->__mode = MILIMETERS;

    pinMode( __t_pin, OUTPUT );
    pinMode( __e_pin, INPUT );

    this->__last_value = 0;

    this->__threshold_val = 0;
    this->__is_above_threshold = false;
}

void    SR04::set_mode( usnd_mode_t mode ) {
    this->__mode = mode;
}

float   SR04::get_last_value() {
    return this->__last_value;
}

float   SR04::update_value() {
    long    duration = 0;
    float   distance = 0;

    #ifdef ESP32
        // ESP32 is a multi core / multi processing chip
        // It is necessary to disable task switches during the readings
        portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
        portENTER_CRITICAL(&mux);
    #else
        cli();
    #endif

    // Clears the trigPin
    digitalWrite(__t_pin, LOW);
    delayMicroseconds(2);
    //  Set trigger to high
    digitalWrite( __t_pin, HIGH );
    //  Wait 10 microseconds
    delayMicroseconds( USND_MU_DELAY );
    //  Set trigger to low
    digitalWrite( __t_pin, LOW );
    //  Read echo value
    //duration = analogRead( __e_pin );
    duration = pulseIn(__e_pin, HIGH);

    #ifdef ESP32
        portEXIT_CRITICAL(&mux);
    #else
        sei();
    #endif

    //  Convert value to distance
    switch ( __mode ) {
    case MILIMETERS:
        distance = duration*0.34/2;
        break;
    case CENTIMETERS:
        distance = duration*0.034/2;
        break;
    case METERS:
        distance = duration*0.0034/2;
        break;
    case INCHES:
        distance = duration*0.034/5.08;
        break;
    }

    //float new_th = distance - this->__last_value;
    //if ( new_th < 0 ) new_th *= -1;

    /*Serial.print( " high th val:  " + String(this->__last_value + this->__threshold_val) );
    Serial.print( " low th val:  " + String(this->__last_value - this->__threshold_val) );
    Serial.println( " distance:  " + String( distance ) );*/
    if ( abs( distance - this->__last_value ) > 100 || abs( distance + this->__last_value ) < 100 ) {
        this->__is_above_threshold = true;
        //Serial.println("threshold!");
    }

    this->__last_value = distance;
    
    //  Return value
    return distance;
}
float   SR04::get_dist() {
    return this->update_value();
}

void    SR04::set_threshold( uint32_t t ) {
    this->__threshold_val = t;
}
void    SR04::reset_threshold() {
    this->__is_above_threshold = false;
}
bool    SR04::is_above_theshold() {
    return this->__is_above_threshold;
}