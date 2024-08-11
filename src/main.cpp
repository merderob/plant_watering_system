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
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "../credentials/credentials.h"
#include "plant_watering_system.h"
#include "index.h"
#include "command_translator.h"

unsigned long exec_period_ms = 100; 
unsigned long prev_exec_time_ms = 0;

PlantWateringSystem system_;
AsyncWebServer server(80);
CommandTranslator translator;

JsonDocument events;

// IP: ...192.168.0.185

namespace frontend
{
    const char* water_param = "water";
    const char* event_param = "event_time";
}

void notFound(AsyncWebServerRequest *request) 
{
    request->send(404, "text/plain", "Not found");
}

void setup()
{
#ifdef DEBUG
    Serial.begin(9600);
#endif

    WiFi.begin(Credentials::ssid.c_str(), Credentials::password.c_str());
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
#ifdef DEBUG
    Serial.println(WiFi.localIP());
#endif

    system_.init();

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send(200, "text/html", index_html);
    });

    server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) 
    {
        if (request->hasParam(frontend::water_param)) 
        {
            const auto command = request->getParam(frontend::water_param)->value();
            const auto event = translator.translateManualCommand(command);
            if (event == WateringCommand::START)
            {
                system_.startWatering();
            }
            else
            {
                system_.stopWatering();
            }
        }
        else if (request->hasParam(frontend::event_param))
        {
            const auto command = request->getParam(frontend::event_param)->value();
            const auto event = translator.translateScheduleCommand(command);
            system_.addWateringEvent(event);

        }
        request->send(200, "text/html", index_html);
    });

    server.on("/events", HTTP_GET, [](AsyncWebServerRequest* request)
    {
        const auto& events_vec = system_.getEvents();
        for (const auto& event: events_vec)
        {
            events.add(event);
        }
        String response;
        serializeJson(events, response);
        request->send(200, "application/json", response);
        events.clear();
    });

    server.onNotFound(notFound);

    server.begin();
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
