cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
set(CMAKE_TOOLCHAIN_FILE cmake/toolchain-arm-none-eabi-gcc.cmake)
project(app VERSION 0.1.0 LANGUAGES CXX C ASM)

include(cmake/stm32f303.cmake)

# Directories
set(SRC_DIR app/src/)
set(INC_DIR app/inc)
set(CORE_DIR app/inc/core)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${SRC_DIR}/*.c)

add_executable(app ${SOURCES})
include_directories(app PRIVARE ${INC_DIR} ${CORE_DIR})

target_link_libraries(app stm32f303)
set_property(TARGET app PROPERTY CXX_STANDARD 17)
stm32_add_linker_script(app PRIVATE STM32F303VCTx_FLASH.ld)
stm32_add_flash_targets(app)
