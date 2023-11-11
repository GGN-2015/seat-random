#include <cstdlib>

#include "MyLog.h"
#include "NameList.h"
#include "RandomMap.h"
#include "SeatSet.h"

int main() {
    system("chcp 65001 > nul"); // change to active code page: unicode

    MyLog      my_log;
    SeatSet    seat_set    (&my_log); // read file when constructed
    NameList   name_list   (&my_log); // read file when constructed
    RandomMap  random_map  (&my_log, &name_list, &seat_set);
    
    random_map.outputToFile("tmp.txt");
    return 0;
}
