#include "DS3218Servo.h"

// サーボ制御ピンを指定 (PWM対応ピンを使用してください)
const int SERVO_PIN = 9; 

// サーボオブジェクトの作成
DS3218Servo myServo;

void setup() {
    Serial.begin(9600);
    // 180度に設定したい場合は myServo.attach(SERVO_PIN, 180);
    myServo.attach(SERVO_PIN, 270); 
    Serial.println("Servo attached (270 degree mode).");
}

void loop() {
    // 角度制御の例 (0度から270度)
    for (int angle = 0; angle <= 270; angle += 10) {
        myServo.writeDegree(angle);
        Serial.print("Angle: ");
        Serial.println(angle);
        delay(500); // 0.5秒待機
    }

    // パルス幅制御の例 (最小から最大)
    myServo.writeMicroseconds(DS3218Servo::MIN_PULSE_US); // 500us (0度)
    Serial.println("Pulse: 500 us");
    delay(1000);

    myServo.writeMicroseconds(DS3218Servo::NEUTRAL_PULSE_US); // 1500us (中立)
    Serial.println("Pulse: 1500 us (Neutral)");
    delay(1000);

    myServo.writeMicroseconds(DS3218Servo::MAX_PULSE_US); // 2500us (最大角度)
    Serial.println("Pulse: 2500 us");
    delay(1000);
}