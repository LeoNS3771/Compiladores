SHELL := /bin/bash
SCANNER := flex
SCANNER_PARAMS := -o lex.yy.cc lexico.l
PARSER := bison
PARSER_PARAMS := -d -o y.tab.cc sintatico.y
CXX := g++
CXXFLAGS := -Wno-free-nonheap-object -std=c++17
FILE := programa.sk

all: glf
	./glf < $(FILE)

glf: y.tab.cc lex.yy.cc
	$(CXX) $(CXXFLAGS) -o glf y.tab.cc lex.yy.cc

lex.yy.cc: lexico.l y.tab.hh
	$(SCANNER) $(SCANNER_PARAMS)

y.tab.cc y.tab.hh: sintatico.y
	$(PARSER) $(PARSER_PARAMS)

run: glf
	./glf < $(FILE) > /tmp/output.c && gcc /tmp/output.c -o /tmp/output && /tmp/output

clean:
	rm -f y.tab.cc y.tab.hh lex.yy.cc glf stack.hh location.hh position.hh