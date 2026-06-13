#ifndef LOOPS_HH
#define LOOPS_HH

#include <string>

struct loopInfo {
    int depth;
    std::string labelStart;
    std::string labelEnd;
    std::string labelContinue;
};

#endif