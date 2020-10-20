#include <Arduino.h>
#include <CircularBuffer.h>

CircularBuffer<int, 3> buf;

void setup()
{
  Serial.begin(115200);

  buf.push(10);
  buf.push(11);
  buf.push(12);
  buf.push(13);

  Serial.println();
  for (decltype(buf)::index_t i = 0; i < buf.size(); i++)
    Serial.println(buf[i]);
}

void loop()
{
  delay(100);
}