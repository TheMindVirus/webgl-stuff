#include <DmxSimple.h>

const size_t bufsz = 1 + 512;
uint8_t buffer[bufsz] = {};
size_t pos = 0;
size_t count = 0;

void setup()
{
    Serial.begin(250000, SERIAL_8N2);
}

void loop()
{
    int n = Serial.available();
    for (int i = 0; i < n; ++i)
    {
        buffer[pos] = Serial.read();
        count = 0;
        pos += 1;
        if (pos >= bufsz)
        {
            for (int j = 0; j < bufsz; ++j)
            {
                DmxSimple.write(j, buffer[j]);
            }
            Serial.println(bufsz);
            pos = 0;
        }
    }
    if (count > 1000) { pos = 0; }
    delay(1);
}
