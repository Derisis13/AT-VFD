cmake_minimum_required(VERSION 3.21)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_STANDARD 99)
project(vfdprog C)

set(CMAKE_C_COMPILER avr-gcc)
set(TARGET_CPU ATmega88)

add_compile_definitions("__AVR_${TARGET_CPU}__")
include_directories(/usr/lib/avr/include)
set(CMAKE_C_FLAGS "-O3 -Wall")

add_link_options(-Wl,--print-memory-usage)
add_executable(${PROJECT_NAME} main.c)

add_custom_target(
        FLASH
        avrdude -p ${TARGET_CPU} -c USBasp -v -U flash:w:${PROJECT_BINARY_DIR}/${PROJECT_NAME}:a
        DEPENDS ${PROJECT_NAME}
        COMMENT "Flash to ${TARGET_CPU}"
)