#declare variable
EXE := main
OBJS := Linked_List.o AdjList.o solution.o main.o
OBJS_DIR := .objs
INC_DIR := ./include ../../../Linked_List/include/ ../../../Adjacent_List/include

CC = g++
INCLUDE_FLAGS = $(foreach d, $(INC_DIR), -I $d)
#CTAGS_UTIL = /usr/bin/
CTAGS_UTIL = 
CTAGS_FILES = ./include
CTAGS_FLAGS = $(foreach d, $(CTAGS_FILES),-a $d/*)
GCC_EXCLUSIVE_WARNING_OPTIONS =  # -Wno-unused-but-set-variable
CLANG_EXCLUSIVE_WARNING_OPTIONS =  # -Wno-unused-parameter -Wno-unused-variable
ifeq ($(CXX),g++)
EXCLUSIVE_WARNING_OPTIONS = $(GCC_EXCLUSIVE_WARNING_OPTIONS)
else
EXCLUSIVE_WARNING_OPTIONS = $(CLANG_EXCLUSIVE_WARNING_OPTIONS)
endif
#WARNINGS_AS_ERRORS = -Werror # Un-commenting this line makes compilation much more strict.
WARNINGS = -pedantic -Wall $(WARNINGS_AS_ERRORS) -Wfatal-errors -Wextra $(EXCLUSIVE_WARNING_OPTIONS)
# ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer # for debugging, if supported on the OS

## Flags for compiling
CFLAGS = -g -c -std=c++14 -O0 $(WARNINGS) -MMD -MP $(ASANFLAGS)

## Flags for linking:
LDFLAGS += -std=c++14 $(ASANFLAGS)

# Rule for `all` (first/default rule):
all: $(INC_DIR) $(EXE) all_file_tags

# Rule for linking the final executable:
# - $(EXE) depends on all object files in $(OBJS)
# - `patsubst` function adds the directory name $(OBJS_DIR) before every object file
$(EXE): $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
	$(CC) $^ $(LDFLAGS) $(INCLUDE_FLAGS) -o $@

# Rules for compiling source code.
# - Every object file is required by $(EXE)
# - Generates the rule requiring the .cpp file of the same name
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(INC_DIR):
	@mkdir -p $@

all_file_tags : 
	$(CTAGS_UTIL)ctags -R ./*
	$(CTAGS_UTIL)ctags $(CTAGS_FLAGS)

# Standard C++ Makefile rules:
clean:
	rm -rf $(EXE) $(TEST) $(OBJS_DIR) $(CLEAN_RM) *.o *.d *.dSYM
	rm -rf ./tags

tidy: clean
	rm -rf doc

.PHONY: all tidy clean
