
LIBS= /home/me/spinning-cube/assimp/lib/libassimp.a /home/me/spinning-cube/assimp/lib/libIrrXML.a /home/me/spinning-cube/assimp/lib/libzlib.a /home/me/spinning-cube/assimp/lib/libzlibstatic.a

RELEASE = -O3
DEBUG = 
BUILD = $(RELEASE)

all: asm wasm

native:
	g++ Cube.cpp ./glad/glad.c -I./ -ldl -lglfw -lassimp

build:
	mkdir build

asm:
	echo source /home/me/Downloads/emsdk/emsdk_env.sh
	emcc Cube.cpp /home/me/spinning-cube/assimp/lib/libassimp.a -I./assimp/include -L./assimp/lib -I./ -o build/asmjs.html -s ALLOW_MEMORY_GROWTH=1 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s USE_WEBGL2=1 -s USE_GLFW=3 -s WASM=0 -s USE_FREETYPE=1  -s STB_IMAGE=1  -s EXIT_RUNTIME=1 -s FORCE_FILESYSTEM=1  -s NO_DISABLE_EXCEPTION_CATCHING --preload-file data -std=c++1z --bind -lidbfs.js $(BUILD)
wasm:
	echo source /home/me/Downloads/emsdk/emsdk_env.sh
	emcc Cube.cpp /home/me/spinning-cube/assimp/lib/libassimp.a -I./assimp/include -L./assimp/lib -I./ -o build/webassembly.html -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s USE_WEBGL2=1 -s USE_GLFW=3 -s USE_FREETYPE=1  -s STB_IMAGE=1  -s EXIT_RUNTIME=1 -s FORCE_FILESYSTEM=1  -s NO_DISABLE_EXCEPTION_CATCHING --preload-file data -std=c++1z --bind -lidbfs.js $(BUILD)

clean:
	rm -rf Cube build
