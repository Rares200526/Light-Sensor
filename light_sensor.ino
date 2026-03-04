const int led = 8;          // Pin for the LED
const int sensor_pin = A0;  // Pin for the photoresistor (LDR)
int sensorValue;            // Variable to store the read value
const int threshold = 100;  // Ideal threshold (between 150 and 240)

bool ledState = false;      // LED state memory (initially OFF)
bool wasTouched = false;    // Remembers if the finger was already covering it

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);       // Start the Serial Monitor
}

void loop() {
  sensorValue = analogRead(sensor_pin); // Read the sensor value
  Serial.println(sensorValue);          // Print the value to the Serial Monitor
  
  // Check if the sensor is touched (value drops below the threshold)
  bool isTouched = (sensorValue < threshold);

  // If the sensor was JUST touched (and wasn't touched before)
  if (isTouched == true && wasTouched == false) {
    
    // Toggle the LED state (from OFF to ON, and vice versa)
    ledState = !ledState; 
    
    // Send the command to the physical LED
    if (ledState == true) {
      digitalWrite(led, HIGH);
    } else {
      digitalWrite(led, LOW);
    }
    
    // A short delay so you have time to lift your finger (debounce)
    delay(300); 
  }

  // Save the current state to know it for the next loop iteration
  wasTouched = isTouched; 
  
  delay(10); // Small delay for stability
}