#include <Arduino.h>

#include <Ticker.h>

//  Individual Tickers
Ticker tmp_ticker, uso_ticker, mic_ticker, pir_ticker;

//  Layered Tickers
Ticker highRefreshRateSensorsTicker, lowRefreshRateSensorsTicker, soundsTicker, lightsTicker;

#include <sensors_helper.hpp>
#include <lights_helper.hpp>
#include <sounds_helper.hpp>

void HR_sensors_loop();
void LR_sensors_loop();
void LR_sensors_loop_test();
void lights_loop();

//  soundReactiveTest01_setup
Ticker usonicTicker;
void update_usensor();

/**
 * Acoustic response with the Ultrasonic sensor
 */ 
void lightSequences_setup() {
  vTaskDelay(1000);
  Serial.begin(115200);

  lights_setup();
  //highRefreshRateSensorsTicker.attach_ms( 50, HR_sensors_loop );

  lowRefreshRateSensorsTicker.attach_ms( 250, LR_sensors_loop_test );
  lightsTicker.attach_ms( 50, lights_loop );
  
  Serial.println( "tickers_layers_setup... \tDONE" );
}

/**
 * Acoustic response with the Ultrasonic sensor
 */ 
void soundReactiveTest01_setup() {
  Serial.begin(115200);
  vTaskDelay(1000);

  usons_setup();

  Serial.print( "\tDONE\tAudio Setup.\n" );
  setup_audio();

  usonicTicker.attach_ms( 500, update_usensor );
}

/**
 * Acoustic response with the microphpone
 */
void sound_reactive_test_2() {}

void setup() {

  soundReactiveTest01_setup();

  Serial.print( "\tDONE\tMain setup.\n" );
}

void loop() {}

void HR_sensors_loop() {
  micp_sensor.update_value();
  pifr_sensor.update_value();

  Serial.println("HR_sensors_loop");
}

void LR_sensors_loop_test() {
  Serial.print("LR_sensors_loop_test - ");
  
  float temp = temp_sensor.update_value();
  float dist = uson_sensor_1.update_value();
  dist = ( dist > 2500 ) ? 2500 : dist;

  Serial.print("\tTEMP : ");
  Serial.print( String( temp ) );
  Serial.print("\tUSON : ");
  Serial.print( String( dist ) );
  Serial.println(" mapped to: " + String(map( dist , 0, 2500, 0, 255 )));

  update_brightness_from_uson( dist );
}

void LR_sensors_loop() {
  /*for ( int i = 0; i < 3; i++ ) {
    uson_sensor_list[i].update_value();
  }*/
  temp_sensor.update_value();

  float min_reading = 1000;
  for ( int i = 0; i < 2; i++ ) {
    min_reading = (uson_sensor_list[i].update_value() < min_reading) ? uson_sensor_list[i].get_last_value() : min_reading;
  }
  update_brightness_from_uson( min_reading );

  Serial.print("LR_sensors_loop - ");
  Serial.print("\tTEMP : ");
  Serial.print( String(temp_sensor.get_temp()) );
  Serial.print("\tUSON : ");
  Serial.println( String(uson_sensor_1.get_last_value()) );
}

void update_usensor() {
  Serial.println("INIT\tupdate_usensor");
  float distance = uson_sensor_1.update_value();
  Serial.println("USON data: " + String( distance ) );
  Serial.println("DONE\tupdate_usensor");

  if ( uson_sensor_1.is_above_theshold() ) {
    Serial.println( (uson_sensor_1.is_above_theshold() ) ? "-------- above threshold ----------" : "--" );
  }

  //if ( !soundsTicker.active_default() && uson_sensor_1.is_above_theshold() ) {
  if ( !soundTickerFlag && uson_sensor_1.is_above_theshold() ) {
  //if ( uson_sensor_1.is_above_theshold() ) {

    Serial.print( "\tDONE\tSample MP3 playback begins.\n" );
    init_audio();
    soundsTicker.attach_ms( 50, loop_audio );
    uson_sensor_1.reset_threshold();

    soundTickerFlag = true;
  }
}