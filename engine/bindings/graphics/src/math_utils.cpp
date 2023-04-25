

#include "../../../bindings/graphics/include/math_utils.h"

BOOST_PYTHON_OPAQUE_SPECIALIZED_TYPE_ID(GLFWwindow)

vec4Wrap::vec4Wrap(float x, float y, float z, float w) : vec4(x, y, z, w) {}
vec4Wrap::vec4Wrap(float a) : vec4(a, a, a, a) {}
vec4Wrap::vec4Wrap() : vec4(){}

glm::vec4 custom_deleter_vec4::operator()(glm::vec4* f) {
  return *f;
}


vec3Wrap::vec3Wrap(float x, float y, float z) : vec3(x, y, z) {}
vec3Wrap::vec3Wrap(float a) : vec3(a, a, a) {}
vec3Wrap::vec3Wrap() : vec3(){}

glm::vec3 custom_deleter_vec3::operator()(glm::vec3* f) {
  return *f;
}
vec2Wrap::vec2Wrap(float x, float y) : vec2(x, y) {}
vec2Wrap::vec2Wrap(float a) : vec2(a, a) {}
vec2Wrap::vec2Wrap() : vec2(){}

void wrap_vec2() {
  python::class_<glm::vec2, boost::shared_ptr<glm::vec2>>("vec2", python::no_init)
  .def("__init__", python::make_constructor(&make_vec2))
  .def("copy", &copy_vec2, python::return_value_policy<python::manage_new_object>())
  .def("__mul__", &mul_vec2, python::return_value_policy<python::manage_new_object>())
  .def("__truediv__", &div_vec2, python::return_value_policy<python::manage_new_object>())
  .def("__imul__", &mul_vec2, python::return_value_policy<python::manage_new_object>())
  .def("__add__", &add_vec2, python::return_value_policy<python::manage_new_object>())
  .def("__sub__", &sub_vec2, python::return_value_policy<python::manage_new_object>())
  .def("__str__", &print_vec2)
  .def("__repr__", &print_vec2)
  .def("__eq__", &eq_vec2)
  .def_readwrite("x", &vec2::x)
  .def_readwrite("y", &vec2::y)
  ;

}

void wrap_vec3() {
  python::class_<glm::vec3, boost::shared_ptr<glm::vec3>>("vec3", python::no_init)
  .def("__init__", python::make_constructor(&make_vec3))
  .def("copy", &copy_vec3, python::return_value_policy<python::manage_new_object>())
  .def("__mul__", &mul_vec3, python::return_value_policy<python::manage_new_object>())
  .def("__truediv__", &div_vec3, python::return_value_policy<python::manage_new_object>())
  .def("__imul__", &mul_vec3, python::return_value_policy<python::manage_new_object>())
  .def("__add__", &add_vec3, python::return_value_policy<python::manage_new_object>())
  .def("__sub__", &sub_vec3, python::return_value_policy<python::manage_new_object>())
  .def("__str__", &print_vec3)
  .def("__repr__", &print_vec3)
  .def("__setitem__", &set_index_vec3)
  .def("__getitem__", &get_index_vec3)
  .def("__eq__", &eq_vec3)
  .def_readwrite("x", &vec3::x)
  .def_readwrite("y", &vec3::y)
  .def_readwrite("z", &vec3::z);
}

void wrap_vec4() {
  python::class_<glm::vec4, boost::shared_ptr<glm::vec4>>("vec4", python::no_init)
  .def("__init__", python::make_constructor(&make_vec4))
  .def("__init__", python::make_constructor(&make_vec4_from_vec3))
  .def("__mul__", &mul_vec4_mat4, python::return_value_policy<python::manage_new_object>())
  .def("__truediv__", &div_vec4, python::return_value_policy<python::manage_new_object>())
  .def("__imul__", &mul_vec4, python::return_value_policy<python::manage_new_object>())
  .def("__add__", &add_vec4, python::return_value_policy<python::manage_new_object>())
  .def("__str__", &print_vec4)
  .def("__repr__", &print_vec4)
  .def("__setitem__", &set_index_vec4)
  .def("__getitem__", &get_index_vec4)
  .def_readwrite("x", &vec4::x)
  .def_readwrite("y", &vec4::y)
  .def_readwrite("z", &vec4::z)
  .def_readwrite("w", &vec4::w);
}

void wrap_mat3() {

    python::class_<glm::mat3, boost::shared_ptr<glm::mat3>>("mat3", python::no_init)
    .def("__init__", python::make_constructor(&make_mat3))
    .def("__mul__", &mul_mat3, python::return_value_policy<python::manage_new_object>())
    .def("__mul__", &mul_mat3_vec3, python::return_value_policy<python::manage_new_object>())
    .def("__mul__", &mul_mat3_float, python::return_value_policy<python::manage_new_object>())
    .def("__add__", &add_mat3, python::return_value_policy<python::manage_new_object>())

    .def("__getitem__", &get_index_mat3, python::return_value_policy<python::manage_new_object>())
    .def("__setitem__", &set_index_mat3)

    .def("__str__", &print_mat3);

    python::def("mat4_cast", mat3_mat4_cast, python::return_value_policy<python::manage_new_object>());

    python::def("inverse", static_cast<glm::mat3* (*)(glm::mat3 const &m)>(&_inverse_mat3), python::return_value_policy<python::manage_new_object>());
    python::def("transpose", static_cast<glm::mat3* (*)(glm::mat3 const &m)>(&_transpose_mat3), python::return_value_policy<python::manage_new_object>());
    python::def("orthonormalize_orientation", static_cast<glm::mat3* (*)(glm::mat3 m)>(&_orthonormalize_orientation), python::return_value_policy<python::manage_new_object>());
    python::def("skew_symmetric", static_cast<glm::mat3* (*)(glm::vec3 const &v)>(&_skew_symmetric), python::return_value_policy<python::manage_new_object>());
    python::def("form_orthogonal_basis", static_cast<glm::mat3* (*)(glm::vec3 const &v)>(&_form_orthogonal_basis), python::return_value_policy<python::manage_new_object>());
}

void wrap_mat2() {

    python::class_<glm::mat2, boost::shared_ptr<glm::mat2>>("mat2", python::init<float>())
    .def("__init__", python::make_constructor(&make_mat2))
    .def("__mul__", &mul_mat2_vec2, python::return_value_policy<python::manage_new_object>())
    .def("__mul__", &mul_mat2_mat2, python::return_value_policy<python::manage_new_object>())
    ;

    python::def("rotate", rotate_mat2, python::return_value_policy<python::manage_new_object>());

}

void wrap_quat() {

    python::class_<glm::quat, boost::shared_ptr<glm::quat>>("quat", python::no_init)
    .def("__init__", python::make_constructor(&make_quat))
    .def("__mul__", &mul_quat, python::return_value_policy<python::manage_new_object>())
    .def("__mul__", &mul_quat_float, python::return_value_policy<python::manage_new_object>())
    .def("__add__", &add_quat, python::return_value_policy<python::manage_new_object>());

    python::def("normalize", static_cast<glm::quat* (*)(glm::quat const &m)>(&_normalize_quat), python::return_value_policy<python::manage_new_object>());
    python::def("mat4_cast", quat_mat4_cast, python::return_value_policy<python::manage_new_object>());
}

void wrap_mat4() {

    python::class_<glm::mat4, boost::shared_ptr<glm::mat4>>("mat4", python::no_init)
    .def("__init__", python::make_constructor(&make_mat4))
    .def("__mul__", &mul_mat4, python::return_value_policy<python::manage_new_object>())
    .def("__mul__", &mul_mat4_vec4, python::return_value_policy<python::manage_new_object>())
    .def("__str__", &print_mat4)
    .def("copy", &copy_mat4, python::return_value_policy<python::manage_new_object>())
    .def("__getitem__", &get_index_mat4, python::return_value_policy<python::manage_new_object>())
    .def("__setitem__", &set_index_mat4)
    .def("__lookAt", _lookAt, python::return_value_policy<python::manage_new_object>());

    python::def("inverse", static_cast<glm::mat4* (*)(glm::mat4 const &m)>(&_inverse), python::return_value_policy<python::manage_new_object>());
    python::def("transpose", static_cast<glm::mat4* (*)(glm::mat4 const &m)>(&_transpose), python::return_value_policy<python::manage_new_object>());

    python::def("perspective", _perspective, python::return_value_policy<python::manage_new_object>());
    python::def("ortho", _ortho, python::return_value_policy<python::manage_new_object>());
    python::def("lookAt", _lookAt, python::return_value_policy<python::manage_new_object>());
    python::def("translate", _translate, python::return_value_policy<python::manage_new_object>());
    python::def("rotate", _rotate, python::return_value_policy<python::manage_new_object>());
    python::def("scale", _scale, python::return_value_policy<python::manage_new_object>());
    python::def("mat3_cast", _mat3_cast, python::return_value_policy<python::manage_new_object>());
    python::def("interpolate", _interpolate, python::return_value_policy<python::manage_new_object>());

}



int setCursorVisible(GLFWwindow* window, bool isVisible) {
  if (isVisible) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  } else {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  }
  return 0;
}

int isJoystickPresent() {
  return glfwJoystickPresent(GLFW_JOYSTICK_1);
}

std::vector<float> getJoystickAxes() {
  if (glfwJoystickPresent(GLFW_JOYSTICK_1)) {
        int axesCount;
        const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);

        std::vector<float> axesVec;
        for (int i = 0; i < 6; i++) {
          axesVec.push_back(axes[i]);
        }
        return axesVec;
  } else {
    std::vector<float> axesVec(6);
    return axesVec;
  }
}

int loadGL() {
    // Alternative use the builtin loader, e.g. if no other loader function is available
    
    // if (!gladLoadGL()) {
    //     std::cout << "Failed to initialize OpenGL context" << std::endl;
    //     return -1;
    // }
    return -1;
}

// GLFWusercontext* _glfwCreateUserContext(GLFWwindow* window) {

// }

glm::quat custom_deleter_quat::operator()(glm::quat* f) {
  return *f;
}

glm::mat2 custom_deleter_mat2::operator()(glm::mat2* f) {
  return *f;
}

glm::mat4 custom_deleter_mat4::operator()(glm::mat4* f) {
  return *f;
}

glm::mat3 custom_deleter_mat3::operator()(glm::mat3* f) {
  return *f;
}

glm::vec4* get_index_mat4(glm::mat4 const &mat, int index) {
  glm::vec4* tmp = new glm::vec4();
  *tmp = mat[index];
  std::unique_ptr<glm::vec4, custom_deleter_vec4> _m( tmp );
  return _m.get();
}

void set_index_mat4(glm::mat4 &mat, int index, glm::vec4 value) {
  mat[index] = value;
}


glm::vec3* get_index_mat3(glm::mat3 const &mat, int index) {
  glm::vec3* tmp = new glm::vec3();
  *tmp = mat[index];
  std::unique_ptr<glm::vec3, custom_deleter_vec3> _m( tmp );
  return _m.get();
}

void set_index_mat3(glm::mat3 &mat, int index, glm::vec3 value) {
  mat[index] = value;
}


glm::mat4* mat4Wrap::operator*(glm::mat4 const &mat) {
  glm::mat4* tmp = new glm::mat4();
  *tmp = glm::operator*(*this, mat);
  std::unique_ptr<glm::mat4, custom_deleter_mat4> _m( tmp );
  return _m.get();
}

glm::mat2* mat2Wrap::operator*(glm::mat2 const &mat) {
  glm::mat2* tmp = new glm::mat2();
  *tmp = glm::operator*(*this, mat);
  std::unique_ptr<glm::mat2, custom_deleter_mat2> _m( tmp );
  return _m.get();
}

glm::mat4* mul_mat4(glm::mat4 const &mat1, glm::mat4 const &mat2) {
  glm::mat4* tmp = new glm::mat4();
  *tmp = glm::operator*(mat1, mat2);
  std::unique_ptr<glm::mat4, custom_deleter_mat4> _m( tmp );
  return _m.get();
}

glm::mat3* mul_mat3(glm::mat3 const &mat1, glm::mat3 const &mat2) {
  glm::mat3* tmp = new glm::mat3();
  *tmp = glm::operator*(mat1, mat2);
  std::unique_ptr<glm::mat3, custom_deleter_mat3> _m( tmp );
  return _m.get();
}

glm::mat3* add_mat3(glm::mat3 const &mat1, glm::mat3 const &mat2) {
  glm::mat3* tmp = new glm::mat3();
  *tmp = glm::operator+(mat1, mat2);
  std::unique_ptr<glm::mat3, custom_deleter_mat3> _m( tmp );
  return _m.get();
}

glm::quat* mul_quat(glm::quat const &mat1, glm::quat const &mat2) {
  glm::quat* tmp = new glm::quat();
  *tmp = glm::operator*(mat1, mat2);
  std::unique_ptr<glm::quat, custom_deleter_quat> _m( tmp );
  return _m.get();
}

glm::quat* add_quat(glm::quat const &mat1, glm::quat const &mat2) {
  glm::quat* tmp = new glm::quat();
  *tmp = glm::operator+(mat1, mat2);
  std::unique_ptr<glm::quat, custom_deleter_quat> _m( tmp );
  return _m.get();
}

glm::quat* mul_quat_float(glm::quat const &mat1, float v) {
  glm::quat* tmp = new glm::quat();
  *tmp = glm::operator*(mat1, v);
  std::unique_ptr<glm::quat, custom_deleter_quat> _m( tmp );
  return _m.get();
}

glm::vec2* mul_mat2_vec2(glm::mat2 const &mat, glm::vec2 const &vec) {
  glm::vec2* tmp = new glm::vec2();
  *tmp = mat * vec;
  std::unique_ptr<glm::vec2, custom_deleter_vec2> _m( tmp );
  return _m.get();
}

glm::vec2* rotate_mat2(glm::mat2 m, float angle, glm::vec2 axis) {

  glm::vec2* tmp = new glm::vec2();

  glm::mat2 rot_mat = glm::mat2(cos(angle),  sin(angle),
               -sin(angle), cos(angle));

  *tmp = m * rot_mat * axis;
  std::unique_ptr<glm::vec2, custom_deleter_vec2> _m( tmp );

  return _m.get();
}

glm::mat2* mul_mat2_mat2(glm::mat2 const &m1, glm::mat2 const &m2) {
  glm::mat2* tmp = new glm::mat2(1.0);
  *tmp = glm::operator*(m1, m2);
  std::unique_ptr<glm::mat2, custom_deleter_mat2> _m( tmp );
  return _m.get();
}

glm::vec4* mul_mat4_vec4(glm::mat4 const &mat, glm::vec4 const &vec) {
  glm::vec4* tmp = new glm::vec4();
  *tmp = mat * vec;
  std::unique_ptr<glm::vec4, custom_deleter_vec4> _m( tmp );
  return _m.get();
}

glm::vec3* mul_mat3_vec3(glm::mat3 const &mat, glm::vec3 const &vec) {
  glm::vec3* tmp = new glm::vec3();
  *tmp = mat * vec;
  std::unique_ptr<glm::vec3, custom_deleter_vec3> _m( tmp );
  return _m.get();
}

glm::mat3* mul_mat3_float(glm::mat3 const &mat, float f) {
  glm::mat3* tmp = new glm::mat3();
  *tmp = mat * f;
  std::unique_ptr<glm::mat3, custom_deleter_mat3> _m( tmp );
  return _m.get();
}


glm::mat4* mat4Wrap::__lookAt (glm::vec3 const &eye, glm::vec3 const &center, glm::vec3 const &up)
{
    glm::mat4 *tmp = new glm::mat4();
    *tmp = glm::lookAt(eye, center, up);
    std::unique_ptr<glm::mat4, custom_deleter_mat4> m( tmp );
    return m.get();
}

std::string print_mat4(glm::mat4 const &m) {
  return glm::to_string(m);
}

std::string print_mat3(glm::mat3 const &m) {
  return glm::to_string(m);
}

glm::mat3* _mat3_cast (glm::mat4 const &mat)
{
    glm::mat3 *tmp = new glm::mat3();
    *tmp = glm::mat3(mat);
    std::unique_ptr<glm::mat3, custom_deleter_mat3> m( tmp );
    return m.get();
}

boost::shared_ptr<glm::mat2> make_mat2(float v1, float v2, float v3, float v4)
{
  return boost::make_shared<glm::mat2>(v1, v2, v3, v4);
}

boost::shared_ptr<glm::mat4> make_mat4(float m)
{
  return boost::make_shared<glm::mat4>(m);
}

boost::shared_ptr<glm::mat3> make_mat3(glm::vec3 right, glm::vec3 up, glm::vec3 front)
{
  return boost::make_shared<glm::mat3>(right, up, front);
}

boost::shared_ptr<glm::quat> make_quat(float w, float x, float y, float z)
{
  return boost::make_shared<glm::quat>(w,x,y,z);
}

glm::vec2 custom_deleter_vec2::operator()(glm::vec2* f) {
  return *f;
}


vector<vector<vec3>> custom_deleter_vecvecVec3::operator()(vector<vector<vec3>>* f) {
  return *f;
}

glm::vec4* mul_vec4(glm::vec4 const &v1, float const &f) {
  glm::vec4* tmp = new glm::vec4();
  *tmp = glm::operator*(v1, f);
  std::unique_ptr<glm::vec4, custom_deleter_vec4> _v( tmp );
  return _v.get();
}

glm::vec4* mul_vec4_mat4(glm::vec4 const &vec, glm::mat4 const &mat) {
  glm::vec4* tmp = new glm::vec4();
  *tmp = vec * mat;
  std::unique_ptr<glm::vec4, custom_deleter_vec4> _m( tmp );
  return _m.get();
}


glm::vec3* mul_vec3(glm::vec3 const &v1, float const &f) {
  glm::vec3* tmp = new glm::vec3();
  *tmp = glm::operator*(v1, f);
  std::unique_ptr<glm::vec3, custom_deleter_vec3> _v( tmp );
  return _v.get();
}

glm::vec2* mul_vec2(glm::vec2 const &v1, float const &f) {
  glm::vec2* tmp = new glm::vec2();
  *tmp = glm::operator*(v1, f);
  std::unique_ptr<glm::vec2, custom_deleter_vec2> _v( tmp );
  return _v.get();
}
vector<vector<vec3>>* add_vecvecVec3(vector<vector<vec3>> const &v1, vector<vector<vec3>> const &v2) {
  vector<vector<vec3>>* tmp = new vector<vector<vec3>>();

  tmp->reserve( v1.size() + v2.size() ); // preallocate memory
  tmp->insert( tmp->end(), v1.begin(), v1.end() );
  tmp->insert( tmp->end(), v2.begin(), v2.end() );


  std::unique_ptr<vector<vector<vec3>>, custom_deleter_vecvecVec3> _v( tmp );
  return _v.get();
}

glm::vec4* div_vec4(glm::vec4 const &v1, glm::vec4 const &v2) {
  glm::vec4* tmp = new glm::vec4();
  *tmp = glm::operator/(v1, v2);
  std::unique_ptr<glm::vec4, custom_deleter_vec4> _v( tmp );
  return _v.get();
}

glm::vec4* add_vec4(glm::vec4 const &v1, glm::vec4 const &v2) {
  glm::vec4* tmp = new glm::vec4();
  *tmp = glm::operator+(v1, v2);
  std::unique_ptr<glm::vec4, custom_deleter_vec4> _v( tmp );
  return _v.get();
}

glm::mat4* copy_mat4(glm::mat4 v1) {
  glm::mat4 *tmp = new glm::mat4();
  *tmp = v1;
  std::unique_ptr<glm::mat4, custom_deleter_mat4> _v( tmp );
  return _v.get();
}

glm::vec2* copy_vec2(glm::vec2 v1) {
  glm::vec2 *tmp = new glm::vec2();
  *tmp = v1;
  std::unique_ptr<glm::vec2, custom_deleter_vec2> _v( tmp );
  return _v.get();
}

glm::vec3* copy_vec3(glm::vec3 v1) {
  glm::vec3 *tmp = new glm::vec3();
  *tmp = v1;
  std::unique_ptr<glm::vec3, custom_deleter_vec3> _v( tmp );
  return _v.get();
}



boost::shared_ptr<glm::vec4> make_vec4(float x, float y, float z, float w)
{
  return boost::make_shared<glm::vec4>(x, y, z, w);
}

boost::shared_ptr<glm::vec4> make_vec4_from_vec3(glm::vec3 v, float w)
{
  return boost::make_shared<glm::vec4>(v.x, v.y, v.z, w);
}

glm::vec3* div_vec3(glm::vec3 const &v1, glm::vec3 const &v2) {
  glm::vec3* tmp = new glm::vec3();
  *tmp = glm::operator/(v1, v2);
  std::unique_ptr<glm::vec3, custom_deleter_vec3> _v( tmp );
  return _v.get();
}

glm::vec3* add_vec3(glm::vec3 const &v1, glm::vec3 const &v2) {
  glm::vec3* tmp = new glm::vec3();
  *tmp = glm::operator+(v1, v2);
  std::unique_ptr<glm::vec3, custom_deleter_vec3> _v( tmp );
  return _v.get();
}

glm::vec3* sub_vec3(glm::vec3 const &v1, glm::vec3 const &v2) {
  glm::vec3* tmp = new glm::vec3();
  *tmp = glm::operator-(v1, v2);
  std::unique_ptr<glm::vec3, custom_deleter_vec3> _v( tmp );
  return _v.get();
}

boost::shared_ptr<glm::vec3> make_vec3(float x, float y, float z)
{
  return boost::make_shared<glm::vec3>(x, y, z);
}

glm::vec2* div_vec2(glm::vec2 const &v1, glm::vec2 const &v2) {
  glm::vec2* tmp = new glm::vec2();
  *tmp = glm::operator/(v1, v2);
  std::unique_ptr<glm::vec2, custom_deleter_vec2> _v( tmp );
  return _v.get();
}

glm::vec2* add_vec2(glm::vec2 const &v1, glm::vec2 const &v2) {
  glm::vec2* tmp = new glm::vec2();
  *tmp = glm::operator+(v1, v2);
  std::unique_ptr<glm::vec2, custom_deleter_vec2> _v( tmp );
  return _v.get();
}

glm::vec2* sub_vec2(glm::vec2 const &v1, glm::vec2 const &v2) {
  glm::vec2* tmp = new glm::vec2();
  *tmp = glm::operator-(v1, v2);
  std::unique_ptr<glm::vec2, custom_deleter_vec2> _v( tmp );
  return _v.get();
}


boost::shared_ptr<glm::vec2> make_vec2(float x, float y)
{
  return boost::make_shared<glm::vec2>(x, y);
}

float custom_deleter_float::operator()(float* f) {
  return *f;
}

glm::vec3* __add__(glm::vec3 const &v1, glm::vec3 const &v2) {
    glm::vec3* tmp = new glm::vec3();
    *tmp = v1 + v2;
    std::unique_ptr<glm::vec3, custom_deleter_vec3> v( tmp );
    return v.get();
}

glm::vec3* _mul(glm::vec3 const &v1, glm::vec3 const &v2) {
    glm::vec3* tmp = new glm::vec3();
    *tmp = v1 * v2;
    std::unique_ptr<glm::vec3, custom_deleter_vec3> v( tmp );
    return v.get();
}
glm::vec4* newVec4(float x, float y, float z, float w) {
    glm::vec4* tmp = new glm::vec4(x, y, z, w);
    std::unique_ptr<glm::vec4, custom_deleter_vec4> v( tmp );
    return v.get();
}

std::string print_vec4(glm::vec4 const &v) {
  return glm::to_string(v);
}

float get_index_vec4(glm::vec4 const &v, int index) {
  float* tmp = new float();
  *tmp = v[index];
  std::unique_ptr<float, custom_deleter_float> _m( tmp );
  return *_m.get();
}

void set_index_vec4(glm::vec4 &v, int index, float value) {
  v[index] = value; 
}

bool eq_vec3(glm::vec3 rhs, glm::vec3 lhs) {
  return rhs == lhs;
}

bool eq_vec2(glm::vec2 rhs, glm::vec2 lhs) {
  return rhs == lhs;
}

float get_index_vec3(glm::vec3 const &v, int index) {
  float* tmp = new float();
  *tmp = v[index];
  std::unique_ptr<float, custom_deleter_float> _m( tmp );
  return *_m.get();
}

void set_index_vec3(glm::vec3 &v, int index, float value) {
  v[index] = value; 
}


glm::vec3* newVec3(float x, float y, float z) {
    glm::vec3* tmp = new glm::vec3(x, y, z);
    std::unique_ptr<glm::vec3, custom_deleter_vec3> v( tmp );
    return v.get();
}

std::string print_vec3(glm::vec3 const &v) {
  return glm::to_string(v);
}


glm::vec2* newVec2(float x, float y) {
    glm::vec2* tmp = new glm::vec2(x, y);
    std::unique_ptr<glm::vec2, custom_deleter_vec2> v( tmp );
    return v.get();
}

std::string print_vec2(glm::vec2 const &v) {
  return glm::to_string(v);
}

glm::quat* _angle_axis(float rad_angle, glm::vec3 const &axis) {
    glm::quat* tmp = new glm::quat();
    *tmp = glm::angleAxis(rad_angle, axis);
    std::unique_ptr<glm::quat, custom_deleter_quat> v( tmp );
    return v.get();
}

glm::quat* _slerp(glm::quat const &x, glm::quat const &y, float interpolationFactor) {
    glm::quat* tmp = new glm::quat();
    *tmp = glm::slerp(x, y, interpolationFactor);
    std::unique_ptr<glm::quat, custom_deleter_quat> v( tmp );
    return v.get();
}

glm::vec3* _cross(glm::vec3 const &v1,  glm::vec3 const &v2) {
    glm::vec3* tmp = new glm::vec3();
    *tmp = glm::cross(v1, v2);
    std::unique_ptr<glm::vec3, custom_deleter_vec3> v( tmp );
    return v.get();
}

float _dot3(glm::vec3 const &v1,  glm::vec3 const &v2) {
    float* tmp = new float();
    *tmp = glm::dot(v1, v2);
    std::unique_ptr<float, custom_deleter_float> v( tmp );
    return *v.get();
}

float _length3(glm::vec3 const &v1) {
    float* tmp = new float();
    *tmp = glm::length(v1);
    std::unique_ptr<float, custom_deleter_float> v( tmp );
    return *v.get();
}

float _length2(glm::vec2 const &v1) {
    float* tmp = new float();
    *tmp = glm::length(v1);
    std::unique_ptr<float, custom_deleter_float> v( tmp );
    return *v.get();
}

glm::vec2* _normalize_vec2(glm::vec2 const &m)
{
    glm::vec2 *tmp = new glm::vec2();
    if (m == glm::vec2(0,0)) {
      *tmp = m;
      std::unique_ptr<glm::vec2, custom_deleter_vec2> _m( tmp );
      return _m.get();
    } else {
      *tmp = glm::normalize(m);
      std::unique_ptr<glm::vec2, custom_deleter_vec2> _m( tmp );    
      return _m.get();  
    }

}

glm::vec3* _normalize(glm::vec3 const &m)
{
    glm::vec3 *tmp = new glm::vec3();
    if (m == glm::vec3(0,0,0)) {
      *tmp = m;
      std::unique_ptr<glm::vec3, custom_deleter_vec3> _m( tmp );
      return _m.get();
    } else {
      *tmp = glm::normalize(m);
      std::unique_ptr<glm::vec3, custom_deleter_vec3> _m( tmp );    
      return _m.get();  
    }

}

float _dot2(glm::vec2 const &v1,  glm::vec2 const &v2) {
    float* tmp = new float();
    *tmp = glm::dot(v1, v2);
    std::unique_ptr<float, custom_deleter_float> v( tmp );
    return *v.get();
}

float _distance(glm::vec3 const &v1,  glm::vec3 const &v2) {
    float* tmp = new float();
    *tmp = glm::distance(v1, v2);
    std::unique_ptr<float, custom_deleter_float> v( tmp );
    return *v.get();
}

float _distance2(glm::vec2 const &v1,  glm::vec2 const &v2) {
    float* tmp = new float();
    *tmp = glm::distance(v1, v2);
    std::unique_ptr<float, custom_deleter_float> v( tmp );
    return *v.get();
}
// TO DO:
// does unique ptr need releasing? Check answers by Tanner Sansbury on SO

glm::mat3* _inverse_mat3(glm::mat3 const &m)
{
    glm::mat3 *tmp = new glm::mat3();
    *tmp = glm::inverse(m);
    std::unique_ptr<glm::mat3, custom_deleter_mat3> _m( tmp );
    return _m.get();
}

glm::mat4* quat_mat4_cast(glm::quat const &q)
{
    glm::mat4 *tmp = new glm::mat4();
    *tmp = glm::mat4(q);
    std::unique_ptr<glm::mat4, custom_deleter_mat4> _m( tmp );
    return _m.get();
}

glm::mat4* mat3_mat4_cast(glm::mat3 const &m)
{
    glm::mat4 *tmp = new glm::mat4();
    *tmp = glm::mat4(m);
    std::unique_ptr<glm::mat4, custom_deleter_mat4> _m( tmp );
    return _m.get();
}

glm::quat* _normalize_quat(glm::quat const &m)
{
    glm::quat *tmp = new glm::quat();
    *tmp = glm::normalize(m);
    std::unique_ptr<glm::quat, custom_deleter_quat> _m( tmp );
    return _m.get();
}

glm::mat3* _skew_symmetric(glm::vec3 const &vector)
{
    glm::mat3 *tmp = new glm::mat3();
    *tmp = glm::mat3(glm::vec3(0.0, vector.z, -vector.y), glm::vec3(-vector.z,0,vector.x), glm::vec3(vector.y,-vector.x,0));
    std::unique_ptr<glm::mat3, custom_deleter_mat3> _m( tmp );
    return _m.get();
}

glm::mat3* _form_orthogonal_basis(glm::vec3 const &v)
{
    glm::mat3 *tmp = new glm::mat3();
    *tmp = formOrthogonalBasis(v);
    std::unique_ptr<glm::mat3, custom_deleter_mat3> _m( tmp );
    return _m.get();
}

glm::mat3* _orthonormalize_orientation(glm::mat3 m)
{
    glm::mat3 *tmp = new glm::mat3();

    m[0] = glm::normalize(m[0]);
    m[2] = glm::normalize(glm::cross(m[0], m[1]));
    m[1] = glm::normalize(glm::cross(m[2], m[0]));

    *tmp = m;
    std::unique_ptr<glm::mat3, custom_deleter_mat3> _m( tmp );
    return _m.get();
}


glm::mat4* _interpolate(glm::mat4 const &m1, glm::mat4 const &m2, float delta)
{
    glm::mat4 *tmp = new glm::mat4();
    *tmp = glm::interpolate(m1, m2, delta);
    std::unique_ptr<glm::mat4, custom_deleter_mat4> _m( tmp );
    return _m.get();
}

glm::mat3* _transpose_mat3(glm::mat3 const &m)
{
    glm::mat3 *tmp = new glm::mat3();
    *tmp = glm::transpose(m);
    std::unique_ptr<glm::mat3, custom_deleter_mat3> _m( tmp );
    return _m.get();
}

glm::mat4* _inverse(glm::mat4 const &m)
{
    glm::mat4 *tmp = new glm::mat4();
    *tmp = glm::inverse(m);
    std::unique_ptr<glm::mat4, custom_deleter_mat4> _m( tmp );
    return _m.get();
}

glm::mat4* _transpose(glm::mat4 const &m)
{
    glm::mat4 *tmp = new glm::mat4();
    *tmp = glm::transpose(m);
    std::unique_ptr<glm::mat4, custom_deleter_mat4> _m( tmp );
    return _m.get();
}

glm::mat4* _translate(glm::mat4 const &m, glm::vec3 const &v)
{
    glm::mat4 *tmp = new glm::mat4();
    *tmp = glm::translate(m, v);
    std::unique_ptr<glm::mat4, custom_deleter_mat4> _m( tmp );
    return _m.get();
}
glm::mat4* _rotate (glm::mat4 const &m, const float &rot, glm::vec3 const &v)
{
    glm::mat4 *tmp = new glm::mat4();
    *tmp = glm::rotate(m, rot, v);
    std::unique_ptr<glm::mat4, custom_deleter_mat4> _m( tmp );
    return _m.get();
}

glm::mat4* _scale(glm::mat4 const &m, glm::vec3 const &v)
{
    glm::mat4 *tmp = new glm::mat4();
    *tmp = glm::scale(m, v);
    std::unique_ptr<glm::mat4, custom_deleter_mat4> _m( tmp );
    return _m.get();
}

glm::mat4* _lookAt (glm::vec3 const &eye, glm::vec3 const &center, glm::vec3 const &up)
{
    glm::mat4 *tmp = new glm::mat4();
    *tmp = glm::lookAt(eye, center, up);
    std::unique_ptr<glm::mat4, custom_deleter_mat4> m( tmp );
    return m.get();
}

glm::mat4* _perspective(float const &fovy, float const &aspect, float const &near, float const &far)
{
    glm::mat4 *tmp = new glm::mat4();
    *tmp = glm::perspective(fovy, aspect, near, far);
    std::unique_ptr<glm::mat4, custom_deleter_mat4> m( tmp );
    return m.get();
}
glm::mat4* _ortho(float const &left, float const &right, float const &bottom, float const &top, float const &near, float const &far)
{
    glm::mat4 *tmp = new glm::mat4();
    *tmp = glm::ortho(left, right, bottom, top, near, far);
    std::unique_ptr<glm::mat4, custom_deleter_mat4> m( tmp );
    return m.get();
}

glm::vec3* _unproject(glm::vec3 const &win,  glm::mat4 const &model, glm::mat4 const &proj, glm::vec4 const &viewport) {
    glm::vec3* tmp = new glm::vec3();
    *tmp = glm::unProject(win, model, proj, viewport);
    std::unique_ptr<glm::vec3, custom_deleter_vec3> v( tmp );
    return v.get();
}



int setVsync(int value) {
  glfwWindowHint( GLFW_DOUBLEBUFFER, value );
  return 0;
}

int setCullFace(int value) {
  if (value){
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
  } else {
    glDisable(GL_CULL_FACE);
  }
  return 0;
}

int setDepthTest(int value) {
  if (value){
    glEnable(GL_DEPTH_TEST);
  } else {
    glDisable(GL_DEPTH_TEST);
  }
  return 0;
}

int clearDepthBuffer() {
  glClear(GL_DEPTH_BUFFER_BIT);
  return 0;
}

int clearColorBuffer() {
  glClear(GL_COLOR_BUFFER_BIT);
  return 0;
}


int setAlphaTransparency(int value) {
  if (value) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
  } else {
    glDisable(GL_BLEND);
  }
  return 0;
}
/// @brief checks the state (pressed, released, held, etc...) of the queried button 
/// @param window the current window
/// @param
int getMouseButton(GLFWwindow* window, int button) {
  return glfwGetMouseButton(window, button);
}



glm::vec3 getPixel(unsigned int x, unsigned int y) {
  struct{ GLubyte red, green, blue; } pixel;
  glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixel);
  return glm::vec3(pixel.red, pixel.green, pixel.blue);
}

bool operator==(Data d1, const Data d2) {
  return &d1 == &d2;
}


void wrap_mathUtils() {

    python::def("dot", _dot2);
    python::def("normalize", _normalize_vec2, python::return_value_policy<python::manage_new_object>());

    python::def("normalize", _normalize, python::return_value_policy<python::manage_new_object>());
    python::def("dot", _dot3);
    python::def("cross", _cross, python::return_value_policy<python::manage_new_object>());
    python::def("length", _length3);
    python::def("length", _length2);
    python::def("distance", _distance);
    python::def("distance", _distance2);
    python::def("angle_axis", _angle_axis,  python::return_value_policy<python::manage_new_object>());
    python::def("slerp", _slerp,  python::return_value_policy<python::manage_new_object>());

    python::def("ray_intersect_sphere", intersect);
    python::def("ray_cast", rayCast);
    python::def("ray_intersect_plane", intersectPlane);
    python::def("ray_intersect_quad", rayIntersectQuad);
    python::def("ray_intersect_object", rayObjectIntersect);
    python::def("ray_intersect_animated_object", rayAnimatedObjectIntersect);
    python::def("ray_intersect_triangle", rayTriangleIntersect);
    python::def("line_segment_intersect_triangle", lineSegmentTriangleIntersect);
    python::def("ray_intersect_box", rayBoxIntersect);
    python::def("box_intersect_box", check_collision);
    python::def("box_intersect_plane", boxPlaneIntersect);
    python::def("sphere_intersect_object", sphereObjectIntersect);
    python::def("min_distance_point_to_plane", minDistancePointToPlane);
    // GL/app/window utility functions
    python::def("set_depth_test", setDepthTest);
    python::def("set_cull_face", setCullFace);
    python::def("set_vsync", setVsync);
    python::def("clear_depth_buffer", clearDepthBuffer);
    python::def("clear_color_buffer", clearColorBuffer);
    python::def("set_alpha_transparency", setAlphaTransparency);
    //python::def("load_GL", loadGL);
    python::def("set_cursor_visible", setCursorVisible);
    python::def("get_pixel", getPixel);
    python::def("unproject", _unproject, python::return_value_policy<python::manage_new_object>());
    python::def("reflect", reflect);
    
    python::def("terminate", glfwTerminate);
    python::def("get_time", glfwGetTime);
    python::def("get_key", glfwGetKey);
    python::def("get_position", getPosition);

    python::def("get_mouse_button", getMouseButton);
    python::def("set_input_mode", glfwSetInputMode);
    python::def("make_context_current", glfwMakeContextCurrent, boost::python::return_value_policy<boost::python::return_opaque_pointer>());
    python::def("get_current_context", glfwGetCurrentContext, boost::python::return_value_policy<boost::python::return_opaque_pointer>());
    python::def("set_window_should_close", glfwSetWindowShouldClose, boost::python::return_value_policy<boost::python::return_opaque_pointer>());

    python::def("is_joystick_present", isJoystickPresent, boost::python::return_value_policy<boost::python::return_by_value>());
    python::def("get_joystick_axes", getJoystickAxes, boost::python::return_value_policy<boost::python::return_by_value>()); 

    python::class_<BoundingBox>("BoundingBox", python::init<>())
    .def("get_translated_vertices", &BoundingBox::getTranslatedVertices)
    .def("setup", &BoundingBox::setup)
    .def_readwrite("model_matrix", &BoundingBox::modelMatrix)
    .def_readwrite("velocity", &BoundingBox::velocity)
    .def_readwrite("to_draw", &BoundingBox::toDraw)
    .def_readwrite("min", &BoundingBox::min)
    .def_readwrite("max", &BoundingBox::max)
    ;
    python::class_<CollisionInfo>("CollisionInfo", python::init<>())
    .def_readwrite("position", &CollisionInfo::position)
    .def_readwrite("normal", &CollisionInfo::normal)
    .def_readwrite("depth", &CollisionInfo::depth)
    ;

    // Custom iterator wrapper

    // Register interable conversions.

    iterable_converter()
    // Build-in type.
    .from_python<std::vector<StaticMesh> >()
    .from_python<std::vector<AnimatedMesh> >()

    .from_python<std::vector<double> >()
    // Each dimension needs to be convertable.
    .from_python<std::vector<std::string> >()
    .from_python<std::vector<std::vector<std::string> > >()
    // User type.
    .from_python<std::vector<float> >()
    .from_python<std::vector<glm::mat4> >()
    .from_python<std::vector<std::vector<glm::mat4> > >()
    .from_python<std::vector<std::vector<glm::vec3> > >()
    .from_python<std::vector<StaticModel> >()
    .from_python<std::vector<Texture> >()
    .from_python<std::vector<Vertex> >() 
    .from_python<std::vector<VertexTransform> >() 
    .from_python<std::vector<glm::vec3> >()  
    .from_python<std::vector<Data> >()              
    ;

    // wrap vector of StaticMeshes
    boost::python::class_< std::vector < StaticMesh > >("StaticMeshVector")
        .def(boost::python::vector_indexing_suite<std::vector< StaticMesh > >());

        // wrap vector of AnimatedMeshes
    boost::python::class_< std::vector < AnimatedMesh > >("AnimatedMeshVector")
        .def(boost::python::vector_indexing_suite<std::vector< AnimatedMesh > >());

    // wrap vector of Textures
    boost::python::class_< std::vector < Texture > >("TextureVector")
        .def(boost::python::vector_indexing_suite<std::vector< Texture > >());
    // wrap vector of Vertex
    boost::python::class_< std::vector < Vertex > >("VertexVector")
        .def(boost::python::vector_indexing_suite<std::vector< Vertex > >());

    // wrap vector of VertexTransform
    boost::python::class_< std::vector < VertexTransform > >("VertexTransformVector")
        .def(boost::python::vector_indexing_suite<std::vector< VertexTransform > >());

    // wrap vector of Vertex
    boost::python::class_< std::vector < float > >("FloatVector")
        .def(boost::python::vector_indexing_suite<std::vector< float > >());

    // wrap vector of vector of vec3
    boost::python::class_<std::vector< std::vector< glm::vec3 > > >("Vec3VectorVector")
        .def(boost::python::vector_indexing_suite<std::vector< std::vector< glm::vec3 > > >());

    // wrap vector of vec3
    boost::python::class_<std::vector< glm::vec3 > >("Vec3Vector")
        .def(boost::python::vector_indexing_suite<std::vector< glm::vec3 > >());


    // wrap vector of mat4
    boost::python::class_<std::vector< glm::mat4 > >("Mat4Vector")
        .def(boost::python::vector_indexing_suite<std::vector< glm::mat4 > >());

    // wrap vector of unsigned int
    boost::python::class_<std::vector< unsigned int > >("UnsignedIntVector")
        .def(boost::python::vector_indexing_suite<std::vector< unsigned int > >());

    // wrap vector of Data
    boost::python::class_< std::vector < Data > >("DataVector")
        .def(boost::python::vector_indexing_suite<std::vector< Data > >());
}