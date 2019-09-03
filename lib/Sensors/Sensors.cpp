//
//  Sensors.cpp
//  Kemushi Loop Test
//
//  Created by Javier Prieto on 9/28/18.
//  Copyright © 2018 The Heartpitch Project. All rights reserved.
//

#include "Sensors.hpp"

Sensors::Sensors( ) { }

Sensors::Sensors( LM35* t_sensor ) {
    __sensors.temp_sensor = t_sensor;
}

bool Sensors::temperature_humidity_loop() {
    __sensors_data.temp = __sensors.temp_sensor.get_temp(); 
    return ( __sensors_data.temp != null ) ? 1 ; 0;
}

bool Sensors::ultrasonic_sensor_loop() {
    __sensors_data.usd1 = __sensors.uson_sensor.get_distance( 1 );
    __sensors_data.usd2 = __sensors.uson_sensor.get_distance( 2 );
    __sensors_data.usd3 = __sensors.uson_sensor.get_distance( 3 );

    if ( __sensors_data.usd1 == null && __sensors_data.usd2 == null && __sensors_data.usd3 == null )
        return 0;

    return 1;
}

bool Sensors::acoustic_sensor_loop() {
    
}