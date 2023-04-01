
LIBS= /home/me/spinning-cube/assimp/lib/libassimp.a /home/me/spinning-cube/assimp/lib/libIrrXML.a /home/me/spinning-cube/assimp/lib/libzlib.a /home/me/spinning-cube/assimp/lib/libzlibstatic.a

all: asm

native:
	g++ Cube.cpp ./glad/glad.c -I./ -ldl -lglfw -lassimp

build:
	mkdir build

asm:
	echo source /home/me/Downloads/emsdk/emsdk_env.sh
	emcc Cube.cpp /home/me/spinning-cube/assimp/lib/libassimp.a -I./assimp/include -L./assimp/lib -I./ -o build/asmjs.html -s USE_WEBGL2=1 -s USE_GLFW=3 -s WASM=0 -s USE_FREETYPE=1  -s STB_IMAGE=1 --preload-file data -std=c++1z --bind

wasm: build
	emcc Cube.cpp -o build/webassembly.html -s USE_WEBGL2=1 -s USE_GLFW=3 -s WASM=1 -s USE_FREETYPE=1 -s STB_IMAGE=1  --preload-file data -std=c++1z --bind

clean:
	rm -rf Cube build
