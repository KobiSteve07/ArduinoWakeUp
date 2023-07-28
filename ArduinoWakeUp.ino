#include <LiquidCrystal.h> // Library for 16x2 LCD
#include <string.h> // Library for memcpy

// Initialize the LCD pins
const int rs_a = 3, en_a = 2, d4_a = 7, d5_a = 6, d6_a = 5, d7_a = 4;
const int rs_b = 9, en_b = 8, d4_b = 13, d5_b = 12, d6_b = 11, d7_b = 10;

LiquidCrystal lcda(rs_a, en_a, d4_a, d5_a, d6_a, d7_a); // Initialize the left LCD
LiquidCrystal lcdb(rs_b, en_b, d4_b, d5_b, d6_b, d7_b); // Initialize the right LCD

struct {
  const int BACKLIGHT_PIN_1 = A0; // Pin for controlling the backlight of the left LCD
  const int BACKLIGHT_PIN_2 = A1; // Pin for controlling the backlight of the right LCD
} BACKLIGHTPINS;

struct {
  const int SW_PIN = A5;  // Joystick switch pin
  const int VRX_PIN = A3; // Joystick X-axis pin
  const int VRY_PIN = A4; // Joystick Y-axis pin
} JOYSTICKPINS;

const int INACTIVITY_TIMEOUT = 10000; // 10 seconds in milliseconds

int selectedOption = 0; // Variable to track the selected option
bool menuChanged = true; // Variable to track if the menu has changed
unsigned long lastActivityTime = 0; // Variable to store the last time the joystick was moved
int layer = 0; // Menu layer
const String options[4] = {"burnerpc1", "burnerpc2", "burnerpc3", "gamingpc"}; // Menu options
String temp_options[4]; // Temp menu options
struct{
  int xValue = 0;
  int yValue = 0;
  int switchValue = 0;
} CordValues;

void setup() {
  Serial.begin(9600); // Initialize serial communication

  pinMode(BACKLIGHTPINS.BACKLIGHT_PIN_1, OUTPUT); // Set the backlight pin of the left LCD as OUTPUT
  pinMode(BACKLIGHTPINS.BACKLIGHT_PIN_2, OUTPUT); // Set the backlight pin of the right LCD as OUTPUT
  digitalWrite(BACKLIGHTPINS.BACKLIGHT_PIN_1, HIGH);
  digitalWrite(BACKLIGHTPINS.BACKLIGHT_PIN_2, HIGH);

  memcpy(temp_options, options, sizeof(options)); // fills the temporary options with default values from options array

  lcda.begin(16, 2); // Set up the left LCD with 16 columns and 2 rows
  lcdb.begin(16, 2); // Set up the right LCD with 16 columns and 2 rows

  // Print a message to the LCD.
  updateMenuDisplay();
}

void loop() {
  CordValues.xValue = analogRead(JOYSTICKPINS.VRY_PIN); // Read Y-axis joystick value (reversed X-axis)
  CordValues.yValue = analogRead(JOYSTICKPINS.VRX_PIN); // Read X-axis joystick value (reversed Y-axis)
  CordValues.switchValue = analogRead(JOYSTICKPINS.SW_PIN); // Read joystick switch value

  // Print debugging information to the Serial Monitor
  Serial.print("X: ");
  Serial.print(CordValues.xValue);
  Serial.print("\tY: ");
  Serial.print(CordValues.yValue);
  Serial.print("\tButton: ");
  Serial.println(CordValues.switchValue);

  // Check for joystick activity and reset the timer if any movement is detected
  if (abs(530 - CordValues.xValue) > 100 || abs(530 - CordValues.yValue) > 100) {
    lastActivityTime = millis();
    // Turn on the display and backlight
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
  }

  // Check if the inactivity timeout has passed, and perform necessary actions
  if (millis() - lastActivityTime >= INACTIVITY_TIMEOUT) {
    // Clear the displays
    lcda.clear();
    lcdb.clear();

    // Set A0 and A1 to low to turn off the power to the displays
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
  } else {
    // Handle menu navigation
    if (CordValues.yValue > 900 && menuChanged) {
      // Move up in the menu
      if (selectedOption == 0 || selectedOption == 1) {
        selectedOption += 2;
      } else {
        selectedOption -= 2;
      }
      menuChanged = false;
    } else if (CordValues.yValue < 100 && menuChanged) {
      // Move down in the menu
      if (selectedOption == 2 || selectedOption == 3) {
        selectedOption -= 2;
      } else {
        selectedOption += 2;
      }
      menuChanged = false;
    } else if (CordValues.xValue > 900 && menuChanged) {
      // Move left in the menu
      if (selectedOption == 1 || selectedOption == 3) {
        selectedOption -= 1;
      } else {
        selectedOption += 1;
      }
      menuChanged = false;
    } else if (CordValues.xValue < 100 && menuChanged) {
      // Move right in the menu
      if (selectedOption == 0 || selectedOption == 2) {
        selectedOption += 1;
      } else {
        selectedOption -= 1;
      }
      menuChanged = false;
    } else if (CordValues.switchValue < 100) {
      // Button pressed
      selectedOption = 0;
      if(layer == 0) {
        temp_options[0] = options[selectedOption];
        temp_options[1] = "Toggle Power";
        temp_options[2] = "";
        temp_options[3] = "Back";
        layer++;
      }else if(layer == 1) {
        if(selectedOption == 4) {
          memcpy(temp_options, options, sizeof(options));
          layer--;
        }
      }
    } else if (CordValues.xValue >= 100 && CordValues.xValue <= 900 && CordValues.yValue >= 100 && CordValues.yValue <= 900) {
      // Allow menu change when joystick is in the middle position
      menuChanged = true;
    }


    // Update the menu display
    updateMenuDisplay();

    // Add a small delay to avoid flickering due to rapid menu updates
    delay(100);
  }
}

void updateMenuDisplay() {
  lcda.clear();
  lcda.setCursor(0, 0);
  lcda.print((selectedOption == 0 ? ">" : " ") + temp_options[0]);
  lcda.setCursor(0, 1);
  lcda.print((selectedOption == 2 ? ">" : " ") + temp_options[2]);

  lcdb.clear();
  lcdb.setCursor(0, 0);
  lcdb.print((selectedOption == 1 ? ">" : " ") + temp_options[1]);
  lcdb.setCursor(0, 1);
  lcdb.print((selectedOption == 3 ? ">" : " ") + temp_options[3]);
}