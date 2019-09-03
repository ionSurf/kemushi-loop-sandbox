#include <Arduino.h>

#ifndef LM35_h
#define LM35_h
#endif

/*#ifdef __cplusplus
extern "C" {}
#endif*/

typedef enum {
    CELSIUS,
    FARENHEIT,
    KELVIN
} temp_mode_t;

class LM35 {
public:
    LM35( short );

    void    set_mode( temp_mode_t );
    float   get_temp();
    float   update_value();
    float   get_last_value();

    void print_value();
private:
    short unsigned int __min_refresh_lapse;

    short unsigned int __pin;
    temp_mode_t __mode;

    float __last_value;
};