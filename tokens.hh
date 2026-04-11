#ifndef TOKENS_HH
#define TOKENS_HH
#include <string>

struct node{
    std::string label;
    std::string translation;
};

struct literal{
    std::string label;
};

struct symbol{
    std::string name;
    std::string type;
    std::string label;
};
#endif