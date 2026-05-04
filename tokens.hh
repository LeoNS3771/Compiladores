#ifndef TOKENS_HH
#define TOKENS_HH
#include "symbols.hh"

struct node {
    std::string label;
    std::string type;
    std::string translation;
    bool is_materialized = false;
};

enum struct Op { ARITHMETIC, LOGICAL, RELATIONAL, ASSIGNMENT};

const std::map<std::string, Op> operators = {
    {"+",  Op::ARITHMETIC},
    {"-",  Op::ARITHMETIC},
    {"*",  Op::ARITHMETIC},
    {"/",  Op::ARITHMETIC},
    {"%",  Op::ARITHMETIC},
    {"==", Op::RELATIONAL},
    {"!=", Op::RELATIONAL},
    {"<=", Op::RELATIONAL},
    {">=", Op::RELATIONAL},
    {"<",  Op::RELATIONAL},
    {">",  Op::RELATIONAL},
    {"||", Op::LOGICAL},
    {"&&", Op::LOGICAL},
    {"!",  Op::LOGICAL},
    {"=",  Op::ASSIGNMENT}
};


#endif