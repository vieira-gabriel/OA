program: Trabalho_oa.cpp Registros.cpp
	g++ -o main -lasan -O -g -fsanitize=address -fno-omit-frame-pointer Trabalho_oa.cpp Registros.cpp