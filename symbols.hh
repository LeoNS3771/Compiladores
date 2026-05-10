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

    symbol(std::string n) : name(n), type("undefined"), label(""), is_static(false) {}
};
extern std::map<std::string, std::shared_ptr<symbol>> symbols;


/*
std::vector<std::vector<std::string>> ops = {
    {"+", "-", "*", "/", "%"},     
    {"==", "!=", "<=", ">=", "<", ">"},
    {"||", "&&", "!"}
};
extern std::map<std::string, std::string> op;
*/
#endif