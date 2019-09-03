#ifndef SR04_HPP
#define SR04_HPP
#endif

#include <Arduino.h>

#ifndef Sensor_hpp
#include <Sensor.hpp>
#endif

#define USND_MU_DELAY 10

typedef enum {
    MILIMETERS,
    CENTIMETERS,
    METERS,
    INCHES
} usnd_mode_t;

class SR04 : public Sensor {
public:
    SR04();
    SR04( uint8_t, uint8_t );

    void    set_mode( usnd_mode_t );
    float   get_last_value();
    float   update_value();
    float   get_dist();

    void    print_value();

    void    set_threshold( uint32_t );
    void    reset_threshold();
    bool    is_above_theshold();
    
private:
    usnd_mode_t __mode;
    uint8_t     __t_pin;
    uint8_t     __e_pin;

    float       __last_value;
    float       __threshold_val;
    bool        __is_above_threshold;
};