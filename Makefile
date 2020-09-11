#-------------------------------------------------------------------------------
# Estrutura do projeto
# sdl2mf/
#├── bin/
#│   └── sdl2mf*
#├── doc/
#├── inc/
#│   └── game.h
#├── obj/
#│   ├── game.o
#│   └── main.o
#├── src/
#│   ├── game.cpp
#│   └── main.cpp
#├── LICENSE
#├── Makefile
#└── README.md
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# Nome do projeto
# https://stackoverflow.com/questions/18136918/how-to-get-current-relative-directory-of-your-makefile
#-------------------------------------------------------------------------------
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
NAME := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))

#-------------------------------------------------------------------------------
# Diretórios
#-------------------------------------------------------------------------------
BIN_DIR=./bin
INC_DIR=./inc
OBJ_DIR=./obj
SRC_DIR=./src

#-------------------------------------------------------------------------------
# Source, Header, and Object
#-------------------------------------------------------------------------------
SRC = ${wildcard $(SRC_DIR)/*.cpp}
OBJ = ${addprefix $(OBJ_DIR)/, ${notdir ${SRC:.cpp=.o}}}
INC = -I${INC_DIR}

#-------------------------------------------------------------------------------
# Compilador, flags e bibliotecas
#-------------------------------------------------------------------------------
CC=g++
EM=em++
CFLAGS= -Wall -Wextra -pedantic -ansi -std=c++17
LFLAGS= -lSDL2

TARGET=$(BIN_DIR)/$(NAME)

.PHONY: clean all dirs run

all:
	@echo
	@echo Compiling
	$(MAKE) $(TARGET)

em:
	$(EM) -v -s "ENVIRONMENT=web" -s "USE_SDL=2" -o $(TARGET).html $(SRC) $(LIB) $(INC) $(LFLAGS) $(CFLAGS)

dirs:
	@mkdir -vp $(BIN_DIR) $(OBJ_DIR)

$(TARGET): dirs $(OBJ)
	@echo
	@echo Linking $@
	$(CC) -o $@ $(OBJ) $(LIB) $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo
	@echo Building $@
	$(CC) -c $^ -o $@ $(CFLAGS) $(INC)

run: $(TARGET)
	$(TARGET) 2>&1 | tee log.err


clean:
	@echo Cleaning...
	@rm -rvf *~ $(OBJ_DIR) $(BIN_DIR)

.PRECIOUS: %.o
