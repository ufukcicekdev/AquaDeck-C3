#include <BleKeyboard.h>

BleKeyboard bleKeyboard("Ufuk Stream Deck", "Ufuk", 100);

void spotlightAc(String kelime) {
  // 1. Önce her şeyi bırak (temiz bir başlangıç)
  bleKeyboard.releaseAll();
  delay(500);

  // 2. Spotlight'ı aç (CMD + Space)
  bleKeyboard.press(KEY_LEFT_GUI);
  bleKeyboard.press(' ');
  delay(150);
  bleKeyboard.releaseAll();
  
  // Spotlight animasyonunun bitmesini bekle
  delay(1200); 

  // 3. Karakterleri gönder
  for(int i = 0; i < kelime.length(); i++) {
    char c = kelime[i];
    
    if (c == 'i') {
      // Mac Türkçe Klavye'de 'i' harfi, US düzenindeki " ' " tuşundadır.
      // print yerine doğrudan write kullanarak fiziksel tuş koordinatını gönderiyoruz.
      bleKeyboard.write('\''); 
    } 
    else if (c == 'ı') {
      // Eğer kelime içinde ı varsa (Örn: ınstagram yazdıysan) o 'i' tuşundadır.
      bleKeyboard.write('i');
    }
    else {
      bleKeyboard.print(c);
    }
    delay(50); // Yazma hızını Mac'in algılayabileceği seviyeye çektik
  }
  
  delay(800); 
  bleKeyboard.write(KEY_RETURN);
}

void setup() {
  delay(2000);
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 21, 20); 
  bleKeyboard.begin();
}

void loop() {
  if (!bleKeyboard.isConnected()) return;

  if (Serial1.available() > 0) {
    char gelen = Serial1.read();
    
    switch (gelen) {
      case 'A': spotlightAc("youtube"); break;
      case 'B': spotlightAc("instagram"); break;
      case 'C': spotlightAc("github"); break;
      case 'D': spotlightAc("google"); break;
      case 'E': spotlightAc("gmail"); break;
      case 'F': spotlightAc("code"); break;
      
      case 'M': bleKeyboard.write(KEY_MEDIA_MUTE); break;
      case 'U': bleKeyboard.write(KEY_MEDIA_VOLUME_UP); break;
    }
    delay(500);
  }
}
