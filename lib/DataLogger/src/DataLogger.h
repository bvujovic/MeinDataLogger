#pragma once

#include "CircularBuffer.h"
#include <LittleFS.h>

template <typename T, size_t S>
class DataLogger
{
private:
    CircularBuffer<T, S> buf;
    //B File fp;
    const char *fileName;
    bool dumpLock = false;

    void setFileName(const char *fileName) { this->fileName = fileName; }

public:
    DataLogger(const char *);

    // Broj stavki u baferu.
    int size() { return buf.size(); }
    
    // Dohvatanje stavke iz bafera.
    T get(int idx) { return buf[idx]; }
    
    // Dohvatanje stavke iz bafera.
    const T &operator[](int i)
    {
        const T &obj = buf[i];
        return obj;
    }

    // Dodavanje stavke u bafer (kruznu listu).
    void add(T el)
    {
        if (!dumpLock)
            buf.push(el);
    }

    // Prosledjena funkcija se izvrsava za sve stavke u baferu.
    void forEach(void (*f)(void *));

    // Vraca ime fajla koje je prosledjeno konstruktoru.
    const char *getFileName() { return fileName; }

    // Prebacivanje podataka iz bafera u fajl.
    void dumpToFile(void (*)(void *, File &), bool clearBuffer = true);
    // mozda bi bilo dobro da se napravi varijanta da korisnik moze da odabere da se fajl
    // drzi otvoren tj. da dumpToFile() radi bez open/close fajla

    // Brisanje podataka u fajlu.
    void clearFile();
};

#include "DataLogger.tpp"