
#include <time.h>

int rand_basic(int a, int b){
    int mx = a > b ? a : b;
    int mn = a > b ? b : a;
    time_t timestamp = time(NULL);

    return mn + (timestamp % (mx-mn));
}
