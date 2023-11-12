#pragma once
#include <ctime>
#include <string>

class MyLog {
private:
    double m_time_begin;
    double getClockNow() const {
        return (double)clock() / CLOCKS_PER_SEC;
    }
    double getRunTimeNow() const {
        return getClockNow() - m_time_begin;
    }

public:
    MyLog() {
        m_time_begin = getClockNow();
    }
    void log(std::string msg) { // print console log
        fprintf(stderr, "[%10.3lf] %s\n", getRunTimeNow(), msg.c_str());
    }
};