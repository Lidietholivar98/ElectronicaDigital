#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal.h>

#define NUMPIXELS 9    // número de neopixeles en strip
#define LUZ1_PIN 4     // Pin de luz 1
#define LUZ2_PIN 10    // Pin de luz 2
#define LUZ3_PIN 9     // Pin de luz 3
#define LUZ4_PIN 7     // Pin de luz 4
#define SERVO_2_PIN 2  // Pin del servo 2
#define SERVO_3_PIN 3  // Pin del servo 3
#define SERVO_4_PIN 5  // Pin del servo 4
#define SERVO_5_PIN 6  // Pin del servo 5
// Límites de tiempo
#define HOURS_IN_DAY 24
#define MINUTES_IN_HOUR 60
#define SECONDS_IN_MINUTE 60
#define MILLISECONDS_IN_SECOND 1000
//Botonera
#define PIN_BOTON1 11
#define PIN_BOTON2 12
#define PIN_BOTON3 13
//BUZZER
#define PIN_BUZZ 8

//lcd
#define RS 14
#define E 15
#define D4 16
#define D5 17
#define D6 19
#define D7 18

int hora = 12, minuto = 0, segundo = 0;
int am_pm = 1, am_pm_alarma = 0;    //am: 0; pm: 1
int am_pm2 = 1, am_pm_alarma2 = 0;  //am: 0; pm: 1
int am_pm3 = 1, am_pm_alarma3 = 0;  //am: 0; pm: 1

//Estado de los botones
int estado1, estado2, estado3;
int horaAlarma = 0;
int minutoAlarma = 0;
int segundoAlarma = 0;
int horaAlarma2 = 0;
int segundoAlarma2 = 0;
int minutoAlarma2 = 0;
int horaAlarma3 = 0;
int minutoAlarma3 = 0;
int segundoAlarma3 = 0;

bool esAlarma = false;      //variable para controlar ciclo configuracion alarma
bool esAlarma2 = false;     //variable para controlar ciclo configuracion alarma
bool esAlarma3 = false;     //variable para controlar ciclo configuracion alarma
bool esConfigHora = false;  //variable para controlar ciclo configuracion hora
bool sonarAlarma = false;   //variable para controlar alarma

int sonido = 250;  // Frecuencia buzzer

// variables repetitivas
byte contador = 0, redColor = 0, greenColor = 0, blueColor = 0;

// Definición de variables y objetos
//Adafruit_LiquidCrystal lcd(0);
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
Servo servo_2;
Servo servo_3;
Servo servo_4;
Servo servo_5;
Adafruit_NeoPixel luz1(NUMPIXELS, LUZ1_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel luz2(NUMPIXELS, LUZ2_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel luz3(NUMPIXELS, LUZ3_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel luz4(NUMPIXELS, LUZ4_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  lcd.begin(16, 2);
  luz1.begin();
  luz2.begin();
  luz3.begin();
  luz4.begin();

  // Configuración del pin de los servomotores
  servo_2.attach(SERVO_2_PIN);
  servo_3.attach(SERVO_3_PIN);
  servo_4.attach(SERVO_4_PIN);
  servo_5.attach(SERVO_5_PIN);

  //Configuracion de los pines para los botones
  pinMode(PIN_BOTON1, INPUT);
  pinMode(PIN_BOTON2, INPUT);
  pinMode(PIN_BOTON3, INPUT);

  //Configuracion pin para el buzzer
  pinMode(PIN_BUZZ, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  //configuracion de alarmas

  //alarma 1
  while (hora == horaAlarma && minuto == minutoAlarma) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hora de pastilla");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("DISPENSADOR 1Y4");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Clonazepan Y");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("  Quetiapina  ");
    delay(500);

    setColor();

    for (int i = 0; i < NUMPIXELS; i++) {
      luz1.setPixelColor(i, luz1.Color(redColor, greenColor, blueColor));
      luz4.setPixelColor(i, luz4.Color(redColor, greenColor, blueColor));
      luz1.show();
      luz4.show();

      delay(200);
    }

    // Starting the motor that opens the lid
    servo_2.write(180);
    servo_5.write(180);
    delay(1000);
    servo_5.write(0);
    servo_2.write(0);

    delay(1000);

    // reproducir sonido
    tone(8, 440);
    delay(500);
    noTone(8);
    delay(100);
    // apagar luces servo y limpiar pantalla
    lcd.clear();
    contador++;
    segundo++;
    if (contador == 3) {
      horaAlarma++;
      for (int i = 0; i < NUMPIXELS; i++) {
        luz1.setPixelColor(i, 0, 0, 0);
        luz4.setPixelColor(i, 0, 0, 0);
        luz1.show();
        luz4.show();
        delay(200);
        contador = 0;
      }
    }
  }

  //ALARMA 2
  while (hora == horaAlarma2 && minuto == minutoAlarma2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hora de la pastilla");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TOMAR DISP 3 ");
    lcd.setCursor(0, 1);
    lcd.print("  Quetiapina  ");

    setColor();

    for (int i = 0; i < NUMPIXELS; i++) {
      luz3.setPixelColor(i, luz3.Color(redColor, greenColor, blueColor));
      luz3.show();
      delay(200);
    }

    // Starting the motor that opens the lid
    servo_4.write(180);
    delay(1000);
    servo_4.write(0);
    delay(1000);

    // reproducir sonido
    tone(8, 440);
    delay(500);
    noTone(8);
    delay(100);

    // apagar luces servo y limpiar pantalla
    lcd.clear();
    contador++;
    segundo++;
    if (contador == 3) {
      horaAlarma2++;
      for (int i = 0; i < NUMPIXELS; i++) {
        luz3.setPixelColor(i, 0, 0, 0);
        luz3.show();
        delay(200);
        contador = 0;
      }
    }
  }

  //Alarma 3
  while (hora == horaAlarma3 && minuto == minutoAlarma3) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hora de pastilla");
    delay(500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DISPENSADOR");
    lcd.setCursor(0, 1);
    lcd.print("1, 2, 3, 4");
    delay(500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Clarityne Plus");
    lcd.setCursor(0, 1);
    lcd.print("Midazolam");
    delay(500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Quetiapina");
    lcd.setCursor(0, 1);
    lcd.print("Misoprostol");
    delay(500);
    lcd.clear();

    setColor();

    for (int i = 0; i < NUMPIXELS; i++) {
      luz1.setPixelColor(i, luz1.Color(redColor, greenColor, blueColor));
      luz4.setPixelColor(i, luz4.Color(redColor, greenColor, blueColor));
      luz2.setPixelColor(i, luz2.Color(redColor, greenColor, blueColor));
      luz3.setPixelColor(i, luz3.Color(redColor, greenColor, blueColor));
      luz1.show();
      luz2.show();
      luz3.show();
      luz4.show();
      delay(200);
    }

    // Starting the motor that opens the lid
    servo_2.write(180);
    servo_5.write(180);
    servo_3.write(180);
    servo_4.write(180);
    delay(1000);
    servo_2.write(0);
    servo_5.write(0);
    servo_3.write(0);
    servo_4.write(0);

    delay(1000);

    // reproducir sonido
    tone(8, 440);
    delay(500);
    noTone(8);
    delay(100);

    // apagar luces servo y limpiar pantalla
    lcd.clear();
    contador++;
    segundo++;
    if (contador == 4) {
      horaAlarma3++;
      for (int i = 0; i < NUMPIXELS; i++) {
        luz1.setPixelColor(i, 0, 0, 0);
        luz2.setPixelColor(i, 0, 0, 0);
        luz3.setPixelColor(i, 0, 0, 0);
        luz4.setPixelColor(i, 0, 0, 0);
        luz1.show();
        luz2.show();
        luz3.show();
        luz4.show();
        contador = 0;
      }
    }
  }

  desplegarHora();
  //Inicialmente esta en LOW
  estado1 = digitalRead(PIN_BOTON1);
  if (estado1 == HIGH) {  //Esta presionado
    lcd.clear();
    modoConfig();
  }
  resetearVariablesDeControl();
}

void desplegarHora() {
  lcd.setCursor(0, 0);
  lcd.print("   Hora actual    ");
  lcd.setCursor(0, 1);
  lcd.print("   ");
  if (hora < 10) lcd.print("0");
  lcd.print(hora);
  lcd.print(":");
  if (minuto < 10) lcd.print("0");
  lcd.print(minuto);
  lcd.print(":");
  if (segundo < 10) lcd.print("0");
  lcd.print(segundo);

  if (am_pm == 0) lcd.print(" AM");
  if (am_pm == 1) lcd.print(" PM");

  delay(1000);

  segundo = segundo + 1;  //Incremento del contador de segundos
  // Cálculo del reloj con display
  // Gestión de segundos, minutos y horas
  if (segundo == 60) {
    segundo = 0;
    minuto = minuto + 1;
  }
  if (minuto == 60) {
    minuto = 0;
    hora = hora + 1;
  }
  if (hora == 13) {
    hora = 1;
    am_pm = am_pm + 1;

    if (am_pm == 2) am_pm = 0;
  }
}

void modoConfig() {
  delay(250);
  while (!esConfigHora) {
    configurarHora();
  }
  delay(250);
  while (!esAlarma) {
    configurarAlarma();
  }
  delay(250);
  while (!esAlarma2) {
    configurarAlarma2();
  }
  delay(250);
  while (!esAlarma3) {
    configurarAlarma3();
  }
}

void configurarHora() {
  // Ajuste hora
  delay(300);
  lcd.setCursor(0, 0);
  lcd.print("Config hora");
  lcd.setCursor(0, 1);
  if (hora < 10) lcd.print("0");
  lcd.print(hora);
  lcd.print(":");
  if (minuto < 10) lcd.print("0");
  lcd.print(minuto);
  lcd.print(":");
  if (segundo < 10) lcd.print("0");
  lcd.print(segundo);

  if (am_pm == 0) lcd.print(" AM");
  if (am_pm == 1) lcd.print(" PM");

  estado1 = digitalRead(PIN_BOTON2);
  if (estado1 == 1) hora = hora + 1;  //incrementa hora

  estado2 = digitalRead(PIN_BOTON3);
  if (estado2 == 1) {
    segundo = 0;
    minuto = minuto + 1;  //incrementa minuto
  }
  if (segundo == 60) {
    segundo = 0;
    minuto = minuto + 1;
  }
  if (minuto == 60) {
    minuto = 0;
    hora = hora + 1;
  }
  if (hora == 13) {
    hora = 1;
    am_pm = am_pm + 1;
    if (am_pm == 2) am_pm = 0;
  }

  estado3 = digitalRead(PIN_BOTON1);  //Memoriza hora y sale de SETUP hora
  if (estado3 == HIGH) {
    esConfigHora = true;
    lcd.clear();
  }
}

void configurarAlarma() {
  delay(300);
  lcd.setCursor(0, 0);
  lcd.print("Config alarma");
  lcd.setCursor(0, 1);
  if (horaAlarma < 10) lcd.print("0");  // Siempre dos dígitos
  lcd.print(horaAlarma);
  lcd.print(":");
  if (minutoAlarma < 10) lcd.print("0");
  lcd.print(minutoAlarma);
  lcd.print(":");
  if (segundoAlarma < 10) lcd.print("0");
  lcd.print(segundoAlarma);
  if (am_pm_alarma == 0) lcd.print(" AM");
  if (am_pm_alarma == 1) lcd.print(" PM");

  estado1 = digitalRead(PIN_BOTON2);
  if (estado1 == 1) horaAlarma = horaAlarma + 1;  //Incrementa hora

  estado2 = digitalRead(PIN_BOTON3);
  if (estado2 == 1) {
    segundoAlarma = 0;
    minutoAlarma = minutoAlarma + 1;  //Incrementa minutos
  }
  if (minutoAlarma == 60) {
    minutoAlarma = 0;
    horaAlarma = horaAlarma + 1;
  }
  if (horaAlarma == 13) {
    horaAlarma = 1;
    am_pm_alarma = am_pm_alarma + 1;

    if (am_pm_alarma == 2) am_pm_alarma = 0;
  }
  estado3 = digitalRead(PIN_BOTON1);  //Memeoriza alarma y sale de SETUP alarma
  if (estado3 == HIGH) {
    esAlarma = true;
    lcd.clear();
  }
}

void configurarAlarma2() {
  delay(300);
  lcd.setCursor(0, 0);
  lcd.print("Config alarma 2");
  lcd.setCursor(0, 1);
  if (horaAlarma2 < 10) lcd.print("0");  // Siempre dos dígitos
  lcd.print(horaAlarma2);
  lcd.print(":");
  if (minutoAlarma2 < 10) lcd.print("0");
  lcd.print(minutoAlarma2);
  lcd.print(":");
  if (segundoAlarma2 < 10) lcd.print("0");
  lcd.print(segundoAlarma2);
  if (am_pm_alarma2 == 0) lcd.print(" AM");
  if (am_pm_alarma2 == 1) lcd.print(" PM");

  estado1 = digitalRead(PIN_BOTON2);
  if (estado1 == 1) horaAlarma2 = horaAlarma2 + 1;  //Incrementa hora

  estado2 = digitalRead(PIN_BOTON3);
  if (estado2 == 1) {
    segundoAlarma2 = 0;
    minutoAlarma2 = minutoAlarma2 + 1;  //Incrementa minutos
  }
  if (minutoAlarma2 == 60) {
    minutoAlarma2 = 0;
    horaAlarma2 = horaAlarma2 + 1;
  }
  if (horaAlarma2 == 13) {
    horaAlarma2 = 1;
    am_pm_alarma2 = am_pm_alarma2 + 1;

    if (am_pm_alarma2 == 2) am_pm_alarma2 = 0;
  }
  estado3 = digitalRead(PIN_BOTON1);  //Memeoriza alarma y sale de SETUP alarma
  if (estado3 == HIGH) {
    esAlarma2 = true;
    lcd.clear();
  }
}

void configurarAlarma3() {
  delay(300);
  lcd.setCursor(0, 0);
  lcd.print("Config alarma 3");
  lcd.setCursor(0, 1);
  if (horaAlarma3 < 10) lcd.print("0");  // Siempre dos dígitos
  lcd.print(horaAlarma3);
  lcd.print(":");
  if (minutoAlarma3 < 10) lcd.print("0");
  lcd.print(minutoAlarma3);
  lcd.print(":");
  if (segundoAlarma3 < 10) lcd.print("0");
  lcd.print(segundoAlarma3);
  if (am_pm_alarma3 == 0) lcd.print(" AM");
  if (am_pm_alarma3 == 1) lcd.print(" PM");

  estado1 = digitalRead(PIN_BOTON2);
  if (estado1 == 1) horaAlarma3 = horaAlarma3 + 1;  //Incrementa hora

  estado2 = digitalRead(PIN_BOTON3);
  if (estado2 == 1) {
    segundoAlarma3 = 0;
    minutoAlarma3 = minutoAlarma3 + 1;  //Incrementa minutos
  }
  if (minutoAlarma3 == 60) {
    minutoAlarma3 = 0;
    horaAlarma3 = horaAlarma3 + 1;
  }
  if (horaAlarma3 == 13) {
    horaAlarma3 = 1;
    am_pm_alarma3 = am_pm_alarma3 + 1;

    if (am_pm_alarma3 == 2) am_pm_alarma3 = 0;
  }
  estado3 = digitalRead(PIN_BOTON1);  //Memeoriza alarma y sale de SETUP alarma
  if (estado3 == HIGH) {
    esAlarma3 = true;
    lcd.clear();
  }
}

void resetearVariablesDeControl() {
  esConfigHora = false;
  esAlarma = false;
  esAlarma2 = false;
  esAlarma3 = false;
}

// Establecer color aleatorio para luces
void setColor() {
  redColor = random(0, 255);
  greenColor = random(0, 255);
  blueColor = random(0, 255);
}