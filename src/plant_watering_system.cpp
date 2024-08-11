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

#include "plant_watering_system.h"

void PlantWateringSystem::init()
{
    max_watering_duration_s_ = Params::max_watering_duration_s;
    valve_pump_delay_ms_ = Params::valve_pump_delay_ms;

    pump_.init();
    valve_.init();
    sensor_.init();
    clock_.init();
}

void PlantWateringSystem::executeStandby()
{
    if (!events_.empty())
    {
        int remove_index = -1;
        for (size_t id = 0; id < events_.size(); id++)
        {
            if (events_[id].getStartTime() <= clock_.getTime())
            {
                const auto &event = events_[id];
                active_event_ = std::unique_ptr<WateringEvent>(new WateringEvent(event.getStartTime(), event.getEndTime(), event.isValid()));
                remove_index = id;
                if (!startWatering())
                {
                    return;
                }
                break;
            }
        }
        if (remove_index != -1)
        {
            events_.erase(events_.begin() + remove_index);
        }
    }
}

void PlantWateringSystem::executeWatering()
{
    if (watering_started_at_ + max_watering_duration_s_ <= clock_.getTime())
    {
        stopWatering();
        return;
    }

    if (active_event_ == nullptr)
    {
        return;
    }

    if (active_event_->getEndTime() <= clock_.getTime())
    {
        active_event_ = nullptr;
        stopWatering();
    }
}

void PlantWateringSystem::execute()
{
    clock_.update();
    sensor_.read();
    switch (state_)
    {
    case State::STANDBY:
        executeStandby();
        break;
    case State::WATERING:
        executeWatering();
        break;
    }
}

bool PlantWateringSystem::startWatering()
{
    if (!sensor_.waterLevelOk())
    {
#ifdef DEBUG
        Serial.print("Water level not ok, cannot start watering: ");
        Serial.println(sensor_.getValue());
#endif
        return false;
    }
    valve_.open();
    delay(valve_pump_delay_ms_);
    pump_.enable();
    state_ = State::WATERING;
    watering_started_at_ = clock_.getTime();
    return true;
}

void PlantWateringSystem::stopWatering()
{
    pump_.disable();
    valve_.close();
    state_ = State::STANDBY;
}

void PlantWateringSystem::addWateringEvent(WateringEvent event)
{
    if (event.isValid())
    {
        events_.push_back(event);
    }
#ifdef DEBUG
    else
    {
        Serial.println("Invalid event received");
    }
#endif
}

std::vector<std::string> PlantWateringSystem::getEvents() const
{
    std::vector<std::string> ret;
    for (const auto &event : events_)
    {
        ret.push_back(clock_.timeToString(event.getStartTime()));
    }
    return ret;
}
