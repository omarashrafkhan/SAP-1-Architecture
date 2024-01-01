#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

typedef struct {
  // Input
  pin_t A;
  pin_t B;
  pin_t Cin;

  // Output
  pin_t Cout;
  pin_t Sum;
} chip_state_t;


void update_pins(chip_state_t *chip) {
  // Read the input values
  int a = pin_read(chip->A);
  int b = pin_read(chip->B);
  int cin = pin_read(chip->Cin);

  // Calculate XOR of inputs
  int sum = a ^ b ^ cin;

  // Implement carry-out logic (Cout)
  int cout = (a & b) | ((a ^ b) & cin);

  // Write the results to the output pins
    
  pin_write(chip->Sum, 0);
  pin_write(chip->Cout, 0);

  pin_write(chip->Sum, sum);
  pin_write(chip->Cout, cout);

  // Print the values for debugging
  printf("Input values: A=%d, B=%d, Cin=%d\n", a, b, cin);
  printf("Sum: %d, Cout: %d\n", sum, cout);
  printf("============================");
}




void chip_pin_change(void *user_data, pin_t pin, uint32_t value) {
  chip_state_t *chip = (chip_state_t *)user_data;
  // Add your pin change handling logic here
  // For example, you might want to call update_pins to update the output based on the new pin state
  update_pins(chip);
}

void chip_init() {
  chip_state_t *chip = malloc(sizeof(chip_state_t));

  chip->A = pin_init("A", INPUT_PULLDOWN);
  chip->B = pin_init("B", INPUT_PULLDOWN);
  chip->Cin = pin_init("Cin", INPUT_PULLDOWN);

  chip->Sum = pin_init("Sum", OUTPUT);
  chip->Cout = pin_init("Cout", OUTPUT);

  const pin_watch_config_t watch_config = {
    .edge = BOTH,
    .pin_change = chip_pin_change,
    .user_data = chip
  };

  pin_watch(chip->A, &watch_config);
  pin_watch(chip->B, &watch_config);
  pin_watch(chip->Cin, &watch_config);

  // TODO: Initialize the chip, set up IO pins, create timers, etc.

}