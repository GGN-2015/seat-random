#include "MyLog.h"
#include "SeatSet.h"

int main() {
    MyLog   my_log;
    SeatSet seat_set(&my_log);

    seat_set.debugOutput();
    return 0;
}
