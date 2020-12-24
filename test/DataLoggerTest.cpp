#include <Arduino.h>
#include "DataLogger.h"

// https://github.com/rlogiacco/CircularBuffer/blob/master/examples/Struct/Struct.ino
// https://github.com/rlogiacco/CircularBuffer/blob/master/examples/Interrupts/Interrupts.ino

typedef struct
{
  ulong ms;
  int val;
} Rec;

DataLogger<Rec, 3> dl("/dl.txt");
DataLogger<String, 10> dls("/strings.txt");

// void recPrintln(void *obj)
// {
//   Rec *r = (Rec *)obj;
//   Serial.print(r->ms);
//   Serial.print('\t');
//   Serial.println(r->val);
// }

void dumpToFile(void *obj, File &fp)
{
  Rec *r = (Rec *)obj;
  fp.print(r->ms);
  fp.print('\t');
  fp.println(r->val);
}

void setup()
{
  Serial.begin(115200);
  Serial.println();

  dl.add(Rec{millis(), 123});
  dl.add(Rec{2222, -123});
  dl.add(Rec{millis(), 247});
  // dl.forEach(recPrintln);
  dl.dumpToFile(dumpToFile);
  dl.add(Rec{millis(), 333});
  dl.dumpToFile(dumpToFile);
  dl.add(Rec{millis(), 444});
  dl.dumpToFile(dumpToFile);
  dl.add(Rec{millis(), 555});
  dl.dumpToFile(dumpToFile);

  File fp = LittleFS.open(dl.getFileName(), "r");
  String s = "";
  if (fp)
  {
    Serial.print("File size: ");
    Serial.println(fp.size());
    Serial.print(fp.readString());
    Serial.println("*** END ***");
    fp.close();
  }
  else
    Serial.println("Fajl nije otvoren za citanje.");
}

void loop()
{
  delay(100);
}
