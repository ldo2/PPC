TOP_DIR = ../..

include $(TOP_DIR)/Makefile.include

MSIUTHREAD_SRC = $(wildcard *.cpp)
MSIUTHREAD_OBJS = $(shell for file in $(MSIUTHREAD_SRC);do echo "$(MSIUTHREAD_OBJ_DIR)/`basename $$file .cpp`.o"; done)

$(MSIUTHREAD_OBJ_DIR)/%.o: %.cpp
	$(GPP) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

compile-net-lib: $(MSIUTHREAD_OBJS)

clean:
	rm -f $(MSIUTHREAD_OBJ_DIR)/*.o *~
	
