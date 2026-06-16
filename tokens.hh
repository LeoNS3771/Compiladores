#ifndef TOKENS_HH
#define TOKENS_HH
#include "symbols.hh"
#include "loops.hh"

struct node {
    std::string label;
    Type type;
    std::string translation;
    bool is_materialized;
    bool is_static;

    std::string jumps;
    std::string labels_jumps;
    std::vector<std::string> elements; // labels dos elementos do array

    node() : label(""), type(), translation(""), is_materialized(false), is_static(false), jumps(""), labels_jumps("") {}
};

inline std::string to_ir_type(const Type& t) {
    if(t.is_array())        return t.base + "*";
    if(t.base == "bool")    return "int";
    if(t.base == "string")  return "char*";
    return t.base;
}

// Sobrecarga para compatibilidade com chamadas to_ir_type(string) que ainda existem
inline std::string to_ir_type(const std::string& s) {
    return to_ir_type(Type(s));
}

enum class ContextType { LOOP, SWITCH };

struct Context {
    ContextType type;
    int depth;
    std::string start_label;
    std::string end_label;
    std::string continue_label;
    node switch_node;
};

struct op {
    std::string label;
    std::string category;

    op() : label(""), category("") {}
    op(std::string l, std::string c) : label(l), category(c) {}
};

#endif