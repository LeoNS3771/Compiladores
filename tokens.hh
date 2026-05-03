#ifndef TOKENS_HH
#define TOKENS_HH
#include "symbols.hh"

enum token{literal,identifier};

struct node {
    std::string label;
    std::string type;
    std::string translation;
    bool is_materialized = false;
};

#endif