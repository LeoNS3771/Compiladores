SHELL := /bin/bash
SCANNER := flex
SCANNER_PARAMS := -o lex.yy.cc lexico.l
PARSER := bison
PARSER_PARAMS := -d -o y.tab.cc sintatico.y
CXX := g++
CXXFLAGS := -Wno-free-nonheap-object -std=c++17
FILE := exemplos/03_declaracao_temp.foca

all: glf translate

compile: glf

glf: y.tab.cc lex.yy.cc
	$(CXX) $(CXXFLAGS) -o glf y.tab.cc lex.yy.cc

lex.yy.cc: lexico.l y.tab.hh
	$(SCANNER) $(SCANNER_PARAMS)

y.tab.cc y.tab.hh: sintatico.y
	$(PARSER) $(PARSER_PARAMS)

translate: glf
	./glf < $(FILE)

run: glf
	./glf < $(FILE) > /tmp/foca_output.c && gcc /tmp/foca_output.c -o /tmp/foca_output && /tmp/foca_output

test: glf
	@pass=0; fail=0; \
	for f in exemplos/*.foca; do \
		name=$$(basename $$f .foca); \
		expected="exemplos/$$name.expected"; \
		if [ -f "$$expected" ]; then \
			if ./glf < $$f 2>/dev/null | diff -q - $$expected > /dev/null 2>&1; then \
				echo "  PASS: $$name"; \
				pass=$$((pass + 1)); \
			else \
				echo "  FAIL: $$name"; \
				fail=$$((fail + 1)); \
			fi; \
		fi; \
	done; \
	echo ""; \
	echo "Resultado: $$pass passou, $$fail falhou"

test-%: glf
	@name=$(patsubst test-%,%,$@); \
	foca=$$(ls exemplos/$${name}_*.foca 2>/dev/null | head -1); \
	if [ -z "$$foca" ]; then \
		echo "Exemplo nao encontrado para etapa $$name"; \
		exit 1; \
	fi; \
	expected=$$(echo $$foca | sed 's/.foca/.expected/'); \
	echo "Entrada: $$foca"; \
	echo "---"; \
	./glf < $$foca; \
	echo "---"; \
	if diff <(./glf < $$foca 2>/dev/null) $$expected > /dev/null 2>&1; then \
		echo "PASS"; \
	else \
		echo "FAIL - Diferenca:"; \
		diff <(./glf < $$foca 2>/dev/null) $$expected; \
	fi

clean:
	rm -f y.tab.cc y.tab.hh lex.yy.cc glf stack.hh location.hh position.hh