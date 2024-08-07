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

#include <Arduino.h>
#include <WiFi.h>
#include "../credentials/credentials.h"
#include "plant_watering_system.h"

unsigned long exec_period_ms = 100; 
unsigned long prev_exec_time_ms = 0;

PlantWateringSystem system_;

// iip: ...192.168.0.185

void setup()
{
    WiFi.begin(Credentials::ssid.c_str(), Credentials::password.c_str());
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
    system_.init();
}

void loop()
{
    const auto time_ms = millis();
    if (time_ms - prev_exec_time_ms > exec_period_ms)
    {
        system_.execute();
        prev_exec_time_ms = time_ms;
    }
}
