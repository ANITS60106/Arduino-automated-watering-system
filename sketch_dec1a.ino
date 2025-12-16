#include <SoftwareSerial.h>

SoftwareSerial bluetooth(2, 3);

int soilPin = A0;
int relayPin = 6;

int threshold = 440;

bool autoMode = true;

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
}

void loop() {
  if (bluetooth.available()) {
    String command = bluetooth.readStringUntil('\n');
    command.trim();

    if (command == "AUTO") {
      autoMode = true;
    }
    else if (command == "ON") {
      autoMode = false;
      digitalWrite(relayPin, HIGH);
    }
    else if (command == "OFF") {
      autoMode = false;
      digitalWrite(relayPin, LOW);
    }
  }

  int soilValue = analogRead(soilPin);

  if (autoMode) {
    if (soilValue > threshold) {
      digitalWrite(relayPin, HIGH);
    } else {
      digitalWrite(relayPin, LOW);
    }
  }

  bluetooth.print("SOIL:");
  bluetooth.print(soilValue);

  bluetooth.print(";STATUS:");
  bluetooth.print(soilValue > threshold ? "DRY" : "WET");

  bluetooth.print(";MODE:");
  bluetooth.println(autoMode ? "AUTO" : "MANUAL");
  Serial.println(soilValue);

  delay(500);
}