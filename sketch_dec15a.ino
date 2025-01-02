#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Ultrasonik sensör pinleri
#define TRIG_PIN 02
#define ECHO_PIN 14

// Kırmızı LED pinleri
#define LED1_PIN 16
#define LED2_PIN 15

// Ses modülü pinleri
#define SOUND_PIN 05

// Wi-Fi bilgileri
const char* ssid = "Seher's Galaxy A23"; // Wi-Fi ağ adı
const char* password = "eegk4824"; // Wi-Fi şifre

// IFTTT Webhook bilgileri
const char* ifttt_event_name = "motion_detected"; // IFTTT'de oluşturduğumuz etkinlik adı
const char* ifttt_key = "bEgv7jVq0Pv0vVXXS55iP47gYN71xI_neJJpfF6LxS4"; // IFTTT'den aldığımız Webhooks API anahtarı

WiFiClient wifiClient;

void setup() {
  // Pin modları
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(SOUND_PIN, OUTPUT);

  // Başlangıç değerleri
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(SOUND_PIN, LOW);

  // Seri haberleşme
  Serial.begin(9600);

  // WiFi bağlantısı
  Serial.print("WiFi'ye bağlanılıyor...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi bağlantısı başarılı!");
}

void loop() {
  // Mesafe ölçümü
  long distance = measureDistance();
  Serial.print("Mesafe: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Eğer mesafe 50 cm'den azsa
  if (distance <= 50) {
    digitalWrite(LED1_PIN, HIGH);  // LED1 yanar
    digitalWrite(LED2_PIN, HIGH); // LED2 yanar
    digitalWrite(SOUND_PIN, HIGH); // Ses modülü çalar
    sendIFTTTNotification(distance); // IFTTT bildirim gönderimi
    delay(4000); // Ses ve LED'lerin aktif kalma süresi
    digitalWrite(SOUND_PIN, LOW);  // Ses modülü durur
  } else {
    digitalWrite(LED1_PIN, LOW);  // LED1 söner
    digitalWrite(LED2_PIN, LOW);  // LED2 söner
  }

  delay(3000); // Döngü beklemesi
}

// Mesafeyi ölçen fonksiyon
long measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Echo süresini ölçme
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Süreyi cm'ye çevirme
  long distance = duration * 0.034 / 2;
  return distance;
}

// IFTTT bildirim gönderimi fonksiyonu
void sendIFTTTNotification(long distance) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "http://maker.ifttt.com/trigger/" + String(ifttt_event_name) + "/with/key/" + String(ifttt_key) + "?value1=" + String(distance);
    http.begin(wifiClient, url); // Güncellenmiş begin kullanımı
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("IFTTT Bildirimi Gönderildi. HTTP Cevap Kodu: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("IFTTT Bildirimi Başarısız. HTTP Hata Kodu: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi bağlantısı yok, IFTTT bildirimi gönderilemiyor.");
  }
}
