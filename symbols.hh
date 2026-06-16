#ifndef SYMBOLS_HH
#define SYMBOLS_HH

#include <string>
#include <memory>
#include <vector>
#include <map>

struct Type {
    enum class Kind { PRIMITIVE, ARRAY };
    Kind kind;
    std::string base;
    int array_size;

    bool is_primitive() const { return kind == Kind::PRIMITIVE; }
    bool is_array()     const { return kind == Kind::ARRAY; }

    Type()                   : kind(Kind::PRIMITIVE), base("undefined"), array_size(0) {}  // Default
    Type(std::string b)      : kind(Kind::PRIMITIVE), base(b),           array_size(0) {}  // Default definindo tipo base


    // comparações entre structs (antes era string, mas strut não tem == e != por padrão)
    bool operator==(const Type& o) const { return kind == o.kind && base == o.base; }
    bool operator!=(const Type& o) const { return kind != o.kind || base != o.base; }
};

struct symbol {
    std::string name;
    std::string label;
    Type type;
    bool is_static;

    symbol(std::string n) : name(n), type(), label(""), is_static(false) {}
};

#endif