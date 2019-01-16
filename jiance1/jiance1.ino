#include <dht11.h>


dht11 DHT11;
#define DHT11PIN 2

int dustPin =A0;
float dustVal = 0;
int ledPower = 10;
int delayTime = 280;
int delayTime2 = 40;
float offTime = 9680;
int Beep=12;//峰鸣器数字口
int MQ2=A3;//可燃气体传感器模拟口;
int MQ7=A4;//一氧化碳传感器
int MQ135=A2;//苯系有害气体传感器模拟口;
int val=0;
int Digital_Value=0;
float temp_Value=0;


double dewPointFast(double celsius, double humidity)    //快速计算
{
double a = 17.271;
double b = 237.7;
double temp = (a * celsius) / (b + celsius) + log(humidity/100);
double Td = (b * temp) / (a - temp);
return Td;
}




void setup() {

pinMode(Beep,OUTPUT);
pinMode(MQ2,INPUT);
pinMode(MQ7,INPUT);
pinMode(MQ135,INPUT);
pinMode(ledPower,OUTPUT);
pinMode(dustPin,INPUT);
Serial.begin(115200);
Serial.println("======START=====");
digitalWrite(Beep, HIGH);

}

void loop() {
    
String readNum = "";
if(Serial.available()>0)
{
  
  readNum=Serial.readString();
  delay(100);
  if(readNum=="g")
  {
    while(1)
    {
    int wendu = getTemp();
    int co = getMQ7();
    int shidu = getHumidity();
    int keran = getMQ2();
    int youdu = getMQ135();
    int pm = getPm();
       if(wendu>35||pm>1500||co>300||keran>300||youdu>200)
        {
           digitalWrite(Beep, LOW);
         }
       else
         {
         digitalWrite(Beep, HIGH);
       }
     Serial.print("wendu");
     Serial.println(wendu);
     delay(1200);
     if(wendu>35||pm>1500||co>300||keran>300||youdu>200)
        {
           digitalWrite(Beep, LOW);
         }
       else
         {
         digitalWrite(Beep, HIGH);
       }
     Serial.print("co");
     Serial.println(co);
     delay(1500);
     if(wendu>35||pm>1500||co>300||keran>300||youdu>200)
        {
           digitalWrite(Beep, LOW);
         }
       else
         {
         digitalWrite(Beep, HIGH);
       }
     Serial.print("shidu");
       Serial.println(shidu);
     delay(1200);
     if(wendu>35||pm>1500||co>300||keran>300||youdu>200)
        {
           digitalWrite(Beep, LOW);
         }
       else
         {
         digitalWrite(Beep, HIGH);
       }
     Serial.print("keran");
     Serial.println(keran);
     delay(1500);
     if(wendu>35||pm>1500||co>300||keran>300||youdu>200)
        {
           digitalWrite(Beep, LOW);
         }
       else
         {
         digitalWrite(Beep, HIGH);
       }
     Serial.print("youdu");
      Serial.println(youdu);
     delay(1500);
        if(wendu>35||pm>1500||co>300||keran>300||youdu>200)
        {
           digitalWrite(Beep, LOW);
         }
       else
         {
         digitalWrite(Beep, HIGH);
       }
     
     Serial.print("pm");
      Serial.println(pm);
     delay(1200);

     if(wendu>35||pm>1500||co>300||keran>300||youdu>200)
        {
           digitalWrite(Beep, LOW);
         }
       else
         {
         digitalWrite(Beep, HIGH);
       }  
    }
    }
    else if(readNum == "w")
    {
       Serial.println("======START=====");
     getPm();
     delay(1000);
     getMQ2();
    delay(1000);
    getMQ135();
    delay(1000);
     getMQ7();
    delay(1000);
    getTemp();
    delay(1000);
   getHumidity();
    delay(1000);

      
     }
  
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
         pm= (float(dustVal / 1024) - 0.0356) * 120000 * 0.035;
        
      }
       
   
      return pm;
  
  
  }
int getMQ7()    //一氧化碳传感器
{
    int val;
   val=analogRead(MQ7);
  return val;
  
  }


//可燃气体传感器
int  getMQ2()
{
  int val;
  val=analogRead(MQ2);

  
  return val;
}


int  getMQ135()  //有毒气体传感器
{
  int n = analogRead(MQ135);
  int MQ135 = n * 0.9; //将输出数值转换
  
  return MQ135;
}
int getTemp()
{
  int chk = DHT11.read(DHT11PIN);
  int Temp=DHT11.temperature;
  return Temp;
  
  }
int getHumidity()
{
   int Humidity = DHT11.humidity;
    return Humidity;
  
  
  }
