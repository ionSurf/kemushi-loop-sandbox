#include <NeoPixelEffects.hpp>

/*Context::Context() {}*/

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos, Adafruit_NeoPixel* strip) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip->Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip->Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

ColorWipe_Context::ColorWipe_Context() {
    this->step          = 0;
    this->step_limit    = 0;
    this->color         = 0;
}

void    ColorWipe_Context::set_color( uint32_t c ) {
    this->color = c;
}

void    ColorWipe_Context::set_step_limit( uint32_t lim ) {
    this->step_limit = lim;
}
bool    ColorWipe_Context::next() {
    if ( step < this->step_limit ) {
        this->step += 1;
        return true;
    }
    return false;
}
bool    ColorWipe_Context::render( Adafruit_NeoPixel* strip ) {
    strip->setPixelColor(this->step, this->color);
    strip->show();

    return true;
}



Rainbow_Context::Rainbow_Context() {
    this->steps[0]      = 0;
    this->steps[1]      = 0;

    this->steps_limits[0]   = 0;
    this->steps_limits[1]   = 0;

    this->brightness        = 255;

    this->step_increment    = 1;
}

void    Rainbow_Context::set_steps_limits( uint32_t step_i, uint32_t step_j ) {
    this->steps_limits[0] = step_i;
    this->steps_limits[1] = step_j;
}
void    Rainbow_Context::set_step_increment( uint8_t inc ) {
    this->step_increment    = inc;
}
void    Rainbow_Context::set_brightness( uint8_t b ) {
    this->brightness        = b;
}
bool    Rainbow_Context::next() {
    if ( this->steps[1] < this->steps_limits[1] ) {
        this->steps[1] += step_increment;
        return true;
    } else {
        return false;
    }
}
bool    Rainbow_Context::render( Adafruit_NeoPixel* strip ) {
    for ( steps[ 0 ] = 0 ; steps[ 0 ] < this->steps_limits[ 0 ]; steps[ 0 ]++ ) {
        //strip->setPixelColor( steps[0], Wheel( ( steps[ 0 ] + steps[ 1 ] ) & 255, strip ) );
        strip->setPixelColor( steps[0], strip->ColorHSV(steps[1], 255, this->brightness) );
        //strip->setPixelColor( steps[0], Wheel(strip->gamma8(steps[1]), strip) );
    }
    strip->show();

    return true;
}
void    Rainbow_Context::reset( ) {
    this->steps[0] = 0;
    this->steps[1] = 0;
}



RainbowCycle_Context::RainbowCycle_Context() {
    this->steps[0]      = 0;
    this->steps[1]      = 0;

    this->steps_limits[0]   = 0;
    this->steps_limits[1]   = 0;

    this->cycles    = 5;
}

void    RainbowCycle_Context::set_cycles( uint32_t cyc ) {
    this->cycles    = cyc;
}
void    RainbowCycle_Context::set_steps_limits( uint32_t step_i, uint32_t step_j ) {
    this->steps[0] = step_i;
    this->steps[1] = step_j;
}
bool    RainbowCycle_Context::next() {
    if ( this->steps[1] < this->steps_limits[1]*this->cycles ) {
        this->steps[1] += 1;
        return true;
    } else {
        return false;
    }
}
bool    RainbowCycle_Context::render( Adafruit_NeoPixel* strip ) {
    for ( this->steps[0] = 0; this->steps[0] < this->steps_limits[0]; this->steps[0]++ ) {
        strip->setPixelColor(steps[0], Wheel(((steps[0] * this->steps_limits[1] / steps_limits[0] ) + steps[1]) & 255, strip));
    }
    strip->show();

    return true;
}



TheaterChase_Context::TheaterChase_Context() {
    this->steps[0]      = 0;
    this->steps[1]      = 0;
    this->steps[2]      = 0;

    this->steps_limits[0]   = 0;
    this->steps_limits[1]   = 0;

    this->stage     = 1;
    this->color     = 0;
    this->step_inc  = 0;
    this->cycles    = 3;
}

void    TheaterChase_Context::set_cycles( uint32_t cyc ) {
    this->cycles    = cyc;
}
void    TheaterChase_Context::set_step_increment(uint32_t inc) {
    this->step_inc = inc;
}
void    TheaterChase_Context::set_steps_limits( uint32_t step_i, uint32_t step_j ) {
    this->steps[0] = step_i;
    this->steps[1] = step_j;
}
bool    TheaterChase_Context::next() {
    if ( this->steps[1] < this->steps_limits[1] ) {
        this->steps[1] += 1;
    } else {
        if ( this->steps[2] < this->cycles ) {
            this->steps[2] += 1;
                
            //  Reset values
            this->steps[1] = 0;

        } else {
            return false;
        }
    }

    return true;
}
bool    TheaterChase_Context::render( Adafruit_NeoPixel* strip ) {
    if ( this->stage > 0 ) {
        for ( steps[0] = 0; steps[0] < steps_limits[0]; steps[0]+= this->step_inc ) {
            strip->setPixelColor( this->steps[0] + this->steps[1], this->color );
        }
        
        strip->show();

        this->stage *= -1;

    } else {
        //  Turn leds off on non initial state
        for ( steps[0] = 0; steps[0] < steps_limits[0]; steps[0]+= this->step_inc ) {
            strip->setPixelColor( this->steps[0] + this->steps[1] - 1, 0 );
        }

        //  Turn next leds on
        for ( steps[0] = 0; steps[0] < steps_limits[0]; steps[0]+= this->step_inc ) {
            strip->setPixelColor( this->steps[0] + this->steps[1], this->color );
        }
        
        strip->show();
    } /*else {
        //  Turn leds off on last initial state
        for ( steps[0] = 0; steps[0] < steps_limits[0]; steps[0]+= this->step_inc ) {
            strip->setPixelColor( this->steps[0] + this->steps[1] - 1, 0 );
        }
    }*/

    return true;
}



TheaterChaseRainbow_Context::TheaterChaseRainbow_Context() {
    this->steps[0]      = 0;
    this->steps[1]      = 0;
    this->steps[2]      = 0;

    this->steps_limits[0]   = 0;
    this->steps_limits[1]   = 0;

    this->stage     = 1;
    this->step_inc  = 0;
    this->cycles    = 3;
}

void    TheaterChaseRainbow_Context::set_steps_limits( uint32_t step_i, uint32_t step_j, uint32_t step_k ) {
    this->steps[0] = step_i;
    this->steps[1] = step_j;
    this->steps[2] = step_k;
}
bool    TheaterChaseRainbow_Context::next() {
    if ( this->stage > 0 ) {
        if ( this->steps[2] < this->steps_limits[2] ) {
            this->steps[2] += this->step_inc;

            this->stage *= -1;
        } else {
            if ( this->steps[1] < this->steps_limits[1] ) {
                this->steps[1] += 1;
                
                //  Reset values
                this->steps[2] = 0;

            } else {
                if ( this->steps[ 0 ] < this->steps_limits[0] ) {
                    this->steps[0] += 1;
                    
                    //  Reset values
                    this->steps[2] = 0;
                    this->steps[1] = 0;

                } else {
                    return false;
                }
            }
        }
    } else {
        this->stage *= -1;
    }

    return true;
}
bool    TheaterChaseRainbow_Context::render( Adafruit_NeoPixel* strip ) {
    if ( this->stage == 0 ) {
        strip->setPixelColor( this->steps[2] + this->steps[1], Wheel( (steps[2]+steps[0]) % 255, strip ) );
        strip->show();
    } else {
        strip->setPixelColor( this->steps[2] + this->steps[1], 0 );
    }

    return true;
}