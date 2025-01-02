# Uyarımatik
**Evden çıkarken telefon, cüzdan, anahtar gibi önemli eşyaları unutmak, hem zaman kaybına hem de çeşitli aksiliklere yol açabiliyor. Bu proje ile sesli ve görsel uyarılarla aynı zamanda telefona bildirim göndererek bu sorunu ortadan kaldırmak hedeflenmiştir.**

## Kullanılan Donanımlar

**NodeMCU ESP8266:** Sistem kontrolü ve programlama.
**Ultrasonik Sensör (HC-SR04):** mesafe ölçmek.
**ISD1820 Ses Modülü:** Kayıtlı ses ile kullanıcıyı uyarmak.
**Kırmızı LED'ler:** Görsel uyarı sağlamak.
**Breadboard ve Dirençler(330 ohm):** Bağlantılar için altyapı.
**Wi-Fi:** IFTTT Webhooks ile iletişim için internet bağlantısı

## Sistem Bağlantıları
**LED Bağlantıları:**
Kırmızı LED 1: Uzun bacak D0, kısa bacak GND.
Kırmızı LED 2: Uzun bacak D8, kısa bacak GND.

**Ses Modülü Bağlantıları**
VCC → 3V
GND → G
P-L → D1

**Ultrasonik Sensör Bağlantıları:**
VCC → VV
GND → G
Echo → D5
Trig → D4

## Çalışma Prensibi
Ultrasonik sensör, evden çıkmaya hazırlanan kişinin mesafesini ölçer.
Eğer kişi 50 cm’den daha yakında ise:
Kırmızı LED'ler yanar.
Ses modülü mesajı çalar.
Wi-Fi üzerinden IFTTT Webhooks API ile bir HTTP GET isteği ile telefona bildirim gönderilir.
Eğer mesafe 50 cm’den fazla ise sistem bekleme moduna geçer.

