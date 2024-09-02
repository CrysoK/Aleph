PROGRAM = aleph

all: $(PROGRAM)

BISON_DIR = src/bison/
BISON_NAME = parser
BISON_Y = $(BISON_DIR)$(BISON_NAME).y
BISON_C = $(BISON_DIR)$(BISON_NAME).tab.c
BISON_H = $(BISON_DIR)$(BISON_NAME).tab.h
BISON_ARGS = -d -v --report=all
# state: estados del autómata
# itemset: ?
# lookahead: posibles siguientes tokens
# solved: cómo se solucinó un conflicto (left, right, etc)
# counterexamples: ejemplos de conflictos
# https://www.gnu.org/software/bison/manual/html_node/Understanding.html

FLEX_DIR = src/flex/
FLEX_NAME = scanner
FLEX_L = $(FLEX_DIR)$(FLEX_NAME).l
FLEX_C = $(FLEX_DIR)lex.yy.c
FLEX_ARGS =

H_DIR = src/
H_FILES := $(wildcard $(H_DIR)*.h)
H_FILES += $(wildcard $(H_DIR)ast/*.h)
H_FILES += $(wildcard $(H_DIR)eval/*.h)

C_DIR = src/
C_FILES := $(wildcard $(C_DIR)*.c)
C_FILES += $(wildcard $(C_DIR)ast/*.c)
C_FILES += $(wildcard $(C_DIR)eval/*.c)

C_ARGS = -std=c11 -O2 -pedantic -Wall -Wextra -Wno-unused-function \
-Wno-unused-parameter -Wmissing-declarations -Wmissing-prototypes \
-Wstrict-prototypes -Wredundant-decls -finstrument-functions
#-Wall -Wextra

debug: C_ARGS += -g -fno-inline -fno-omit-frame-pointer -ggdb # Dr. Memory
debug: $(PROGRAM)

$(PROGRAM): $(C_FILES) $(H_FILES) $(FLEX_C) $(BISON_C)
	gcc $(C_ARGS) $(C_FILES) $(FLEX_C) $(BISON_C) -o $@
	echo gcc $(C_ARGS) $(C_FILES) $(FLEX_C) $(BISON_C) -o $@ > _gcc.cmd

$(BISON_C): $(BISON_Y)
	bison -o $(BISON_C) $(BISON_Y) $(BISON_ARGS)
	echo bison -o $(BISON_C) $(BISON_Y) $(BISON_ARGS) > _bison.cmd

$(FLEX_C): $(FLEX_L)
	flex -o $(FLEX_C) $(FLEX_L)
	echo flex -o $(FLEX_C) $(FLEX_L) > _flex.cmd

# Elimina lo creado por make
rm:
	rm -f $(PROGRAM) $(PROGRAM).exe $(BISON_C) $(BISON_H) $(FLEX_C)
