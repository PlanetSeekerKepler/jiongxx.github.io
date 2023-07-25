SRC1 = modbus.c
MAIN = main.c 
EXE = modbus.exe
LEFT_ALIGH = -12
note:
	@printf "Modbus RTU service\n"
	@printf "%${LEFT_ALIGH}s%s\n" "generate:" "generate executable file."
	@printf "%${LEFT_ALIGH}s%s\n" "clear:" "clear all object and executable files."
	@printf "%${LEFT_ALIGH}s%s\n" "run:" "run executable file."
	@printf "The first character can be called as the same.\n"
generate:
	@echo "Start assembling."
	@gcc -c ${SRC1} ${MAIN}
	@echo "Start linking."
	@gcc *.o -o ${EXE}
	@echo "finished."
clear:
	@rm *.o
	@rm *.exe
	@echo "All Object and executable files has clear."
run:
	@.\${EXE}
