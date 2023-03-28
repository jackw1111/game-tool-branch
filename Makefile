kernel := $(shell sh -c 'uname -s 2>/dev/null || echo not')

ifeq ($(kernel),Linux)
    CLANG_ARGS = -lGL -lGLU -lglut
endif
ifeq ($(kernel),Darwin)
    CLANG_ARGS = -framework GLUT -framework OpenGL -Wno-deprecated
endif

all: asm

native:
	g++ Cube.cpp ./glad/glad.c -I./ -ldl -lglfw -lassimp

build:
	mkdir build

asm:
	echo source /home/me/Downloads/emsdk/emsdk_env.sh
	emcc Cube.cpp -o build/asmjs.html -s USE_WEBGL2=1 -s USE_GLFW=3 -s WASM=0 -s USE_FREETYPE=1  -s STB_IMAGE=1 --preload-file data -std=c++1z --bind

wasm: build
	emcc Cube.cpp -o build/webassembly.html -s USE_WEBGL2=1 -s USE_GLFW=3 -s WASM=1 -s USE_FREETYPE=1 -s STB_IMAGE=1  --preload-file data -std=c++1z --bind

clean:
	rm -rf Cube build
