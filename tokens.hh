#ifndef TOKENS_HH
#define TOKENS_HH
#include "symbols.hh"
#include "loops.hh"

struct node{
    std::string label;
    std::string type;
    std::string ir_type; // Tipo que vai ser passado para o codigo intermediario
    std::string translation;
    bool is_materialized;
    bool is_static;

    // Se for um nó condicional
    std::string jumps; 
    std::string labels_jumps;

    node() : label(""), type(""), translation(""), is_materialized(false), is_static(false), jumps(""), labels_jumps("") {}
};

enum class ContextType {LOOP, SWITCH};

struct Context {
    ContextType type;
    int depth;
    std::string start_label;
    std::string end_label;

    // Caso seja um switch
    node switch_node;
};


struct op{
    std::string label;
    std::string category;
    
    op() : label(""), category("") {}
    op(std::string l, std::string c) : label(l), category(c) {}
};

#endif