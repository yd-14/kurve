#ifndef FONT_HPP
#define FONT_HPP

extern "C" {
// Include the GLAD loader *before* including GLFW!
#include "glad/glad.h"

// Include the GLFW library (should be the same for all OS):
#include <GLFW/glfw3.h>

// Include FreeType2
#include "ft2build.h"
#include FT_FREETYPE_H
}

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <map>
#include <string>

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;         // Size of glyph
    glm::ivec2 Bearing;      // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class Font {
   private:
    std::map<char, Character> Characters;
    unsigned int texture;
    unsigned int VAO;
    unsigned int VBO;
    GLuint shader_id;
   public:
    Font();
    ~Font();
    void draw_text(std::string text, 
                    float x, 
                    float y, 
                    float scale, 
                    glm::vec3 color);
};

#endif