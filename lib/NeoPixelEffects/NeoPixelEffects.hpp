#ifndef NeoPixelEffects_hpp
#define NeoPixelEffects_hpp
#endif

#include <Adafruit_NeoPixel.h>

class Context {
public:
  static uint32_t Wheel(byte , Adafruit_NeoPixel* );
};

class ColorWipe_Context {
public:
  ColorWipe_Context();

  uint32_t    color;
  uint16_t    step;
  uint32_t    step_limit;

  void set_color( uint32_t );
  void set_step_limit( uint32_t );

  bool next();
  bool render( Adafruit_NeoPixel* );
};

class Rainbow_Context {
public:
  Rainbow_Context();
  uint8_t     brightness;
  uint16_t    steps[2];
  uint32_t    steps_limits[2];
  uint8_t     step_increment;

  void set_steps_limits( uint32_t, uint32_t );
  void set_step_increment( uint8_t );
  void set_brightness( uint8_t );

  bool  next();
  bool  render( Adafruit_NeoPixel* );

  void  reset();
};

class RainbowCycle_Context {
public:
  RainbowCycle_Context();

  uint32_t    cycles;
  uint16_t    steps[2];
  uint32_t    steps_limits[2];

  void set_cycles( uint32_t );
  void set_steps_limits( uint32_t, uint32_t );

  bool next();
  bool render( Adafruit_NeoPixel* );
};

class TheaterChase_Context {
public:
  TheaterChase_Context();

  uint32_t    color;
  uint32_t    cycles;
  uint16_t    steps[3];
  uint32_t    steps_limits[2];
  uint32_t    step_inc;
  int8_t      stage;

  void set_cycles( uint32_t );
  void set_step_increment( uint32_t );
  void set_steps_limits( uint32_t, uint32_t );

  bool next();
  bool render( Adafruit_NeoPixel* );
};

class TheaterChaseRainbow_Context {
public:
  TheaterChaseRainbow_Context();

  uint32_t    cycles;
  uint16_t    steps[3];
  uint32_t    steps_limits[3];

  uint32_t    step_inc;
  int8_t      stage;

  void set_step_increment( uint32_t );
  void set_steps_limits( uint32_t, uint32_t, uint32_t );

  bool next();
  bool render( Adafruit_NeoPixel* );
};