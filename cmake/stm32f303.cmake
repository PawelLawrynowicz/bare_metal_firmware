# Make sure that git submodule is initialized and updated
set(LIBOPENCM3_DIR ${CMAKE_SOURCE_DIR}/libopencm3)

if(NOT EXISTS ${LIBOPENCM3_DIR}/Makefile)
  message(FATAL_ERROR "libopencm3 submodule not found. Initialize with 'git submodule update --init' in the source directory")
endif()

set(LIBOPENCM3_INC_DIR ${LIBOPENCM3_DIR}/include)

# create a target to build libopencm3 -- only for the target we need
add_custom_target(libopencm3 make TARGETS=stm32/f3 WORKING_DIRECTORY ${LIBOPENCM3_DIR})

# Create a specific CPU target with the appropriate options etc
add_library(stm32f303 STATIC IMPORTED)
set_property(TARGET stm32f303 PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${LIBOPENCM3_DIR}/include)
set_property(TARGET stm32f303 PROPERTY IMPORTED_LOCATION ${LIBOPENCM3_DIR}/lib/libopencm3_stm32f3.a)
add_dependencies(stm32f303 libopencm3)
target_link_directories(stm32f303 INTERFACE ${LIBOPENCM3_DIR}/lib)

target_compile_definitions(stm32f303 INTERFACE -DSTM32F3)

set(COMPILE_OPTIONS
  --static
  -nostartfiles
  -fno-common
  -mcpu=cortex-m4
  -mthumb
  -mfloat-abi=hard
  -mfpu=fpv5-d16
)
target_compile_options(stm32f303 INTERFACE ${COMPILE_OPTIONS})
target_link_options(stm32f303 INTERFACE ${COMPILE_OPTIONS})

function(stm32_add_flash_targets TARGET)
  add_custom_target(${TARGET}-stlink-flash
    bash -c "openocd -f /usr/share/openocd/scripts/interface/stlink-v2.cfg \
                -f /usr/share/openocd/scripts/target/stm32f3x.cfg \
                -c 'reset_config none; program ${TARGET}.elf verify reset exit'"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS ${TARGET}
    VERBATIM
  )
endfunction()