#ifndef TOKENS_HH
#define TOKENS_HH
#include "symbols.hh"
#include "loops.hh"

struct node{
    std::string label;
    std::string type;
    std::string translation;
    bool is_materialized;
    bool is_static;

    node() : label(""), type(""), translation(""), is_materialized(false), is_static(false) {}
};

struct op{
    std::string label;
    std::string category;
    
    op() : label(""), category("") {}
    op(std::string l, std::string c) : label(l), category(c) {}
};

#endif