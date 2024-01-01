// Wokwi Custom Chip - For docs and examples see:
// https://docs.wokwi.com/chips-api/getting-started
//
// SPDX-License-Identifier: MIT
// Copyright 2023 Omar A Khan

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  // TODO: Put your chip variables here
  pin_t A;
  pin_t B;
  pin_t C;
  pin_t D;
  pin_t E;
  pin_t F;
  pin_t G;
  pin_t H;
 int binaryArray[7];

} chip_state_t;

void chip_init() {
  chip_state_t *chip = malloc(sizeof(chip_state_t));

  chip->A = pin_init("OUT1", OUTPUT);
  chip->B = pin_init("OUT2", OUTPUT);
  chip->C = pin_init("OUT3", OUTPUT);
  chip->D = pin_init("OUT4", OUTPUT);
  chip->E = pin_init("OUT5", OUTPUT);
  chip->F = pin_init("OUT6", OUTPUT);
  chip->G = pin_init("OUT7", OUTPUT);
  chip->H = pin_init("OUT8", OUTPUT);

  chip->binaryArray[0] =1 ; //load 1
  chip->binaryArray[1] =0 ;
  chip->binaryArray[2] =1 ;
  chip->binaryArray[3] =1 ;
  chip->binaryArray[4] =1 ;
  chip->binaryArray[5] =0 ;
  chip->binaryArray[6] =0 ;
  chip->binaryArray[7] =1 ;

  // Print the array values
  printf("Binary Array Values: ");
  for (int i = 0; i < 8; ++i) {
    printf("%d, ", chip->binaryArray[i]);
  }
  printf("\n");


  pin_write(chip->A, chip->binaryArray[0]);
  pin_write(chip->B, chip->binaryArray[1]);
  pin_write(chip->C, chip->binaryArray[2]);
  pin_write(chip->D, chip->binaryArray[3]);
  pin_write(chip->E, chip->binaryArray[4]);
  pin_write(chip->F, chip->binaryArray[5]);
  pin_write(chip->G, chip->binaryArray[6]);
  pin_write(chip->H, chip->binaryArray[7]);

  // TODO: Initialize the chip, set up IO pins, create timers, etc.

  
}
