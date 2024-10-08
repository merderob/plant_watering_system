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

#include "sensor.h"

void Sensor::init()
{
    enabled_ = Params::sensor_enabled;
    sensor_pin_ = Params::sensor_pin;
    min_sensor_value_ = Params::min_sensor_value;
    pinMode(sensor_pin_, INPUT);
}

void Sensor::read()
{
    cur_sensor_value_ = analogRead(sensor_pin_);
}

bool Sensor::waterLevelOk() const
{
#ifdef DEBUG
    Serial.print("Sensor value: ");
    Serial.println(cur_sensor_value_);
    return true;
#endif
    if (!enabled_)
    {
        return true;
    }
    return cur_sensor_value_ > min_sensor_value_;
}

uint16_t Sensor::getValue() const
{
    return cur_sensor_value_;
}

#ifdef DEBUG
void Sensor::log()
{
    Serial.print("Sensor value: ");
    Serial.println(cur_sensor_value_);
}
#endif
