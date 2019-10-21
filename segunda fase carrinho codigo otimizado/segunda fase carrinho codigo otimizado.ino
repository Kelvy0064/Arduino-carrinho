
#include <SoftwareSerial.h>
#include <Servo.h>
Servo motor;
int gatilho = 9; // pino TRIG do sensor ultrassônico
int echo = 8;    // pino ECHO do sensor ultrassônico
int wheelsLeftForwardIN1 = 10, wheelsLeftReverseIN2 = 11;
int wheelsRigthForwardIN3 = 12, wheelsRigthReverseIN4 = 13;
float tempo;
const float calculationNumberForCm = 29.4;
const float dividedByTwo = 2;
float calculation;
float distanceObstacleCm;
float distanceObstacleCmFrontRight;
float distanceObstacleCmFrontLeft;
float rigthSide;
float leftSide;
const int front = 90;
const int right = 0;
const int left = 180;
const int frontRight = 45;
const int frontLeft = 137;
const int waitingTimeServo = 500;
void setup()
{
    Serial.begin(9600);
    pinMode(wheelsLeftForwardIN1, OUTPUT);
    pinMode(wheelsLeftReverseIN2, OUTPUT);
    pinMode(wheelsRigthForwardIN3, OUTPUT);
    pinMode(wheelsRigthReverseIN4, OUTPUT);
    motor.attach(7);
    pinMode(gatilho, OUTPUT);
    digitalWrite(gatilho, LOW);
    delayMicroseconds(10);
    pinMode(echo, INPUT);
}

void  walkForward() 
{
    digitalWrite(wheelsLeftForwardIN1, HIGH);
    digitalWrite(wheelsLeftReverseIN2, LOW);
    digitalWrite(wheelsRigthForwardIN3, HIGH);
    digitalWrite(wheelsRigthReverseIN4, LOW);
}

void stopCar()
{
    digitalWrite(wheelsLeftForwardIN1, LOW);
    digitalWrite(wheelsLeftReverseIN2, LOW);
    digitalWrite(wheelsRigthForwardIN3, LOW);
    digitalWrite(wheelsRigthReverseIN4, LOW);
}

void ultrassonico(int directionToTurn)
{
    motor.write(directionToTurn);
    delay(waitingTimeServo);
    digitalWrite(gatilho, HIGH);
    delayMicroseconds(10);
    digitalWrite(gatilho, LOW);
    tempo = pulseIn(echo, HIGH);
    // calcular as distâncias em centímetros
    calculation = tempo / calculationNumberForCm / dividedByTwo;
}

void loop()
{
    ultrassonico(front);
    distanceObstacleCm = calculation;
    ultrassonico(frontRight);
    distanceObstacleCmFrontRight = calculation;
    ultrassonico(frontLeft);
    distanceObstacleCmFrontLeft = calculation;
    if ((distanceObstacleCm >= 40) && (distanceObstacleCmFrontRight >= 40) && (distanceObstacleCmFrontLeft >= 40))
    {
        while (distanceObstacleCm > 40)
        {
            walkForward();
            ultrassonico(front);
            distanceObstacleCm = calculation;
            if (distanceObstacleCm <= 40)
            {
                stopCar();
                break;            }
            ultrassonico(frontRight);
            distanceObstacleCmFrontRight = calculation;
            if (distanceObstacleCmFrontRight <= 40)
            {
                stopCar();
                break;
            }
            ultrassonico(frontLeft);
            distanceObstacleCmFrontLeft = calculation;
            if (distanceObstacleCmFrontLeft <= 40)
            {
                stopCar();
                break;
            }
        }
    }
    else if ((distanceObstacleCm <= 40) || (distanceObstacleCmFrontRight <= 40) || (distanceObstacleCmFrontLeft <= 40))
    {
        //calcular a distancia do lado direito
        ultrassonico(right);
        rigthSide = calculation;
        //calcular a distancia do lado esquerdo
        ultrassonico(left);
        leftSide = calculation;
        motor.write(90);

        if (leftSide > rigthSide)
        {
            for (int i = 0; i <= 72; i++)
            {
                digitalWrite(wheelsLeftForwardIN1, LOW);
                digitalWrite(wheelsLeftReverseIN2, HIGH);
                digitalWrite(wheelsRigthForwardIN3, HIGH);
                digitalWrite(wheelsRigthReverseIN4, LOW);
                distanceObstacleCm = 50;
            }
            while (distanceObstacleCm >= 40)
            {
                walkForward();
                ultrassonico(front);
                distanceObstacleCm = calculation;
                if (distanceObstacleCm <= 40)
                {
                    stopCar();
                    break;
                }
                ultrassonico(frontRight);
                distanceObstacleCmFrontRight = calculation;
                if (distanceObstacleCmFrontRight <= 40)
                {
                    stopCar();
                    break;
                }
                ultrassonico(frontLeft);
                distanceObstacleCmFrontLeft = calculation;
                if (distanceObstacleCmFrontLeft <= 40)
                {
                    stopCar();
                    break;
                }
            }
        }
        else
        {
            for (int i = 0; i <= 70; i++)
            {
                digitalWrite(wheelsLeftForwardIN1, HIGH);
                digitalWrite(wheelsLeftReverseIN2, LOW);
                digitalWrite(wheelsRigthForwardIN3, LOW);
                digitalWrite(wheelsRigthReverseIN4, HIGH);
                distanceObstacleCm = 50;
            }
            while (distanceObstacleCm >= 40)
            {
                walkForward();
                ultrassonico(front);
                distanceObstacleCm = calculation;
                if (distanceObstacleCm <= 40)
                {
                    stopCar();
                    break;
                }
                ultrassonico(frontRight);
                distanceObstacleCmFrontRight = calculation;
                if (distanceObstacleCmFrontRight <= 40)
                {
                    stopCar();
                    break;
                }
                ultrassonico(frontLeft);
                distanceObstacleCmFrontLeft = calculation;
                if (distanceObstacleCmFrontLeft <= 40)
                {
                stopCar();
                break;
                }
            }
        }
    }
}
