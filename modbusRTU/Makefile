SRC1 = modbus.c
MAIN = main.c 
EXE = modbus.exe
generate:
	@echo "Start compiling."
	@gcc -c ${SRC1} ${MAIN}
	@echo "Start linking."
	@gcc *.o -o ${EXE}
clear:
	@rm *.o
	@rm *.exe
run:
	@.\${EXE}
