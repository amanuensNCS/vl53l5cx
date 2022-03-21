# Non Blocking VL53L5CX library
This is library is based on ST's ultralite driver STSW-IMG023. It has been expanded to support non blocking reading and writing.

## docs
A majority of the funtions are the same as the official ST library. [See their documentation](docs/VL53L5CX_ULD_UM2884.pdf)
What we have added to the library are interrupt based non blocking functions to read from these sensors.  

### platform
This struct needs to be provided to the library and conatins information what i2c address the sensor has and a pointer to an i2c handler.
```
typedef struct
{
    uint16_t  			address;
    I2C_HandleTypeDef 	*hi2c;

} VL53L5CX_Platform;
```

### Non blocking functions
All non blocking funtions can be found in the vl53l5cx_plugin_async.h file

## examples
An example implementation is availabe for the CM7 core on a stm32H755xx.
