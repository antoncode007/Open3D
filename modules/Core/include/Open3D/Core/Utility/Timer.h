// ----------------------------------------------------------------------------
// -                        Open3D: www.open-3d.org                            -
// ----------------------------------------------------------------------------
// Imported on Apr 11th, 2018 from the Open3D project
// Copyright (c) 2018 www.open3d.org
// released under MIT licence
//
// A fork of their project is avilable at legacy-code.open-3d.org
// Refer to http://legacy-code.open-3d.org/blob/master/LICENSE
// for their full licence
// Check http://legacy-code.open-3d.org/graphs/contributors
// to get the list of their contributors and their contributions
//
// The rights of any later updates or modifications are reserved
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018, Hamdi Sahloul - www.open-3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#pragma once

#include <string>

namespace open3d {

class Timer
{
public:
    Timer();
    ~Timer();

public:
    static double GetSystemTimeInMilliseconds();

public:
    void Start();
    void Stop();
    void Print(const std::string &timer_info) const;
    double GetDuration() const;

private:
    double start_time_in_milliseconds_;
    double end_time_in_milliseconds_;
};

class ScopeTimer : public Timer
{
public:
    ScopeTimer(const std::string &scope_timer_info = "");
    ~ScopeTimer();

private:
    std::string scope_timer_info_;
};

class FPSTimer : public Timer
{
public:
    FPSTimer(const std::string &fps_timer_info = "", int expectation = -1,
            double time_to_print = 3000.0, int events_to_print = 100);

    /// Function to signal an event
    /// It automatically prints FPS information when duration is more than
    /// time_to_print_, or event has been signaled events_to_print_ times.
    void Signal();

private:
    std::string fps_timer_info_;
    int expectation_;
    double time_to_print_;
    int events_to_print_;
    int event_fragment_count_;
    int event_total_count_;
};

}   // namespace open3d
