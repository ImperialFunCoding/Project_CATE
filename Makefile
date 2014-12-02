CXX:=g++
CXX_FLAGS:=-Isrc
VPATH:=src

PROG:=bin/cate
SRC:=$(shell find src -name "*.cpp")
OBJ:=$(SRC:cpp=o)

.PHONY: all clean rebuild install

all: info $(PROG)

info:
	@echo Starting build.

install: all
	cp $(PROG) /usr/local/bin/$(shell basename $(PROG))

rebuild: clean all

clean:
	rm -f $(OBJ) $(PROG)

$(PROG): $(OBJ)
	@echo "  Linking $@"
	@-rm -f $@
	@$(CXX) -o $@ $(OBJ) $(CXX_FLAGS) $(LD_FLAGS)
	@echo "Successfully build target: $@"

%.o: %.cpp
	@echo "  Compiling $(<F)"
	@-rm -f $@
	@$(CXX) -c $(CXX_FLAGS) $< -o $@

