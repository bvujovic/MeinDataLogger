#include <Arduino.h>
#include <CircularBuffer.h>

CircularBuffer<const char *, 3> buf;

void setup()
{
  Serial.begin(115200);

  buf.push("Misha");
  buf.push("Kostic");
  buf.push("Panta");
  buf.push("Bojan");
  buf.push("Bole");

  Serial.println();
  for (decltype(buf)::index_t i = 0; i < buf.size(); i++)
    Serial.println(buf[i]);

  Serial.println();
  Serial.println(buf.size());
  Serial.println();

  // petlja je malo preuredjena jer nema smisla da se napise uslov i>=0
  // jer je to uvek ispunjeno za neki uint koji se koristi za i
  for (decltype(buf)::index_t i = buf.size() - 1;; i--)
  {
    Serial.println(buf[i]);
    if (i == 0)
      break;
  }
}

void loop()
{
  delay(100);
}
