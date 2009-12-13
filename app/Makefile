
SHELL = /bin/sh
TOP_DIR = .

include $(TOP_DIR)/Makefile.include

default: all

all: make-subdirs server

make-subdirs:
	@echo
	@echo $(DECO_L) Making directories tree $(DECO_R)
	mkdir -p $(SRC_DIR)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
	mkdir -p $(SERVER_OBJ_DIR)
	mkdir -p $(MSIUNET_OBJ_DIR)
	mkdir -p $(MSIUERROR_OBJ_DIR)
	mkdir -p $(MSIUTHREAD_OBJ_DIR)

server: $(SERVER_PROG)

$(SERVER_PROG): server-lib
	@echo
	@echo $(DECO_L) Making server $(DECO_R)
	$(GPP) $(SERVER_OBJ_DIR)/*.o $(LFLAGS) -o $@

server-lib: net-lib error-lib
	@echo
	@echo $(DECO_L) Making server library $(DECO_R)
	cd $(SERVER_SRC_DIR); $(MAKE) $(MFLAGS)
	
net-lib: thread-lib error-lib
	@echo
	@echo $(DECO_L) Making MSIU net library $(DECO_R)
	cd $(MSIUNET_SRC_DIR); $(MAKE) $(MFLAGS)
	
thread-lib: error-lib
	@echo
	@echo $(DECO_L) Making MSIU thread library $(DECO_R)
	cd $(MSIUTHREAD_SRC_DIR); $(MAKE) $(MFLAGS)
	
error-lib: 
	@echo
	@echo $(DECO_L) Making MSIU error library $(DECO_R)
	cd $(MSIUERROR_SRC_DIR); $(MAKE) $(MFLAGS)

clean:
	@echo
	@echo $(DECO_L) cleaning $(DECO_R)
	for d in $(SRC_DIR)/*/; do (cd $$d; $(MAKE) clean ); done
	rm -f "$(SERVER_PROG)" 

force:
	make clean
	make all
	
