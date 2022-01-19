# Non Blocking VL53L5CX library
This is library is based on ST's ultralite driver STSW-IMG023. It has been expanded to support non blocking reading and writing.

## docs
A majority of the funtions are the same as the official ST library. [See their documentation](docs/VL53L5CX_ULD_UM2884.pdf)


### platform
```
typedef struct
{
    uint16_t  			address;
	I2C_HandleTypeDef 	*hi2c;

} VL53L5CX_Platform;
```
The platform struct contains an address and the HAL i2c handler.

### Non blocking functions
All non blocking funtions can be found in the vl53l5cx_plugin_async.h file