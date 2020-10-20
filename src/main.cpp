#include <Arduino.h>
#include "DataLogger.h"

// https://github.com/rlogiacco/CircularBuffer/blob/master/examples/Struct/Struct.ino
// https://github.com/rlogiacco/CircularBuffer/blob/master/examples/Interrupts/Interrupts.ino

typedef struct
{
  ulong ms;
  int val;

  void println() {
    Serial.print(ms);
    Serial.print('\t');
    Serial.println(val);
  }
} Rec;

DataLogger<Rec, 3> dl;

void setup()
{
  Serial.begin(115200);
  Serial.println();

  dl.add(Rec {millis(), 123});
  dl.add(Rec {2222, -123});
  dl.add(Rec {millis(), 247});

  // dl.get(0).println();
  // dl.get(1).println();

  // for (int i = 0; i < dl.size(); i++)
  //   dl.get(i).println();

}

void loop()
{
  delay(100);
}
