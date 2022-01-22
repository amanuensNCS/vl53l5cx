#include <stdint.h>
#include "vl53l5cx_api.h"

uint8_t vl53l5cx_check_data_ready_async_start(VL53L5CX_Configuration *p_dev);
uint8_t vl53l5cx_check_data_ready_async_in_progress(VL53L5CX_Configuration *p_dev);
uint8_t vl53l5cx_check_data_ready_async_finish(VL53L5CX_Configuration *p_dev,
		uint8_t *p_result);

uint8_t vl53l5cx_get_ranging_data_async_start(VL53L5CX_Configuration *p_dev);
uint8_t vl53l5cx_get_ranging_data_async_in_progress(VL53L5CX_Configuration *p_dev);
uint8_t vl53l5cx_get_ranging_data_async_finish(VL53L5CX_Configuration *p_dev,
		VL53L5CX_ResultsData *p_results);
