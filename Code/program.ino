const int battery_pin_1 = A0;
const int battery_pin_2 = A1;
const int battery_pin_3 = A2;
const int temp_sens = A5;
const int current_sens = A4;
const int t1 = 11;
const int t2 = 12;
const int t3 = 13;
const int relay = A3;
const int buzzer = 8;
#include <SoftwareSerial.h>
SoftwareSerial espSerial(10, 9);  // RX, TX pins for ESP8266
#define UBIDOTS_TOKEN "BBUS-DScBcAQxFtA1EkyvRz6dCWWuFgg0e8"
#define DEVICE_LABEL "BMS"

float sensorValue1,sensorValue2;

#include <LiquidCrystal.h>              // include the library code:
LiquidCrystal lcd(0, 1, 2, 3, 4, 7);    // initialize the library with the numbers of the interface pins

float adc_Value,V_1,V_2,V_3,temp,current,total_vtg,per_vtg;
void setup() 
{
  pinMode(t1 , OUTPUT);
  pinMode(t2 , OUTPUT);
  pinMode(t3 , OUTPUT);
  pinMode(relay , OUTPUT);
  pinMode(buzzer , OUTPUT);
  digitalWrite(t1 , LOW);
  digitalWrite(t2 , LOW);
  digitalWrite(t3 , LOW);
  digitalWrite(relay , LOW);
  lcd.begin(16, 2);
  beep();
  espSerial.begin(9600);
  beep();
  connectToWiFi();
  lcd.setCursor(4,0);           // set the cursor to column 4, line 0
  lcd.print("Battery");
  lcd.setCursor(0,1);           // set the cursor to column 0, line 1
  lcd.print("Managment System");
  delay(1000);
  lcd.clear();
}


void loop() 
{
  lcd.clear();
  read_voltage();
    
  lcd.setCursor(0,0);           // set the cursor to column 0, line 0
  lcd.print(V_1);
  
  lcd.setCursor(6,0);           // set the cursor to column 5, line 0
  lcd.print(V_2);
  
  lcd.setCursor(12,0);           // set the cursor to column 10, line 0
  lcd.print(V_3);

  lcd.setCursor(0,1);           // set the cursor to column 0, line 1
  lcd.print(temp);
  lcd.print("C");

  lcd.setCursor(9,1);           // set the cursor to column 8, line 1
  lcd.print(current);
  lcd.print("mA");  
  
  sendToUbidots();
  
  if((V_1 > V_2) || (V_1 > V_3))
  {
    digitalWrite(t1 , HIGH);
    delay(2000);
    digitalWrite(t1 , LOW);
  }
  if((V_2 > V_1) || (V_2 > V_3))
  {
    digitalWrite(t2 , HIGH);
    delay(2000);
    digitalWrite(t2 , LOW);
  }
  if((V_3 > V_1) || (V_3 > V_2))
  {
    digitalWrite(t3 , HIGH);
    delay(2000);
    digitalWrite(t3 , LOW);
  }
  
  if(total_vtg < 12)
  {
    digitalWrite(relay , HIGH);
    delay(1000);
  }
  else
  {
    digitalWrite(relay , LOW);
    delay(1000);
  }
  
}
void read_voltage()
{
  adc_Value = analogRead(battery_pin_1);
  V_1 = (adc_Value*4.88)/1000;
 
  adc_Value = analogRead(battery_pin_2);
  V_2 = ((adc_Value*4.88)/1000)*2;
  V_2 = V_2  - V_1;
  
  adc_Value = analogRead(battery_pin_3);
  V_3 = ((adc_Value*4.88)/1000)*2.8;
  V_3 = V_3 - V_2 - V_1;

  total_vtg = V_1 + V_2 + V_3;
  per_vtg = (total_vtg / 12.6)*100;
  adc_Value = analogRead(temp_sens);
  temp = adc_Value/2;
  temp = 80-temp;

  adc_Value = analogRead(current_sens);
  current = (adc_Value*4.88);
}
void connectToWiFi() 
{
 lcd.print("Connecting to WiFi");
  espSerial.println("AT+CWJAP=\"battery\",\"12345678\"");
  while(!espSerial.find("OK"));
  lcd.clear();
}

void sendToUbidots()
{
  espSerial.println("AT+CIPSTART=\"TCP\",\"industrial.api.ubidots.com\",80");
  while(!espSerial.find("Linked"));
  delay(100);
  String payload="{\"B1\": "+String(V_1)+",\"B2\": "+String(V_2)+",\"B3\": "+String(V_3)+",\"per\": "+String(per_vtg)+",\"I\": "+String(current)+",\"Temp\": "+String(temp)+"}";
  
  String request = "POST /api/v1.6/devices/" DEVICE_LABEL "/ HTTP/1.1\r\n";
  request += "Host: industrial.api.ubidots.com\r\n";
  request += "X-Auth-Token: " + String(UBIDOTS_TOKEN) + "\r\n";
  request += "Content-Type: application/json\r\n";
  request += "Content-Length: " + String(payload.length()) + "\r\n\r\n";
  request += payload;

  espSerial.print("AT+CIPSEND=");  
  espSerial.println(request.length());  
  while(!espSerial.find(">"));

  espSerial.print(request);
  while(!espSerial.find("OK"));
  while(!espSerial.find("OK"));
  while(!espSerial.find("OK"));
  delay(100);  
  espSerial.println("AT+CIPCLOSE");
  while(!espSerial.find("Unlink"));
  delay(100);
  beep();
}
void beep()
{
  digitalWrite(buzzer,HIGH);
  delay(200);
  digitalWrite(buzzer,LOW);
}
