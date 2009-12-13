TOP_DIR = ../..

include $(TOP_DIR)/Makefile.include

MSIUERROR_SRC = $(wildcard *.cpp)
MSIUERROR_OBJS = $(shell for file in $(MSIUERROR_SRC);do echo "$(MSIUERROR_OBJ_DIR)/`basename $$file .cpp`.o"; done)

$(MSIUERROR_OBJ_DIR)/%.o: %.cpp
	$(GPP) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

compile-error-lib: $(MSIUERROR_OBJS)
	
clean:
	rm -f $(MSIUERROR_OBJ_DIR)/*.o *~
