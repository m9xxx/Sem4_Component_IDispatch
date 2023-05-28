cls

g++ -c ./source/client/main.cpp -o ./build/client/main.o

g++ ./build/client/main.o -o ./build/client/main.exe -lole32 -loleaut32 -luser32