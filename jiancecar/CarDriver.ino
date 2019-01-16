int E1 = 10;
int M1 = 12;
int E2 = 11;
int M2 = 13;
String p = "";
void back(int value1, int value2)
{


  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, value1);   //PWM调速
  analogWrite(E2, value2);   //PWM调速
  delay(30);

}
void go(int value1, int value2)
{

  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, value1);   //PWM调速
  analogWrite(E2, value2);

}
void left(int value1, int value2)
{

  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, value1);   //PWM调速
  analogWrite(E2, value2);

}
void right(int value1, int value2)
{

  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, value1);   //PWM调速
  analogWrite(E2, value2);

}
void sotp(int value1, int value2)
{

  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, value1);   //PWM调速
  analogWrite(E2, value2);

}


void setup()
{
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  Serial.begin(115200);
  Serial.println("======START=====");
}

void loop()
{
  while (Serial.available() > 0)
  {
    p += char(Serial.read());
    delay(2);
  }
  if (p.length() > 0)
  {
    //前进
    if (p == "g") {
      go(200, 200);
      Serial.println(p);
    }
    //后退
    if (p == "b")
    {
      back(200, 200);
      Serial.println(p);
    }
    //左转
    if (p == "l0")
    {
      left(195, 200);
      Serial.println(p);
    }
    if (p == "l1")
    {
      left(185, 200);
      Serial.println(p);
    }
    if (p == "l2")
    {
      left(175, 200);
      Serial.println(p);
    }
    if (p == "l3")
    {
      left(165, 200);
      Serial.println(p);
    }
    if (p == "l4")
    {
      left(155, 250);
      Serial.println(p);
    }
    if (p == "l5")
    {
      left(145, 250);
      Serial.println(p);
    }
    if (p == "l6")
    {
      left(145, 250);
      Serial.println(p);
    }
    if (p == "l7")
    {
      left(145, 250);
      Serial.println(p);
    }
    if (p == "l8")
    {
      left(130, 250);
      Serial.println(p);
    }
    if (p == "l9")
    {
      left(125, 250);
      Serial.println(p);
    }
    //右转
    if (p == "r0")
    {
      right(200,195);
      Serial.println(p);
    }
    if (p == "r1")
    {
      right(200,185);
      Serial.println(p);
    }
    if (p == "r2")
    {
      right(200,175);
      Serial.println(p);
    }
    if (p == "r3")
    {
      right(200,165);
      Serial.println(p);
    }
    if (p == "r4")
    {
      right(250,175);
      Serial.println(p);
    }
    if (p == "r5")
    {
      right(250,165);
      Serial.println(p);
    }
    if (p == "r6")
    {
      right(250,155);
      Serial.println(p);
    }
    if (p == "r7")
    {
      right(250,145);
      Serial.println(p);
    }
    if (p == "r8")
    {
      right(250,135);
      Serial.println(p);
    }
    if (p == "r9")
    {
      right(250, 150);
      Serial.println(p);
    }
    //停止
    if (p == "s")
    {
      sotp(0, 0);
      Serial.println(p);
    }
    p = "";
  }

}
