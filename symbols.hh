#ifndef SYMBOLS_HH
#define SYMBOLS_HH

#include <string>
#include <memory>
#include <map>

struct symbol{
    std::string name;
    std::string type; 
    std::string label;

    symbol(std::string n) : name(n), type(""), label("") {}
};

extern std::map<std::string, std::shared_ptr<symbol>> symbols;

#endif