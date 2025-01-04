#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Mendefinisikan pin untuk MQ-2 dan Buzzer
#define MQ2_PIN A0    // Sensor MQ-2 di pin A0 (analog)
#define BUZZER_PIN D5 // Buzzer di pin D5 (digital)

// Menginisialisasi LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat I2C LCD adalah 0x27, 16 kolom dan 2 baris

void setup() {
  // Inisialisasi LCD dan serial monitor
  lcd.begin();
  lcd.backlight(); // Menyalakan lampu latar LCD
  Serial.begin(115200);

  // Mengatur pin buzzer sebagai output
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  int mq2Value = analogRead(MQ2_PIN); // Membaca nilai dari sensor MQ-2
  Serial.print("MQ2 Value: ");
  Serial.println(mq2Value); // Menampilkan nilai sensor di Serial Monitor

  // Menampilkan status pada LCD
  if (mq2Value > 200) { // Jika gas terdeteksi
    lcd.clear(); // Bersihkan layar LCD
    lcd.setCursor(0, 0);
    lcd.print("GAS DETECTED!!!"); // Tampilkan pesan deteksi gas
    lcd.setCursor(0, 1);
    lcd.print("Gas Value: ");
    lcd.print(mq2Value); // Tampilkan nilai gas

    // Menghasilkan bunyi buzzer terus-menerus
    tone(BUZZER_PIN, 1000); // Frekuensi 1000Hz
  } else { // Jika tidak ada gas
    lcd.clear(); // Bersihkan layar LCD
    lcd.setCursor(0, 0);
    lcd.print("NO GAS DETECTED!!!"); // Tampilkan pesan tidak ada gas
    lcd.setCursor(0, 1);
    lcd.print("Gas Value: ");
    lcd.print(mq2Value); // Tampilkan nilai gas

    // Pola "tit-tit-ti"
    tone(BUZZER_PIN, 1000); // Bunyi pendek pertama
    delay(100);
    noTone(BUZZER_PIN);
    delay(100);
    tone(BUZZER_PIN, 1000); // Bunyi pendek kedua
    delay(100);
    noTone(BUZZER_PIN);
    delay(100);
    tone(BUZZER_PIN, 1000); // Bunyi panjang
    delay(300);
    noTone(BUZZER_PIN);
    delay(500);
  }

  delay(500); // Jeda sebelum membaca nilai lagi
}
