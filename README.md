# Non Blocking VL53L5CX library
The goal of this libarary is to provide a non blocking way to use the vl53l5cx sensors (also refered to as TOF sensors in the context of this project) by modifying ST's standard vl53l5cx library.

ST provides an "Ultra Light Driver" (ULD) to get interface with the TOF sensors but the drivers has the limitation that it does not support a non blocking way to get sensor data without using an interrupt pin. We have extended this ULD with some functions to enable an interrupt based non blocking method of receiving data. Functions implemented by us all contain "async" somewhere in its name and are all found in [platform.c](src/platform.c), [vl53l5cx_plugin_async.c](src/vl53l5cx_plugin_async.c) or [vl53l5cx_plugin_async.h](inc/vl53l5cx_plugin_async.h). 

## Installation

Copy the src and inc folders into your project. Depending on the platform you might have to change the platform.c to implement basic writing and reading to the sensor. Our platform.c contains HAL code that worked on a STM32H7 chip. The library then requires you pass it an I2C HAL handle as well as the i2c address for the sensor (see the platform header below). 

You will also have to write an interrupt service routine to use the sensors in an async manner. Explanation of this is described below and you can also see the example project's [main file](examples/h755_vl53l5cx/CM7/Core/Src/main.c) to see one way to implement it. All our code is tagged with "NCS BEGIN <our code> NCS END" so that you can search for it. 

## How to use

### Configuration av sensors

Configuration of the sensor is done just like with ST's ULD and docs can be found [here](docs/VL53L5CX_ULD_UM2884.pdf).

### Fetching data blocking

See page 14 of [UM2884](docs/VL53L5CX_ULD_UM2884.pdf).

### Fetching data async

The async API implements two features, one to get the latest measurment, and a second one to check if a new measurment has been made since the last read measurment.
Each such feature is implemented using 3 functions, an "*_async_start()", an "*_async_in_progress()" and an "*_async_finish()" and the workflow of using these function is to

1. Use "*_async_start()" to initlize the call. This will send some i2c commando to the tof sensor.
2. In the I2C interrupt, check for *_async_in_progress()". This only reads a local boolean if the the last initilized call was of this type.
3. If *_async_in_progress()" returns true then you can collect the data with the "*_async_finish()" function.

If one just wants the latest measurment without caring about if a new measurement has been taken since last measurement then you can directly use "vl53l5cx_get_ranging_data_async_start()". Otherwise you can use "vl53l5cx_check_data_ready_async_start()" and if after the steps above "vl53l5cx_check_data_ready_async_finish()" indicated that new data is ready then you can initilize with  "vl53l5cx_get_ranging_data_async_start()" as normal.

### platform
For the library to work you need to provide a struct with the i2c address of the sensor and a pointer to an i2c handler.
```
typedef struct
{
    uint16_t  			address;
    I2C_HandleTypeDef 	*hi2c;

} VL53L5CX_Platform;
```

### Non blocking functions
All non blocking funtions can be found in the vl53l5cx_plugin_async.h file as well as one "writeAsync()" function in platform.c

## examples
An example implementation is availabe for the CM7 core on a stm32H755xx under the [example](examples). The whole h755_vl53l5cx folder should be selected when importing into STM32CubeIDE. Our own code in the files specified in the beggining and in the main.c file where it is tagged with "NCS BEGIN" and "NCS END". The example code assumues use of the [53l5A1 breakout board](https://www.st.com/en/evaluation-tools/x-nucleo-53l5a1.html) for pinout.
