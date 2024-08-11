// Copyright © 2024 Robert Takacs
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
// files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
// is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#pragma once

#include <stdint.h>

// #define DEBUG

struct Params
{
    /// @brief The relay pin which enables the pump.
    static const uint8_t pump_relay_pin = 15;
    /// @brief The relay pin which enables the valve.
    static const uint8_t valve_relay_pin = 12;
    /// @brief Stores if the water level sensor is enabled.
    static const bool sensor_enabled = false;
    /// @brief The pin used for reading the sensor's measurements.
    static const uint8_t sensor_pin = 33;
    /// @brief The minival sensor value to accept as being "underwater".
    static const uint16_t min_sensor_value = 2000;
    /// @brief The NTP offset in hours.
    static const long ntp_offset = 0;
    /// @brief The NTP polling interval.
    static const unsigned long ntp_interval_ms =  60 * 1000;
    /// @brief The delay to enable the pump after opening the valve.
    static const uint32_t valve_pump_delay_ms = 500;
    /// @brief The maximum watering duration.
    static const uint32_t max_watering_duration_s = 60;
};
