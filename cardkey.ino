#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
#define SERVO_PIN 6
#define BUZZER_PIN 7

MFRC522 rfid(SS_PIN, RST_PIN);
Servo lockServo;

byte validUID[4] = {0x05, 0xA3, 0xC7, 0x01};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  lockServo.attach(SERVO_PIN);
  lockServo.write(0);

  pinMode(BUZZER_PIN, OUTPUT);

  Serial.println("Sistema startirana");
  Serial.println("Doblijete karta...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  if (isValidCard(rfid.uid.uidByte, rfid.uid.size)) {
    Serial.println("Validna karta");
    grantAccess();
  } else {
    Serial.println("Nevalidna karta");
    denyAccess();
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  delay(1000);
}

bool isValidCard(byte *uid, byte uidSize) {
  if (uidSize != 4) return false;

  for (byte i = 0; i < 4; i++) {
    if (uid[i] != validUID[i]) return false;
  }
  return true;
}

void grantAccess() {
  tone(BUZZER_PIN, 2000, 150);
  delay(200);
  lockServo.write(90);
  delay(3000);
  lockServo.write(0);
}

void denyAccess() {
  for (int i = 0; i < 3; i++) {
    tone(BUZZER_PIN, 1000, 200);
    delay(300);
  }
}