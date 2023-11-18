#include <cstdlib>

#include "MyLog.h"
#include "NameList.h"
#include "RandomMap.h"
#include "SeatSet.h"

#define SUB_PROCESS (1)
int main() {
    #ifdef _WIN32
        #if (!SUB_PROCESS) // do not change chcp in subprocess mod
            system("chcp 65001 > nul"); // change to active code page: unicode
        #endif
    #endif

    MyLog      my_log;
    SeatSet    seat_set    (&my_log); // read file when constructed
    NameList   name_list   (&my_log); // read file when constructed
    RandomMap  random_map  (&my_log, &name_list, &seat_set);
    
    random_map.outputToRandomFile();
    return 0;
}
