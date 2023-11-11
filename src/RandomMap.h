#pragma once

#include "MyLog.h"
#include "NameList.h"
#include "RandomList.h"
#include "SeatSet.h"

#define RANDOM_FILENAME_LENGTH (32)

class RandomMap {
private:
    MyLog*      m_my_log;
    NameList*   m_name_list;
    SeatSet*    m_seat_set;
    RandomList  m_random_list;
    int         m_total_number; // total number of seat = total number of name

    std::string getRandomFileName() const {
        std::string filename = "";
        for(int i = 0; i < RANDOM_FILENAME_LENGTH; i += 1) {
            filename += (char)('0' + m_rand_list.getRandomInt(0, 9));
        }
        filename += ".txt";
        return filename;
    }

public:
    RandomMap(MyLog* log, NameList* name_list, SeatSet* seat_set): 
        m_my_log(log), m_name_list(name_list), m_seat_set(seat_set), m_random_list(log) {
        m_total_number = m_name_list -> getSize();

        if(m_name_list -> getSize() != m_seat_set -> getSeatCnt()) {
            m_my_log -> log("RandomMap: total number of name != total number of seat.");
            assert(m_name_list -> getSize() == m_seat_set -> getSeatCnt());
        }
        m_random_list.generate(m_total_number);
    }

    void outputToFile(std::string filename) const {
        FILE* fpout = fopen(filename.c_str(), "w"); // output to file
        assert(fpout != nullptr);

        int row = m_seat_set -> getRowCnt();
        int col = m_seat_set -> getColCnt();

        int cnt = 0;
        for(int i = 0; i < row; i += 1) {
            for(int j = 0; j < col; j += 1) {
                int flag = m_seat_set -> getFlagByIndex(i, j);
                std::string name_now = "";

                if(flag == FLAG_SEAT) {
                    int active_pos = m_random_list.getValueByIndex(cnt);
                    name_now       = m_name_list -> getNameByIndex(active_pos);
                    cnt           += 1;
                }

                if(j != col - 1) {
                    name_now += ","; // seprate every name with a comma
                }
                fprintf(fpout, "%s", name_now.c_str());
            }
            fprintf(fpout, "\n");
        }
        fclose(fpout);
    }

    void outputToRandomFile() {
        std::string filename = getRandomFilename();
        std::string filepath = "..\\history\\" + filename;

        outputToFile(filepath);
        printf("%s\n", filename.c_str()); // output filename to stdout
    }
};