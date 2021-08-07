const int LedA1 = 2;
const int LedA2 = 3;
const int LedA3 = 4;
const int LedA4 = 5;
const int LedA5 = 6;
const int But1 = 7;
const int But2 = 8;
const int But3 = 9;
const int LedB1 = 13;
const int LedB2 = 11;
const int RelayPin = 12;
int Ledx = 0;
int Ledy = 0;
String LedA = "0";
String LedB = "0";
String minutestr = "0";
int Mode = 0;
int B1state = LOW;
int B2state = LOW;
int B3state = LOW;
int hour = 0;
int min1 = 0;
int min2 = 0;
int minute = 0;
int sec = 0;
bool B1ready = true;
bool B2ready = true;
bool B3ready = true;
bool LedB1On = false;
bool LedB2On = false;
bool RelayOn = false;


long lastDebounceTimeb1 = 0;
long lastDebounceTimeb2 = 0;
long lastDebounceTimeb3 = 0;
long debounceDelay = 300;
long ledSwitchDelay = 300;
long lastLedB1switch = 0;
long lastLedB2switch = 0;
long lastButtonPress = 0;
long LedTimeout = 10000;
long finalTimeoutCheck = 10500;
long tSinceButtonPressed = 0;
long lastprinted = 0;
long lastRelayswitch = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LedA1, OUTPUT);
  pinMode(LedA2, OUTPUT);
  pinMode(LedA3, OUTPUT);
  pinMode(LedA4, OUTPUT);
  pinMode(LedA5, OUTPUT);
  pinMode(But1, INPUT);
  pinMode(But2, INPUT);
  pinMode(But3, INPUT);
  pinMode(LedB1, OUTPUT);
  pinMode(LedB2, OUTPUT);
  pinMode(RelayPin, OUTPUT);
  digitalWrite(RelayPin, HIGH);
}

void loop() {
  B1state = digitalRead(But1);
  B2state = digitalRead(But2);
  B3state = digitalRead(But3);
  
  //TTTTTTTTTTTTTTTTTTTTTTT...Button..1...TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
  if (((millis() - lastDebounceTimeb1) > debounceDelay) && (B1ready) && (B1state == HIGH)) {
    if (Ledy == 0){
      Ledx = Mode;
    }
    else if (Ledy == 1){
      Mode += 1; 
      Ledx = Mode;
    }
    else if (Ledy == 4){
      hour += 1; 
      if(hour==24) {
        hour=0;
        sec = 0;
      }
      Ledx = hour;
    }
    else if (Ledy == 5){
      min1 += 1; 
      if(min1 == 6) {
        min1=0;
        sec = 0;
      }
      Ledx = min1;
      minutestr = String(min1) + String(min2);
      minute = minutestr.toInt();
    }
    else if (Ledy == 6){
      min2 += 1; 
      if(min2==10) {
        min2=0;
        sec = 0;
      }
      Ledx = min2;
      minutestr = String(min1) + String(min2);
      minute = minutestr.toInt();
    }
    
    B1ready = false;
    lastDebounceTimeb1 = millis();
  }
  else if (B1state == LOW) {
    if (Ledy == 0){
      Ledx = 0;
    }
    B1ready = true;
  }
  //TTTTTTTTTTTTTTTTTTTTTT...Button..2.(RESET)..TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
  if (((millis() - lastDebounceTimeb2) > debounceDelay) && (B2ready) && (B2state == HIGH)) {
    Mode = 0;
    Ledx = 0;
    Ledy = 0;
    B2ready = false;
    lastDebounceTimeb2 = millis();
  }
  else if (B2state == LOW) {
    B2ready = true;
  }
  //TTTTTTTTTTTTTTTTTTTTT...Button..3...TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
  if (((millis() - lastDebounceTimeb3) > debounceDelay) && (B3ready) && (B3state == HIGH)) {
    Ledy += 1;
    if (Ledy == 1){
      Ledx = Mode;
    }
    else if (Ledy == 4){
      Ledx = hour;
    }
    else if (Ledy == 5){
      minutestr = String(minute);
      min1 = (minutestr.substring(0,1)).toInt();
      Ledx = min1;
    }
    else if (Ledy == 6){
      minutestr = String(minute);
      min2 = (minutestr.substring(1,2)).toInt();
      Ledx = min2;
    }
    else {
      Ledx = 0;
    }
    B3ready = false;
    lastDebounceTimeb3 = millis();
  }
  else if (B3state == LOW) {
    B3ready = true;
  }
  //TTTTTTTTTTTTTTTTTTTTTTT...Reset..LED..A...TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
  if (Mode == 32) {
    Mode = 0;
    Ledx = 0;
  }
  LedA = String(Ledx);
  //TTTTTTTTTTTTTTTTTTTTTTTT...Reset..LED..B...TTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
  if (Ledy == 7) {
    Ledy = 0;
  }
  LedB = String(Ledy);
  //TTTTTTTTTTTTTTTTTTTTTTT...Display..LED..A...TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
  if (LedA == "0") {
    digitalWrite(LedA1, LOW);
    digitalWrite(LedA2, LOW);
    digitalWrite(LedA3, LOW);
    digitalWrite(LedA4, LOW);
    digitalWrite(LedA5, LOW);
  }
  else if (LedA == "1") {
    digitalWrite(LedA1, HIGH);
    digitalWrite(LedA2, LOW);
    digitalWrite(LedA3, LOW);
    digitalWrite(LedA4, LOW);
    digitalWrite(LedA5, LOW);
  }
  else if (LedA== "2") {
    digitalWrite(LedA1, LOW);
    digitalWrite(LedA2, HIGH);
    digitalWrite(LedA3, LOW);
    digitalWrite(LedA4, LOW);
    digitalWrite(LedA5, LOW);
  }
  else if (LedA == "3") {
    digitalWrite(LedA1, HIGH);
    digitalWrite(LedA2, HIGH);
    digitalWrite(LedA3, LOW);
    digitalWrite(LedA4, LOW);
    digitalWrite(LedA5, LOW);
  }
  else if (LedA== "4") {
    digitalWrite(LedA1, LOW);
    digitalWrite(LedA2, LOW);
    digitalWrite(LedA3, HIGH);
    digitalWrite(LedA4, LOW);
    digitalWrite(LedA5, LOW);
  }
  else if (LedA == "5") {
    digitalWrite(LedA1, HIGH);
    digitalWrite(LedA2, LOW);
    digitalWrite(LedA3, HIGH);
    digitalWrite(LedA4, LOW);
    digitalWrite(LedA5, LOW);
  }
  else if (LedA == "6") {
    digitalWrite(LedA1, LOW);
    digitalWrite(LedA2, HIGH);
    digitalWrite(LedA3, HIGH);
    digitalWrite(LedA4, LOW);
    digitalWrite(LedA5, LOW);
  }
  else if (LedA == "7") {
    digitalWrite(LedA1, HIGH);
    digitalWrite(LedA2, HIGH);
    digitalWrite(LedA3, HIGH);
    digitalWrite(LedA4, LOW);
    digitalWrite(LedA5, LOW);
  }
  else if (LedA== "8") {
    digitalWrite(LedA1, LOW);
    digitalWrite(LedA2, LOW);
    digitalWrite(LedA3, LOW);
    digitalWrite(LedA4, HIGH);
    digitalWrite(LedA5, LOW);
  }
  else if (LedA == "9") {
    digitalWrite(LedA1, HIGH);
    digitalWrite(LedA2, LOW);
    digitalWrite(LedA3, LOW);
    digitalWrite(LedA4, HIGH);
    digitalWrite(LedA5, LOW);
  }
  else if (LedA== "10") {
    digitalWrite(LedA1, LOW);
    digitalWrite(LedA2, HIGH);
    digitalWrite(LedA3, LOW);
    digitalWrite(LedA4, HIGH);
    digitalWrite(LedA5, LOW);
  }
  else if (LedA == "11") {
    digitalWrite(LedA1, HIGH);
    digitalWrite(LedA2, HIGH);
    digitalWrite(LedA3, LOW);
    digitalWrite(LedA4, HIGH);
    digitalWrite(LedA5, LOW);
  }
  else if (LedA== "12") {
    digitalWrite(LedA1, LOW);
    digitalWrite(LedA2, LOW);
    digitalWrite(LedA3, HIGH);
    digitalWrite(LedA4, HIGH);
    digitalWrite(LedA5, LOW);
  }
  else if (LedA == "13") {
    digitalWrite(LedA1, HIGH);
    digitalWrite(LedA2, LOW);
    digitalWrite(LedA3, HIGH);
    digitalWrite(LedA4, HIGH);
    digitalWrite(LedA5, LOW);
  }
  else if (LedA == "14") {
    digitalWrite(LedA1, LOW);
    digitalWrite(LedA2, HIGH);
    digitalWrite(LedA3, HIGH);
    digitalWrite(LedA4, HIGH);
    digitalWrite(LedA5, LOW);
  }
  else if (LedA == "15") {
    digitalWrite(LedA1, HIGH);
    digitalWrite(LedA2, HIGH);
    digitalWrite(LedA3, HIGH);
    digitalWrite(LedA4, HIGH);
    digitalWrite(LedA5, LOW);
  }
  else if (LedA== "16") {
    digitalWrite(LedA1, LOW);
    digitalWrite(LedA2, LOW);
    digitalWrite(LedA3, LOW);
    digitalWrite(LedA4, LOW);
    digitalWrite(LedA5, HIGH);
  }
  else if (LedA == "17") {
    digitalWrite(LedA1, HIGH);
    digitalWrite(LedA2, LOW);
    digitalWrite(LedA3, LOW);
    digitalWrite(LedA4, LOW);
    digitalWrite(LedA5, HIGH);
  }
  else if (LedA== "18") {
    digitalWrite(LedA1, LOW);
    digitalWrite(LedA2, HIGH);
    digitalWrite(LedA3, LOW);
    digitalWrite(LedA4, LOW);
    digitalWrite(LedA5, HIGH);
  }
  else if (LedA == "19") {
    digitalWrite(LedA1, HIGH);
    digitalWrite(LedA2, HIGH);
    digitalWrite(LedA3, LOW);
    digitalWrite(LedA4, LOW);
    digitalWrite(LedA5, HIGH);
  }
  else if (LedA== "20") {
    digitalWrite(LedA1, LOW);
    digitalWrite(LedA2, LOW);
    digitalWrite(LedA3, HIGH);
    digitalWrite(LedA4, LOW);
    digitalWrite(LedA5, HIGH);
  }
  else if (LedA == "21") {
    digitalWrite(LedA1, HIGH);
    digitalWrite(LedA2, LOW);
    digitalWrite(LedA3, HIGH);
    digitalWrite(LedA4, LOW);
    digitalWrite(LedA5, HIGH);
  }
  else if (LedA == "22") {
    digitalWrite(LedA1, LOW);
    digitalWrite(LedA2, HIGH);
    digitalWrite(LedA3, HIGH);
    digitalWrite(LedA4, LOW);
    digitalWrite(LedA5, HIGH);
  }
  else if (LedA == "23") {
    digitalWrite(LedA1, HIGH);
    digitalWrite(LedA2, HIGH);
    digitalWrite(LedA3, HIGH);
    digitalWrite(LedA4, LOW);
    digitalWrite(LedA5, HIGH);
  }
  else if (LedA== "24") {
    digitalWrite(LedA1, LOW);
    digitalWrite(LedA2, LOW);
    digitalWrite(LedA3, LOW);
    digitalWrite(LedA4, HIGH);
    digitalWrite(LedA5, HIGH);
  }
  if (LedA == "25") {
    digitalWrite(LedA1, HIGH);
    digitalWrite(LedA2, LOW);
    digitalWrite(LedA3, LOW);
    digitalWrite(LedA4, HIGH);
    digitalWrite(LedA5, HIGH);
  }
  else if (LedA== "26") {
    digitalWrite(LedA1, LOW);
    digitalWrite(LedA2, HIGH);
    digitalWrite(LedA3, LOW);
    digitalWrite(LedA4, HIGH);
    digitalWrite(LedA5, HIGH);
  }
  else if (LedA == "27") {
    digitalWrite(LedA1, HIGH);
    digitalWrite(LedA2, HIGH);
    digitalWrite(LedA3, LOW);
    digitalWrite(LedA4, HIGH);
    digitalWrite(LedA5, HIGH);
  }
  if (LedA== "28") {
    digitalWrite(LedA1, LOW);
    digitalWrite(LedA2, LOW);
    digitalWrite(LedA3, HIGH);
    digitalWrite(LedA4, HIGH);
    digitalWrite(LedA5, HIGH);
  }
  else if (LedA == "29") {
    digitalWrite(LedA1, HIGH);
    digitalWrite(LedA2, LOW);
    digitalWrite(LedA3, HIGH);
    digitalWrite(LedA4, HIGH);
    digitalWrite(LedA5, HIGH);
  }
  else if (LedA == "30") {
    digitalWrite(LedA1, LOW);
    digitalWrite(LedA2, HIGH);
    digitalWrite(LedA3, HIGH);
    digitalWrite(LedA4, HIGH);
    digitalWrite(LedA5, HIGH);
  }
  else if (LedA == "31") {
    digitalWrite(LedA1, HIGH);
    digitalWrite(LedA2, HIGH);
    digitalWrite(LedA3, HIGH);
    digitalWrite(LedA4, HIGH);
    digitalWrite(LedA5, HIGH);
  }

  //TTTTTTTTTTTTTTTTTTT...Display..LED..B...TTTTTTTTTTTTTTTTTTTTTTTTT
  if (LedB == "0") {
    digitalWrite(LedB1, LOW);
    digitalWrite(LedB2, LOW);
  }
  else if (LedB == "1") {
    digitalWrite(LedB1, HIGH);
    digitalWrite(LedB2, LOW);
  }
  else if (LedB == "2") {
    digitalWrite(LedB1, LOW);
    digitalWrite(LedB2, HIGH);
  }
  else if (LedB == "3") {
    digitalWrite(LedB1, HIGH);
    digitalWrite(LedB2, HIGH);
  }
  
  else if ((LedB == "4") && ((millis() - lastLedB1switch) > ledSwitchDelay)) {
    if (LedB1On) {
    digitalWrite(LedB1, LOW);
    LedB1On = false;
    lastLedB1switch = millis();
    }
    else {
    digitalWrite(LedB1, HIGH);
    LedB1On = true;
    lastLedB1switch = millis();
    }
  }
  else if (LedB == "4") {
    digitalWrite(LedB2, LOW);
  }
  
  else if ((LedB == "5") && ((millis() - lastLedB2switch) > ledSwitchDelay)) {
    //Led_blink(LedB2, LedB2On, lastLedB2switch);
    if (LedB2On) {
    digitalWrite(LedB2, LOW);
    LedB2On = false;
    lastLedB2switch = millis();
    }
    else {
    digitalWrite(LedB2, HIGH);
    LedB2On = true;
    lastLedB2switch = millis();
    }
  }
  else if (LedB == "5") {
    digitalWrite(LedB1, LOW);
  }
  else if ((LedB == "6") && ((millis() - lastLedB1switch) > ledSwitchDelay)) {
    if (LedB1On) {
    digitalWrite(LedB1, LOW);
    digitalWrite(LedB2, LOW);
    LedB1On = false;
    lastLedB1switch = millis();
    }
    else {
    digitalWrite(LedB1, HIGH);
    digitalWrite(LedB2, HIGH);
    LedB1On = true;
    lastLedB1switch = millis();
    }
  }
  //TTTTTTTTTTTTTTTT..LED..TIMEOUT..TTTTTTTTTTTTTTTTTTTTTTT
  tSinceButtonPressed = millis()-lastButtonPress;
  if ((B1state == HIGH) || (B2state == HIGH) || (B3state == HIGH)){
    lastButtonPress = millis();
  } 
  else if ((tSinceButtonPressed > LedTimeout) && (tSinceButtonPressed < finalTimeoutCheck)){
    Ledx = 0;
    Ledy = 0;
  }
  
  //TTTTTTTTTTTTTTTT..TIME..TTTTTTTTTTTTTTTTTTTTTTT
  if ((Ledy == 0) && (millis()-lastprinted > 1000)){
    sec += 1;
    if(sec==60) {
      sec=0;
      minute=minute+1;
    }
    if(minute==60) {
      minute=0;
      hour=hour+1;
    }
    if(hour==24) {
      hour=0;
    }
    Serial.println(String(hour) + ":" + String(minute) + ":" + String(sec));
    lastprinted = millis();
  }

  
  //TTTTTTTTTTTTTTTT..RELAY..CONTROL..TTTTTTTT..State here what you want the thing to do in each mode
  if ((Mode == 1) && ((millis()-lastRelayswitch)>3000) && (Ledy == 0)) {
    digitalWrite(RelayPin, HIGH);
    delay(5000);
    digitalWrite(RelayPin, LOW);
    lastRelayswitch = millis();
  }
  else if ((Mode == 2) && ((millis()-lastRelayswitch)>2000) && (Ledy == 0)){
    digitalWrite(RelayPin, HIGH);
    delay(2000);
    digitalWrite(RelayPin, LOW);
    lastRelayswitch = millis();
  }
  else if ((Mode == 3) && ((millis()-lastRelayswitch)>1500) && (Ledy == 0)){
    digitalWrite(RelayPin, HIGH);
    delay(1500);
    digitalWrite(RelayPin, LOW);
    lastRelayswitch = millis();
  }
  // etc.
}
