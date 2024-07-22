int x_pin = 4;
int y_pin = 5;
int sw_pin = 2;
char characterToSend = 'N'; // Default characterToSend
bool lastButtonState = false;
int buttonPressCounter = 0;
char incomingChar; // Variable to store the incoming character
float receivedFloat; // Variable to store received float

void setup() {
  pinMode(x_pin, INPUT);
  pinMode(y_pin, INPUT);
  pinMode(sw_pin, INPUT);
  digitalWrite(sw_pin, HIGH); // Enable pull-up resistor on the button pin

  Serial.begin(9600); // Serial Monitor
  // Remove the while loop that waits for the serial port to connect
  // while (!Serial) {
  //   ; // Wait for the serial port to connect
  // }

  Serial1.begin(9600); // HC-05 Bluetooth module
}

void loop() {
  int x_data = analogRead(x_pin);
  int y_data = analogRead(y_pin);
  int sw_data = digitalRead(sw_pin);

  // Determine if the button state has changed
  if (sw_data != lastButtonState) {
    delay(50); // Debounce delay
    if (sw_data != lastButtonState) {
      // Button state has changed
      lastButtonState = sw_data;

      if (sw_data == LOW) {
        // Button is pressed
        buttonPressCounter = (buttonPressCounter + 1) % 3; // Cycle through 0, 1, 2

        if (buttonPressCounter == 1) {
          // Send 'm' when button is pressed the first time
          characterToSend = 'm';
          Serial.println("Sending 'm'");
        } else if (buttonPressCounter == 2) {
          // Send 'z' when button is pressed the second time
          characterToSend = 'z';
          Serial.println("Sending 'z'");
        } else {
          // Resume normal behavior when button is pressed the third time
          characterToSend = 'N';
          Serial.println("Normal mode resumed");
        }
      }
    }
  }

  // Normal operation to send other characters based on joystick position
  if (buttonPressCounter == 0) { // Only check joystick when buttonPressCounter is 0
    if (x_data > 820 && y_data < 15) {
      characterToSend = 'B';
      Serial.println("Forward");
    } else if (x_data < 20 && y_data > 800) {
      characterToSend = 'R';
      Serial.println("Left");
    } else if (x_data > 1020 && y_data < 1000) {
      characterToSend = 'L';
      Serial.println("Right");
    } else if (x_data > 800 &&x_data < 1000 && y_data > 1000) {
      characterToSend = 'F';
      Serial.println("Back");
    } else if (x_data < 900 && y_data < 900) {
      characterToSend = 'N';
    }  else if (x_data < 800 && y_data > 1000) {
      characterToSend = 'r';
    }else if (x_data > 1020 && y_data > 1020) {
      characterToSend = 'l';
    }
  }

  // Send the character via Bluetooth
  Serial1.write(characterToSend); 
  Serial.print("Sent character: ");
  Serial.println(characterToSend);

  delay(100); // Adjust delay as necessary for responsiveness
}
