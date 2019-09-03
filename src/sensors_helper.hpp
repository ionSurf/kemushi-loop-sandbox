#include "LM35.hpp"
#include "SR04.hpp"
#include "MicSensor.hpp"
#include "HCSR501.hpp"

LM35      temp_sensor( 13 );

//SR04      uson_sensor_1( 22, 23 );
SR04      uson_sensor_1( 13, 12 );
SR04      uson_sensor_2( 21, 26 );
SR04      uson_sensor_3( 19, 15 );
SR04      uson_sensor_list[3] = { uson_sensor_1, uson_sensor_2, uson_sensor_3 };

MicSensor micp_sensor( 32 ); //32

HCSR501   pifr_sensor( 33 ); //33

int sensors_loop_profiler = 0;

String temp_output, dist_output, piri_output, micp_output;
float temp;

//  Function declaring
void print_temp();
void print_dist();
void print_piri();
void print_ints();

/*void mic_test_setup() {
  micp_output = "Sound intensity is: ";
  mic_ticker.attach_ms( 50, print_ints );
}

void pir_test_setup() {
  micp_output = "Infrared sensor value: ";
  mic_ticker.attach_ms( 50, print_piri );
}

void sensors_tickers_setup() {
  temp_output = "Temperature is: ";
  dist_output = "Ultrasonic distance is: ";
  micp_output = "Sound intensity is: ";
  piri_output = "PIR presence is: ";

  temp_sensor.set_mode( FARENHEIT );
  tmp_ticker.attach_ms( 500, print_temp );
  uso_ticker.attach_ms( 500, print_dist );
  mic_ticker.attach_ms( 500, print_ints );
  pir_ticker.attach_ms( 500, print_piri );
}*/

void usons_setup() {
  uson_sensor_1.set_threshold( 100 );
  uson_sensor_2.set_threshold( 100 );
  uson_sensor_3.set_threshold( 100 );
}

void print_dist() {
  float dist1 = uson_sensor_1.get_dist();
  float dist2 = uson_sensor_2.get_dist();
  float dist3 = uson_sensor_3.get_dist();

  Serial.println( dist_output + String( dist1 ) + ", " + String( dist2 ) + ", " + String( dist3 ) );
}

void print_ints() {
  float sound_intensity = micp_sensor.get_intensity();

  Serial.println( micp_output + String( sound_intensity ) );
}

void print_piri() {
  Serial.print( piri_output);
  ( pifr_sensor.has_presence() ) ? Serial.println( "true" ) : Serial.println( "false" );
}