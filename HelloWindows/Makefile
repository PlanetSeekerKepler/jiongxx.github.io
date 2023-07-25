GDI32 = C:\w64devkit\x86_64-w64-mingw32\lib\libgdi32.a
MAIN = HelloWindowsDesktop.cpp
EXE = app.exe
generate:
	@g++ -Wall .\${MAIN} -mwindows ${GDI32} -o ${EXE}
clear:
	@rm ${EXE}
run:
	@.\${EXE}