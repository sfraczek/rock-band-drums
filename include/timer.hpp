#pragma once

#include <chrono>

struct Timer
{
    Timer() : begin(std::chrono::steady_clock::now()) {}

    bool IsItTime(std::chrono::milliseconds ms)
    {
        auto end = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(end - begin) >= ms)
        {
            begin = end;
            return true;
        }
        return false;
    }
    std::chrono::steady_clock::time_point begin;
};
