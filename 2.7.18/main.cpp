#include <emscripten/emscripten.h>

// https://kripken.github.io/emscripten-site/docs/porting/connecting_cpp_and_javascript/embind.html

#include <emscripten/bind.h>
#include <iostream>
#include <string>

std::string str = "Hello World.";

void printString()
{
    std::cout << str << std::endl;
}

std::string getString()
{
    return str;
}

void setString(std::string s)
{
    str = s;
}

EMSCRIPTEN_BINDINGS(my_module)
{
    emscripten::function("printString", &printString);
    emscripten::function("getString", &getString);
    emscripten::function("setString", &setString);
}