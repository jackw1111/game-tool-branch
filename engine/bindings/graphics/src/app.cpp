#include "../../../bindings/graphics/include/app.h"

extern Application *app;
extern int inputEnabled;

// ApplicationWrap::ApplicationWrap() : Application() {};
ApplicationWrap::ApplicationWrap(PyObject *p, std::string title, unsigned int WIDTH, unsigned int HEIGHT, bool fullscreen, bool MSAA) : Application(title, WIDTH, HEIGHT, fullscreen, MSAA), self(p) {}
ApplicationWrap::ApplicationWrap(PyObject *p, const Application& x) : Application(x), self(p) {}

int ApplicationWrap::setup(std::string title, unsigned int WIDTH, unsigned int HEIGHT, bool fullscreen, bool MSAA) {
  return Application::setup(title, WIDTH, HEIGHT, fullscreen, MSAA);
}

void ApplicationWrap::update()
{
    call_method<void>(self, "update");
}

void ApplicationWrap::onKeyPressed(int key, int scancode, int action, int mods) 
{
    if (inputEnabled) {
      call_method<void>(self, "on_key_pressed", key, scancode, action, mods);
    }
}

void ApplicationWrap::onCharPressed(unsigned int _char) 
{
    // BUG: recursion
    //call_method<void>(self, "on_char_pressed", _char);
}

void ApplicationWrap::onMouseClicked(int button, int action, int mods)
{
  if (inputEnabled) {
    call_method<void>(self, "on_mouse_clicked", button, action, mods);
  }
}

void ApplicationWrap::onMouseScrolled(double xpos, double ypos)
{
    call_method<void>(self, "on_mouse_scrolled", xpos, ypos);
}

void ApplicationWrap::onWindowResized(int width, int height)
{
    call_method<void>(self, "on_window_resized", width, height);
}

void ApplicationWrap::onMouseMoved(double xpos, double ypos)
{
  if (inputEnabled) {
    call_method<void>(self, "on_mouse_moved", xpos, ypos);
  }
}

void ApplicationWrap::onJoystickMoved(int jid, int event)
{
    call_method<void>(self, "on_joystick_moved", jid, event);
}

float ApplicationWrap::getFPS() {
  return Application::getFPS();
}


void ApplicationWrap::gameLoop()
{
    Application::gameLoop();
}

void ApplicationWrap::draw()
{
    Application::draw();
}
BOOST_PYTHON_OPAQUE_SPECIALIZED_TYPE_ID(GLFWwindow);

static void onMouseClicked(GLFWwindow* window, int button, int action, int mods)
{
    app->onMouseClicked(button, action, mods);
}
static void onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    app->onKeyPressed(key, scancode, action, mods);
}
static void onCharPressed(GLFWwindow* window, unsigned int _char)
{
    app->onCharPressed(_char);
}
static void onWindowResized(GLFWwindow* window, int width, int height)
{
    glViewport(0,0, width, height);
    app->onWindowResized(width, height);
}
static void onMouseMoved(GLFWwindow* window, double xpos, double ypos)
{
    app->onMouseMoved(xpos, ypos);
}

static void onWindowClose(GLFWwindow* window) {
    app->onWindowClose(window);
}

void joystick_callback(int jid, int event)
{
    if (event == GLFW_CONNECTED)
    {
        std::cout <<" joystick connected" << std::endl;
        // The joystick was connected
    }
    else if (event == GLFW_DISCONNECTED)
    {
        // The joystick was disconnected
        std::cout <<" joystick disconnected" << std::endl;
    }
}

// glfwMakeContextCurrent(app->window);
// GLFWwindow *window = app->window;
// glfwSetWindowUserPointer(window, &app);

// glfwSetCursorPosCallback(window, []( GLFWwindow* window, double x, double y)
// {
//     Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
//     app->onMouseMoved(x, y);
// });

// glfwSetMouseButtonCallback(window, []( GLFWwindow* window, int button, int action, int mods)
// {
//     Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
//     app->onMouseClicked(button, action, mods);
// });

// glfwSetKeyCallback(window, []( GLFWwindow* window, int key, int scancode, int action, int mods)
// {
//     Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
//     app->onKeyPressed(key, scancode, action, mods);
// });

void main_loop() {
    app->gameLoop();
}
bool mainLoopSet = false;
void run(python::object obj) {
    if (mainLoopSet) {
      glfwDestroyWindow(app->window);
    }
    app = python::extract<ApplicationWrap*>(obj);
    std::cout << "app: " << app << std::endl;
    //if (!mainLoopSet) {
    glfwSetCursorPosCallback(app->window, onMouseMoved);
    glfwSetMouseButtonCallback(app->window, onMouseClicked);
    glfwSetKeyCallback(app->window, onKeyPressed);
    //}
    
    if (mainLoopSet)  {
        emscripten_cancel_main_loop();
    }
    mainLoopSet = true;
    //glfwSetJoystickCallback(onJoystickMoved);
    //glfwSetFramebufferSizeCallback(app->window, onWindowResized);
    //glfwSetScrollCallback(app->window, onMouseScrolled);
    //glfwSetCharCallback(app->window, onCharPressed);
    
    emscripten_set_main_loop(main_loop, 0, true);
}



void wrap_Application() {
       boost::python::class_<Application,ApplicationWrap> ("Application", init<std::string, unsigned int, unsigned int, bool, bool>())
         .def("setup", &ApplicationWrap::setup)
      .def_readwrite("lastX", &Application::lastX)
      .def_readwrite("lastY", &Application::lastY)
      .def_readwrite("deltaTime", &Application::deltaTime)
      .def_readwrite("currentFrame", &Application::currentFrame)
      .def_readwrite("lastFrame", &Application::lastFrame)
      .def_readwrite("active_camera", &Application::active_camera)
      .def_readwrite("sky_box", &Application::sky_box)
      .def_readwrite("debug", &Application::debug)
      .def_readwrite("light_projection_matrix", &Application::lightProjection)
      .def_readwrite("light_view_matrix", &Application::lightView)
      .def_readwrite("use_custom_view_matrix", &Application::useCustomViewMatrix)
      .def_readwrite("frustum", &Application::frustum)
      .add_property("shadow_resolution", &Application::getShadowMapResolution, &Application::setShadowMapResolution)
      .def_readwrite("window", &Application::window)

      //.add_property("window", boost::python::make_function(&Application::getWindow, boost::python::return_value_policy<boost::python::return_opaque_pointer>()), &Application::setWindow)
      .def("update", &ApplicationWrap::update)
      .def("on_key_pressed", &ApplicationWrap::onKeyPressed)
    //   .def("on_char_pressed", &ApplicationWrap::onCharPressed)
      .def("on_mouse_clicked", &ApplicationWrap::onMouseClicked)
    //   .def("on_window_resized", &ApplicationWrap::onWindowResized)
    //   .def("on_mouse_scrolled", &ApplicationWrap::onMouseScrolled)
      .def("on_mouse_moved", &ApplicationWrap::onMouseMoved)
    //   .def("on_joystick_moved", &ApplicationWrap::onJoystickMoved)
      .def("gameLoop", &ApplicationWrap::gameLoop)
      .def("get_fps", &ApplicationWrap::getFPS)
      .def("set_background_color", &Application::setBackgroundColor)
      .def_readwrite("frustum_culling", &Application::frustumCullingEnabled)
         ;
    
      python::def("run", run);

}

// extern Application *app;

// static void onMouseClicked(GLFWwindow* window, int button, int action, int mods)
// {
//     app->onMouseClicked(button, action, mods);
// }
// static void onMouseScrolled(GLFWwindow* window, double xpos, double ypos)
// {
//     app->onMouseScrolled(xpos, ypos);
// }
// static void onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
// {
//     app->onKeyPressed(key, scancode, action, mods);
// }
// static void onCharPressed(GLFWwindow* window, unsigned int _char)
// {
//     app->onCharPressed(_char);
// }
// static void onWindowResized(GLFWwindow* window, int width, int height)
// {
//     glViewport(0,0, width, height);
//     app->onWindowResized(width, height);
// }
// static void onMouseMoved(GLFWwindow* window, double xpos, double ypos)
// {
//     app->onMouseMoved(xpos, ypos);
// }

// static void onJoystickMoved(int jid, int event)
// {
//     app->onJoystickMoved(jid, event);
// }

// void run(python::object obj) {
//   app = python::extract<ApplicationWrap*>(obj);

//   glfwSetCursorPosCallback(app->window, onMouseMoved);
//   glfwSetJoystickCallback(onJoystickMoved);
//   glfwSetMouseButtonCallback(app->window, onMouseClicked);
//   glfwSetFramebufferSizeCallback(app->window, onWindowResized);
//   glfwSetScrollCallback(app->window, onMouseScrolled);
//   glfwSetKeyCallback(app->window, onKeyPressed);
//   glfwSetCharCallback(app->window, onCharPressed);

//   while(!glfwWindowShouldClose(app->window))
//   {
//       app->gameLoop();
//       glfwSwapBuffers(app->window);
//       glFinish();
//       glfwPollEvents();    
//   }
//   glfwDestroyWindow(app->window);
//   glfwTerminate();
// }