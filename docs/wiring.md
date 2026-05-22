# Devre Bağlantıları

Bu doküman, **Otomatik Sera Sulama Sistemi** için temel bağlantı yapısını gösterir.

## Arduino Uno - DS3231 RTC

| DS3231 | Arduino Uno |
|---|---|
| VCC | 5V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

## Arduino Uno - Röle Modülü

| Röle Modülü | Arduino Uno |
|---|---|
| VCC | 5V |
| GND | GND |
| IN | D7 |

## Röle - Pompa / Vana Bağlantısı

Röle, pompa veya vana gibi harici bir yükü Arduino'dan izole şekilde açıp kapatmak için kullanılır.

Temel bağlantı mantığı:

```text
Harici güç kaynağı (+) → Röle COM
Röle NO → Pompa / Vana (+)
Pompa / Vana (-) → Harici güç kaynağı (-)
```

> Not: Pompa veya vana kullanırken yükün çalışma voltajına uygun ayrı bir güç kaynağı kullanılması önerilir. Arduino'nun 5V pininden doğrudan motor/pompa beslemek doğru değildir.

## Basit Bağlantı Şeması

Şemayı görüntülemek için: [`../images/automated-greenhouse-wiring.svg`](../images/automated-greenhouse-wiring.svg)

## Dikkat Edilecek Noktalar

- Röle modülünün aktif çalışma durumu modele göre değişebilir. Bazı modüller LOW sinyalde, bazıları HIGH sinyalde aktif olur.
- Kod içinde bu durum `RELAY_ACTIVE_STATE` ve `RELAY_PASSIVE_STATE` değişkenleriyle ayarlanabilir.
- Pompa gibi endüktif yüklerde güvenlik için uygun besleme, diyot/koruma elemanları ve izolasyon dikkate alınmalıdır.
- Harici güç kaynağı kullanırken Arduino GND ve yük besleme GND bağlantısı, kullanılan röle modülü ve sistem tasarımına göre dikkatli değerlendirilmelidir.
