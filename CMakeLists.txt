cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
set(CMAKE_TOOLCHAIN_FILE cmake/toolchain-arm-none-eabi-gcc.cmake)
project(app VERSION 0.1.0 LANGUAGES CXX C ASM)

include(cmake/stm32f303.cmake)

################################################################################
# SHARED
################################################################################

set(CORE_SRC_DIR shared/src/core)
set(CORE_INC_DIR shared/inc/core)
set(SHARED_SRC_DIR shared/src)
set(SHARED_INC_DIR shared/inc)

################################################################################
# BOOTLOADER
################################################################################

set(BOOTLOADER_SRC_DIR bootloader/src/)
set(BOOTLOADER_INC_DIR bootloader/inc)
file(GLOB_RECURSE BOOTLOADER_SOURCES CONFIGURE_DEPENDS ${BOOTLOADER_SRC_DIR}/*.c)

add_executable(bootloader ${BOOTLOADER_SOURCES})
include_directories(bootloader PRIVATE ${BOOTLOADER_INC_DIR} ${SHARED_INC_DIR})

target_link_libraries(bootloader stm32f303)
stm32_add_linker_script(bootloader PRIVATE STM32F303VCTx_BOOTLOADER.ld)

target_link_options(bootloader PUBLIC LINKER:-Map=bootloader.map)

add_custom_command(
  TARGET bootloader
  COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:bootloader> $<TARGET_FILE_DIR:bootloader>/bootloader.bin
  COMMENT "Generating binary bootloader file"
)

add_custom_command(TARGET bootloader
  COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/pad_bootloader.py
  RESULT_VARIABLE padding_script_result
  COMMENT "Running padding bootloader script"
)

################################################################################
# APP BINARY
################################################################################

set(SRC_DIR app/src/)
set(INC_DIR app/inc)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${SRC_DIR}/*.c)
file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS ${CORE_SRC_DIR}/*.c)

add_executable(app ${SOURCES} ${CORE_SOURCES} ${BOOTLOADER_SRC_DIR}/bootloader.S)
include_directories(app PRIVATE ${INC_DIR} ${SHARED_INC_DIR} ${CORE_INC_DIR})

target_link_libraries(app stm32f303)
set_property(TARGET app PROPERTY CXX_STANDARD 17)
stm32_add_linker_script(app PRIVATE STM32F303VCTx_FLASH.ld)
stm32_add_flash_targets(app)