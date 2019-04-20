/*Carla Molins Pitarch*/

// Midterm The New Arcade Fall 2018

//int cards[] = {0, 1, 2, 3, 4, 5, 6, 7};
int cards[] = {1, 2, 3, 4, 5, 6, 7, 8};
int n = sizeof(cards) / sizeof(cards[0]);

int disabledButtons[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

int ledPin1 = 2;
int ledPin2 = 3;
int ledPin3 = 4;
int ledPin4 = 5;
int ledPin5 = 6;
int ledPin6 = 7;
int ledPin7 = 8;
int ledPin8 = 9;

//0 is a placeholder to avoid using -1 when accesing the array using the number of button.
int leds[] = {0, ledPin1, ledPin2, ledPin3, ledPin4, ledPin5, ledPin6, ledPin7, ledPin8};

int buttonPin1 = 22;
int buttonPin2 = 23;
int buttonPin3 = 24;
int buttonPin4 = 25;
int buttonPin5 = 26;
int buttonPin6 = 27;
int buttonPin7 = 28;
int buttonPin8 = 29;

int firstButtonPressed;
int lastButtonPressed;
bool firstButtonReleased = false;
bool secondButtonReleased = false;
int currentLed;
int currentPreviousLed;

int pair1[] = {0, 0};
int pair2[] = {0, 0};
int pair3[] = {0, 0};
int pair4[] = {0, 0};

int pairsFound = 0;
int totalPairs = sizeof(cards) / 2;
int level = 2;

int counter = 0;


void setup() {
  int i;
  Serial.begin(9600);
  Serial.println("Welcome to the Brilliant Blinking Memory");
  Serial.println("");

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin6, OUTPUT);
  pinMode(ledPin7, OUTPUT);
  pinMode(ledPin8, OUTPUT);

  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(buttonPin6, INPUT_PULLUP);
  pinMode(buttonPin7, INPUT_PULLUP);
  pinMode(buttonPin8, INPUT_PULLUP);

  Serial.println("Shuffling LEDs");
  Serial.println("");
  shuffle (cards, n);
  for (int i = 0; i < n; i++) {
    Serial.print(cards[i]);
    Serial.print("   ");
  }

  pair(cards, pair1, pair2, pair3, pair4);

  delay(1000);

  for (int i = 1; i < sizeof(leds) ; i++) {
    digitalWrite(leds[i], LOW);
    delay(100);
    digitalWrite(leds[i], HIGH);
    delay(100);
    digitalWrite(leds[i], LOW);
  }

}


void loop() {

  int buttonState1 = digitalRead (buttonPin1);
  int buttonState2 = digitalRead (buttonPin2);
  int buttonState3 = digitalRead (buttonPin3);
  int buttonState4 = digitalRead (buttonPin4);
  int buttonState5 = digitalRead (buttonPin5);
  int buttonState6 = digitalRead (buttonPin6);
  int buttonState7 = digitalRead (buttonPin7);
  int buttonState8 = digitalRead (buttonPin8);

  checkButtonPressed(buttonState1, buttonState2, buttonState3, buttonState4, buttonState5, buttonState6, buttonState7, buttonState8);

  blinkPattern();

  checkPairs();

  finishGame();

}


/*  Econjack Randomizer function */
void swap (int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}


/*  Econjack Randomizer function */
void shuffle( int cards[], int n )
{
  // Use a different seed value so that we don't get same
  // result each time we run this program
  randomSeed(analogRead(A0));

  // Start from the last element and swap one by one. We don't
  // need to run for the first element that's why i > 0
  for (int i = n - 1; i > 0; i--)
  {
    long j = random(0, n);
    swap(&cards[i], &cards[j]);
  }
}

void pair( int cards[], int pair1[], int pair2[], int pair3[], int pair4[]) {

  Serial.println("");
  Serial.println("Find here the matching pairs");
  //Serial.println(cards[0] + "," + cards[1]);

  pair1[0] = cards[0];
  pair1[1] = cards[1];

  Serial.print(pair1[0]);
  Serial.print(" , ");
  Serial.println(pair1[1]);

  pair2[0] = cards[2];
  pair2[1] = cards[3];
  // Serial.println(pair2[0]+ "," + pair2[1]);
  Serial.print(pair2[0]);
  Serial.print(" , ");
  Serial.println(pair2[1]);

  pair3[0] = cards[4];
  pair3[1] = cards[5];
  //Serial.println(pair3[0]+ "," + pair3[1]);
  Serial.print(pair3[0]);
  Serial.print(" , ");
  Serial.println(pair3[1]);

  pair4[0] = cards[6];
  pair4[1] = cards[7];
  //Serial.println(pair4[0]+ "," + pair4[1]);
  Serial.print(pair4[0]);
  Serial.print(" , ");
  Serial.println(pair4[1]);
}


void startNewGame() {

  Serial.println("Shuffling LEDs");
  Serial.println("");
  shuffle (cards, n);
  for (int i = 0; i < n; i++) {
    Serial.print(cards[i]);
    Serial.print("   ");
  }

  //currentLed=0;

  firstButtonPressed = 0;
  lastButtonPressed = 0;
  firstButtonReleased = false;
  secondButtonReleased = false;
  currentLed = -1;

  //re-enable all buttons!
  for (int i = 0; i < sizeof(disabledButtons); i++) {
    disabledButtons[i] = 0;
  }

  pair(cards, pair1, pair2, pair3, pair4);

  delay(1000);
}


void blinkPattern() {

  //Different levels are created by dividing the delay by the level, creating faster animations at every level.

  if (currentLed == pair1[0] || currentLed == pair1[1]) {

    Serial.println ("pair1");
    //Serial.println( chooseLed());

    digitalWrite(chooseLed(), HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000 / level);                     // wait for a second
    digitalWrite(chooseLed(), LOW);    // turn the LED off by making the voltage LOW
    delay(1000 / level);
    digitalWrite(chooseLed(), HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000 / level);                     // wait for a second
    digitalWrite(chooseLed(), LOW);    // turn the LED off by making the voltage LOW
    delay(1000 / level);
    digitalWrite(chooseLed(), HIGH);   // turn the LED on (HIGH is the voltage level)

    currentLed = 0;

  } else if (currentLed == pair2[0] || currentLed == pair2[1]) {

    Serial.println ("pair2");
    //Serial.println( chooseLed());
    digitalWrite(chooseLed(), HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100 / level);                     // wait for a second
    digitalWrite(chooseLed(), LOW);    // turn the LED off by making the voltage LOW
    delay(1000 / level);
    Serial.println( chooseLed());
    digitalWrite(chooseLed(), HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100 / level);                     // wait for a second
    digitalWrite(chooseLed(), LOW);    // turn the LED off by making the voltage LOW
    delay(1000 / level);
    digitalWrite(chooseLed(), HIGH);   // turn the LED on (HIGH is the voltage level)
    currentLed = 0;

  } else if (currentLed == pair3[0] || currentLed == pair3[1]) {

    Serial.println ("pair3");
    //Serial.println( chooseLed());
    digitalWrite(chooseLed(), HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100 / level);                     // wait for a second
    digitalWrite(chooseLed(), LOW);    // turn the LED off by making the voltage LOW
    delay(100 / level);
    Serial.println( chooseLed());
    digitalWrite(chooseLed(), HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000 / level);                     // wait for a second
    digitalWrite(chooseLed(), LOW);    // turn the LED off by making the voltage LOW
    delay(1000 / level);
    digitalWrite(chooseLed(), HIGH);   // turn the LED on (HIGH is the voltage level)
    currentLed = 0;

  } else if (currentLed == pair4[0] || currentLed == pair4[1]) {

    Serial.println ("pair3");
    //Serial.println( chooseLed());
    digitalWrite(chooseLed(), HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000 / level);                     // wait for a second
    digitalWrite(chooseLed(), LOW);    // turn the LED off by making the voltage LOW
    delay(1000 / level);
    Serial.println( chooseLed());
    digitalWrite(chooseLed(), HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100 / level);                     // wait for a second
    digitalWrite(chooseLed(), LOW);    // turn the LED off by making the voltage LOW
    delay(100 / level);
    digitalWrite(chooseLed(), HIGH);   // turn the LED on (HIGH is the voltage level)
    currentLed = 0;
  }
}

void checkButtonPressed(int buttonState1, int buttonState2, int buttonState3, int buttonState4, int buttonState5, int buttonState6, int buttonState7, int buttonState8) {
  // Pressing first button

  if (buttonState1 == LOW && counter == 0) {
    if (disabledButtons[1] > 0) {
      return;
    }

    firstButtonPressed = 1;
    currentLed = 1;
    currentPreviousLed = 1;
    counter = 1;
    Serial.println( "Button 1 pressed");

  }
  if (buttonState2 == LOW && counter == 0) {
    if (disabledButtons[2] > 0) {
      return;
    }

    firstButtonPressed = 2;
    currentLed = 2;
    currentPreviousLed = 2;

    counter = 1;
    Serial.println( "Button 2 pressed");

  }
  if (buttonState3 == LOW && counter == 0) {
    if (disabledButtons[3] > 0) {
      return;
    }

    firstButtonPressed = 3;
    counter = 1;
    currentLed = 3;
    currentPreviousLed = 3;

    Serial.println( "Button 3 pressed");

  }
  if (buttonState4 == LOW && counter == 0) {
    if (disabledButtons[4] > 0) {
      return;
    }

    firstButtonPressed = 4;
    counter = 1;
    currentLed = 4;
    currentPreviousLed = 4;

    Serial.println( "Button 4 pressed");

  }
  if (buttonState5 == LOW && counter == 0) {
    if (disabledButtons[5] > 0) {
      return;
    }

    firstButtonPressed = 5;
    counter = 1;
    currentLed = 5;
    currentPreviousLed = 5;

    Serial.println( "Button 5 pressed");

  }
  if (buttonState6 == LOW && counter == 0) {
    if (disabledButtons[6] > 0) {
      return;
    }

    firstButtonPressed = 6;
    counter = 1;
    currentLed = 6;
    currentPreviousLed = 6;

    Serial.println( "Button 6 pressed");
  }

  if (buttonState7 == LOW && counter == 0) {
    if (disabledButtons[7] > 0) {
      return;
    }

    firstButtonPressed = 7;
    counter = 1;
    currentLed = 7;
    currentPreviousLed = 7;

    Serial.println( "Button 7 pressed");
  }

  if (buttonState8 == LOW && counter == 0) {
    if (disabledButtons[8] > 0) {
      return;
    }

    firstButtonPressed = 8;
    counter = 1;
    currentLed = 8;
    currentPreviousLed = 8;

    Serial.println( "Button 8 pressed");
  }

  // No button pressed
  if (buttonState1 == HIGH && counter == 0
      || buttonState2 == HIGH && counter == 0
      || buttonState3 == HIGH && counter == 0
      || buttonState4 == HIGH && counter == 0
      || buttonState5 == HIGH && counter == 0
      || buttonState6 == HIGH && counter == 0
      || buttonState7 == HIGH && counter == 0
      || buttonState8 == HIGH && counter == 0) {
    counter = 0;
  }

  //Serial.println(counter);

  // first button released
  if (buttonState1 == HIGH && counter == 1
      || buttonState2 == HIGH && counter == 1
      || buttonState3 == HIGH && counter == 1
      || buttonState4 == HIGH && counter == 1
      || buttonState5 == HIGH && counter == 1
      || buttonState6 == HIGH && counter == 1
      || buttonState7 == HIGH && counter == 1
      || buttonState8 == HIGH && counter == 1 ) {
    counter = 1;
    firstButtonReleased = true;
  }

  // Pressing second button

  if (buttonState1 == LOW && counter == 1 && firstButtonReleased && firstButtonPressed != 1) {
    if (disabledButtons[1] > 0) {
      return;
    }

    lastButtonPressed = 1;
    counter = 2;
    currentLed = 1;
    Serial.println( "Button 1 ");
  }

  if (buttonState2 == LOW && counter == 1 && firstButtonReleased && firstButtonPressed != 2) {
    if (disabledButtons[2] > 0) {
      return;
    }

    lastButtonPressed = 2;
    counter = 2;
    currentLed = 2;
    Serial.println( "Button 2 ");
  }
  if (buttonState3 == LOW && counter == 1 && firstButtonReleased && firstButtonPressed != 3) {
    if (disabledButtons[3] > 0) {
      return;
    }

    lastButtonPressed = 3;
    counter = 2;
    currentLed = 3;
    Serial.println( "Button 3 ");
    //delay (1000);

  }
  if (buttonState4 == LOW && counter == 1 && firstButtonReleased && firstButtonPressed != 4) {
    if (disabledButtons[4] > 0) {
      return;
    }

    lastButtonPressed = 4;
    counter = 2;
    currentLed = 4;
    Serial.println( "Button 4 ");
  }
  if (buttonState5 == LOW && counter == 1 && firstButtonReleased && firstButtonPressed != 5) {
    if (disabledButtons[5] > 0) {
      return;
    }

    lastButtonPressed = 5;
    counter = 2;
    currentLed = 5;
    Serial.println( "Button 5 ");

  }
  if (buttonState6 == LOW && counter == 1 && firstButtonReleased && firstButtonPressed != 6) {
    if (disabledButtons[6] > 0) {
      return;
    }

    lastButtonPressed = 6;
    counter = 2;
    currentLed = 6;
    Serial.println( " , ");
    Serial.println( "Button 6 ");

  }
  if (buttonState7 == LOW && counter == 1 && firstButtonReleased && firstButtonPressed != 7) {
    if (disabledButtons[7] > 0) {
      return;
    }

    lastButtonPressed = 7;
    counter = 2;
    currentLed = 7;
    Serial.println( " , ");
    Serial.println( "Button 7 ");

  }
  if (buttonState8 == LOW && counter == 1 && firstButtonReleased && firstButtonPressed != 8) {
    if (disabledButtons[8] > 0) {
      return;
    }

    lastButtonPressed = 8;
    counter = 2;
    currentLed = 8;
    Serial.println( " , ");
    Serial.println( "Button 8 ");

  }

  // second button released
  if (counter == 2
      && buttonState1 == HIGH
      && buttonState2 == HIGH
      && buttonState3 == HIGH
      && buttonState4 == HIGH
      && buttonState5 == HIGH
      && buttonState6 == HIGH
      && buttonState7 == HIGH
      && buttonState8 == HIGH) {

    Serial.print( firstButtonPressed);
    Serial.print( " , ");
    Serial.println( lastButtonPressed);

    counter = 0;
    secondButtonReleased = true;
  }
}


int chooseLed() {
  if (currentLed == 1) {
    return ledPin1;
  } else if (currentLed == 2) {
    return ledPin2;
  } else if (currentLed == 3) {
    return ledPin3;
  } else if (currentLed == 4) {
    return ledPin4;
  } else if (currentLed == 5) {
    return ledPin5;
  } else if (currentLed == 6) {
    return ledPin6;
  } else if (currentLed == 7) {
    return ledPin7;
  } else if (currentLed == 8) {
    return ledPin8;
  }
}


void correctPair() {

  pairsFound ++;
  Serial.print("You've found ");
  Serial.print(pairsFound);
  Serial.println(" pairs.");
  currentLed = 0;
}


void incorrectPair() {

  digitalWrite(leds[firstButtonPressed], LOW);
  digitalWrite(leds[lastButtonPressed], LOW);
  currentLed = 0;
}


void checkPairs() {

  if (firstButtonReleased && secondButtonReleased) {

    if (firstButtonPressed == pair1[0] || firstButtonPressed == pair1[1]) {

      if (lastButtonPressed == pair1[0] || lastButtonPressed == pair1[1]) {

        correctPair();
        Serial.println("correct");
        firstButtonReleased = false;
        secondButtonReleased = false;
        firstButtonPressed = 0;
        lastButtonPressed = 0;
        //disable buttons
        disabledButtons[pair1[0]] = 1;
        disabledButtons[pair1[1]] = 1;


      } else {
        Serial.println("incorrect");
        incorrectPair();
        firstButtonReleased = false;
        secondButtonReleased = false;
        firstButtonPressed = 0;
        lastButtonPressed = 0;

      }

    } else if (firstButtonPressed == pair2[0] || firstButtonPressed == pair2[1]) {

      if (lastButtonPressed == pair2[0] || lastButtonPressed == pair2[1]) {

        correctPair();
        Serial.println("correct");
        firstButtonReleased = false;
        secondButtonReleased = false;
        firstButtonPressed = 0;
        lastButtonPressed = 0;

        disabledButtons[pair2[0]] = 1;
        disabledButtons[pair2[1]] = 1;

      } else {
        Serial.println("incorrect");
        incorrectPair();
        firstButtonReleased = false;
        secondButtonReleased = false;
        firstButtonPressed = 0;
        lastButtonPressed = 0;

      }

    } else if (firstButtonPressed == pair3[0] || firstButtonPressed == pair3[1]) {

      if (lastButtonPressed == pair3[0] || lastButtonPressed == pair3[1]) {

        correctPair();
        Serial.println("correct");
        firstButtonReleased = false;
        secondButtonReleased = false;
        firstButtonPressed = 0;
        lastButtonPressed = 0;

        disabledButtons[pair3[0]] = 1;
        disabledButtons[pair3[1]] = 1;

      } else {
        Serial.println("incorrect");
        incorrectPair();
        firstButtonReleased = false;
        secondButtonReleased = false;
        firstButtonPressed = 0;
        lastButtonPressed = 0;

      }

    } else if (firstButtonPressed == pair4[0] || firstButtonPressed == pair4[1]) {

      if (lastButtonPressed == pair4[0] || lastButtonPressed == pair4[1]) {

        correctPair();
        Serial.println("correct");
        firstButtonReleased = false;
        secondButtonReleased = false;
        firstButtonPressed = 0;
        lastButtonPressed = 0;

        disabledButtons[pair4[0]] = 1;
        disabledButtons[pair4[1]] = 1;

      } else {
        Serial.println("incorrect");
        incorrectPair();
        firstButtonReleased = false;
        secondButtonReleased = false;
        firstButtonPressed = 0;
        lastButtonPressed = 0;

      }

    } else {
      Serial.println("incorrect");
      incorrectPair();
      firstButtonReleased = false;
      secondButtonReleased = false;
      firstButtonPressed = 0;
      lastButtonPressed = 0;

    }
  }
}


void finishGame() {

  if (pairsFound == (n / 2)) {

    Serial.println("You won");

    for (int i = 1; i < sizeof(leds) ; i++) {
      digitalWrite(leds[i], LOW);
      delay(100);
      digitalWrite(leds[i], HIGH);
      delay(100);
      digitalWrite(leds[i], LOW);
    }

    pairsFound = 0;
    levelUp();

  }
}


void levelUp() {

  level = level * 2;
  Serial.println("Level up");
  startNewGame();
  Serial.println("New game");
}

