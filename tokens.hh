#ifndef TOKENS_HH
#define TOKENS_HH
#include "symbols.hh"
#include "loops.hh"

struct node {
    std::string label;
    std::string name;
    Type type;
    std::string translation;
    bool is_materialized;
    bool is_static;

    std::string jumps;
    std::string labels_jumps;
    std::vector<std::string> elements; // labels dos elementos do array
    std::vector<std::vector<std::string>> elements_group; // para array de structs

    node() : label(""), type(), translation(""), is_materialized(false), is_static(false), jumps(""), labels_jumps("") {}
};

// Movi to_ir_type para o sintatico pra conseguir ler structs
std::string to_ir_type(const Type& t);  // só declaração

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