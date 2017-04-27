#include <iostream>
#include "OpenNICam.h"

int main() {
    // create a camera that will display some debug info when connected
    OpenNICam cam;

    // let's wait so the callbacks can get called
    // wait for [enter]
    std::cout << "Press enter to quit." << std::endl;
    getchar();

    return 0;
}