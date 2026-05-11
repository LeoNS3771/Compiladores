#ifndef SYMBOLS_HH
#define SYMBOLS_HH

#include <string>
#include <memory>
#include <vector>
#include <map>

struct symbol{
    std::string name;
    std::string label;
    std::string type;
    bool is_static;
    bool is_initialized;

    symbol(std::string n) : name(n), type("undefined"), label(""), is_static(false), is_initialized(false) {}
};
#endif