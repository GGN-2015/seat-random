#pragma once

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "MyLog.h"
typedef std::vector<int> IntList;

class RandomList {
private:
    MyLog*  m_my_log;
    IntList m_int_list;
    IntList m_rev_list;

public:
    int getRandomInt(int L, int R) const {
        assert(R >= L);

        #ifdef _WIN32
            int rnd = (rand() << 15) | rand();
        #else
            int rnd = rand(); // linux flavor random integer
        #endif

        return rnd % (R - L + 1) + L;
    }

    RandomList(MyLog* log): m_my_log(log) {
        srand(time(NULL));
    }

    int getValueByIndex(int index) const {
        assert(0 <= index && index < m_int_list.size());
        return m_int_list[index];
    }

    void generate(int length) {
        assert(length > 0);

        // construct initial array
        m_int_list.clear();
        m_rev_list.clear(); // rev_list is the reverse function
        for(int i = 0; i < length; i += 1) {
            m_int_list.push_back(i);
        }

        // random shuffle
        for(int i = length - 1; i >= 0; i -= 1) {
            int j = getRandomInt(i, length - 1);
            if(j != i) {
                std::swap(m_int_list[i], m_int_list[j]);
            }
        }

        // generate rev_list
        m_rev_list.resize(length, 0);
        for(int i = 0; i < length; i += 1) {
            m_rev_list[m_int_list[i]] = i; // give the value, get the position
        }
    }

    int get(int index) const {
        assert(0 <= index && index < m_int_list.size());
        return m_int_list[index]; // return a value in array
    }

    int getIndex(int value) const {
        assert(0 <= value && value < m_rev_list.size());
        return m_rev_list[value];
    }

    void debugOutput() const {
        assert(m_int_list.size() > 0);
        
        for(int i = 0; i < m_int_list.size(); i += 1) {
            m_my_log -> log(std::to_string(m_int_list[i]));
        }
    }

    void selfCheck(int length, int trial_time) {
        assert(trial_time > 0);
        assert(length > 0);

        IntList hit_cnt; // count the position frequency for value = 0
        hit_cnt.resize(length, 0);

        for(int i = 0; i < trial_time; i += 1) {
            this -> generate(length);

            hit_cnt[getIndex(0)] += 1;
        }

        // output trial rate
        for(int i = 0; i < hit_cnt.size(); i += 1) {
            m_my_log -> log("Hit Rate For Position " + std::to_string(i) + " = "
                + std::to_string(1.0 * hit_cnt[i] / trial_time)); // output hit rate
        }
    }
};