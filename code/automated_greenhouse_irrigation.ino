/*
  Otomatik Sera Sulama Sistemi
  Geliştirici: Mehmet Efe Demirel

  Donanım:
  - Arduino Uno
  - DS3231 RTC modülü
  - 1 kanal röle modülü
  - Pompa / vana / test yükü

  Açıklama:
  Sistem, RTC modülünden aldığı saat bilgisine göre belirlenen sulama
  zamanlarında röleyi aktif eder. Röle belirlenen süre boyunca açık kalır,
  ardından kapanır.
*/

#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

const byte RELAY_PIN = 7;

// Birçok röle modülü LOW sinyal ile aktif olur. Kullandığın röle HIGH ile aktifse
// RELAY_ACTIVE_STATE ve RELAY_PASSIVE_STATE değerlerini ters çevir.
const byte RELAY_ACTIVE_STATE = LOW;
const byte RELAY_PASSIVE_STATE = HIGH;

const unsigned long WATERING_DURATION_MS = 10000; // 10 saniye

struct WateringTime {
  byte hour;
  byte minute;
};

// Örnek sulama saatleri: 08:00 ve 18:00
WateringTime wateringTimes[] = {
  {8, 0},
  {18, 0}
};

const byte WATERING_TIME_COUNT = sizeof(wateringTimes) / sizeof(wateringTimes[0]);

bool wateringActive = false;
bool wateredThisMinute = false;
unsigned long wateringStartTime = 0;
int lastCheckedMinute = -1;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, RELAY_PASSIVE_STATE);

  if (!rtc.begin()) {
    Serial.println("RTC modulu bulunamadi. Baglantilari kontrol edin.");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC guc kaybetmis. Saat bilgisini bilgisayar saatine gore ayarliyorum.");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  Serial.println("Otomatik sera sulama sistemi baslatildi.");
}

void loop() {
  DateTime now = rtc.now();

  resetMinuteFlagIfNeeded(now);

  if (!wateringActive && !wateredThisMinute && isWateringTime(now)) {
    startWatering();
    wateredThisMinute = true;
  }

  if (wateringActive && millis() - wateringStartTime >= WATERING_DURATION_MS) {
    stopWatering();
  }

  printTime(now);
  delay(1000);
}

bool isWateringTime(DateTime now) {
  for (byte i = 0; i < WATERING_TIME_COUNT; i++) {
    if (now.hour() == wateringTimes[i].hour && now.minute() == wateringTimes[i].minute) {
      return true;
    }
  }
  return false;
}

void startWatering() {
  wateringActive = true;
  wateringStartTime = millis();
  digitalWrite(RELAY_PIN, RELAY_ACTIVE_STATE);
  Serial.println("Sulama basladi.");
}

void stopWatering() {
  wateringActive = false;
  digitalWrite(RELAY_PIN, RELAY_PASSIVE_STATE);
  Serial.println("Sulama tamamlandi.");
}

void resetMinuteFlagIfNeeded(DateTime now) {
  if (now.minute() != lastCheckedMinute) {
    lastCheckedMinute = now.minute();
    wateredThisMinute = false;
  }
}

void printTime(DateTime now) {
  Serial.print("Saat: ");
  printTwoDigits(now.hour());
  Serial.print(":");
  printTwoDigits(now.minute());
  Serial.print(":");
  printTwoDigits(now.second());
  Serial.print(" | Role: ");
  Serial.println(wateringActive ? "AKTIF" : "PASIF");
}

void printTwoDigits(int number) {
  if (number < 10) {
    Serial.print("0");
  }
  Serial.print(number);
}
