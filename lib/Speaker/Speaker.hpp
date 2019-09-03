#include <Arduino.h>

class Speaker {
private:
    uint8_t     __pin;
    uint16_t    __vol;
    bool        __in_use;
public:
    Speaker();
    Speaker( uint8_t );

    void        set_pin( uint8_t );
    uint8_t     get_pin( );
    void        set_volume( uint16_t );
    uint16_t    get_volume();
    bool        is_busy();
    bool        play_tone();
    bool        stop();
};