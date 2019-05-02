const int columnPins[9] = {0,1,3,4,5,6,7,8,12};
const int layerPins[3] = {9,10,11};
const int lumPin = A0;
const int speedPin = A1;
const int interruptPin = 2;
const int autoPin = A2;

int lum = 255;
int autoCount = 0;

volatile int mode = 1;

void setup() {
    for(int i=0;i<9;i++) {
        pinMode(columnPins[i], OUTPUT);
        digitalWrite(columnPins[i], HIGH);
    }
    
    for(int i=0;i<3;i++) {
        pinMode(layerPins[i], OUTPUT);
        digitalWrite(layerPins[i], LOW);
    }
    
    pinMode(lumPin, INPUT);
    pinMode(speedPin, INPUT);
    
    pinMode(interruptPin, INPUT_PULLUP);
    pinMode(autoPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interruptPin), pinISR, LOW);
    
    randomSeed(analogRead(10));
}

void pinISR() {
    if(mode == 6) {
        mode = 1;
    }
    else {
        mode += 1;
    }
}

void loop() {
    lum = analogRead(lumPin) / 4;
    
    if(digitalRead(autoPin) == LOW) {
        autoCount += 1;
        
        if(autoCount > 10) {
            pinISR();
            autoCount = 0;
        }
    }
    else {
        autoCount = 0;
    }
    
    switch(mode) {
        case 1:
            randomBlink();
            break;
        
        case 2:
            mill();
            break;
        
        case 3:
            layerSuite();
            break;
        
        case 4:
            columnSuite();
            break;
        
        case 5:
            blink();
            break;
        
        default:
            allOn();
    }
    
    timer();
}

void timer() {
    delay((((255 - analogRead(speedPin)) * 100) / 255) * 25);
}

void allLayerOff() {
    for(int i=0;i<3;i++) {
        digitalWrite(layerPins[i], LOW);
    }
}

void allColumnOff() {
    for(int i=0;i<9;i++) {
       digitalWrite(columnPins[i], HIGH);
    }
}

void allOff() {   
    allLayerOff();
    allColumnOff();
}

void allLayerOn() {
    for(int i=0;i<3;i++) {
        analogWrite(layerPins[i], lum);
    }
}

void allColumnOn() {
    for(int i=0;i<9;i++) {
       digitalWrite(columnPins[i], LOW);
    }
}

void allOn() {
    allLayerOn();
    allColumnOn();
}

void randomBlink() {
    for(int i=0;i<5;i++) { 
    
        allOff();
    
        int rdmLayer = random(0,3);
        int rdmColumn = random(0,9);
    
        analogWrite(layerPins[rdmLayer], lum);
        digitalWrite(columnPins[rdmColumn], LOW);
        
        timer();
    }
}

void mill() {
    allOff();
    
    allLayerOn();
    digitalWrite(columnPins[4], LOW);
    
    digitalWrite(columnPins[0], LOW);
    timer();
    
    digitalWrite(columnPins[0], HIGH);
    digitalWrite(columnPins[1], LOW);
    timer();
    
    digitalWrite(columnPins[1], HIGH);
    digitalWrite(columnPins[2], LOW);
    timer();
    
    digitalWrite(columnPins[2], HIGH);
    digitalWrite(columnPins[5], LOW);
    timer();
    
    digitalWrite(columnPins[5], HIGH);
    digitalWrite(columnPins[8], LOW);
    timer();
    
    digitalWrite(columnPins[8], HIGH);
    digitalWrite(columnPins[7], LOW);
    timer();
    
    digitalWrite(columnPins[7], HIGH);
    digitalWrite(columnPins[6], LOW);
    timer();
    
    digitalWrite(columnPins[6], HIGH);
    digitalWrite(columnPins[3], LOW);
}

void layerSuite() {
    allOff();
    
    allColumnOn();
    
    for(int i=0;i<3;i++) {
        analogWrite(layerPins[i], lum);
        timer();
    }
    
    for(int i=2;i>=0;i--) {
        digitalWrite(layerPins[i], LOW);
        timer();
    }
}

void columnSuite() {
    allOff();
    
    allLayerOn();
    
    for(int i=0;i<9;i++) {
        digitalWrite(columnPins[i], LOW);
        timer();
    }
    
    for(int i=8;i>=0;i--) {
        digitalWrite(columnPins[i], HIGH);
        timer();
    }
}

void blink() {
    for(int i=0;i<5;i++) {
        allOn();
        timer();
        allOff();
        timer();
    }
}