#include <MicSensor.hpp>

MicSensor::MicSensor()
    : Sensor( MIC_MIN_REFRESH_LAPSE, MIC_MAX_REFRESH_LAPSE ) {}

MicSensor::MicSensor( uint8_t pin )
    : Sensor( MIC_MIN_REFRESH_LAPSE, MIC_MAX_REFRESH_LAPSE ) {
        __pin = pin;
        pinMode( __pin, INPUT );
}

float MicSensor::update_value() {
    this->__last_value = analogRead( __pin );
    return this->__last_value;
}

float MicSensor::get_intensity() {
    update_value();
    return this->__last_value;
}