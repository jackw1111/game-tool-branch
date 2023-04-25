
# Note: the bindings have to be built first with `make python` and then `make` for the emscripten build 

GLFW=
INCLUDE_GLFW = 
CC =em++
CC2 =emcc

# Variables
###############################################]
SRC=engine/core/graphics/src/
SRC2=engine/core/physics/src/
LIBS = #-ldl -lassimp -lfreetype -lpython2.7 -lboost_python27 $(GLFW) -lopenal -laudio
INCLUDE= $(INCLUDE_GLFW) -I./2.7.18/destdir/include/python2.7 -I/home/jack/game-tool/engine/core/graphics/lib/include -I./engine/core/graphics/lib/ -I/usr/include/python2.7 -I/usr/lib/x86_64-linux-gnu -I./engine/core/graphics/include/ -I./engine/core/physics/include/ -I./engine/core/graphics/lib/ -I./engine/core/graphics/lib/freetype-2.10.1/include
CPPLIBS=  -L/home/me/Documents/3d-graphics-project/engine/core/graphics/lib/ -L/usr/lib/python2.7/config-3.7m-x86_64-linux-gnu/ -L./usr/lib/ $(LIBS) -std=c++11
FLAGS =-Wall -fPIC #-msse2 -Wno-missing-profile# -Wl,--no-undefined  #-Werror
DEBUG= #-g -O0  
RELEASE= -O3 #-funroll-loops -fno-signed-zeros -fno-trapping-math -fprofile-use -fopenmp -D_GLIBCXX_PARALLEL
BUILD = $(DEBUG)


# Make C++ Library
###############################################]

INC=engine/core/graphics/include/
INCS = $(wildcard $(INC)*.h)

OBJ=engine/core/graphics/obj/
_OBJS = $(INCS:.h=.o)
OBJS = $(sort $(subst engine/core/graphics/include/, engine/core/graphics/obj/, $(_OBJS)))  # engine/core/graphics/obj/glad.o

INC2=engine/core/physics/include/
INCS2 = $(wildcard $(INC2)*.h)
OBJ2=engine/core/physics/obj/
_OBJS2 = $(INCS2:.h=.o)
OBJS2 = $(sort $(subst engine/core/physics/include/, engine/core/physics/obj/, $(_OBJS2)))

NO_MAIN_OBJS = $(filter-out engine/core/graphics/obj/main.o, $(OBJS) $(OBJS2))

BOOST_HEADERS=  -I /home/me/Downloads/boost_1_68_0/boost/python

cpp: $(NO_MAIN_OBJS)
	echo source /home/me/Downloads/emsdk/emsdk_env.sh
	@echo "building engine..."
	@$(CC) -DUSE_CPP $(BUILD) -c $(INCLUDE) $(FLAGS) engine/core/graphics/src/main.cpp -o engine/core/graphics/obj/main.o  -I ./pymodules 
	@$(CC) $(BUILD) $(INCLUDE) engine/core/graphics/obj/main.o $(NO_MAIN_OBJS)  $(BINDINGS_OBJS) $(BINDINGS_OBJS2) $(FLAGS) -I ./2.7.18/destdir/include/python2.7 -I ./pymodules ./pymodules/modules.a ./pymodules/libboost_python27.a ./pymodules/libpython2.7.a  ./pymodules/libassimp.a --shell-file pymodules/webprompt-shell.html -o engine/bin/asmjs.html -s USE_WEBGL2=1 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s WASM=0 -s EXPORTED_RUNTIME_METHODS='[ccall,cwrap]' -s EXPORT_EXCEPTION_HANDLING_HELPERS -s EXPORTED_FUNCTIONS='[_main, _PyRun_SimpleString, _PyRun_SimpleString, _runPythonCode, _resetState, _toggleInput]' -s USE_GLFW=3 -s FORCE_FILESYSTEM=1  -s USE_FREETYPE=1 --preload-file data -s ALLOW_MEMORY_GROWTH=1 -fexceptions  -lidbfs.js -s ASSERTIONS=1 #-s ASSERTIONS=1  --preload-file data  -s FORCE_FILESYSTEM=1    $(BOOST_HEADERS) -s USE_BOOST_HEADERS=1 --bind -s LINKABLE=1 -s EXPORT_ALL=1 -s USE_FREETYPE=1 -s USE_WEBGL2=1  --bind -s ASSERTIONS=1  # $(CPPLIBS) 
	@echo "Finished."


$(OBJ)%.o : $(SRC)%.cpp
	@echo building $* ...
	@$(CC) $(BUILD) -c $(INCLUDE) $(FLAGS) $< -o $@ 

$(OBJ2)%.o : $(SRC2)%.cpp
	@echo building $* ...
	@$(CC) $(BUILD) -c $(INCLUDE) $(FLAGS) $< -o $@ 

# Make Python Library
###############################################

BINDINGS_INC=engine/bindings/graphics/include/
BINDINGS_SRC=engine/bindings/graphics/src/
BINDINGS_OBJ=engine/bindings/graphics/obj/

BINDINGS_INCS=$(wildcard $(BINDINGS_INC)*.h)

_BINDINGS_OBJS = $(BINDINGS_INCS:.h=.o)
BINDINGS_OBJS = $(sort $(subst engine/bindings/graphics/include/, engine/bindings/graphics/obj/, $(_BINDINGS_OBJS)))


BINDINGS_INC2=engine/bindings/physics/include/
BINDINGS_SRC2=engine/bindings/physics/src/
BINDINGS_OBJ2=engine/bindings/physics/obj/

BINDINGS_INCS2=$(wildcard $(BINDINGS_INC2)*.h)

_BINDINGS_OBJS2 = $(BINDINGS_INCS2:.h=.o)
BINDINGS_OBJS2 = $(sort $(subst engine/bindings/physics/include/, engine/bindings/physics/obj/, $(_BINDINGS_OBJS2)))


python: $(BINDINGS_OBJS) $(BINDINGS_OBJS2)
	@echo $(NO_MAIN_OBJS)
	@echo $(BINDINGS_OBJS)
	@echo "building engine..."
	@$(CC) $(BUILD) -c $(INCLUDE) $(FLAGS) engine/bindings/graphics/src/main.cpp -o engine/bindings/graphics/obj/main.o -I ./pymodules
	@$(CC) $(BUILD) -shared $(INCLUDE) -o engine/bin/engine.o engine/core/graphics/obj/main.o  $(NO_MAIN_OBJS) $(BINDINGS_OBJS) $(BINDINGS_OBJS2) $(CPPLIBS) -I ./pymodules

exe: $(BINDINGS_OBJS)
	@echo $(NO_MAIN_OBJS)
	@echo $(BINDINGS_OBJS)

	@echo "building engine..."
	@$(CC) $(BUILD) -c $(INCLUDE) $(FLAGS) engine/core/graphics/src/main.cpp -o engine/core/graphics/obj/main.o
	@$(CC) $(BUILD) $(INCLUDE) -o engine/bin/engine  engine/core/graphics/obj/main.o  $(NO_MAIN_OBJS) $(CPPLIBS)


$(BINDINGS_OBJ)%.o : $(BINDINGS_SRC)%.cpp
	@echo building binding for $* ...
	@$(CC) $(BUILD) -c $(INCLUDE) -I $(BINDINGS_INC) $(FLAGS) $< -o $@ -I ./pymodules


$(BINDINGS_OBJ2)%.o : $(BINDINGS_SRC2)%.cpp
	@echo building binding for $* ...
	@$(CC) $(BUILD) -c $(INCLUDE) -I $(BINDINGS_INC2) $(FLAGS) $< -o $@ 

###############################################


engine/core/graphics/obj/glad.o : engine/core/graphics/lib/glad/glad.c
	@echo building glad ...
	@$(CC2) -c $(INCLUDE) $(FLAGS) $< -o $@

bin:
	@$(CC) $(BUILD) -c $(INCLUDE) $(FLAGS) engine/core/graphics/src/main.cpp -o engine/core/graphics/obj/main.o 
	@$(CC) $(BUILD) $(INCLUDE) -o engine/bin/engine engine/core/graphics/obj/main.o $(NO_MAIN_OBJS) 

all:
	make cpp
	make python

clean:
	@echo "cleaning engine..."
	@rm engine/bin/engine.so engine/core/graphics/obj/*.o example

docs:
	doxygen Doxyfile