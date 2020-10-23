#include "DataLogger.h"

template <typename T, size_t S>
DataLogger<T, S>::DataLogger(const char *fileName)
{
    LittleFS.begin();
    setFileName(fileName);
    clearFile();
}

template <typename T, size_t S>
void DataLogger<T, S>::forEach(void (*f)(void *))
{
    for (int i = 0; i < size(); i++)
    {
        // f(&(buf[i]));
        T obj = buf[i];
        f(&obj);
    }
}

template <typename T, size_t S>
void DataLogger<T, S>::dumpToFile(void (*f)(void *, File &), bool clearBufferAfter)
{
    File fp = LittleFS.open(fileName, "a");
    dumpLock = true;
    for (int i = 0; i < size(); i++)
    {
        T obj = buf[i];
        f(&obj, fp);
    }
    if (clearBufferAfter)
        buf.clear();
    dumpLock = false;
    fp.close();
}

template <typename T, size_t S>
void DataLogger<T, S>::clearFile()
{
    File fp = LittleFS.open(fileName, "w");
    if (fp)
        fp.close();
}