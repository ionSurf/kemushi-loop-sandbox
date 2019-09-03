#ifndef MicSensor_hpp
#define MicSensor_hpp
#endif

#include <Arduino.h>

#ifndef Sensor_hpp
#include <Sensor.hpp>
#endif

#define MIC_MIN_REFRESH_LAPSE 10
#define MIC_MAX_REFRESH_LAPSE -1

class MicSensor : public Sensor {
public:
    MicSensor();
    MicSensor( uint8_t );

    float   update_value();
    float   get_intensity();
    void    print_value();
private:    
    uint8_t __pin;

    float __last_value;
};