cmake_minimum_required(VERSION 3.13...3.27)

# initialize the SDK based on PICO_SDK_PATH
set(PICO_SDK_PATH /home/binod/Documents/pico-projects/pico-sdk/)

# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
# initialize the Raspberry Pi Pico SDK
pico_sdk_init()


# rest of your project
add_executable(blinky
    blinky.c
)


# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(blinky pico_stdlib)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(blinky)

pico_enable_stdio_usb(blinky 1)