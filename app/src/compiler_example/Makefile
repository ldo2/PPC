TOP_DIR = ../..

include $(TOP_DIR)/Makefile.include

SC_EXAMPLE_SRC = $(wildcard *.cpp)
SC_EXAMPLE_OBJS = $(shell for file in $(SC_EXAMPLE_SRC);do echo "$(SC_EXAMPLE_OBJ_DIR)/`basename $$file .cpp`.o"; done)

$(SC_EXAMPLE_OBJ_DIR)/%.o: %.cpp
	$(GPP) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

compile-sc-examples: $(SC_EXAMPLE_OBJS)
	
clean:
	rm -f $(SC_EXAMPLE_OBJ_DIR)/*.o *~
