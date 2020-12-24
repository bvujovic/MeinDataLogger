#include <Arduino.h>
#include "DataLogger.h"

// Pamti promenu vrednosti na nekom digitalnom pinu. Prikazuje sve promene prilikom sledeceg reseta.

struct Rec
{
    ulong ms;
    bool val;
};

void dumpToFile(void *obj, File &fp)
{
    Rec *r = (Rec *)obj;
    fp.printf("%5ld %8s \n", r->ms % 100000, r->val ? "HIGH" : "LOW");
}

DataLogger<Rec, 20> vals("/vals.txt", dumpToFile);

void forEach(void *obj)
{
    Rec *r = (Rec *)obj;
    Serial.println(r->val);
    // fp.print(r->ms);
    // fp.print('\t');
    // fp.println(r->val ? "HIGH" : "LOW");
}
// vals.forEach(forEach);

const int pinButton = D1;
bool valButton = 1;

void setup()
{
    pinMode(pinButton, INPUT_PULLUP);

    Serial.begin(115200);
    Serial.println();

    Serial.println("Fajl:");
    Serial.println(vals.readFromFile());
}

void loop()
{
    delay(20);

    bool newValButton = digitalRead(pinButton);
    if (valButton != newValButton)
    {
        Serial.println(newValButton ? "HI" : "LO");
        ulong ms = millis();
        valButton = newValButton;
        // vals.add(Rec{millis(), valButton});
        // vals.saveToFile(dumpToFile, true);

        // vals.addSave(Rec{millis(), valButton}, dumpToFile);

        // vals.addSave(Rec{millis(), valButton});

        vals.addSaveDelayed(Rec{millis(), valButton});

        Serial.println(millis() - ms);
    }

    vals.refresh(millis());
}