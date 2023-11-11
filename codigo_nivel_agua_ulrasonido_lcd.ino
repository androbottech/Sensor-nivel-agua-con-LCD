#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
const int buz=9;
const int echo=A3;
const int trigger=A4;
long tiempo;
float distancia;
int porc =0;

void setup()
{
  lcd.begin(16,2);
  pinMode(echo,INPUT);
  pinMode(trigger,OUTPUT);
  pinMode(buz,OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  lcd.clear();
  medir();
  porcentaje();
  lcd.setCursor(4,0);//columna,fila
  lcd.print(distancia);
  lcd.print("cm");
  lcd.setCursor(4,1);//columna,fila
  lcd.print(porc);
  lcd.print("%");
  delay(100);

  if(porc>=99){alarma();}
}

void alarma()
{
  digitalWrite(buz,1);
  delay(500);
  digitalWrite(buz,0);
  delay(500);
}
void porcentaje()
{
  porc = map(distancia,5,90,100,0);//convertir de cm a %
}

void medir()
{
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  
  tiempo=pulseIn(echo,HIGH);//us=microsegundos
  distancia = float(tiempo*0.0343)/2;
  delay(10);
}
