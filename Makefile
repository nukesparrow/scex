
CFLAGS += -DDEBUG -I.

EXAMPLES_OBJ = examples/1.o
EXAMPLES = examples/1

.PHONY: all examples

all: examples
	
examples: $(EXAMPLES)
	
$(EXAMPLES): $(EXAMPLES_OBJ)

clean:
	$(RM) $(EXAMPLES_OBJ) $(EXAMPLES)
