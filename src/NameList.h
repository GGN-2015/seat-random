#pragma once

#include <cassert>
#include <cstring>
#include <string>
#include <vector>
#include "MyLog.h"

#define NAME_LIST_FILE "..\\config\\name_list.txt"
#define MAX_NAME_LENGTH (32)

typedef std::vector<std::string> StringList;

class NameList {
private:
    StringList m_name_list;
    MyLog*     m_my_log;

public:
    NameList(MyLog* log): m_my_log(log) {
        FILE* fpin = fopen(NAME_LIST_FILE, "r");
        if(fpin == nullptr) {
            m_my_log -> log("NameList: name list file not found.");
            assert(fpin != nullptr);
        }

        while(!feof(fpin)) {
            char buffer[MAX_NAME_LENGTH + 1] = {};
            (void)fgets(buffer, MAX_NAME_LENGTH, fpin); // a name a line

            for(int i = 0; buffer[i]; i += 1) {
                if(buffer[i] == '\n' || buffer[i] == '\r' || buffer[i] == EOF) {
                    buffer[i] = 0; // delete CRLF in the end of line
                }
            }

            int name_length = strlen(buffer); // do not include empty string into name list
            if(name_length >= 1) {
                m_name_list.push_back(std::string(buffer));
            }
            
        }
    }

    int getSize() const {
        return m_name_list.size();
    }

    void debugOutput() const {
        m_my_log -> log("NameList: total name_cnt = " + std::to_string(m_name_list.size()));
        for(int i = 0; i < m_name_list.size(); i += 1) {

            m_my_log -> log(std::to_string(i) + ":\t\t" + m_name_list[i] + "\t\t("
                + std::to_string(m_name_list[i].size()) + ")"); // output every name
        }
    }

    std::string getNameByIndex(int index) const {
        assert(0 <= index && index < m_name_list.size());
        return m_name_list[index];
    }
};