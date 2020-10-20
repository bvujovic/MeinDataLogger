#pragma once

#include "CircularBuffer.h"

template <typename T, size_t S>
// template <typename T>
class DataLogger
{
private:
    //TODO parametrizovati kapacitet bafera
    CircularBuffer<T, S> buf;

public:
    // DataLogger(/* args */);

    void add(T el);
    T get(int idx);
};

#include "DataLogger.tpp"