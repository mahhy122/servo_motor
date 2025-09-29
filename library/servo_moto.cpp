#include "DS3218Servo.h"
#include <Servo.h> // Arduino標準のServoライブラリを利用してPWM生成を簡略化

// Servoオブジェクトを内部的に使用
// 通常のArduino UNO/Nanoなどでは16ビットタイマを2つ使用するため、最大12個のサーボが使用可能
Servo internalServo;

DS3218Servo::DS3218Servo(){
    _pin = -1;
    _max_degree = 180; // デフォルトは180度
    _current_pulse_us = NEUTRAL_PULSE_US;
}
void DS3218Servo::attach(int pin, int max_degree) {
    _pin = pin;
    _max_degree = (max_degree == 270) ? 270 : 180; // 180°または270°に限定 

    // Servoライブラリのattachを使用
    internalServo.attach(_pin, MIN_PULSE_US, MAX_PULSE_US);
    
    // 初期位置としてニュートラル位置に設定
    writeMicroseconds(NEUTRAL_PULSE_US); 
}

void DS3218Servo::writeMicroseconds(int pulse_us) {
    // 範囲チェックとクランプ (500usから2500us) 
    _current_pulse_us = constrain(pulse_us, MIN_PULSE_US, MAX_PULSE_US);

    // ServoライブラリのwriteMicrosecondsを使用
    internalServo.writeMicroseconds(_current_pulse_us);
}

void DS3218Servo::writeDegree(int degree) {
    // ニュートラル位置(1500us)
    int pulse_us;
    if (_max_degree == 180) {
        // 0 -> 500, 90 -> 1500, 180 -> 2500
        pulse_us = map(degree, 0, 180, MIN_PULSE_US, MAX_PULSE_US);
    } else { // _max_degree == 270
        // 0 -> 500, 135 -> 1500, 270 -> 2500
        pulse_us = map(degree, 0, 270, MIN_PULSE_US, MAX_PULSE_US);
    }
    // パルス幅を設定
    writeMicroseconds(pulse_us);
}

int DS3218Servo::readMicroseconds() {
    return _current_pulse_us;
}

void DS3218Servo::detach() {
    internalServo.detach();
    _pin = -1;
}