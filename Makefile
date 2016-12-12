
#VPATH = examples

CFLAGS += -DDEBUG -I.

LIB_OBJ = scex.o

EXAMPLES_OBJ = examples/1.o
EXAMPLES = examples/1

.PHONY: all examples

all: $(LIB_OBJ) examples
	
examples: $(EXAMPLES)
	
$(EXAMPLES): $(EXAMPLES_OBJ) $(LIB_OBJ)

clean:
	$(RM) $(LIB_OBJ) $(EXAMPLES_OBJ) $(EXAMPLES)
