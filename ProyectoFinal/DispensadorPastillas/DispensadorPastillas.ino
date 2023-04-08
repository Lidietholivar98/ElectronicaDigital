#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_LiquidCrystal.h>
#include <EEPROM.h>

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
//Botonera
#define PIN_BOTON1 11
#define PIN_BOTON2 12
#define PIN_BOTON3 13
//BUZZER
#define PIN_BUZZ 8

int hora = 12;
int minuto = 0;
int segundo = 0;
int am_pm = 1, am_pm_alarma = 0; //am: 0; pm: 1

//Estado de los botones
int estado1;
int estado2;
int estado3;

int horaAlarma=0, minutoAlarma=0, segundoAlarma=0;
bool esAlarma = false;//variable para controlar ciclo configuracion alarma
bool esConfigHora = false;//variable para controlar ciclo configuracion hora
bool sonarAlarma = false;//variable para controlar alarma

int sonido = 250;  // Frecuencia buzzer

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

  //Configuracion de los pines para los botones
  pinMode(PIN_BOTON1, INPUT);
  pinMode(PIN_BOTON2, INPUT);
  pinMode(PIN_BOTON3, INPUT);

  //Configuracion pin para el buzzer
  pinMode(PIN_BUZZ, OUTPUT);

  Serial.begin(9600);

  //Para recuperar cambios del EEPROM
  //variable = EEPROM.read(0);
  //variable = EEPROM.read(1);
}

void loop() {

  desplegarHora();
  //Inicialmente esta en LOW
  estado1 = digitalRead(PIN_BOTON1);
  Serial.println(estado1);  
  if (estado1 == HIGH) {  //Esta presionado
    lcd.clear();
    modoConfig();
  }
  activarDesactivarAlarma();
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

  delay(100);

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
}

void configurarHora() {
  Serial.println("Estoy en config hora");
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
  if (estado1 == 1)hora = hora + 1;  //incrementa hora 

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
  Serial.println("Estoy en config alarma");
  delay(300);
  lcd.setCursor(0, 0);
  lcd.print("Config alarma");
  lcd.setCursor(0,1);
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
  estado3 = digitalRead(PIN_BOTON1);//Memeoriza alarma y sale de SETUP alarma
  if (estado3 == HIGH) {
    esAlarma = true;
    lcd.clear();
  }
}

void activarDesactivarAlarma() {
  if (horaAlarma == hora && minutoAlarma == minuto && am_pm_alarma == am_pm && sonarAlarma) {
    Serial.println("Suena alarma");
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hora de pastilla");
    lcd.setCursor(0, 1);
    lcd.print("Tomar Propanol");

    set_color();

    for (int i = 0; i < NUMPIXELS; i++) {
      luz_1.setPixelColor(i, luz_1.Color(red_color, green_color, blue_color));
      luz_1.show();
      delay(50);
    }

    //activar el buzzer
    tone(PIN_BUZZ, sonido, 1);
    delay(100);
    tone(PIN_BUZZ, sonido, 0);

    estado2 = digitalRead(PIN_BOTON3);//Determina si se debe apagar la alarma
    if (estado2 == HIGH) {
      Serial.println("Se apaga alarma");
      noTone(PIN_BUZZ);
      delay(250);
      sonarAlarma = false;
    }
  } 
  else {
    Serial.println("Se apaga alarma segunda vez");
    Serial.print("Valor de sonarAlarma ");
    Serial.println(sonarAlarma);
    noTone(PIN_BUZZ);  //Apaga buzzer
  }

  if (minutoAlarma == minuto) {

  } else {
    Serial.println("Se cambia variable a true");
    sonarAlarma = true;  //Variable a 1 después del minuto de sonido
  }                 // 1 minuto de alarma
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

void guardarAlarma1(String nombreAlarma, int hora, int minuto){
  //Para guardar cambios en el EEPROM
  //EEPROM.write(0, variable);
  //EEPROM.write(1, variable);
  //EEPROM.write(2, variable);
}

void guardarAlarma2(String nombreAlarma, int hora, int minuto){
  //Para guardar cambios en el EEPROM
  //EEPROM.write(3, variable);
  //EEPROM.write(4, variable);
  //EEPROM.write(5, variable);
}

void guardarAlarma3(String nombreAlarma, int hora, int minuto){
  //Para guardar cambios en el EEPROM
  //EEPROM.write(6, variable);
  //EEPROM.write(7, variable);
  //EEPROM.write(8, variable);
}