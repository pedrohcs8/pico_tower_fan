#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"

#include "display_driver.h"

bool inited = false;

int number = 0;

bool power = false;
bool umidificar = false;
bool brisa = false;
int velocidade = 1;
int timer = 0;
bool dormir= false;
bool purificar = false;

void handleButtons(uint16_t result) {
  if (result > 10 && result < 30) {
    umidificar = !umidificar;
  }

  if (result > 85 && result < 110) {
    brisa = !brisa;
  }

  if (result > 50 && result < 75) {
    velocidade++;
    if (velocidade > 3) {
      velocidade = 1;
    }
  }
}

int main() {
  for (int i = 0 ; i < 16; i++) {
    gpio_init(i);
    gpio_set_dir(i, GPIO_OUT);
  }

  adc_init();

  adc_gpio_init(28);

  adc_select_input(2);
  gpio_pull_up(28);

  while(true) {
    uint16_t result = adc_read();
    printf("%d %d\n", result, velocidade);

    if (result > 200 && result < 250) {
      power = !power;
    }

    if (power) {
      handleButtons(result);
      gpio_put(8, 1);

      if (!inited) {
        velocidade = 1;
        inited = true;
      }
    } else {
      for (int i = 0; i < 6; i++) {
        gpio_put(i, 1);
      }

      for (int i = 6; i < 10; i++) {
        gpio_put(i, 0);
      }

      velocidade = 0;
      timer = 0;

      umidificar = false;
      brisa = false;
      dormir = false;
      purificar = false;

      inited = false;
    }

    if (umidificar) {
      gpio_put(4, 0);
      gpio_put(6, 1);
    } else {
      gpio_put(4, 1);
      gpio_put(6, 0);
    }

    if (brisa) {
      gpio_put(3, 0);
      gpio_put(7, 1);
    } else {
      gpio_put(3, 1);
      gpio_put(7, 0);
    }

    if (purificar) {
      gpio_put(5, 0);
      gpio_put(10, 1);
    } else {
      gpio_put(5, 1);
      gpio_put(10, 0);
    }


    switch(velocidade) {
      case 0: {
        gpio_put(0, 1);
        gpio_put(1, 1);
        gpio_put(2, 1);

        noNumber();
        break;
      }

      case 1: {
        gpio_put(0, 0);
        gpio_put(1, 1);
        gpio_put(2, 1);

        showNumber(1);
        break;
      }

      case 2: {
        gpio_put(0, 1);
        gpio_put(1, 0);
        gpio_put(2, 1);

        showNumber(2);
        break;
      }

      case 3: {
        gpio_put(0, 1);
        gpio_put(1, 1);
        gpio_put(2, 0);

        showNumber(3);
        break;
      }
    }

    sleep_ms(150);
  }
}
