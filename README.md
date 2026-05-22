# Otomatik Sera Sulama Sistemi

Arduino Uno, DS3231 RTC modülü ve röle modülü kullanılarak belirlenen zamanlarda sulama işlemini otomatikleştiren mikrodenetleyici tabanlı sera sulama prototipi.

## Proje Amacı

Küçük ölçekli sera veya bitki yetiştirme uygulamalarında sulama işleminin manuel müdahale gerektirmeden, önceden belirlenen zamanlarda otomatik olarak yapılması hedeflenmiştir.

Bu proje ile zaman tabanlı kontrol, röle ile yük sürme ve Arduino tabanlı otomasyon mantığı uygulanmıştır.

## Kullanılan Bileşenler

| Bileşen | Görev |
|---|---|
| Arduino Uno | Ana kontrol birimi |
| DS3231 RTC Modülü | Gerçek zaman bilgisini tutma |
| Röle Modülü | Pompa / vana çıkışını kontrol etme |
| 9V Pil / Harici Güç | Sistemi besleme |
| Jumper kablolar | Devre bağlantıları |
| Pompa, vana veya test yükü | Sulama çıkışı / test çıkışı |

## Gerekli Arduino Kütüphanesi

Bu proje için Arduino IDE üzerinden aşağıdaki kütüphane kurulmalıdır:

- **RTClib by Adafruit**

Kurulum yolu:

```text
Arduino IDE → Tools / Araçlar → Manage Libraries / Kütüphaneleri Yönet → RTClib → Install
```

## Çalışma Mantığı

1. Arduino, DS3231 RTC modülünden saat ve dakika bilgisini okur.
2. Yazılımda tanımlanan sulama zamanı ile mevcut zaman karşılaştırılır.
3. Saat ve dakika eşleştiğinde röle çıkışı aktif edilir.
4. Röle belirlenen süre boyunca açık kalır.
5. Süre tamamlandığında röle kapatılır ve sistem tekrar bekleme durumuna döner.

## Varsayılan Yazılım Ayarları

Kod içinde örnek olarak sistemin her gün **08:00** ve **18:00** saatlerinde **10 saniye** çalışması ayarlanmıştır.

Bu değerleri `wateringTimes` ve `WATERING_DURATION_MS` değişkenlerinden değiştirebilirsin.

```cpp
const unsigned long WATERING_DURATION_MS = 10000;
WateringTime wateringTimes[] = {{8, 0}, {18, 0}};
```

## Bağlantı Özeti

| Modül | Arduino Uno Bağlantısı |
|---|---|
| DS3231 VCC | 5V |
| DS3231 GND | GND |
| DS3231 SDA | A4 |
| DS3231 SCL | A5 |
| Röle VCC | 5V |
| Röle GND | GND |
| Röle IN | D7 |

Daha detaylı bağlantı açıklaması için: [`docs/wiring.md`](docs/wiring.md)

## Devre Şeması

Basit bağlantı şeması için: [`images/automated-greenhouse-wiring.svg`](images/automated-greenhouse-wiring.svg)

## Dosya Yapısı

```text
automated-greenhouse/
├── README.md
├── code/
│   └── automated_greenhouse_irrigation.ino
├── docs/
│   └── wiring.md
└── images/
    └── automated-greenhouse-wiring.svg
```

## Test ve Sonuç

Sistem, RTC modülünden alınan zaman bilgisinin Arduino tarafından okunması ve belirlenen saatlerde röle çıkışının tetiklenmesi üzerine test edilmiştir. Test sürecinde rölenin zaman koşulu sağlandığında aktif olduğu, belirlenen süre tamamlandığında ise tekrar kapandığı gözlemlenmiştir.

Bu prototip, temel zaman tabanlı sulama otomasyonu için çalışır bir yapı sunar. Gelecek aşamada toprak nem sensörü eklenerek sistem yalnızca zamana bağlı değil, sensör verisine göre karar veren kapalı çevrim bir sulama sistemine dönüştürülebilir.

## Gelecek Geliştirmeler

- Toprak nem sensörü ile geri beslemeli kontrol
- LCD veya OLED ekran ile sistem durumu gösterimi
- Daha kararlı güç yönetimi
- ESP32 ile kablosuz veri izleme
- Web panel üzerinden sulama zamanı ayarlama

## Lisans

Bu proje kişisel öğrenme ve portfolyo amacıyla hazırlanmıştır. Dilersen ileride MIT License ekleyebilirsin.

## Geliştirici

**Mehmet Efe Demirel**  
Mekatronik Mühendisliği Öğrencisi  
Otomotiv • Otomasyon • Gömülü Sistemler
