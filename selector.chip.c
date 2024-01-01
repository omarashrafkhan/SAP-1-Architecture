#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  // inputs
  pin_t IN[4][8];

  // control lines
  pin_t CTRL[2];

  // output
  pin_t OUT[8];
} mux_chip_t;

// Function to update the output based on control lines and input values
static void update_output(mux_chip_t *mux_chip) {
  // Calculate the selected input
  int selectedInput = (pin_read(mux_chip->CTRL[1]) << 1) | pin_read(mux_chip->CTRL[0]);

  // Output the selected input values
  for (int i = 0; i < 8; i++) {
    pin_write(mux_chip->OUT[i], pin_read(mux_chip->IN[selectedInput][i]));
  }
  
  // Print the values of inputs, control lines, and outputs
  printf("Inputs: ");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 8; j++) {
      printf("%d ", pin_read(mux_chip->IN[i][j]));
    }
  }
  printf("\nControl Lines: %d %d\n", pin_read(mux_chip->CTRL[0]), pin_read(mux_chip->CTRL[1]));
  printf("Outputs: ");
  for (int i = 0; i < 8; i++) {
    printf("%d ", pin_read(mux_chip->OUT[i]));
  }
  printf("\n");
}

// Callback function when a pin changes
void mux_chip_pin_change(void *user_data, pin_t pin, uint32_t value) {
  mux_chip_t *mux_chip = (mux_chip_t *)user_data;
  update_output(mux_chip);
}

// Initialization function for the multiplexer chip
void chip_init() {
  printf("Initializing 4-to-1 Multiplexer chip\n");

  // Allocate memory for the chip state
  mux_chip_t *mux_chip = malloc(sizeof(mux_chip_t));

  // Initialize input pins
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 8; j++) {
      char pinName[10];
      sprintf(pinName, "IN%d_%d", i + 1, j + 1);
      mux_chip->IN[i][j] = pin_init(pinName, INPUT_PULLDOWN);
    }
  }

  // Initialize control lines
  for (int i = 0; i < 2; i++) {
    char pinName[6];
    sprintf(pinName, "CTRL%d", i + 1);
    mux_chip->CTRL[i] = pin_init(pinName, INPUT_PULLDOWN);
  }

  // Initialize output pins
  for (int i = 0; i < 8; i++) {
    char pinName[6];
    sprintf(pinName, "OUT%d", i + 1);
    mux_chip->OUT[i] = pin_init(pinName, OUTPUT);
  }

  const pin_watch_config_t watch_config = {
      .edge = BOTH,
      .pin_change = mux_chip_pin_change,
      .user_data = mux_chip};

  // Watch input and control pins
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 8; j++) {
      pin_watch(mux_chip->IN[i][j], &watch_config);
    }
  }

  for (int i = 0; i < 2; i++) {
    pin_watch(mux_chip->CTRL[i], &watch_config);
  }

  // Update the output based on the initial values
  update_output(mux_chip);
}
