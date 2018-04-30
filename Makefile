OBJ = secpm.o
CC = g++

compile: $(OBJ)
	@echo [CPP] Link SECPM...
	@$(CC) -fpermissive -static -W -o secpm $(OBJ) -w
	@echo [CPP] Finished!
	@echo "–––––––––––––––––––––––––––"
	@rm secpm.o

$(OBJ):
	@echo [CPP] Compile SECPM...
	@$(CC) -static -W -c main.cpp -o $(OBJ) -w
	@echo [CPP] Finished!
	@echo "–––––––––––––––––––––––––––"
