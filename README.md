# 🚀 AquaDeck-C3

**ESP32-C3 tabanlı, macOS odaklı ve Türkçe Klavye uyumlu Stream Deck projesi.**

AquaDeck-C3, macOS kullanıcılarının Bluetooth LE üzerinden yaşadığı şifreleme (GATT) hatalarını ve Türkçe klavye (i/ı karmaşası) sorunlarını kökten çözen, Nextion HMI ekran destekli bir makro klavye çözümüdür.

## 🛠 1. Yazılım Gereksinimleri ve Versiyonlar

Projenin kararlılığı için aşağıdaki versiyonların kullanılması **şarttır**:

* **ESP32 Board Manager:** `v2.0.14` (Espressif Systems) 
    * *Not: Daha yeni versiyonlarda Bluetooth kütüphanesi farklı davranabilir.*
* **Kütüphane:** [ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard)

## ⚙️ 2. Arduino IDE Ayarları (Kritik)

Yükleme yapmadan önce **Tools (Araçlar)** menüsünden şu ayarları birebir uygulayın:

* **Board (Kart):** `ESP32C3 Dev Module`
* **USB CDC On Boot:** `Enabled`  
    *(Bu ayar "Disabled" olursa Serial Monitor'de hiçbir çıktı göremezsiniz!)*
* **Flash Mode:** `DIO`
* **Flash Size:** `4MB`
* **Partition Scheme:** `Default 4MB with spiffs`
* **Core Debug Level:** `None` (Veya hata ayıklama için Info)
* **Erase All Flash Before Sketch Upload:** `Enabled`  
    *(İlk kurulumda eski Bluetooth eşleşme verilerini temizlemek için gereklidir.)*



## 🔧 3. Kritik Kütüphane Modifikasyonu

macOS üzerindeki "GATT_INSUF_ENCRYPTION" hatasını aşmak için `BleKeyboard.cpp` dosyasında şu değişikliği yapın:

1.  `BleKeyboard.cpp` dosyasını bir metin editörüyle açın.
2.  `setAuthenticationMode` satırını bulun ve şu iki satırı ekleyin:

```cpp
pSecurity->setAuthenticationMode(ESP_LE_AUTH_BOND);
pSecurity->setCapability(ESP_IO_CAP_NONE);
