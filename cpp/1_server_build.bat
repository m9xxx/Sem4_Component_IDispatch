cls

g++ -c ./source/server/components.cpp -o ./build/server/components.o
g++ -c ./source/server/main.cpp -o ./build/server/main.o

g++ -shared ./build/server/components.o ./build/server/main.o -o ./build/server/main.dll -lole32 -loleaut32 -luser32 -Wl,--kill-at