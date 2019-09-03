#include <Arduino.h>

#ifndef Sensor_hpp
#include <Sensor.hpp>
#endif

#define PIRI_MIN_REFRESH_LAPSE 500
#define PIRI_MAX_REFRESH_LAPSE -1

class HCSR501 : public Sensor {
public:
    HCSR501();
    HCSR501( uint8_t );

    void update_value();
    bool has_presence();

    void print_value();
private:
    uint8_t __pin;
    bool    __last_value;
};