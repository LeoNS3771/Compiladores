#ifndef SYMBOLS_HH
#define SYMBOLS_HH

#include <string>
#include <memory>
#include <map>


/*enum struct type{INT, FLOAT, CHAR, BOOL, WILDCARD, INVALID};
const std::map<std::string,type> types = {
    {"float"},
    {"int" },
    {"bool"},
    {"char"},
}*/

struct symbol{
    std::string name;
    std::string label;
    std::string type; 

    symbol(std::string n) : name(n), type("undefined"), label("") {}
};
extern std::map<std::string, std::shared_ptr<symbol>> symbols;

#endif