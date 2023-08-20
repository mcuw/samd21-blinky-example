// Atmel SAM D21 Xplained Pro with zephyr - blinky example
//
// doc - microchip: https://www.microchip.com/en-us/development-tool/ATSAMD21-XPRO
// example zephyr blink code see https://github.com/platformio/platform-atmelsam/blob/master/examples/zephyr-blink/src/main.c
// pio: https://docs.platformio.org/en/latest/boards/atmelsam/samd21_xpro.html#board-atmelsam-samd21-xpro

#include <zephyr.h>
#include <drivers/gpio.h>

#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0 DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS DT_GPIO_FLAGS(LED0_NODE, gpios)
#else
// A build error here means your board isn't set up to blink an LED.
#error "Unsupported board: led0 devicetree alias is not defined"
#define LED0 ""
#define PIN 0
#define FLAGS 0
#endif

// 1000 msec = 1 sec
#define SLEEP_TIME_MS 1000

void main()
{
  bool led_is_on = true;

  const struct device *dev = device_get_binding(LED0);
  if (dev == NULL)
  {
    return;
  }

  int ret = gpio_pin_configure(dev, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
  if (ret < 0)
  {
    return;
  }

  while (1)
  {
    gpio_pin_set(dev, PIN, (int)led_is_on);
    led_is_on = !led_is_on;
    k_msleep(SLEEP_TIME_MS);
  }
}
