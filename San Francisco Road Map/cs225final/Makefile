# LD = clang++
# CXX = clang++
# INCLUDES = -Igraph.h 
# CXXEXTRAS = -Wall -Werror -pedantic
# CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
# CXXFLAGS2=-std=c++2a -g -fstandalone-debug
# LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

# exec: final
# #tests: bin/tests

# final: graph.cpp main.cpp
# 	$(CXX) $(CXXFLAGS2) $(CXXEXTRAS) $(INCLUDES) $^ -o $@

# test: graph.o catchmain.o tests.o
# 	$(LD) graph.o catchmain.o tests.o $(LDFLAGS) -o test

# catchmain.o : catch/catchmain.cpp catch/catch.hpp
# 	$(CXX) $(CXXFLAGS) catch/catchmain.cpp

# tests.o : tests.cpp catch/catch.hpp
# 	$(CXX) $(CXXFLAGS) tests.cpp

# graph.o : graph.cpp
# 	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

# .DEFAULT_GOAL := final
# .PHONY: clean final tests

# clean:rm -rf *.o *.d rm -f final rm -f test

# Executable names:
EXE = final
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = Image.o graph.o main.o StickerSheet.o

# Generated files
CLEAN_RM = out.png

# Use the cs225 makefile template:
include cs225/make/cs225.mk

# MP-specific target
TMP_OBJ := $(OBJS)
OBJS = $(filter-out $(EXE_OBJ), $(TMP_OBJ))
OBJS += testimage.o

testimage: $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
	$(LD) $^ $(LDFLAGS) -o $@

