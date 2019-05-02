#define M1_Coil_1  A3
#define M1_Coil_2  A2
#define M1_Coil_3  A1
#define M1_Coil_4  A0

#define M2_Coil_1  15
#define M2_Coil_2  14
#define M2_Coil_3  16
#define M2_Coil_4  10

#define RING_Light_1  5
#define RING_Light_2  6

#define MOTOR_DELAY  20

String valString = ""; // String to hold input Value
String argString = ""; // String to hold input Argument
String rawString;

uint8_t leftRingVal = 255;
uint8_t rightRingVal = 255;

void setup()
{
  Serial.begin(9600);

  pinMode(RING_Light_1, OUTPUT);
  pinMode(RING_Light_2, OUTPUT);
  // -
  analogWrite(RING_Light_1, leftRingVal);
  analogWrite(RING_Light_2, rightRingVal);

  pinMode(M1_Coil_1, OUTPUT);
  pinMode(M1_Coil_2, OUTPUT);
  pinMode(M1_Coil_3, OUTPUT);
  pinMode(M1_Coil_4, OUTPUT);
  // -
  digitalWrite(M1_Coil_1, HIGH);
  digitalWrite(M1_Coil_2, HIGH);
  digitalWrite(M1_Coil_3, HIGH);
  digitalWrite(M1_Coil_4, HIGH);

  pinMode(M2_Coil_1, OUTPUT);
  pinMode(M2_Coil_2, OUTPUT);
  pinMode(M2_Coil_3, OUTPUT);
  pinMode(M2_Coil_4, OUTPUT);
  // -
  digitalWrite(M2_Coil_1, HIGH);
  digitalWrite(M2_Coil_2, HIGH);
  digitalWrite(M2_Coil_3, HIGH);
  digitalWrite(M2_Coil_4, HIGH);

  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop()
{
  listenToSerial();

  /*
    stepMotor(M1_Coil_1, M1_Coil_2, M1_Coil_3, M1_Coil_4, true, 20, 30);
    delay(3000);
    stepMotor(M1_Coil_1, M1_Coil_2, M1_Coil_3, M1_Coil_4, false, 20, 30);
    delay(3000);
    lockMotor(M1_Coil_1, M1_Coil_2, M1_Coil_3, M1_Coil_4);

    stepMotor(M2_Coil_1, M2_Coil_2, M2_Coil_3, M2_Coil_4, true, 20, 30);
    delay(3000);
    stepMotor(M2_Coil_1, M2_Coil_2, M2_Coil_3, M2_Coil_4, false, 20, 30);
    delay(3000);
    lockMotor(M2_Coil_1, M2_Coil_2, M2_Coil_3, M2_Coil_4);
  */
}

void stepMotor(int c1, int c2, int c3, int c4, bool dir, const int steps, const int delayTime)
{
  int _step = steps;

  for (int i = 0; i < steps; i++)
  {
    if (dir)
    {
      _step++;
    }
    else
    {
      _step--;
    }

    if (_step > 7)
    {
      _step = 0;
    }
    if (_step < 0)
    {
      _step = 7;
    }

    switch (_step)
    {
      case 0:
        digitalWrite(c1, LOW);
        digitalWrite(c2, LOW);
        digitalWrite(c3, LOW);
        digitalWrite(c4, HIGH);
        break;
      case 1:
        digitalWrite(c1, LOW);
        digitalWrite(c2, LOW);
        digitalWrite(c3, HIGH);
        digitalWrite(c4, HIGH);
        break;
      case 2:
        digitalWrite(c1, LOW);
        digitalWrite(c2, LOW);
        digitalWrite(c3, HIGH);
        digitalWrite(c4, LOW);
        break;
      case 3:
        digitalWrite(c1, LOW);
        digitalWrite(c2, HIGH);
        digitalWrite(c3, HIGH);
        digitalWrite(c4, LOW);
        break;
      case 4:
        digitalWrite(c1, LOW);
        digitalWrite(c2, HIGH);
        digitalWrite(c3, LOW);
        digitalWrite(c4, LOW);
        break;
      case 5:
        digitalWrite(c1, HIGH);
        digitalWrite(c2, HIGH);
        digitalWrite(c3, LOW);
        digitalWrite(c4, LOW);
        break;
      case 6:
        digitalWrite(c1, HIGH);
        digitalWrite(c2, LOW);
        digitalWrite(c3, LOW);
        digitalWrite(c4, LOW);
        break;
      case 7:
        digitalWrite(c1, HIGH);
        digitalWrite(c2, LOW);
        digitalWrite(c3, LOW);
        digitalWrite(c4, HIGH);
        break;
      default:
        digitalWrite(c1, LOW);
        digitalWrite(c2, LOW);
        digitalWrite(c3, LOW);
        digitalWrite(c4, LOW);
        break;
    }

    delay(delayTime);
  }
}

void lockMotor(int c1, int c2, int c3, int c4)
{
  digitalWrite(c1, HIGH);
  digitalWrite(c2, HIGH);
  digitalWrite(c3, HIGH);
  digitalWrite(c4, HIGH);
}

void listenToSerial()
{
  while (Serial.available())
  {
    char inChar = Serial.read();
    rawString += (char)inChar;
  }

  for (int i = 0; i < rawString.length(); i++)
  {
    if (rawString[i] != ' ')
    {
      if (!isDigit((char)rawString[i]))
        argString += rawString[i];
      else
        valString += rawString[i];
    }
  }

  if (rawString.length() > 0)
  {
    /*
    Serial.print("Raw String: [");
    Serial.print(rawString);
    Serial.print("] - Received Arg: [");
    Serial.print(argString);
    Serial.print("] - Received Val: [");
    Serial.print(valString);
    Serial.println("]");
    */

    if (argString == "RING_L")
    {
      analogWrite(RING_Light_1, valString.toInt());
    }
    else if (argString == "RING_R")
    {
      analogWrite(RING_Light_2, valString.toInt());
    }
    else if (argString == "STEP_L")
    {
      stepMotor(M2_Coil_1, M2_Coil_2, M2_Coil_3, M2_Coil_4, true, valString.toInt(), MOTOR_DELAY);
      lockMotor(M2_Coil_1, M2_Coil_2, M2_Coil_3, M2_Coil_4);
    }
    else if (argString == "STEP_R")
    {
      stepMotor(M2_Coil_1, M2_Coil_2, M2_Coil_3, M2_Coil_4, false, valString.toInt(), MOTOR_DELAY);
      lockMotor(M2_Coil_1, M2_Coil_2, M2_Coil_3, M2_Coil_4);
    }
    else if (argString == "STEP_U")
    {
      stepMotor(M1_Coil_1, M1_Coil_2, M1_Coil_3, M1_Coil_4, true, valString.toInt(), MOTOR_DELAY);
      lockMotor(M1_Coil_1, M1_Coil_2, M1_Coil_3, M1_Coil_4);
    }
    else if (argString == "STEP_D")
    {
      stepMotor(M1_Coil_1, M1_Coil_2, M1_Coil_3, M1_Coil_4, false, valString.toInt(), MOTOR_DELAY);
      lockMotor(M1_Coil_1, M1_Coil_2, M1_Coil_3, M1_Coil_4);
    }
    else if (argString == "RING_ON")
    {
      analogWrite(RING_Light_1, 0);
      analogWrite(RING_Light_2, 0);
    }
    else if (argString == "RING_OFF")
    {
      analogWrite(RING_Light_1, 255);
      analogWrite(RING_Light_2, 255);
    }
    else if (argString == "LIGHTL_U")
    {
      if (leftRingVal >= 5)
      {
        leftRingVal -= 5;
        analogWrite(RING_Light_1, leftRingVal);
      }
    }
    else if (argString == "LIGHTL_D")
    {
      if (leftRingVal <= 250)
      {
        leftRingVal += 5;
        analogWrite(RING_Light_1, leftRingVal);
      }
    }
    else if (argString == "LIGHTR_U")
    {
      if (leftRingVal >= 5)
      {
        rightRingVal -= 5;
        analogWrite(RING_Light_2, rightRingVal);
      }
    }
    else if (argString == "LIGHTR_D")
    {
      if (leftRingVal <= 250)
      {
        rightRingVal += 5;
        analogWrite(RING_Light_2, rightRingVal);
      }
    }

    argString = "";
    valString = "";
    rawString = "";
  }
}
