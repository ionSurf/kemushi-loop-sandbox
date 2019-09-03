#include <Sensor.hpp>

Sensor::Sensor() {
    __min_refresh_lapse = -1;
    __max_refresh_lapse = -1;
};

Sensor::Sensor( uint16_t min_limit, uint16_t max_limit ) {
    __min_refresh_lapse = min_limit;
    __max_refresh_lapse = max_limit;
};