#include <functional>
#include <vector>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/bind.h>
using namespace emscripten;
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include "stb_image.h"

#else
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>


#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <vector>
#include <random>
#include <chrono>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

const char *vertexShaderSource =
"attribute vec3 aPos;\n"
"attribute vec2 aTexCoord;\n"
"varying vec2 TexCoord;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos, 1.0);\n"
"    TexCoord = aTexCoord;\n"
"}\n\0";

const char *fragmentShaderSource =
"precision mediump float;\n"
"uniform sampler2D ourTexture;\n"
"varying vec2 TexCoord;\n"
"void main()\n"
"{\n"
"    gl_FragColor = texture2D(ourTexture, TexCoord);\n"
"}\n\0";


std::function<void()> loop;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

class Quad {
public:
  unsigned int shaderProgram;
  unsigned int VBO, VAO, EBO;
  unsigned int texture;
  Quad() {

  }
  void setup() {
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f    // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);  

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

    int width, height, nrChannels;
    unsigned char *data = stbi_load("data/container.jpg", &width, &height, &nrChannels, 0); 
    glGenTextures(1, &texture); 

    glBindTexture(GL_TEXTURE_2D, texture);  

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
  }
  void draw() {
    // draw our first triangle
    glUseProgram(shaderProgram);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }

};

class Application {

public:
    // timing
  float deltaTime = 0.0;
  float lastFrame = 0.0;
  float currentFrame = 0.0;

  float lastX;
  float lastY;
  
  std::string name = "Application";

  GLFWwindow* window;

public:

  Application(std::string title, unsigned int WIDTH, unsigned int HEIGHT, bool fullscreen);
  virtual int _setup(std::string title, unsigned int WIDTH, unsigned int HEIGHT, bool fullscreen);

  Application();
  void gameLoop();
  // abstract callbacks (can be overridden, no error if not though)
  virtual void update();

  virtual void draw() = 0;
  virtual void setup() = 0;

  float getFPS();
};

unsigned int WIDTH = 800;
unsigned int HEIGHT = 600;

struct getTime
{
    using duration   = std::chrono::steady_clock::duration;
    using rep        = duration::rep;
    using period     = duration::period;
    using time_point = std::chrono::time_point<getTime>;
    static constexpr bool is_steady = true;

    static time_point now() noexcept
    {
        using namespace std::chrono;
        static auto epoch = steady_clock::now();
        return time_point{steady_clock::now() - epoch};
    }
};


Application::Application() {
    _setup("title", WIDTH, HEIGHT, false);
};

float Application::getFPS() {
    return 1.0f/(deltaTime + 0.0001);
}

Application::Application(std::string title, unsigned int _WIDTH, unsigned int _HEIGHT, bool fullscreen) {

    WIDTH = _WIDTH;
    HEIGHT = _HEIGHT;

    _setup(title, WIDTH, HEIGHT, fullscreen);

}

// Use in conjunction with Application() to create an instance but do not create a new window
// useful for drawing to different contexts/windows of OpenGL

int Application::_setup(std::string title, unsigned int WIDTH, unsigned int HEIGHT, bool fullscreen) {

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    if (glfwGetCurrentContext() == NULL) {
        // glfw window creation
        // --------------------
        window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetCursorPosCallback(window, mouse_callback);
        #ifdef __EMSCRIPTEN__
        #else
            // glad: load all OpenGL function pointers
            // ---------------------------------------
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                std::cout << "Failed to initialize GLAD" << std::endl;
                return -1;
            }
        #endif        
    }


    return 0;
}


void Application::update() {

    currentFrame = (float)getTime::now().time_since_epoch().count()/1000000000.0f; // convert nanoseconds to seconds

    deltaTime = (float)(currentFrame - lastFrame);
    lastFrame = currentFrame;

}

void Application::gameLoop() {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // render
    // ------
    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    draw();
    // glBindVertexArray(0); // no need to unbind it every time 

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();

}

// Application *getApplication() {
//     return new Application("example", WIDTH, HEIGHT, false);
// }

#ifdef __EMSCRIPTEN__

float lerp(float a, float b, float t) {
    return (1 - t) * a + t * b;
}
void clearColor(float r, float g, float b) {
    glClearColor(r,g,b,1.0f);

}

void setViewport(int x1, int y1, int x2, int y2) {
    glViewport(x1, y1, x2, y2);   
}

struct ApplicationWrapper : public wrapper<Application> {
    EMSCRIPTEN_WRAPPER(ApplicationWrapper);
    void setup() {
        return call<void>("setup");
    }
    void draw() {
        return call<void>("draw");
    }
};

Application *app;


Application* run(Application* a) {
    app = a;
    return a;
}

EMSCRIPTEN_BINDINGS(my_module) {
    function("lerp", &lerp);
    function("clearColor", &clearColor);
    function("setViewport", &setViewport);

    class_<Quad>("Quad")
    .constructor<>()
    .function("setup", &Quad::setup)
    .function("draw", &Quad::draw)
    ;

    class_<Application>("Application")
    .function("setup", &Application::setup, pure_virtual())
    .function("draw", &Application::draw,  pure_virtual())
    .allow_subclass<ApplicationWrapper>("ApplicationWrapper")
    ;

    function("run", &run, allow_raw_pointers());
}

#endif

std::string readFileIntoString(const std::string& path) {
    std::ifstream input_file(path);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"
             << path << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
    return std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

std::string fileContents;

void main_loop() {
    app->gameLoop();
}

int main(int argc, char *argv[])
{
    std::string fileName = "./data/file.js";
    fileContents = readFileIntoString(fileName);


    time_t t;
    srand((unsigned) time(&t));


    #ifdef __EMSCRIPTEN__
        emscripten_run_script(fileContents.c_str());
        emscripten_set_main_loop(main_loop, 0, true);
    #else
        while (!glfwWindowShouldClose(app->window))
            app->gameLoop();
    #endif


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1);
    if (state == GLFW_PRESS)
    {

        #ifdef __EMSCRIPTEN__
            glClearColor(((rand() % 255 + 1)/255.0f), ((rand() % 255 + 1)/255.0f), ((rand() % 255 + 1)/255.0f), 1.0f);
        #endif
    }    
}

