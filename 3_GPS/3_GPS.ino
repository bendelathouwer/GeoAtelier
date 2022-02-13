#include <TinyGPSPlus.h> // https://github.com/mikalhart/TinyGPSPlus
#include <SoftwareSerial.h>

const uint8_t RXPin = D5;
const uint8_t TXPin = D6;
const uint32_t GPSBaud = 9600;

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(115200);
  while (!Serial) {}
  delay(1000);
  Serial.println();

  ss.begin(GPSBaud);
}

void loop()
{
  // Dispatch incoming characters
  while (ss.available() > 0)
    gps.encode(ss.read());

  if (gps.location.isUpdated() || gps.altitude.isUpdated())
  {
    if (gps.location.isValid() && gps.altitude.isValid()) {
      Serial.print(F("LOCATION   Fix Age="));
      Serial.print(gps.location.age());
      Serial.print(F(" Lat="));
      Serial.print(gps.location.lat(), 6);
      Serial.print(F(" Long="));
      Serial.print(gps.location.lng(), 6);
      Serial.print(F(" Meters="));
      Serial.println(gps.altitude.meters());
    }

  }
  if (gps.date.isUpdated() || gps.time.isUpdated())
  {
    if (gps.date.isValid() && gps.time.isValid()) {
      char s[80];
      sprintf(s, "%04d-%02d-%02dT%02d:%02d:%02d.%02dZ", gps.date.year(), gps.date.month(), gps.date.day(), gps.time.hour(), gps.time.minute(), gps.time.second(), gps.time.centisecond());
      Serial.print(F("DATETIME   Fix Age="));
      Serial.print(gps.time.age());
      Serial.print(F(" "));
      Serial.println(s);
    }
  }

  if (gps.charsProcessed() < 10)
    Serial.println(F("WARNING: No GPS data. Check wiring."));
}
