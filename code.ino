// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_SSD1306.h>

// This #include statement was automatically added by the Particle IDE.
#include "lib1.h"

#define OLED_DC D5
#define OLED_CS D6
#define OLED_RESET D4

// LED
int led1 = D0; 

// Servos
Servo knockServo;
Servo whoServo;

// Button
int button = D3;
int buttonState = 0;

// Screen
static Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

void setup() {
  light_init();
  servo_init();
  button_init();
  display_init();
}

void light_init() {
  pinMode(led1, OUTPUT);
}

void servo_init() {
  knockServo.attach(D1);
  whoServo.attach(D2);
}

void button_init() {
  pinMode(button, INPUT);    
}

void display_init() {
  display.begin(SSD1306_SWITCHCAPVCC);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();     
}

void loop() {

  buttonState = digitalRead(button);
  digitalWrite(led1, LOW);
  
  if (buttonState == HIGH) {
    Serial.println("button pressed");  
    delay(1000);
    digitalWrite(led1, HIGH);      
    knock();
  } else {
    digitalWrite(led1, LOW);            
  }
  
  // And repeat!
}

void knock() {
    // Knock 3 times.
    for (int i = 0; i < 2; i++) {
         Serial.println("knocking"); 
         digitalWrite(led1, LOW);      
         knockServo.write(50);
         delay(1000);         
         knockServo.write(0);
         delay(1000);
    }
    response();
    delay(3000);
    display_joke();
}

void response() {
    Serial.println("response");                  
    whoServo.write(90);
    delay(1000);
    whoServo.write(0);
    delay(1000);
    whoServo.write(90);
}

void display_joke() {
  Serial.println("joke");                  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  
  char* strings[] = {"Deja", "Deja who?", "Knock knock",
                     "Spell", "Spell who?", "Ok. W-H-O.",
                     "Boo", "Boo who?", "No need to cry! It is only a joke",
                     "To", "To who?", "It is to whom.",
                     "Lettuce", "Lettuce who?", "Lettuce in! It is cold.",
                     "Kanga", "Kanga who?", "Actually, it us a kangaroo",
                     "Alec", "Alec who?", "Alec-tricity. Ain't that a shocker!",
                     "Snow", "Snow who?", "Snow use askin' when you could just open the door.",
                     "Doctor", "Doctor who?", "No. Just the Doctor.",
                     "Annie", "Annie who?", "Annie way can you let me in soon?",
                     "Figs", "Figs who?", "Figs the doorbell; it is broken.",
                     "Radio", "Radio who?", "Radio not, here I come!",
                     "Nun", "Nun who?", "Nun of your business!",
                     "Wooden shoe", "Wooden shoe who?", "Wooden shoe like to hear another joke?",
                     "Broken pencil", "Broken pencil who?", "Nevermind. It is pointless.",
                     "Owls say", "Owls say who?", "Yes. Yes they do.",
                     "No one", "No one who?", "..."};

  int nums [] = {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48};
  int index = nums[random(0, 17)];
  int end = index + 3;

  while (index < end) {
    if (index == end - 1) {
      digitalWrite(led1, HIGH);              
    }
    Serial.println(index);
    display.setCursor(0,0);  
    display.println(strings[index]);
    display.display();
    if (index == end - 1) {
      display.println(">> punchline << ha ha haaa");      
      delay(4000);
    } else {
      delay(2000);        
    }    
    display.clearDisplay();
    display.display();
    index = index + 1;
  }
}
