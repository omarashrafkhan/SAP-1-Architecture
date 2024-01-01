/* This custom chip that implements 4-bit hexadecimal to 7 segments display decoder
@author: Renaldas Zioma (rej)
*/

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  // inputs
  pin_t COM; // shares COM pin with 7 segment display
              // in order to sense "anode" or "cathode" mode of the display
              // adjusts ouputs automatically
  pin_t in0;
  pin_t in1;
  pin_t in2;
  pin_t in3;

  // outputs
  pin_t A;
  pin_t B;
  pin_t C;
  pin_t D;
  pin_t E;
  pin_t F;
  pin_t G;
} chip_state_t;

// 7 segment display, see https://docs.wokwi.com/parts/wokwi-7segment
//  AAA 
// F   B 
// F   B
//  GGG
// E   C
// E   C
//  DDD
//  A  B  C   D  E  F   G
enum { SEGMENT_COUNT = 7 };
const int SEGMENTS[16][SEGMENT_COUNT] = {
  { 1, 1, 1,  1, 1, 1,  0 }, // 0
  { 0, 1, 1,  0, 0, 0,  0 }, // 1
  { 1, 1, 0,  1, 1, 0,  1 }, // 2
  { 1, 1, 1,  1, 0, 0,  1 }, // 3

  { 0, 1, 1,  0, 0, 1,  1 }, // 4
  { 1, 0, 1,  1, 0, 1,  1 }, // 5
  { 1, 0, 1,  1, 1, 1,  1 }, // 6
  { 1, 1, 1,  0, 0, 0,  0 }, // 7

  { 1, 1, 1,  1, 1, 1,  1 }, // 8
  { 1, 1, 1,  1, 0, 1,  1 }, // 9
  { 1, 1, 1,  0, 1, 1,  1 }, // A
  { 0, 0, 1,  1, 1, 1,  1 }, // B

  { 1, 0, 0,  1, 1, 1,  0 }, // C
  { 0, 1, 1,  1, 1, 0,  1 }, // D
  { 1, 0, 0,  1, 1, 1,  1 }, // E
  { 1, 0, 0,  0, 1, 1,  1 }, // F
};

static int update_output(chip_state_t *chip) {
  int hex = 
    pin_read(chip->in0) * 1 +
    pin_read(chip->in1) * 2 + 
    pin_read(chip->in2) * 4 +
    pin_read(chip->in3) * 8;

  int is_display_common_mode_set_to_anode = pin_read(chip->COM) == HIGH ? 1: 0;

  const pin_t* pins[SEGMENT_COUNT] = { &chip->A, &chip->B, &chip->C, &chip->D, &chip->E, &chip->F, &chip->G };
  for (int q = 0; q < SEGMENT_COUNT; ++q)
    pin_write(*pins[q], (SEGMENTS[hex][q] ^ is_display_common_mode_set_to_anode) ? HIGH : LOW);

  return hex;
}

void chip_pin_change(void *user_data, pin_t pin, uint32_t value) {
  chip_state_t *chip = (chip_state_t*)user_data;
  int input_value = update_output(chip);
  // Uncomment to DEBUG
  //printf("Output Value: %d\n", input_value);
}

void chip_init() {
  setvbuf(stdout, NULL, _IOLBF, 1024);
  printf("Initializing hex-to-7segment\n");

  chip_state_t *chip = malloc(sizeof(chip_state_t));
  chip->COM = pin_init("COM", INPUT_PULLUP);
  chip->in0 = pin_init("in0", INPUT_PULLDOWN);
  chip->in1 = pin_init("in1", INPUT_PULLDOWN);
  chip->in2 = pin_init("in2", INPUT_PULLDOWN);
  chip->in3 = pin_init("in3", INPUT_PULLDOWN);
  chip->A = pin_init("A", OUTPUT);
  chip->B = pin_init("B", OUTPUT);
  chip->C = pin_init("C", OUTPUT);
  chip->D = pin_init("D", OUTPUT);
  chip->E = pin_init("E", OUTPUT);
  chip->F = pin_init("F", OUTPUT);
  chip->G = pin_init("G", OUTPUT);

  const pin_watch_config_t watch_config = {
    .edge = BOTH,
    .pin_change = chip_pin_change,
    .user_data = chip
  };

  pin_watch(chip->COM, &watch_config);
  pin_watch(chip->in0, &watch_config);
  pin_watch(chip->in1, &watch_config);
  pin_watch(chip->in2, &watch_config);
  pin_watch(chip->in3, &watch_config);
 
  update_output(chip);
}
