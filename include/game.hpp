#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <memory>

extern "C" {
	// Include the GLAD loader *before* including GLFW!
	#include "glad/glad.h"
	
	// Include the GLFW library (should be the same for all OS):
	#include <GLFW/glfw3.h>
}
#include "model.hpp"
#include "border_model.hpp"
#include "player_manager.hpp"
#include "font.hpp"
#include "menu.hpp"
#include "side_panel.hpp"

class Game {
   private:
    GLFWwindow* window;
    std::shared_ptr<BorderModel> border_model;
    std::shared_ptr<PlayerManager> player_manager;
    std::shared_ptr<Font> font; 
    std::shared_ptr<Menu> menu;  
    std::shared_ptr<SidePanel> side_panel;
    bool has_players;
   public:
    Game(GLFWwindow* window);
    int generate_fonts();
    void loop();
    void terminate();
    int get_player_count();
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


#endif
