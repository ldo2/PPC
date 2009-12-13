TOP_DIR = ../..

include $(TOP_DIR)/Makefile.include

SERVER_SRC = $(wildcard *.cpp)
SERVER_OBJS = $(shell for file in $(SERVER_SRC);do echo "$(SERVER_OBJ_DIR)/`basename $$file .cpp`.o"; done)

$(SERVER_OBJ_DIR)/%.o: %.cpp
	$(GPP) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

compile-server-lib: $(SERVER_OBJS)
	
clean:
	rm -f $(SERVER_OBJ_DIR)/*.o *~
