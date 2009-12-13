TOP_DIR = ../..

include $(TOP_DIR)/Makefile.include

STACK_COMPILER_SRC = $(wildcard *.cpp)
STACK_COMPILER_OBJS = $(shell for file in $(STACK_COMPILER_SRC);do echo "$(STACK_COMPILER_OBJ_DIR)/`basename $$file .cpp`.o"; done)

$(STACK_COMPILER_OBJ_DIR)/%.o: %.cpp
	$(GPP) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

compile-sc-lib: $(STACK_COMPILER_OBJS)
	
clean:
	rm -f $(STACK_COMPILER_OBJ_DIR)/*.o *~
