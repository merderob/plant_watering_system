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

#include "command_translator.h"

WateringCommand CommandTranslator::translateManualCommand(const String &command)
{
    if (command == "start")
    {
        return WateringCommand::START;
    }
    return WateringCommand::STOP;
}

WateringEvent CommandTranslator::translateScheduleCommand(const String &command)
{
    if (!checkScheduleCommand(command))
    {
#ifdef DEBUG
        Serial.print("Incorrect command received: ");
        Serial.println(command);
#endif
        return {};
    }

    const auto yr = command.substring(0, 4);
    const auto mth = command.substring(5, 7);
    const auto day = command.substring(8, 10);
    const auto hr = command.substring(11, 13);
    const auto min = command.substring(14, 16);

    tmElements_t tm;
    tm.Hour = hr.toInt();
    tm.Minute = min.toInt();
    tm.Second = 0;
    tm.Day = day.toInt();
    tm.Month = mth.toInt();
    tm.Year = yr.toInt() - 1970;
    time_t start_time = makeTime(tm);
    time_t end_time = start_time + 5; // 5s
    return WateringEvent (start_time, end_time, true);
}

bool CommandTranslator::checkScheduleCommand(const String &command)
{
    if (command.length() != 16 || command[4] != '-' || command[7] != '-' || command[10] != 'T' || command[13] != ':')
    {
        return false;
    }
    return true;
}
