#ifndef Sensor_hpp
#define Sensor_hpp
#endif

#include <Arduino.h>

class Sensor {
public: 
    Sensor();
    Sensor( uint16_t, uint16_t );
private:
    short unsigned int __min_refresh_lapse;
    short unsigned int __max_refresh_lapse;
};