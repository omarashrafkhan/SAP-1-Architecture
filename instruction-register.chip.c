#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  // TODO: Put your chip variables here

  pin_t I0;
  pin_t I1;
  pin_t I2;
  pin_t I3;
  pin_t I4;
  pin_t I5;
  pin_t I6;
  pin_t I7;
  
  pin_t O0;
  pin_t O1;
  pin_t O2;
  pin_t O3;
  pin_t O4;
  pin_t O5;
  pin_t O6;
  pin_t O7;

  // Array to store input values
  int inputValues[8];

} chip_state_t;

// Function to copy input values to output pins
void copy_input_to_output(chip_state_t *chip) {
  
  pin_write(chip->O0, chip->inputValues[0]);
  pin_write(chip->O1, chip->inputValues[1]);
  pin_write(chip->O2, chip->inputValues[2]);
  pin_write(chip->O3, chip->inputValues[3]);
  pin_write(chip->O4, chip->inputValues[4]);
  pin_write(chip->O5, chip->inputValues[5]);
  pin_write(chip->O6, chip->inputValues[6]);
  pin_write(chip->O7, chip->inputValues[7]);
}

void update_pins_ir(chip_state_t *chip) {
  // Read and store the input values into the array
  chip->inputValues[0] = pin_read(chip->I0);
  chip->inputValues[1] = pin_read(chip->I1);
  chip->inputValues[2] = pin_read(chip->I2);
  chip->inputValues[3] = pin_read(chip->I3);
  chip->inputValues[4] = pin_read(chip->I4);
  chip->inputValues[5] = pin_read(chip->I5);
  chip->inputValues[6] = pin_read(chip->I6);
  chip->inputValues[7] = pin_read(chip->I7);

  // Print the values of the array
  printf("Input Values: %d, %d, %d, %d, %d, %d, %d, %d\n",
         chip->inputValues[0], chip->inputValues[1], chip->inputValues[2], chip->inputValues[3],
         chip->inputValues[4], chip->inputValues[5], chip->inputValues[6], chip->inputValues[7]);

  // Copy input values to output pins
  copy_input_to_output(chip);
}


void chip_pin_change(void *user_data, pin_t pin, uint32_t value) {
  chip_state_t *chip = (chip_state_t *)user_data;

  printf("In change");
  // Add your pin change handling logic here
  // For example, you might want to call update_pins to update the output based on the new pin state
  update_pins_ir(chip);
}

void chip_init() {
  chip_state_t *chip = malloc(sizeof(chip_state_t));

  printf("Chip init :) ");

  chip->I0 = pin_init("I0", INPUT_PULLDOWN);
  chip->I1 = pin_init("I1", INPUT_PULLDOWN);
  chip->I2 = pin_init("I2", INPUT_PULLDOWN);
  chip->I3 = pin_init("I3", INPUT_PULLDOWN);
  chip->I4 = pin_init("I4", INPUT_PULLDOWN);
  chip->I5 = pin_init("I5", INPUT_PULLDOWN);
  chip->I6 = pin_init("I6", INPUT_PULLDOWN);
  chip->I7 = pin_init("I7", INPUT_PULLDOWN);
  chip->O0 = pin_init("O0", OUTPUT);
  chip->O1 = pin_init("O1", OUTPUT);
  chip->O2 = pin_init("O2", OUTPUT);
  chip->O3 = pin_init("O3", OUTPUT);
  chip->O4 = pin_init("O4", OUTPUT);
  chip->O5 = pin_init("O5", OUTPUT);
  chip->O6 = pin_init("O6", OUTPUT);
  chip->O7 = pin_init("O7", OUTPUT);

  const pin_watch_config_t watch_config = {
    .edge = BOTH,
    .pin_change = chip_pin_change,
    .user_data = chip
  };

  pin_watch(chip->I0, &watch_config);
  pin_watch(chip->I1, &watch_config);
  pin_watch(chip->I2, &watch_config);
  pin_watch(chip->I3, &watch_config);
  pin_watch(chip->I4, &watch_config);
  pin_watch(chip->I5, &watch_config);
  pin_watch(chip->I6, &watch_config);
  pin_watch(chip->I7, &watch_config);
}
