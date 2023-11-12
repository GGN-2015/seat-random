#pragma once

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>

#define SEAT_SET_FILE  "..\\config\\seat_set.txt"
#define MAX_LINE_WIDTH (32)
#define FLAG_SEAT      (1) // to show someplace is a seat
#define FLAG_EMPTY     (0) // to show someplace is an empty position

typedef std::vector<int>     IntList;
typedef std::vector<IntList> IntMatrix;

class SeatSet {
private:
    MyLog*    m_my_log;
    IntMatrix m_int_matrix;
    int       m_seat_cnt;

    void readInFromFile(FILE* fpin) { // read in data from seat_set.txt
        m_int_matrix.clear();
        int max_width = 0;

        while(!feof(fpin)) { // read from file line by line
            char buffer[MAX_LINE_WIDTH + 1] = {};
            (void)fgets(buffer, MAX_LINE_WIDTH, fpin);

            int line_width = strlen(buffer);
            if(line_width >= MAX_LINE_WIDTH) {
                m_my_log -> log("SeatSet: line too long in seat set file.");
                assert(line_width < MAX_LINE_WIDTH);
            }

            IntList int_list = {}; // create new line
            for(int i = 0; buffer[i]; i += 1) {
                char c = buffer[i];
                if(c == 'X' || c == 'x') { // there is a seat
                    int_list.push_back(FLAG_SEAT);
                    m_seat_cnt += 1;
                }
                if(c == '-' || c == '_') { // there is an empty position
                    int_list.push_back(FLAG_EMPTY);
                }
            }

            // save every line into a matrix
            m_int_matrix.push_back(int_list);
            max_width = std::max(max_width, (int)int_list.size());
        }

        // delete empty line in the end
        while(m_int_matrix.size() > 0 && m_int_matrix[m_int_matrix.size() - 1].size() == 0) {
            m_int_matrix.pop_back();
        }

        // make every row the same length
        assert(max_width > 0);
        for(int i = 0; i < (int)m_int_matrix.size(); i += 1) {
            while(m_int_matrix[i].size() < max_width) {

                // add an empty seat to some line
                m_int_matrix[i].push_back(FLAG_EMPTY);
            }
        }
    }

    std::string getRowString(int row_index) const {
        assert(0 <= row_index && row_index < m_int_matrix.size());

        std::string ans = "";
        const IntList& row_list = m_int_matrix[row_index];

        for(int i = 0; i < row_list.size(); i += 1) {
            assert(row_list[i] == FLAG_SEAT || row_list[i] == FLAG_EMPTY);

            if(row_list[i] == FLAG_SEAT) {
                ans += "X"; // "X" for a seat
            }else {
                ans += "-"; // dash for an empty place
            }
        }
        return ans;
    }

public:
    SeatSet(MyLog* log): m_my_log(log), m_seat_cnt(0) {
        FILE* fpin = fopen(SEAT_SET_FILE, "r"); // check file exist
        if(fpin == nullptr) {
            m_my_log -> log("SeatSet: seat set file not found.");
            assert(fpin != nullptr);
        }

        readInFromFile(fpin);
        assert(m_int_matrix.size() > 0); // there should be at least one line
    }

    void debugOutput() const {
        int row = this -> getRowCnt();
        int col = this -> getColCnt();

        // output the seat set
        m_my_log -> log("SeatSet: debugOutput, total seat_cnt = " + std::to_string(m_seat_cnt));
        for(int i = 0; i < row; i += 1) {
            m_my_log -> log(this -> getRowString(i));
        }
    }

    int getSeatCnt() const {
        return m_seat_cnt; // return the number of seat
    }
    int getRowCnt() const {
        return m_int_matrix.size();
    }
    int getColCnt() const {
        assert(getRowCnt() > 0);
        return m_int_matrix[0].size();
    }

    int getFlagByIndex(int i, int j) const {
        assert(0 <= i && i < getRowCnt());
        assert(0 <= j && j < getColCnt());

        return m_int_matrix[i][j]; // return FLAG_SEAT or FLAG_EMPTY
    }
};