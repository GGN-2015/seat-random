#pragma once

#include <cstdio>
#include <ctime>
#include <string>

class MyLog {
private:
    double initial_time;

    double getClockNow() const {
        return (double)clock() / CLOCKS_PER_SEC;
    }
    double getTimeNow() const {
        return getClockNow() - initial_time;
    }

public:
    MyLog() {
        initial_time = this->getClockNow();
    }

    void log(std::string msg) { // output log into stderr
        fprintf(stderr, "[%9.3f] %s\n", this->getTimeNow(), msg.c_str());
    }
};