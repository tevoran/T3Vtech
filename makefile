CC=x86_64-w64-mingw32-g++-posix



CC_EM=em++

SOURCES := $(shell find src/ -name '*.cpp')
SRC=$(wildcard src/*.cpp)

CFLAGS=-mwindows -o windows/T3Vtech.exe -std=c++17 -Isrc/ -Ivendor/glm/ -Ivendor/yamc/include/ -Lwindows/libs -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image -Iwindows/include -static-libstdc++ -static-libgcc -Wl,-Bstatic -Wl,--whole-archive -lwinpthread -Wl,--no-whole-archive -pedantic -Wall -lmingw32
CFLAGS_EM=-o T3Vtech.html --preload-file assets -O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file assets -s USE_SDL_TTF=2
windows: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS)

emscripten: $(SRC)
	$(CC_EM) $(SRC) $(CFLAGS_EM)
