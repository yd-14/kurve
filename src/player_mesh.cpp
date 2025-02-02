#include "player_mesh.hpp"

#include <iostream>

extern "C" {
#include <math.h>
#include <stdlib.h>
}

PlayerMesh::PlayerMesh(glm::vec3 color) {
    // Triangle data:
    std::vector<vertex_data_t> vertex_data;

    double radius{0.17};
    double delta_angle{(2 * 3.14159265) / parts};
    double angle{0};

    for (int i = 0; i < this->parts; i++) {
        double x{radius * cos(angle)};
        double y{radius * sin(angle)};
        angle += delta_angle;
        vertex_data.push_back(
            {
                .position = {
                    static_cast<GLfloat>(x), 
                    static_cast<GLfloat>(y), 
                    0
                }, 
                .color = color
            }
        );
    }

    // TODO: blackbox! Create a VAO.
    GLuint vao;

    glGenVertexArrays(1, &vao);
    gl_check_error("glGenVertexArrays");

    glBindVertexArray(vao);
    gl_check_error("glBindVertexArray");

    this->vao = vao;

    // Generate and bind a vertex buffer object:
    GLuint vbo;

    glGenBuffers(1, &vbo);
    gl_check_error("glGenBuffers");

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    gl_check_error("glBindBuffer");
    
    this->vbo = vbo;

    // Upload the vertex data to the GPU:
    glBufferData(
        GL_ARRAY_BUFFER, 
        parts * sizeof(vertex_data_t), 
        (const GLvoid*)vertex_data.data(), 
        GL_STATIC_DRAW);
    gl_check_error("glBufferData");

    // Position attribute:
    // Number of attribute, number of components, 
    // data type, normalize, stride, pointer (= offset)
    glVertexAttribPointer(
        ATTRIB_POSITION, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        sizeof(vertex_data_t), 
        (GLvoid*)offsetof(vertex_data_t, position));
    gl_check_error("glVertexAttribPointer [position]");

    glVertexAttribPointer(
        ATTRIB_COLOR, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        sizeof(vertex_data_t), 
        (GLvoid*)offsetof(vertex_data_t, color));
    gl_check_error("glVertexAttribPointer [color]");

    // Enable the attributes:
    glEnableVertexAttribArray(ATTRIB_POSITION);
    gl_check_error("glEnableVertexAttribArray [position]");

    glEnableVertexAttribArray(ATTRIB_COLOR);
    gl_check_error("glEnableVertexAttribArray [color]");
}

PlayerMesh::~PlayerMesh() {
#ifdef DEBUG
    std::cout << "---- DESTROY PlayerMesh ----" << std::endl;
#endif
    glDeleteVertexArrays(1, &this->vao);
    gl_check_error("glDeleteVertexArrays");

    glDeleteBuffers(1, &this->vbo);
    gl_check_error("glDeleteBuffers");
}

void PlayerMesh::draw() {
    this->bind();
    glDrawArrays(GL_TRIANGLE_FAN, 0, this->parts);
    gl_check_error("glDrawArrays");
}