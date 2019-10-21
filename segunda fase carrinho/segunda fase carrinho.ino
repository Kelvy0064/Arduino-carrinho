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

void loop()
{
    motor.write(front);
    // disparar pulso ultrassônico
    digitalWrite(gatilho, HIGH);
    delayMicroseconds(10);
    digitalWrite(gatilho, LOW);
    // medir tempo de ida e volta do pulso ultrassônico
    tempo = pulseIn(echo, HIGH);
    // calcular as distâncias em centímetros
    distanceObstacleCm = tempo / calculationNumberForCm / dividedByTwo;
    if (distanceObstacleCm >= 40)
    {
        while (distanceObstacleCm > 40)
        {
            digitalWrite(wheelsLeftForwardIN1, HIGH);
            digitalWrite(wheelsLeftReverseIN2, LOW);
            digitalWrite(wheelsRigthForwardIN3, HIGH);
            digitalWrite(wheelsRigthReverseIN4, LOW);
            motor.write(front);
            delay(waitingTimeServo);
            digitalWrite(gatilho, HIGH);
            delayMicroseconds(10);
            digitalWrite(gatilho, LOW);
            tempo = pulseIn(echo, HIGH);
            distanceObstacleCm = tempo / calculationNumberForCm / dividedByTwo;
            Serial.println(distanceObstacleCm);
            Serial.println("Frente");
            if (distanceObstacleCm <= 40)
            {
                digitalWrite(wheelsLeftForwardIN1, LOW);
                digitalWrite(wheelsLeftReverseIN2, LOW);
                digitalWrite(wheelsRigthForwardIN3, LOW);
                digitalWrite(wheelsRigthReverseIN4, LOW);
                Serial.println("caindo fora obstaculo frente");
                distanceObstacleCm = 50;
                break;
            }
            motor.write(frontRight);
            delay(waitingTimeServo);
            digitalWrite(gatilho, HIGH);
            delayMicroseconds(10);
            digitalWrite(gatilho, LOW);
            tempo = pulseIn(echo, HIGH);
            distanceObstacleCmFrontRight = tempo / calculationNumberForCm / dividedByTwo;
            Serial.println(distanceObstacleCmFrontRight);
            Serial.println("Direita frente");
            if (distanceObstacleCmFrontRight <= 40)
            {
                digitalWrite(wheelsLeftForwardIN1, LOW);
                digitalWrite(wheelsLeftReverseIN2, LOW);
                digitalWrite(wheelsRigthForwardIN3, LOW);
                digitalWrite(wheelsRigthReverseIN4, LOW);
                Serial.println("caindo fora direita com obstaculo");
                distanceObstacleCm = 50;
                break;
            }
            motor.write(frontLeft);
            delay(waitingTimeServo);
            digitalWrite(gatilho, HIGH);
            delayMicroseconds(10);
            digitalWrite(gatilho, LOW);
            tempo = pulseIn(echo, HIGH);
            distanceObstacleCmFrontLeft = tempo / calculationNumberForCm / dividedByTwo;
            Serial.println(distanceObstacleCmFrontLeft);
            Serial.println("esquerda frente");
            if (distanceObstacleCmFrontRight <= 40)
            {
                digitalWrite(wheelsLeftForwardIN1, LOW);
                digitalWrite(wheelsLeftReverseIN2, LOW);
                digitalWrite(wheelsRigthForwardIN3, LOW);
                digitalWrite(wheelsRigthReverseIN4, LOW);
                Serial.println("caindo fora esquerda com bstaculo");
                distanceObstacleCm = 50;
                break;
            }
        }
    }
    else if ((distanceObstacleCm <= 40) || (distanceObstacleCmFrontRight <= 40) || (distanceObstacleCmFrontLeft <= 40))
    {

        // TODO
        //
        // leftSide  = getDistanceFromDirection(180)
        // rightSide = getDistanceFromDirection(90)
        //

        //calcular a distancia do lado direito
        motor.write(right);
        delay(waitingTimeServo);
        digitalWrite(gatilho, HIGH);
        delayMicroseconds(10);
        digitalWrite(gatilho, LOW);
        tempo = pulseIn(echo, HIGH);
        rigthSide = tempo / calculationNumberForCm / dividedByTwo;
        Serial.println("Mediu o lado direito"); //calcular a distancia do lado esquerdo
        motor.write(left);
        delay(waitingTimeServo);
        digitalWrite(gatilho, HIGH);
        delayMicroseconds(10);
        digitalWrite(gatilho, LOW);
        tempo = pulseIn(echo, HIGH);
        leftSide = tempo / calculationNumberForCm / dividedByTwo;
        motor.write(90);

        if (leftSide > rigthSide)
        {
            Serial.println("Mediu o lado direito");
            for (int i = 0; i <= 72; i++)
            {
                Serial.println("Virando para direita");
                digitalWrite(wheelsLeftForwardIN1, LOW);
                digitalWrite(wheelsLeftReverseIN2, HIGH);
                digitalWrite(wheelsRigthForwardIN3, HIGH);
                digitalWrite(wheelsRigthReverseIN4, LOW);
                distanceObstacleCm = 50;
            }
            while (distanceObstacleCm >= 40)
            {
                digitalWrite(wheelsLeftForwardIN1, HIGH);
                digitalWrite(wheelsLeftReverseIN2, LOW);
                digitalWrite(wheelsRigthForwardIN3, HIGH);
                digitalWrite(wheelsRigthReverseIN4, LOW);
                motor.write(front);
                delay(waitingTimeServo);
                digitalWrite(gatilho, HIGH);
                delayMicroseconds(10);
                digitalWrite(gatilho, LOW);
                tempo = pulseIn(echo, HIGH);
                distanceObstacleCm = tempo / calculationNumberForCm / dividedByTwo;
                Serial.println(distanceObstacleCm);
                Serial.println("Frente");
                if (distanceObstacleCm <= 40)
                {
                    digitalWrite(wheelsLeftForwardIN1, LOW);
                    digitalWrite(wheelsLeftReverseIN2, LOW);
                    digitalWrite(wheelsRigthForwardIN3, LOW);
                    digitalWrite(wheelsRigthReverseIN4, LOW);
                    Serial.println("caindo fora obstaculo frente");
                    distanceObstacleCm = 50;
                    break;
                }
                motor.write(frontRight);
                delay(waitingTimeServo);
                digitalWrite(gatilho, HIGH);
                delayMicroseconds(10);
                digitalWrite(gatilho, LOW);
                tempo = pulseIn(echo, HIGH);
                distanceObstacleCmFrontRight = tempo / calculationNumberForCm / dividedByTwo;
                Serial.println(distanceObstacleCmFrontRight);
                Serial.println("Direita frente");
                if (distanceObstacleCmFrontRight <= 40)
                {
                    digitalWrite(wheelsLeftForwardIN1, LOW);
                    digitalWrite(wheelsLeftReverseIN2, LOW);
                    digitalWrite(wheelsRigthForwardIN3, LOW);
                    digitalWrite(wheelsRigthReverseIN4, LOW);
                    Serial.println("caindo fora direita com obstaculo");
                    distanceObstacleCm = 50;
                    break;
                }
                motor.write(frontLeft);
                delay(waitingTimeServo);
                digitalWrite(gatilho, HIGH);
                delayMicroseconds(10);
                digitalWrite(gatilho, LOW);
                tempo = pulseIn(echo, HIGH);
                distanceObstacleCmFrontLeft = tempo / calculationNumberForCm / dividedByTwo;
                Serial.println(distanceObstacleCmFrontLeft);
                Serial.println("esquerda frente");
                if (distanceObstacleCmFrontRight <= 40)
                {
                    digitalWrite(wheelsLeftForwardIN1, LOW);
                    digitalWrite(wheelsLeftReverseIN2, LOW);
                    digitalWrite(wheelsRigthForwardIN3, LOW);
                    digitalWrite(wheelsRigthReverseIN4, LOW);
                    Serial.println("caindo fora esquerda com bstaculo");
                    distanceObstacleCm = 50;
                    break;
                }
            }
        }
        else
        {
            Serial.println("Virou para esquerda");
            for (int i = 0; i <= 70; i++)
            {
                Serial.println("virando");
                digitalWrite(wheelsLeftForwardIN1, HIGH);
                digitalWrite(wheelsLeftReverseIN2, LOW);
                digitalWrite(wheelsRigthForwardIN3, LOW);
                digitalWrite(wheelsRigthReverseIN4, HIGH);
                distanceObstacleCm = 50;
            }
            while (distanceObstacleCm >= 40)
            {
                digitalWrite(wheelsLeftForwardIN1, HIGH);
                digitalWrite(wheelsLeftReverseIN2, LOW);
                digitalWrite(wheelsRigthForwardIN3, HIGH);
                digitalWrite(wheelsRigthReverseIN4, LOW);
                motor.write(front);
                delay(waitingTimeServo);
                digitalWrite(gatilho, HIGH);
                delayMicroseconds(10);
                digitalWrite(gatilho, LOW);
                tempo = pulseIn(echo, HIGH);
                distanceObstacleCm = tempo / calculationNumberForCm / dividedByTwo;
                Serial.println(distanceObstacleCm);
                Serial.println("Frente");
                if (distanceObstacleCm <= 40)
                {
                    digitalWrite(wheelsLeftForwardIN1, LOW);
                    digitalWrite(wheelsLeftReverseIN2, LOW);
                    digitalWrite(wheelsRigthForwardIN3, LOW);
                    digitalWrite(wheelsRigthReverseIN4, LOW);
                    Serial.println("caindo fora obstaculo frente");
                    distanceObstacleCm = 50;
                    break;
                }
                motor.write(frontRight);
                delay(waitingTimeServo);
                digitalWrite(gatilho, HIGH);
                delayMicroseconds(10);
                digitalWrite(gatilho, LOW);
                tempo = pulseIn(echo, HIGH);
                distanceObstacleCmFrontRight = tempo / calculationNumberForCm / dividedByTwo;
                Serial.println(distanceObstacleCmFrontRight);
                Serial.println("Direita frente");
                if (distanceObstacleCmFrontRight <= 40)
                {
                    digitalWrite(wheelsLeftForwardIN1, LOW);
                    digitalWrite(wheelsLeftReverseIN2, LOW);
                    digitalWrite(wheelsRigthForwardIN3, LOW);
                    digitalWrite(wheelsRigthReverseIN4, LOW);
                    Serial.println("caindo fora direita com obstaculo");
                    distanceObstacleCm = 50;
                    break;
                }
                motor.write(frontLeft);
                delay(waitingTimeServo);
                digitalWrite(gatilho, HIGH);
                delayMicroseconds(10);
                digitalWrite(gatilho, LOW);
                tempo = pulseIn(echo, HIGH);
                distanceObstacleCmFrontLeft = tempo / calculationNumberForCm / dividedByTwo;
                Serial.println(distanceObstacleCmFrontLeft);
                Serial.println("esquerda frente");
                if (distanceObstacleCmFrontRight <= 40)
                {
                    digitalWrite(wheelsLeftForwardIN1, LOW);
                    digitalWrite(wheelsLeftReverseIN2, LOW);
                    digitalWrite(wheelsRigthForwardIN3, LOW);
                    digitalWrite(wheelsRigthReverseIN4, LOW);
                    Serial.println("caindo fora esquerda com bstaculo");
                    distanceObstacleCm = 50;
                    break;
                }
            }
        }
    }
}
