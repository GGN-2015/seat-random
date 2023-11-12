#pragma once
<<<<<<< HEAD

#include <cstdio>
=======
>>>>>>> e8628d851664def5724913356abc4eb6460bceee
#include <ctime>
#include <string>

class MyLog {
private:
<<<<<<< HEAD
    double initial_time;

    double getClockNow() const {
        return (double)clock() / CLOCKS_PER_SEC;
    }
    double getTimeNow() const {
        return getClockNow() - initial_time;
=======
    double m_time_begin;
    double getClockNow() const {
        return (double)clock() / CLOCKS_PER_SEC;
    }
    double getRunTimeNow() const {
        return getClockNow() - m_time_begin;
>>>>>>> e8628d851664def5724913356abc4eb6460bceee
    }

public:
    MyLog() {
<<<<<<< HEAD
        initial_time = this->getClockNow();
    }

    void log(std::string msg) { // output log into stderr
        fprintf(stderr, "[%9.3f] %s\n", this->getTimeNow(), msg.c_str());
=======
        m_time_begin = getClockNow();
    }
    void log(std::string msg) { // print console log
        fprintf(stderr, "[%10.3lf] %s\n", getRunTimeNow(), msg.c_str());
>>>>>>> e8628d851664def5724913356abc4eb6460bceee
    }
};