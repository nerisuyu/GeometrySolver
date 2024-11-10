STD = -std=c++11

all: core.dll


dialog.dll: windialog.c
	gcc -shared $^ -o $@ -lole32 -lcomdlg32 -Iinclude

test: src/drawing.cpp src/wrapper.cpp src/ui_tools_test.cpp
	g++ $^ $(STD) -o ui_tools_test.exe -Iinclude
	
core.dll: src/drawing.cpp src/wrapper.cpp src/matrix.cpp src/solver.cpp 
	g++ -shared $^ $(STD) -o $@ -Iinclude -static

debug: src/drawing.cpp src/wrapper.cpp src/matrix.cpp src/solver.cpp 
	g++ -shared $^ $(STD) -o core.dll -Iinclude -static -DLOGGING=1 

clean:
	rm -f core.dll