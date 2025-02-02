#ifndef MODEL_HPP
#define MODEL_HPP

#include <memory>

#include "mesh.hpp"
#include "shader.hpp"
#include "gl_calls.hpp"
#include "user.hpp"

extern "C" {
// Include the GLAD loader *before* including GLFW!
#include "glad/glad.h"

// Include the GLFW library (should be the same for all OS):
#include <GLFW/glfw3.h>
}

class Model {
   protected:
    user_data_t* user_data;
    virtual void init_uniforms() = 0;
    virtual void init_values() = 0;
   public:
    std::shared_ptr<Mesh> mesh;
    GLuint shader_id;
    virtual void update(GLFWwindow* window) = 0;
    virtual void draw() = 0;
};

#endif