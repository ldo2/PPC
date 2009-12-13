TOP_DIR = ../..

include $(TOP_DIR)/Makefile.include

MSIUNET_SRC = $(wildcard *.cpp)
MSIUNET_OBJS = $(shell for file in $(MSIUNET_SRC);do echo "$(MSIUNET_OBJ_DIR)/`basename $$file .cpp`.o"; done)

$(MSIUNET_OBJ_DIR)/%.o: %.cpp
	$(GPP) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

compile-net-lib: $(MSIUNET_OBJS)

clean:
	rm -f $(MSIUNET_OBJ_DIR)/*.o *~
	
