#include <SoftwareSerial.h>
#include <Servo.h>
Servo motor;
int gatilho = 9; // pino TRIG do sensor ultrassônico
int echo = 8; // pino ECHO do sensor ultrassônico
int wheelsLeftForwardIN1 = 10, wheelsLeftReverseIN2 = 11;
int wheelsRigthForwardIN3 = 12, wheelsRigthReverseIN4 = 13;
float tempo;
const float calculationNumberForCm = 29.4;
const float dividedByTwo = 2;
float distanceObstacleCm;
float rigthSide;
float leftSide;

void setup(){
    Serial.begin(9600);
    pinMode(wheelsLeftForwardIN1, OUTPUT);
    pinMode(wheelsLeftReverseIN2, OUTPUT);
    pinMode(wheelsRigthForwardIN3, OUTPUT);
    pinMode(wheelsRigthReverseIN4, OUTPUT);
    motor.attach(7);
    pinMode(gatilho, OUTPUT);
    digitalWrite(gatilho, LOW);
    delayMicroseconds(10);
    pinMode(echo,INPUT);
}

void loop() {
    motor.write(90);
    // disparar pulso ultrassônico
    digitalWrite(gatilho, HIGH);
    delayMicroseconds(20);
    digitalWrite(gatilho, LOW);
    // medir tempo de ida e volta do pulso ultrassônico
    tempo = pulseIn(echo, HIGH);
    // calcular as distâncias em centímetros
    distanceObstacleCm = tempo / calculationNumberForCm / dividedByTwo;    
    if (distanceObstacleCm >= 20) {
        while (distanceObstacleCm > 20) {
            digitalWrite(wheelsLeftForwardIN1, HIGH);
            digitalWrite(wheelsLeftReverseIN2, LOW);
            digitalWrite(wheelsRigthForwardIN3, HIGH);
            digitalWrite(wheelsRigthReverseIN4, LOW);
            motor.write(90);
            digitalWrite(gatilho, HIGH);
            delayMicroseconds(10);
            digitalWrite(gatilho, LOW);
            tempo = pulseIn(echo, HIGH);
            distanceObstacleCm = tempo / calculationNumberForCm / dividedByTwo;
            if (distanceObstacleCm <= 20) {
                digitalWrite(wheelsLeftForwardIN1, LOW);
                digitalWrite(wheelsLeftReverseIN2, LOW);
                digitalWrite(wheelsRigthForwardIN3, LOW);
                digitalWrite(wheelsRigthReverseIN4, LOW);
              }
        }
    } else {

        // TODO
        // 
        // leftSide  = getDistanceFromDirection(180)
        // rightSide = getDistanceFromDirection(90)
        //
        
        //calcular a distancia do lado direito
        motor.write(0);
        delay(2000);
        digitalWrite(gatilho, HIGH);
        delayMicroseconds(10);
        digitalWrite(gatilho, LOW);
        tempo = pulseIn(echo, HIGH);
        rigthSide = tempo / calculationNumberForCm / dividedByTwo;
        //calcular a distancia do lado esquerdo
        motor.write(180);
        delay(2000);
        digitalWrite(gatilho, HIGH);
        delayMicroseconds(10);
        digitalWrite(gatilho, LOW);
        tempo = pulseIn(echo, HIGH);
        leftSide = tempo / calculationNumberForCm / dividedByTwo;
        //motor.write(90);
        
        if (leftSide > rigthSide) {
            for (int i = 0; i <=75; i++) {
                digitalWrite(wheelsLeftForwardIN1, LOW);
                digitalWrite(wheelsLeftReverseIN2, HIGH);
                digitalWrite(wheelsRigthForwardIN3, HIGH);
                digitalWrite(wheelsRigthReverseIN4, LOW);
            }
            while (distanceObstacleCm >= 20) {
                digitalWrite(wheelsLeftForwardIN1, HIGH);
                digitalWrite(wheelsLeftReverseIN2, LOW);
                digitalWrite(wheelsRigthForwardIN3, HIGH);
                digitalWrite(wheelsRigthReverseIN4, LOW);
                digitalWrite(gatilho, HIGH);
                delayMicroseconds(10);
                digitalWrite(gatilho, LOW);
                tempo = pulseIn(echo, HIGH);
                distanceObstacleCm = tempo / calculationNumberForCm / dividedByTwo;
                if (distanceObstacleCm <= 20) {
                    digitalWrite(wheelsLeftForwardIN1, LOW);
                    digitalWrite(wheelsLeftReverseIN2, LOW);
                    digitalWrite(wheelsRigthForwardIN3, LOW);
                    digitalWrite(wheelsRigthReverseIN4, LOW);
              }
            }
        }else
            for (int i = 0; i <=70; i++) {
              Serial.println("to no for virando as rodas");
                digitalWrite(wheelsLeftForwardIN1, HIGH);
                digitalWrite(wheelsLeftReverseIN2, LOW);
                digitalWrite(wheelsRigthForwardIN3, LOW);
                digitalWrite(wheelsRigthReverseIN4, HIGH);
            }
            while (distanceObstacleCm >= 20) {
              Serial.println("seguindo meu rumo!");
                digitalWrite(wheelsLeftForwardIN1, HIGH);
                digitalWrite(wheelsLeftReverseIN2, LOW);
                digitalWrite(wheelsRigthForwardIN3, HIGH);
                digitalWrite(wheelsRigthReverseIN4, LOW);
                digitalWrite(gatilho, HIGH);
                delayMicroseconds(10);
                digitalWrite(gatilho, LOW);
                tempo = pulseIn(echo, HIGH);
                distanceObstacleCm = tempo / calculationNumberForCm / dividedByTwo;
                if (distanceObstacleCm <= 20) {
                   digitalWrite(wheelsLeftForwardIN1, LOW);
                   digitalWrite(wheelsLeftReverseIN2, LOW);
                   digitalWrite(wheelsRigthForwardIN3, LOW);
                   digitalWrite(wheelsRigthReverseIN4, LOW);
              }
            }
    
    }
}
