#include <Arduino.h>
#include <CircularBuffer.h>

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

CircularBuffer<Rec, 3> buf;

void setup()
{
  // int x = 12;
  buf.push(Rec{millis(), 123});
  Serial.begin(115200);
  // buf.push(11);
  // buf.push(x);
  // if (x != buf.last()) // element se dodaje samo ako je razlicit od poslednjeg
  //   buf.push(x);

  Serial.println();
  for (decltype(buf)::index_t i = 0; i < buf.size(); i++)
    buf[i].println();
}

void loop()
{
  delay(100);
}