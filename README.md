# AT-VFD
Goal: Controlling a VFD with an Atmel microcontroller
<br>
Compatible hardware: [Princeton PT6302](https://pdf1.alldatasheet.com/datasheet-pdf/view/391603/PTC/PT6302.html), [OKI ML9208](https://pdf1.alldatasheet.com/datasheet-pdf/view/135132/OKI/ML9208.html) (note that in naming the PT6302 datasheeet is followed)
<br>
Project is work in progress, breaing changes might come in the future

## Using the driver library
Modify PT6302.h
- Re-define the macro `DISPLAY_DIGITS` to the number of digits on your VFD
- replace the pins in `enum pins` with th pins you have wired to the given controller interface pins 

Include the PT6302.h in your application and use the functions to display whatever you want.

## Building
Use **either** [GNU make](#GNU-make) or [CMake](#CMake) whichever you're familiar with.
### Dependencies
The project uses `avr-libc` as well as `avr-gcc`, please install the packages neccesary. For building you need either GNU make or CMake.
If you're using CLion, it should automatically pick up on `CMakeLists.txt`, but you still need to modify it to your hardware.

### GNU make
Modify `Makefile`:
- Change `MCU` to your target microcontroller
- Change `F_CPU` to the frequency of your microcontroller's clock source
- In `CFLAGS` make sure that the path after `I` is where you have your avr c libraries
- `TARGET` should be the project name (or keep it as is, it doesn't matter)
- In `SRCS` replace `main` with your application's c and header files
- Change the avrdude command in `flash` to the device and port you're using for downloading the firmware

Then in the project directory run 
```shell
make && make flash
``` 
to compile and download firmware.

### CMake
Modify `CMakeLists.txt`:
- Change `TARGET_CPU` to your target microcontroller (in the `set` statement)
- Change `F_CPU` to the frequency of your microcontroller's clock source (in the `set` statement)
- Put the full path to your avr c libraries int the `include_directories` statement
- Replace `main.c` with the name of your c source and header files in the `add_executable` statement 
- Change the avrdude command in the custom targeg`FLASH` to the device and port you're using for downloading the firmware

Create a building directory for cmake and change into it: 
```shell
 mkdir cmake-build-debug && cd cmake-build-debug
 ```
Then compile, link and flash:
```shell
cmake ..  && cmake --build . -t FLASH
```
