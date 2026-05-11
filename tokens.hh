#ifndef TOKENS_HH
#define TOKENS_HH
#include "symbols.hh"
#include <set>

struct node{
    std::string label;
    std::string type;
    std::string translation;
    bool is_materialized;
    bool has_error;
    
    node() : label(""), type(""), translation(""), is_materialized(false), has_error(false) {}
};

struct op{
    std::string label;
    std::string category;

    op() : label(""), category("") {}
    op(std::string l, std::string c) : label(l), category(c) {}
};


////*** TABELAS DE CONVERSÃO ***////

/* Declaração de tabela de conversão binária */
using matrix = std::map<std::pair<std::string, std::string>, std::string>;
inline std::map<std::string, matrix> binary_table;

/* Declaração de tabelas de conversão unárias */
using linear = std::map<std::string,std::string>;
inline std::map<std::string, linear> unary_table;

inline std::set<std::pair<std::string,std::string>> cast_table;


////*** INICIALIZAÇÃO DAS TABELAS DE CONVERSÃO ***////

void inline init_conversion_table(){
    /* Expressões Aritméticas Binárias */
    binary_table["arithmetic"] = {
        {{"int", "int"}, "int"},
        {{"int", "float"}, "float"},
        {{"float", "int"}, "float"},
        {{"float", "float"}, "float"},
        {{"char", "char"}, "char"},
        //{{"string", "string"}, "string"}
    };

    /* Expressões Lógicas Binárias */
    binary_table["logical"] = {
        {{"bool", "bool"}, "bool"}
    };

    /* Expressões Relacionais Binárias */
    binary_table["relational"] = {
        {{"int", "int"}, "bool"},
        {{"float", "float"}, "bool"},
        {{"int", "float"}, "bool"},
        {{"char", "char"}, "bool"}
        //{{"string", "string"}, "bool"}
    };

    /* Expressões Lógicas Unárias */
    unary_table["logical"] = {
        {"bool", "bool"}
    };

    /* Expressões Aritméticas Unárias */
    /*
    unary_table["arithmetic"] = {
        {"int", "int"},
        {"float", "float"},
        {"char", "int"}
    };
    */

    /* Conversão Explícita */
    cast_table = {
        {"float", "int"},
        {"int", "float"},
        {"int", "char"},
        {"char", "int"},
        {"bool", "int"}
    };
}

#endif