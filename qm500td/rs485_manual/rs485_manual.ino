#define PIN_DMX   3

uint8_t dmx_data[] = { LOW, LOW, LOW, HIGH };

void setup()
{
    pinMode(PIN_DMX, OUTPUT);
    digitalWrite(PIN_DMX, HIGH);
    delay(1000);
}

void loop()
{
    digitalWrite(PIN_DMX, LOW);
    delayMicroseconds(100);
    
    digitalWrite(PIN_DMX, HIGH);
    delayMicroseconds(12);
    
    digitalWrite(PIN_DMX, LOW);
    delayMicroseconds(4);
    digitalWrite(PIN_DMX, LOW);
    delayMicroseconds(28);
    digitalWrite(PIN_DMX, HIGH);
    delayMicroseconds(8);

    for (int i = 0; i < sizeof(dmx_data); ++i)
    {
        digitalWrite(PIN_DMX, LOW);
        delayMicroseconds(4);
        digitalWrite(PIN_DMX, dmx_data[i]);
        delayMicroseconds(28);
        digitalWrite(PIN_DMX, HIGH);
        delayMicroseconds(8);
    }
    
    digitalWrite(PIN_DMX, LOW);
    delayMicroseconds(4);
    digitalWrite(PIN_DMX, LOW);
    delayMicroseconds(28);
    digitalWrite(PIN_DMX, HIGH);
    delayMicroseconds(8);
    
    delay(10);
}
