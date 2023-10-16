#include <libopencm3/cm3/vector.h>
#include <libopencm3/stm32/memorymap.h>

#include "common-defines.h"

// bootloader:  0x0800_0000 - 0x0800_7FFF
// program:     0x0800_8000 - 0x0803_FFFF
#define BOOTLOADER_SIZE        (0x4000U)  // 32K
#define MAIN_APP_START_ADDRESS (FLASH_BASE + BOOTLOADER_SIZE)

static void jump_to_main(void) {
  vector_table_t *main_vector_table = (vector_table_t *)(MAIN_APP_START_ADDRESS);
  main_vector_table->reset();
}

int main(void) {
  jump_to_main();
  return 0;
}