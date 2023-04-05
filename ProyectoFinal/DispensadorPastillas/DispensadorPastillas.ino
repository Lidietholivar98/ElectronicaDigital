#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_LiquidCrystal.h>

#define NUMPIXELS 9 // número de neopixeles en strip

#define LUZ_1_PIN 4  // Pin de luz 1
#define LUZ_2_PIN 10 // Pin de luz 2
#define LUZ_3_PIN 9  // Pin de luz 3
#define LUZ_4_PIN 7  // Pin de luz 4

#define SERVO_2_PIN 2 // Pin del servo 2
#define SERVO_3_PIN 3 // Pin del servo 3
#define SERVO_4_PIN 5 // Pin del servo 4
#define SERVO_5_PIN 6 // Pin del servo 5

// Límites de tiempo
#define HOURS_IN_DAY 24
#define MINUTES_IN_HOUR 60
#define SECONDS_IN_MINUTE 60
#define MILLISECONDS_IN_SECOND 1000

int current_hour = 10;
int current_minute = 23;
int current_second = 0;

// Alarma 1
int alarm_hour_1 = 10;
int alarm_minute_1 = 23;
int alarm_second_1 = 6;

// Alarma 2
int alarm_hour_2 = 10;
int alarm_minute_2 = 25;

// variables repetitivas
byte counter = 0;
byte red_color = 0;
byte green_color = 0;
byte blue_color = 0;

// Definición de variables y objetos
Adafruit_LiquidCrystal lcd(0);
Servo servo_2;
Servo servo_3;
Servo servo_4;
Servo servo_5;
Adafruit_NeoPixel luz_1(NUMPIXELS, LUZ_1_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel luz_2(NUMPIXELS, LUZ_2_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel luz_3(NUMPIXELS, LUZ_3_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel luz_4(NUMPIXELS, LUZ_4_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  luz_1.begin();
  luz_2.begin();
  luz_3.begin();
  luz_4.begin();
  lcd.begin(16, 2);
  // Configuración del pin de los servomotores
  servo_2.attach(SERVO_2_PIN);
  servo_3.attach(SERVO_3_PIN);
  servo_4.attach(SERVO_4_PIN);
  servo_5.attach(SERVO_5_PIN);
}

void loop() {

  // Indicar hora actual
  lcd.setCursor(0, 0);
  lcd.print("   Hora Actual    ");
  lcd.setCursor(0, 1);
  lcd.print("   ");

  if (current_hour < 10) {
    lcd.print("0");
  }
  lcd.print(current_hour);
  lcd.print(":");

  if (current_minute < 10) {
    lcd.print("0");
  }
  lcd.print(current_minute);
  lcd.print(":");

  if (current_second < 10) {
    lcd.print("0");
  }
  lcd.print(current_second);

  // Incrementar contador de tiempo
  current_second++;
  if (current_second >= SECONDS_IN_MINUTE) {
    current_second = 0;
    current_minute++;
  }

  if (current_minute >= MINUTES_IN_HOUR) {
    current_minute = 0;
    current_hour++;
  }

  if (current_hour >= HOURS_IN_DAY) {
    current_hour = 0;
  }
  delay(10);

  // Alarma 1
  if (current_hour == alarm_hour_1 && current_minute == alarm_minute_1 &&
      current_second == alarm_second_1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hora de pastilla");
    lcd.setCursor(0, 1);
    lcd.print("Tomar Alprazolam");

    set_color();

    for (int i = 0; i < NUMPIXELS; i++) {
      luz_1.setPixelColor(i, luz_1.Color(red_color, green_color, blue_color));
      luz_1.show();
      delay(50);
    }
    activate_alarm();
  }

  // Alarma 2
  if (current_hour == alarm_hour_2 && current_minute == alarm_minute_2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hora de pastilla");
    lcd.setCursor(0, 1);
    lcd.print("Tomar Doxilamina ");
    lcd.setCursor(0, 0);
    lcd.print("Y");
    lcd.setCursor(0, 1);
    lcd.print("Tomar Clonazepan ");

    set_color();

    for (int i = 0; i < NUMPIXELS; i++) {
      luz_3.setPixelColor(i, luz_3.Color(red_color, green_color, blue_color));
      luz_4.setPixelColor(i, luz_4.Color(red_color, green_color, blue_color));
      luz_3.show();
      luz_4.show();
      delay(50);
    }
    activate_alarm();
  }
}

// Establecer color aleatorio para luces
void set_color() {
  red_color = random(0, 255);
  green_color = random(0, 255);
  blue_color = random(0, 255);
}

// Activar alarma y mover servomotores
void activate_alarm() {
  servo_4.write(180);
  servo_5.write(180);
  delay(MILLISECONDS_IN_SECOND);
  servo_4.write(0);
  servo_5.write(0);
  delay(MILLISECONDS_IN_SECOND);

  // reproducir sonido
  tone(8, 440);
  delay(500);
  noTone(8);
  delay(100);

  counter++;

  // apagar luces servo y limpiar pantalla
  lcd.clear();

  if (counter >= 3) {
    alarm_hour_1++;
  }
}