#include "side_panel.hpp"
#include "user.hpp"

SidePanel::SidePanel(GLFWwindow* window, std::shared_ptr<Font> font) {
    this->window = window;
    this->font = font;
}

void SidePanel::draw(int player_count, int max_score) {
    auto user_data = (user_data_t*)glfwGetWindowUserPointer(this->window);
    // Show the right player names
    float y_pos = 400.0f;
    float count = 0;

    // Draw the score at the top of the Side Panel
    this->font->draw_text(
        std::to_string(max_score),
        460.0f,
        500.0f,
        1.0f,
        glm::vec3(1.0f, 1.0f, 1.0f)
    );
    this->font->draw_text(
        "MAX. SCORE",
        410.0f,
        450.0f,
        0.7f,
        glm::vec3(1.0f, 1.0f, 1.0f)
    );

    for (auto player_info : *user_data->player_info) {
        std::string name = player_info.name;
        auto color = player_info.menu_color;
        if (player_info.is_active == true) {
            y_pos = y_pos - 50.0f;
            auto score_text = std::to_string(player_info.score);
            this->font->draw_text(name, 450.0f, y_pos, 0.6f, color);
            this->font->draw_text(score_text, 400.0f, y_pos, 0.6f, color);
            count += 1.0f;
        }
    }

    GameState game_state = user_data->game_state;
    if (game_state == GAME_PAUSE) {
        this->font->draw_text(
            "Press SPACE",
            400.0f,
            -300.0f,
            0.7f,
            glm::vec3(1.0f, 1.0f, 1.0f));
        this->font->draw_text(
            "to continue",
            400.0f,
            -325.0f,
            0.7f,
            glm::vec3(1.0f, 1.0f, 1.0f));
    } else if (game_state == GAME_ACTIVE) {
        this->font->draw_text(
            "Press SPACE",
            400.0f,
            -300.0f,
            0.7f,
            glm::vec3(1.0f, 1.0f, 1.0f));
        this->font->draw_text(
            "to pause",
            400.0f,
            -325.0f,
            0.7f,
            glm::vec3(1.0f, 1.0f, 1.0f));
    } else if (game_state == GAME_TRANSITION) {
        this->font->draw_text(
            "Press SPACE",
            400.0f,
            -300.0f,
            0.7f,
            glm::vec3(1.0f, 1.0f, 1.0f));
        this->font->draw_text(
            "to start",
            400.0f,
            -325.0f,
            0.7f,
            glm::vec3(1.0f, 1.0f, 1.0f));
    }

}

void SidePanel::update() {

}