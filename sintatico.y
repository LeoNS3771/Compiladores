/*** Configuração do Bison C++***/
%skeleton "lalr1.cc"
%require "3.2"
%language "c++" 

%define api.value.type variant
%define api.token.constructor
%define parse.error verbose // Mensagem de erro melhor
%code requires{
    #include <string>
    #include "tokens.hh"
}

%code {
    #include "y.tab.hh"
    #include <iostream>
    #include <fstream>
    #include <vector>
    #include <string>
    using namespace std;

    yy::parser::symbol_type yylex();
    extern int yylineno;

    int tmp_var_count = 0;
    string code;
    vector<symbol> symbols;
    vector<pair<string, string>> variables;

    string gen_tmp_variable();
    string gen_declarations();
    bool is_numeric(string s);
    symbol* search_symbol(string label, string type_inferred);
    node gen_expr(const node& l, string op, const node& r);
}
/*** Declaração de tokens ***/
%token <literal> TK_INT TK_FLOAT TK_TYPE TK_CHAR TK_BOOL
%token <symbol> TK_ID
%token TK_VAR
%token OP_EQ OP_NE OP_LE OP_GE OP_LT OP_GT
%token OP_AND OP_OR OP_NOT OP_AT

/*** Declaração de nódulos ***/
%type <node> COMMANDS STATEMENT DECL ATRI EXPR
%start S

%right OP_AT
%left  OP_EQ OP_NE OP_LE OP_GE OP_LT OP_GT
%left  OP_OR
%left  OP_AND
%left  '+' '-'
%left  '*' '/' '%'
%right OP_NOT

%%

S           : COMMANDS
            {
                code = "/*Compilador da nossa linguagem... Chacau?*/\n#include <stdio.h>\n#include \"runtime.h\"\nint main(void) {\n";
                code += gen_declarations();
                code += "\n" + $1.translation;
                code += "\n\treturn 0;\n}\n";
            };


COMMANDS    : COMMANDS STATEMENT {$$.translation = $1.translation + $2.translation;}
            | STATEMENT          {$$.translation = $1.translation;};

STATEMENT   : DECL {$$.translation = $1.translation;}
            | ATRI {$$.translation = $1.translation;}
            | EXPR {$$.translation = $1.translation;};
            
DECL        : TK_VAR TK_ID ';' 
            {
                symbol sym;
                sym.name = $2.label;
                sym.type = ""; // Sem tipo na declaração
                symbols.push_back(sym);  
                $$.translation = "";
            };

ATRI        : TK_ID OP_AT EXPR ';'
            {
                symbol* sym = search_symbol($1.label, $3.type);
                if(sym) {
                    // tipo mudou? aloca novo temporário
                    if(sym->type != $3.type && !sym->type.empty()) {
                        sym->type  = $3.type;
                        sym->label = gen_tmp_variable();
                        variables.push_back({sym->label, sym->type});
                    }
                    $$.label = sym->label;
                    $$.translation = $3.translation
                                + "\t" + sym->label + " = " + $3.label + ";\n";
                }
            }
            /*** Operadores numéricos ***/
EXPR        : EXPR '+' EXPR {$$ = gen_expr($1,"+",$3);}
            | EXPR '-' EXPR {$$ = gen_expr($1,"-",$3);}
            | EXPR '*' EXPR {$$ = gen_expr($1,"*",$3);}
            | EXPR '/' EXPR {$$ = gen_expr($1,"/",$3);}
            | EXPR '%' EXPR {$$ = gen_expr($1,"%",$3);}

            /*** Operadores relacionais ***/
            | EXPR OP_EQ EXPR {$$ = gen_expr($1,"==",$3);}
            | EXPR OP_NE EXPR {$$ = gen_expr($1,"!=",$3);}
            | EXPR OP_LE EXPR {$$ = gen_expr($1,"<=",$3);}
            | EXPR OP_GE EXPR {$$ = gen_expr($1,">=",$3);}
            | EXPR OP_LT EXPR {$$ = gen_expr($1,"<",$3);}
            | EXPR OP_GT EXPR {$$ = gen_expr($1,">",$3);}

            /*** Operadores lógicos ***/
            | EXPR OP_OR  EXPR {$$ = gen_expr($1,"||",$3);}
            | EXPR OP_AND EXPR {$$ = gen_expr($1,"&&",$3);}
            | OP_NOT EXPR      
            {
                $$.label = gen_tmp_variable();
                variables.push_back({$$.label, $2.type});
                $$.translation = $2.translation + "\t" + 
                $$.label + " = " + "!" + $2.label + ";\n";
                $$.type = $2.type;
            }
            // Conversão explicita
			| '('TK_TYPE ')' EXPR
			{
                node v;
                v.type = $2.label;
                v.label = gen_tmp_variable();
                variables.push_back({v.label, v.type});

                v.translation = $4.translation + 
                                "\t" + v.label + " = (" + v.type + ")" + $4.label + ";\n"; 
				$$ = v;
			}
            
            | TK_INT
            {
                $$.label = gen_tmp_variable();
                $$.type  = "int";
                variables.push_back({$$.label, "int"});
                $$.translation = "\t" + $$.label + " = " + $1.label + ";\n";
            }

            | TK_FLOAT
            {
                $$.label = gen_tmp_variable();
                $$.type  = "float";
                variables.push_back({$$.label, "float"});
                $$.translation = "\t" + $$.label + " = " + $1.label + ";\n";
            }

            | TK_CHAR
            {
                $$.label = gen_tmp_variable();
                $$.type = "char";
                variables.push_back({$$.label, "char"});
                $$.translation = "\t" + $$.label + " = " + $1.label + ";\n";
            }

            | TK_BOOL
            {
                $$.label = gen_tmp_variable();
                $$.type = "bool";
                variables.push_back({$$.label, "bool"});
                $$.translation = "\t" + $$.label + " = " + $1.label + ";\n";
            }

            | TK_ID 
            {
                symbol *sym = search_symbol($1.label, "");
                if (sym != nullptr) {
                    $$.label = sym->label;
                    $$.type = sym->type;
                    $$.translation = "";
                } else {
                    std::cerr << "Variável não declarada." << std::endl;
                    exit(1);
                }
            };

%%

void yy::parser::error(const std::string& s){
    std::cerr << "Erro na linha " << yylineno << ": " << s << std::endl;
}

string gen_tmp_variable()
{
    tmp_var_count++;
    return "t" + to_string(tmp_var_count);
}

string gen_declarations(){
    string res;
    for(const auto& var : variables)
        res += "\t" + var.second + " " + var.first + ";\n";
    return res;
}

bool is_numeric(string s){
    return s == "int" || s == "float";
}

node gen_expr(const node& l, string op, const node& r){
    node v;
    v.label = gen_tmp_variable(); 

    // Se não for um literal já dá erro
    if(!is_numeric(l.type) || !is_numeric(r.type)){
        std::cerr << "Erro: operação inválida entre tipos "
                  << l.type << " e " << r.type << std::endl;
        exit(1);
    }

    string left_label  = l.label;
    string right_label = r.label;
    string result_type;
    string translation = l.translation + r.translation;

    // coerção
    if(l.type != r.type){
        result_type = "float";
    
    // Converte o literal inteiro para float
        if(l.type == "int" && r.type == "float"){
            string tmp = gen_tmp_variable();
            variables.push_back({tmp, "float"});

            translation += "\t" + tmp + " = (float)" + l.label + ";\n";
            left_label = tmp;
        }

        if(r.type == "int" && l.type == "float"){
            string tmp = gen_tmp_variable();
            variables.push_back({tmp, "float"});

            translation += "\t" + tmp + " = (float)" + r.label + ";\n";
            right_label = tmp;
        }
    }
    else {
        result_type = l.type;
    }
    v.type = result_type;
    v.translation = translation;
    variables.push_back({v.label, result_type});
    translation += "\t" + v.label + " = " + left_label + " " + op + " " + right_label + ";\n";

    return v;
}

// Procurar a variavel na tabela
symbol* search_symbol(string label, string type_inferred = ""){
    for(symbol& sym : symbols){ 
        if(sym.name == label){
            if(sym.label.empty()){
                sym.label = gen_tmp_variable(); 
                sym.type = type_inferred;
                variables.push_back({sym.label, sym.type});
            }
            return &sym;
        }
    }   
    return nullptr; 
}

int main(int argc, char* argv[]){
    tmp_var_count = 0;
    yy::parser p;
    
    if (p.parse() == 0){ 
        cout << code;
        
        ofstream outFile("code.c");
        if(outFile.is_open()) outFile << code << endl;
        
        ofstream ofile("tabela_de_simbolos.txt");
        if(ofile.is_open()) {
            for(const auto& sym : symbols) {
                ofile << sym.type << " | " << sym.name << " | " << sym.label << endl;
            }
        }
    }
    return 0;
}