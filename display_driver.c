#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"

int lastNumber;

uint8_t numberTable[10] = {0x3, 0x9F, 0x25, 0xD, 0x99, 0x49, 0x41, 0x1F, 0x1, 0x9};

void showNumber(int number) {
  if (number == lastNumber) {
    return;
  }

  uint8_t segments = numberTable[number];

  for (int i = 0; i < 8; i++) {
    bool segment = (segments >> i) & 1;

    gpio_put(11, segment);
    sleep_us(50);
    gpio_put(12, 1);
    gpio_put(13, 1);
    sleep_us(50);

    gpio_put(11, 0);
    gpio_put(12, 0);
    gpio_put(13, 0);
  }

  lastNumber = number;
}

void noNumber() {
  for (int i = 0; i < 8; i++) {
    bool segment = (0xFF >> i) & 1;

    gpio_put(11, segment);
    sleep_us(20);
    gpio_put(12, 1);
    gpio_put(13, 1);
    sleep_us(20);

    gpio_put(11, 0);
    gpio_put(12, 0);
    gpio_put(13, 0);
  }

  lastNumber = 0;
}
