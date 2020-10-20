#include "DataLogger.h"

// template <typename T>
// DataLogger::DataLogger(/* args */)
// {
// }

template <typename T, size_t S>
void DataLogger<T,S>::add(T el)
{
    buf.push(el);
}

template <typename T, size_t S>
T DataLogger<T,S>::get(int idx)
{
    return buf[idx];
}
