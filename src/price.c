#include <stdio.h>
#include <string.h>
#include "headers/stl.h"

// Return the associated density with the material
float filamentDensity(char* material) {
  if (strcmp("ABS", material) == 0) {
    return 1.04;
  } else if (strcmp("PLA", material) == 0) {
    return 1.24;
  } else if (strcmp("CFRP", material) == 0) {
    return 1.79;
  } else if (strcmp("Plexiglass", material) == 0) {
    return 1.185;
  } else if (strcmp("Alumide", material) == 0) {
    return 1.36;
  } else if (strcmp("Aluminium", material) == 0) {
    return 2.68;
  } else if (strcmp("Brass", material) == 0) {
    return 8.73;
  } else if (strcmp("Bronze", material) == 0) {
    return 9.0;
  } else if (strcmp("Copper", material) == 0) {
    return 8.96;
  } else if (strcmp("Gold_14K", material) == 0) {
    return 13.6;
  } else if (strcmp("Gold_18K", material) == 0) {
    return 16.5;
  } else if (strcmp("Polyamide_MJF", material) == 0) {
    return 1.01;
  } else if (strcmp("Polyamide_SLS", material) == 0) {
    return 0.95;
  } else if (strcmp("Rubber", material) == 0) {
    return 0.92;
  } else if (strcmp("Silver", material) == 0) {
    return 10.5;
  } else if (strcmp("Steel", material) == 0) {
    return 8.05;
  } else if (strcmp("Titanium", material) == 0) {
    return 4.5;
  } else {
    return 1.2; // Resin
  }
}

// Returns an estimated price of a 3D printer model (FDM)
float calcPrice(char* fname, char type, float infill, float fprice, float wallWidth, char* material) {
  float params[4] = {0, 0, 0, 0};
  getSTLParams(fname, type, params);
  float volume = params[2];
  float area = params[3];
  float outerShellVolume = area * wallWidth;
  float innerInfillVolume = volume - outerShellVolume;
  float fden = filamentDensity(material);
  return (outerShellVolume * fden + innerInfillVolume * fden * infill) * fprice;
}
