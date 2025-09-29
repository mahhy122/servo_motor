#ifndef DS3218SERVO_H
#define DS3218SERVO_H

#include <Arduino.h>

class DS3218Servo {
public:
    // コンストラクタ
    DS3218Servo();
    void attach(int pin, int max_degree = 180);
    //パルス幅をマイクロ秒で指定
    void writeMicroseconds(int pulse_us);
    //動かす部分
    void writeDegree(int degree);
    //現在のパルス幅をマイクロ秒で取得 
    int readMicroseconds();

    void detach();

private:
    int _pin;
    int _max_degree;
    int _current_pulse_us;
    // 最小パルス幅: 500 µsec 
    static const int MIN_PULSE_US = 500;
    // 中立パルス幅: 1500 µsec 
    static const int NEUTRAL_PULSE_US = 1500;
    // 最大パルス幅: 2500 µsec 
    static const int MAX_PULSE_US = 2500;
};

#endif
