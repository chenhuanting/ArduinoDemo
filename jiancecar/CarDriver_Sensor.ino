#include <dht11.h>
char p;

dht11 DHT11;
#define DHT11PIN 5

int dustPin = A0;  //pm2.5模拟口
float dustVal = 0;
int ledPower = 13;   //pm2.5数字口
int delayTime = 280;
int delayTime2 = 40;
float offTime = 9680;
int Beep = 0; //峰鸣器数字口
int MQ2 = A1; //可燃气体传感器模拟口;
int MQ7 = A3; //一氧化碳传感器
int MQ135 = A2; //苯系有害气体传感器模拟口;
int val = 0;
int Digital_Value = 0;
float temp_Value = 0;

/*
   PWM输出控制电机速度
*/
int ENA = 9;
int ENB = 6;
/*
   控制电机正反转
*/
int dirA = 7;
int dirB = 8;

double dewPointFast(double celsius, double humidity)    //快速计算
{
  double a = 17.271;
  double b = 237.7;
  double temp = (a * celsius) / (b + celsius) + log(humidity / 100);
  double Td = (b * temp) / (a - temp);
  return Td;
}
void setup() {

  pinMode(Beep, OUTPUT);
  pinMode(MQ2, INPUT);
  pinMode(MQ7, INPUT);
  pinMode(MQ135, INPUT);
  pinMode(ledPower, OUTPUT);
  pinMode(dustPin, INPUT);
  Serial.begin(9600);
  digitalWrite(Beep, HIGH);
  Serial.println("======START=====");

}

void loop() {
  while (Serial.available() > 0) {
    p = Serial.read();
    //前进
    if (p == 'g') {
      _motor(dirA, 1, ENA, 180);
      _motor(dirB, 0, ENB, 210);
      Serial.println(p);
    }
    //后退
    if (p == 'b')
    {
      _motor(dirA, 0, ENA, 180);
      _motor(dirB, 1, ENB, 210);
      Serial.println(p);
    }
    //左转
    if (p == 'l')
    {
      _motor(dirA, 1, ENA, 180);
      _motor(dirB, 1, ENB, 210);
      Serial.println(p);
    }
    //右转
    if (p == 'r')
    {
      _motor(dirA, 0, ENA, 180);
      _motor(dirB, 0, ENB, 210);
      Serial.println(p);
    }
    //停止
    if (p == 's')
    {
      _motor(dirA, 1, ENA, 0);
      _motor(dirB, 0, ENB, 0);
      Serial.println(p);
    }
    //空气数据开始采集
    if (p == 'd')
    {
      data();
    }
  }
}
/*
   电机驱动函数
*/
void _motor(int DIR, int state, int pwm, int val)
{
  pinMode(DIR, OUTPUT);
  pinMode(pwm, OUTPUT);
  digitalWrite(DIR, state);
  analogWrite(pwm, val);
}
/*
   传感器数据的处理和输出
*/
void data() {
  //温度
  int vol = getTemp();
  int Hum = getHumidity();
  int pm = getPm();
  int co = getMQ7();  
  int kr1 = getMQ2();
  int yd1 = getMQ135();
  String wendu = "wd:";
  wendu.concat(vol);
  Serial.println(wendu);
  delay(1200);
  //湿度
  if(vol>35||pm>1500||co>150||kr1>200||yd1>200)
        {
           digitalWrite(Beep, HIGH);
         }
       else
         {
         digitalWrite(Beep, LOW);
       }
  String Humidity = "sd:";
  Humidity.concat(Hum);
  Serial.println(Humidity);
  delay(1200);
    if(vol>35||pm>1500||co>150||kr1>200||yd1>200)
        {
           digitalWrite(Beep, HIGH);
         }
       else
         {
         digitalWrite(Beep, LOW);
       }
  //PM2.5
 
  String pm25 = "pm:";
  pm25.concat(pm);
  Serial.println(pm25);
  delay(1200);
   if(vol>35||pm>1500||co>150||kr1>200||yd1>200)
        {
           digitalWrite(Beep, HIGH);
         }
       else
         {
         digitalWrite(Beep, LOW);
       }
  //CO
  
  String Co = "co:";
  Co.concat(co);
  Serial.println(Co);
  delay(1200);
   if(vol>35||pm>1500||co>150||kr1>200||yd1>200)
        {
           digitalWrite(Beep, HIGH);
         }
       else
         {
         digitalWrite(Beep, LOW);
       }
  //可燃气体

  String kr = "kr:";
  kr.concat(kr1);
  Serial.println(kr);
  delay(1200);
    if(vol>35||pm>1500||co>150||kr1>200||yd1>200)
        {
           digitalWrite(Beep, HIGH);
         }
       else
         {
         digitalWrite(Beep, LOW);
       }
  //有毒气体

  String yd = "yd:";
  yd.concat(yd1);
  Serial.println(yd);
  delay(1200);
  if(vol>35||pm>1500||co>150||kr1>200||yd1>200)
        {
           digitalWrite(Beep, HIGH);
         }
       else
         {
         digitalWrite(Beep, LOW);
       }
}

int getPm()    //获取pm2.5
{

  float pm;
  int pmm;
  String pm25;
  digitalWrite(ledPower, LOW);
  delayMicroseconds(delayTime);
  dustVal = analogRead(dustPin);
  delayMicroseconds(delayTime2);
  digitalWrite(ledPower, HIGH);
  delayMicroseconds(offTime);
  if (dustVal > 36.455) {
    pm = (float(dustVal / 1024) - 0.0356) * 120000 * 0.035;
  
  }
  pmm = (int)(pm-2200);
  return pmm;
}
int getMQ7()    //一氧化碳传感器
{
  int val1;
  val1 = analogRead(MQ7);
  int val = val1 * 0.3; //将输出数值转换
  //   Serial.print("MQ7:");
  //  Serial.println(val);
  
  return val;

}
//可燃气体传感器
int  getMQ2()
{
  int val;
  val = analogRead(MQ2);
  // Serial.print("MQ2:");
  //  Serial.println(val);
  return val;
}
int  getMQ135()  //有毒气体传感器
{
  int n = analogRead(MQ135);
  int MQ135 = n * 0.45; //将输出数值转换
  //  Serial.print("MQ135:");
  // Serial.println(n);
  return MQ135;
}
int getTemp()
{
  int chk = DHT11.read(DHT11PIN);
  int Temp = DHT11.temperature;
  // Serial.print("wendu");
  //  Serial.println(Temp);
  // Serial.print("Temperature (oC): ");
  // Serial.println((float)DHT11.temperature, 2);
  return Temp;
}
int getHumidity()
{
  int Humidity1 = DHT11.humidity;
  // Serial.print("Humidity (%): ");
  //  Serial.println((float)DHT11.humidity, 2);
  //  Serial.print("shidu(%): ");
  //  Serial.println(Humidity);
  int Humidity=Humidity1*0.8;
  return Humidity;
}
