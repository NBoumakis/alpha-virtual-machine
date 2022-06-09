TARGET = avm

CC = g++
CFLAGS = -Wall -Wextra -g -std=c++14 -I./ -Wno-unused-parameter

OUTDIR = ./bin
DATADIR = ./data
SUBDIR = executer executer/decode executer/execute lib library library/environment library/functions library/reporting loader memory memory/code_segment memory/const_values memory/memcell memory/stack table
DIR_OBJ = ./obj

INCS = $(wildcard *.hpp $(foreach fd, $(SUBDIR), $(fd)/*.hpp))
SRCS = $(wildcard *.cpp $(foreach fd, $(SUBDIR), $(fd)/*.cpp))
NODIR_SRC = $(notdir $(SRCS))
OBJS = $(addprefix $(DIR_OBJ)/, $(SRCS:cpp=o))
INC_DIRS = -I./

PHONY := $(TARGET)
$(TARGET): $(OBJS)  $(DIR_OBJ)/loader/text_scanner.o
	@echo "Linking $@"
	@mkdir -p $(OUTDIR)
	@$(CC) -o $(OUTDIR)/$@ $^ -lm

$(DIR_OBJ)/loader/text_scanner.o: loader/text_scanner.cpp
	@echo "Building" $@
	@$(CC) -o $@ $(CFLAGS) -c $<
	
loader/text_scanner.cpp: loader/text_scanner.l
	@echo "Flexing the text parser"
	@flex++ --outfile=$@ $<

$(DIR_OBJ)/%.o: %.cpp $(INCS)
	@echo "Building" $@
	@mkdir -p $(@D)
	@$(CC) -o $@ $(CFLAGS) -c $<

PHONY += clean
clean:
	rm -rf $(OUTDIR) $(DATADIR) $(DIR_OBJ) loader/text_scanner.cpp

PHONY += echoes
echoes:
	@echo "INC files: $(INCS)"
	@echo "SRC files: $(SRCS)"
	@echo "OBJ files: $(OBJS)"
	@echo "LIB files: $(LIBS)"
	@echo "INC DIR: $(INC_DIRS)"

.PHONY = $(PHONY)
