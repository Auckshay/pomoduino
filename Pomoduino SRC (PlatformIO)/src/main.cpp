#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET -1     // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pins
const int BTN_UP = 2;
const int BTN_START = 3;
const int BTN_DOWN = 4;

// Ultrasonic Sensor & Buzzer Pins
const int TRIG_PIN = 10;
const int ECHO_PIN = 11;
const int BUZZER_PIN = 9;

// Expanded State Machine (Now includes Paused states)
enum TimerState { SET_WORK, SET_BREAK, RUN_WORK, RUN_BREAK, PAUSE_WORK, PAUSE_BREAK };
TimerState currentState = SET_WORK;

// Time tracking variables (in seconds)
long workTime = 1500;  // Default 25 minutes
long breakTime = 300;  // Default 5 minutes
long timeCounter = 0;  // Active countdown timer

// Non-blocking timer variables
unsigned long previousMillis = 0;
unsigned long lastButtonPress = 0;
const unsigned long debounceDelay = 200;

// Start Button duration tracking
unsigned long startBtnTimer = 0;
bool startBtnHandled = false;

// Buzzer & Sensor flags
bool isDistracted = false;
unsigned long lastBeepTime = 0;
bool isBeeping = false;

// Function Prototypes
void updateDisplay(bool forceUpdate);
void playTransitionTone();
void stopBuzzer();
void resetTimer();

void setup() {
    Serial.begin(115200);

    // Initialize display
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }

    pinMode(BTN_UP, INPUT_PULLUP);
    pinMode(BTN_START, INPUT_PULLUP);
    pinMode(BTN_DOWN, INPUT_PULLUP);

    // Initialize Sensor & Buzzer Pins
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    // Initial display draw
    updateDisplay(true);
}

void loop() {
    unsigned long currentMillis = millis();

    // Read standard UP/DOWN buttons
    bool upPressed = !digitalRead(BTN_UP);
    bool downPressed = !digitalRead(BTN_DOWN);

    // ---------------------------------------------------------
    // BUTTON LOGIC: Short vs Long Press for START
    // ---------------------------------------------------------
    bool currentStartBtnState = !digitalRead(BTN_START);
    bool startShortPress = false;
    bool startLongPress = false;

    if (currentStartBtnState) {
        if (startBtnTimer == 0) {
            startBtnTimer = currentMillis; // Start timing the press
            startBtnHandled = false;
        } else if (!startBtnHandled && (currentMillis - startBtnTimer > 1000)) { 
            // Held for 1000ms (1 second) -> Trigger Long Press
            startLongPress = true;
            startBtnHandled = true; // Prevent it from firing continuously
        }
    } else {
        if (startBtnTimer > 0) {
            if (!startBtnHandled && (currentMillis - startBtnTimer > 50)) {
                // Released before 1 second (and passed 50ms debounce) -> Short Press
                startShortPress = true;
            }
            startBtnTimer = 0; // Reset timer for the next press
        }
    }

    // ---------------------------------------------------------
    // STATE 1: SETTING WORK TIME
    // ---------------------------------------------------------
    if (currentState == SET_WORK) {
        if (upPressed && (currentMillis - lastButtonPress > debounceDelay)) {
            if (workTime < 3600) workTime += 60;
            lastButtonPress = currentMillis;
            updateDisplay(true);
        } else if (downPressed && (currentMillis - lastButtonPress > debounceDelay)) {
            if (workTime > 60) workTime -= 60;
            lastButtonPress = currentMillis;
            updateDisplay(true);
        } else if (startShortPress) {
            currentState = SET_BREAK;
            updateDisplay(true);
        }
    }

    // ---------------------------------------------------------
    // STATE 2: SETTING BREAK TIME
    // ---------------------------------------------------------
    else if (currentState == SET_BREAK) {
        if (upPressed && (currentMillis - lastButtonPress > debounceDelay)) {
            if (breakTime < 1800) breakTime += 60;
            lastButtonPress = currentMillis;
            updateDisplay(true);
        } else if (downPressed && (currentMillis - lastButtonPress > debounceDelay)) {
            if (breakTime > 60) breakTime -= 60;
            lastButtonPress = currentMillis;
            updateDisplay(true);
        } else if (startShortPress) {
            // Start the Pomodoro session!
            currentState = RUN_WORK;
            timeCounter = workTime;
            previousMillis = currentMillis;
            isDistracted = false;
            
            playTransitionTone();
            updateDisplay(true);
        }
    }

    // ---------------------------------------------------------
    // STATE 3: RUNNING WORK TIMER
    // ---------------------------------------------------------
    else if (currentState == RUN_WORK) {
        // Read Ultrasonic Sensor
        long duration;
        digitalWrite(TRIG_PIN, LOW);
        delayMicroseconds(2);
        digitalWrite(TRIG_PIN, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIG_PIN, LOW);
        
        duration = pulseIn(ECHO_PIN, HIGH, 5000); 

        if (duration > 0 && (duration / 74 / 2) < 6) {
            isDistracted = true;
        } else {
            isDistracted = false;
        }

        if (isDistracted) {
            previousMillis = currentMillis; 
            updateDisplay(false); 
            
            // Two-Tone Siren
            static bool sirenHigh = false; 
            if (currentMillis - lastBeepTime >= 150) { 
                lastBeepTime = currentMillis;
                sirenHigh = !sirenHigh;
                
                if (sirenHigh) tone(BUZZER_PIN, 3000);
                else tone(BUZZER_PIN, 1000);
                
                isBeeping = true;
            }
        } else {
            stopBuzzer(); 
            
            if (currentMillis - previousMillis >= 1000) {
                previousMillis += 1000;
                timeCounter--;
                updateDisplay(false);

                if (timeCounter <= 0) {
                    currentState = RUN_BREAK;
                    timeCounter = breakTime;
                    isDistracted = false; 
                    playTransitionTone();
                    updateDisplay(true);
                }
            }
        }

        // Pause or Cancel
        if (startShortPress) {
            currentState = PAUSE_WORK;
            stopBuzzer();
            isDistracted = false;
            updateDisplay(true);
        } else if (startLongPress) {
            resetTimer();
        }
    }

    // ---------------------------------------------------------
    // STATE 4: RUNNING BREAK TIMER
    // ---------------------------------------------------------
    else if (currentState == RUN_BREAK) {
        if (currentMillis - previousMillis >= 1000) {
            previousMillis += 1000;
            timeCounter--;
            updateDisplay(false);

            if (timeCounter <= 0) {
                currentState = RUN_WORK;
                timeCounter = workTime;
                playTransitionTone();
                updateDisplay(true);
            }
        }

        // Pause or Cancel
        if (startShortPress) {
            currentState = PAUSE_BREAK;
            updateDisplay(true);
        } else if (startLongPress) {
            resetTimer();
        }
    }

    // ---------------------------------------------------------
    // STATE 5 & 6: PAUSED STATES
    // ---------------------------------------------------------
    else if (currentState == PAUSE_WORK) {
        if (startShortPress) {
            currentState = RUN_WORK;
            previousMillis = currentMillis; // Sync clock
            updateDisplay(true);
        } else if (startLongPress) {
            resetTimer();
        }
    }
    
    else if (currentState == PAUSE_BREAK) {
        if (startShortPress) {
            currentState = RUN_BREAK;
            previousMillis = currentMillis; // Sync clock
            updateDisplay(true);
        } else if (startLongPress) {
            resetTimer();
        }
    }
}

// ---------------------------------------------------------
// HELPERS
// ---------------------------------------------------------
void resetTimer() {
    currentState = SET_WORK;
    isDistracted = false;
    stopBuzzer();
    updateDisplay(true);
}

void playTransitionTone() {
    tone(BUZZER_PIN, 880, 150); 
    delay(150);                 
    tone(BUZZER_PIN, 1319, 300); 
}

void stopBuzzer() {
    if (isBeeping) {
        noTone(BUZZER_PIN);
        isBeeping = false;
    }
}

void updateDisplay(bool forceUpdate) {
    static long lastDisplayedTime = -1;
    static TimerState lastState = SET_WORK;
    static bool lastDistractedState = false;

    // Determine what time value to display
    long timeToDisplay = 0;
    if (currentState == SET_WORK) timeToDisplay = workTime;
    else if (currentState == SET_BREAK) timeToDisplay = breakTime;
    else timeToDisplay = timeCounter; // Used for all RUN and PAUSE states

    // Prevent screen flickering
    if (!forceUpdate && 
        lastDisplayedTime == timeToDisplay && 
        lastState == currentState && 
        lastDistractedState == isDistracted) {
        return; 
    }

    lastDisplayedTime = timeToDisplay;
    lastState = currentState;
    lastDistractedState = isDistracted;

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    // Intercept display if distracted during WORK phase
    if (currentState == RUN_WORK && isDistracted) {
        display.setTextSize(3);
        display.setCursor(1, 20); 
        display.print("FOCUS !");
        display.display();
        return; 
    }

    int minutes = timeToDisplay / 60;
    int seconds = timeToDisplay % 60;

    // Header
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Pomodoro Timer");
    
    // Dynamic Status Text
    display.setCursor(0, 15);
    if (currentState == SET_WORK) display.println("Setup: WORK TIME");
    else if (currentState == SET_BREAK) display.println("Setup: BREAK TIME");
    else if (currentState == RUN_WORK) display.println("Status: FOCUSED");
    else if (currentState == RUN_BREAK) display.println("Status: RELAX...");
    else if (currentState == PAUSE_WORK || currentState == PAUSE_BREAK) display.println("Status: PAUSED");

    // Large Time Text
    display.setTextSize(3);
    display.setCursor(20, 35);
    
    if (minutes < 10) display.print("0");
    display.print(minutes);
    display.print(":");
    if (seconds < 10) display.print("0");
    display.print(seconds);

    display.display();
}