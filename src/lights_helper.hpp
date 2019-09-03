#include <NeoPixelEffects.hpp>

//  Define strip parameters
#define PIN1 4
Adafruit_NeoPixel strip = Adafruit_NeoPixel(17, PIN1, NEO_GRB + NEO_KHZ800);
//  Define state machine contexts
ColorWipe_Context           colorWipeContext;
Rainbow_Context             rainbowContext;
RainbowCycle_Context        rainbowcycleContext;
TheaterChase_Context        theaterChaseContext;
TheaterChaseRainbow_Context theaterChaseRainbowContext;

int lights_loop_profiler = 0;

void set_wipeColorContext() {
  colorWipeContext.set_color( strip.Color(255, 0, 0) );
  colorWipeContext.set_step_limit( strip.numPixels() );
}

void set_rainbowContext() {
  rainbowContext.set_steps_limits( strip.numPixels(), 65535 );
  rainbowContext.set_step_increment(100);
}

void set_rainbowCycleContext() {
  rainbowcycleContext.set_steps_limits( strip.numPixels(), 256 );
  rainbowcycleContext.set_cycles( 5 );
}

void set_theaterChaseContext() {
  theaterChaseContext.set_step_increment( 3 );
  theaterChaseContext.set_steps_limits( strip.numPixels(), 3 );
}

void set_theaterChaseRainbowContext() {

}

void lights_setup() {
  strip.begin();
  strip.show();

  set_wipeColorContext();

  while( colorWipeContext.next() ) {
    colorWipeContext.render( &strip );
  }

  set_rainbowContext();
  set_rainbowCycleContext();
  set_theaterChaseContext();
  set_theaterChaseRainbowContext();

  Serial.println( "lights_setup... \t\tDONE" );
}

long map_channel( long ch_reading, long chin_min, long chin_max, long chout_min, long chout_max ) {
  return map( ch_reading, chin_min, chin_max, chout_min, chout_max );
}

void update_brightness_from_uson( float input ) {
  rainbowContext.set_brightness( map(input, 0, 2500, 0, 255) );
}

void update_color_from_uson( float input ) {
  for ( int i = 0; i < strip.numPixels(); i++ ) {
    strip.setPixelColor( i, Context::Wheel( map( input , 0, 1000, 0, 255 ), &strip ) );
  }
}

void lights_loop() {
  rainbowContext.render( &strip );
  if ( !rainbowContext.next() ) {
    rainbowContext.reset();
    //lightsTicker.detach();
  }
  Serial.print("lights_loop");
  Serial.println( String(lights_loop_profiler) );
  lights_loop_profiler++;
}