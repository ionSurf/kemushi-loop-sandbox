//
//  Sensors.hpp
//  Kemushi Loop Test
//
//  Created by Javier Prieto on 9/28/18.
//  Copyright © 2018 The Heartpitch Project. All rights reserved.
//

#ifndef Sensors_hpp
#define Sensors_hpp
#endif

#include "LM35.hpp"

typedef struct {
    LM35* temp_sensor;
} Sensors_t;

typedef struct {
    uint16_t tmp;
    uint16_t usd1;
    uint16_t usd2;
    uint16_t usd3;
    uint16_t pir;
    uint16_t mic;
} Sensors_data_t;

/*class Sensor {
private:
    uint16_t __min_refresh_lapse;
    uint16_t __max_refresh_lapse;
}*/

class Sensors {
public:
    Sensors();
    Sensors( LM35* );
    bool temperature_humidity_loop();
    bool ultrasonic_sensor_loop();

    bool loop();    // Main loop
private:
    Sensors_t __sensors;
    Sensors_data_t  __sensors_data;
};