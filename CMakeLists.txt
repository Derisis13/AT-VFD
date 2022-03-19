cmake_minimum_required(VERSION 3.21)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_STANDARD 99)
project(vfdprog C)

set(CMAKE_C_COMPILER avr-gcc)
set(OBJCOPY avr-objcopy)
set(TARGET_CPU atmega88)

add_compile_definitions("__AVR_${TARGET_CPU}__" "F_CPU=8000000UL")
include_directories(/usr/lib/avr/include)
set(CMAKE_C_FLAGS "-Os -mcall-prologues -mmcu=${TARGET_CPU} -Wall")

add_link_options(-Wl,--print-memory-usage)
add_executable(${PROJECT_NAME}.bin main.c PT6302.c PT6302.h)

add_custom_target(
        FLASH
        ${OBJCOPY} -j .text -j .data -O ihex ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex &&
        avrdude -p ${TARGET_CPU} -c USBasp -v -U flash:w:${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex:a
        DEPENDS ${PROJECT_NAME}.bin
        COMMENT "Flash to ${TARGET_CPU}"
)