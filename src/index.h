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

#include <Arduino.h>

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>

<head>
    <title>Watering</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">

    <style>
        html {
            font-family: Helvetica;
            display: inline-block;
            margin: 0px auto;
            text-align: center;
            background-color: #2e2e2e;
            color: #e2e2e2;
        }

        .button {
            border: none;
            color: rgb(34, 34, 34);
            padding: 12px;
            text-decoration: none;
            background-color: #53fafa;
            font-size: 24px;
            margin: 2px;
            cursor: pointer;
            width: 120px;
            border-radius: 8px;
        }

        .outer {
            width: 100%;
            text-align: center;
        }

        .inner {
            display: inline-block;
        }


        .button.lg {
            background-color: #b9b9b9;
            width: 200px;
        }
    </style>
</head>


<body>
    <h2>Watering System</h2>
    <p>Manual control</p>
    <div class="outer">
        <div class="inner">
            <a href="/get?water=start"><button class="button"> START </button></a>
        </div>
        <div class="inner">
            <a href="/get?water=stop"><button class="button"> STOP </button></a>
        </div>
    </div>
    <br />
    <p>Schedule Event</p>
    <br />

    <form>
        <input type="datetime-local" id="event_time" name="event_time">
        <input class="button lg" type="submit" value="Schedule">
    </form>
</body>

</html>
)rawliteral";