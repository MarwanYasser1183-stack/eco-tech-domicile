#include <Keypad.h>
#include <SoftwareSerial.h>
#include <Servo.h>

#define IR_PIN 9           // Pin for IR sensor
#define BUZZER_PIN 11      // Pin for buzzer
#define bluetoothTx 13     // TX pin for Bluetooth communication
#define bluetoothRx  12    // RX pin for Bluetooth communication
#define mq2Pin A0
#define led 10
#define tempinside A1     // Analog pin A0 for sensor 1
#define tempoutside A2    // Analog pin A1 for sensor 2
#define fan 13
#define servoPin 12
const int buzzerTone = 1000;  // Frequency of the buzzer tone
const float Vref = 5.0;        // Reference voltage
const int ADCResolution = 1024; // ADC resolution

const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {5, 6, 7, 8};
byte colPins[COLS] = {2, 3, 4};
 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

bool systemArmed = false;
Servo myServo;

void setup() {
  pinMode(IR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW); // Initially turn off the buzzer
  bluetooth.begin(9600);
  Serial.begin(9600);
   myServo.attach(servoPin);
}

void loop() {
  // Read the analog values from the sensors
  int sensorValue1 = analogRead(tempoutside);
  int sensorValue2 = analogRead(tempinside);

  // Convert analog values to temperature in Celsius
  float temperature1 = (sensorValue1 * Vref / ADCResolution) * 100;
  float temperature2 = (sensorValue2 * Vref / ADCResolution) * 100;

  // Print the temperatures on the serial monitor
  Serial.print("Temperature Sensor outside: ");
  Serial.print(temperature1);
  Serial.println(" °C");

  Serial.print("Temperature Sensor inside: ");
  Serial.print(temperature2);
  Serial.println(" °C");

  // Send temperatures over Bluetooth
  bluetooth.print("Temperature outside: ");
  bluetooth.print(temperature1);
  bluetooth.println(" °C");

  bluetooth.print("Temperature inside: ");
  bluetooth.print(temperature2);
  bluetooth.println(" °C");

  // Wait for a short delay before reading the sensors again
  delay(1000);

  int sensorValue = analogRead(mq2Pin); // Read analog value from MQ-2 sensor
  if (sensorValue > 350) { // If sensor reading exceeds the threshold
    bluetooth.println("LOW Gas detected"); // Send "Gas detected" over Bluetooth
    Serial.println("LOW Gas detected"); // Print "Gas detected" to serial monitor for debugging
    digitalWrite(led, HIGH);
    myServo.write(180);
    delay(5000); // Wait for 10 seconds
    digitalWrite(led, LOW); 
    myServo.write(0);
  }

  if (sensorValue > 500) { // If sensor reading exceeds the threshold
    bluetooth.println("HIGH Gas detected"); // Send "Gas detected" over Bluetooth
    Serial.println("HIGH Gas detected"); // Print "Gas detected" to serial monitor for debugging
    digitalWrite(led, HIGH);
    digitalWrite(BUZZER_PIN, HIGH); // Turn on the LED indicator
    myServo.write(180);
    digitalWrite(fan,HIGH);
    delay(5000); // Wait for 10 seconds
    digitalWrite(led, LOW); 
    digitalWrite(BUZZER_PIN, LOW);// Turn off the LED indicator
    digitalWrite(fan,LOW);
    myServo.write(0);
  }

  if (!systemArmed) {
    char key = keypad.getKey();
    if (key != NO_KEY) {
      bluetooth.println("Pressed Key: " + String(key)); // Print pressed key to Bluetooth module
      if (key == '#') {
        armSystem();
      }
    }
  } else {
    // Check IR sensor for motion
    if (digitalRead(IR_PIN) == LOW) {
      sendAlert();
    }
    
    char key = keypad.getKey();
    if (key != NO_KEY) {
      bluetooth.println("Pressed Key: " + String(key)); // Print pressed key to Bluetooth module
      if (key == '*') {
        disarmSystem();
      }
    }
  }
}

void armSystem() {
  if (authenticateUser("111")) {
    systemArmed = true;
    digitalWrite(BUZZER_PIN, HIGH);  // Turn on the buzzer to indicate armed state
    delay(1000); // Delay for one second
    digitalWrite(BUZZER_PIN, LOW); // Turn off the buzzer after one second
    bluetooth.println("System armed");
  } else {
    bluetooth.println("Incorrect arm code");
  }
}

void disarmSystem() {
  if (authenticateUser("333")) {
    systemArmed = false;
    bluetooth.println("System disarmed");
  } else {
    bluetooth.println("Incorrect disarm code");
  }
}

bool authenticateUser(String code) {
  String enteredCode = "";
  char key;
  bluetooth.println("Enter code:");
  while ((key = keypad.getKey()) != '#') {
    if (key != NO_KEY) {
      bluetooth.println("Pressed Key: " + String(key)); // Debug: Print pressed key to Bluetooth module
      enteredCode += key;
    }
  }
  bluetooth.println("Entered Code: " + enteredCode); // Debug: Print entered code to Bluetooth module
  return enteredCode == code;
}

void sendAlert() {
  bluetooth.println("Stranger detected");
  tone(BUZZER_PIN, buzzerTone);
  delay(1000); // Buzz for one second
  noTone(BUZZER_PIN); // Turn off the buzzer
}