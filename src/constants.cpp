#include <string>

#include "constants.hpp"

const int INIT_SCREEN_WIDTH = 600;
const int INIT_SCREEN_HEIGHT = 600;
const int MIN_SCREEN_WIDTH = INIT_SCREEN_WIDTH;
const int MIN_SCREEN_HEIGHT = INIT_SCREEN_HEIGHT;

const char WIN_TITLE[] = "OpenGL Project";

const float BLACK[]{ 0.09f, 0.09f, 0.09f, 1.0f };
const float WHITE[]{ 0.85f, 0.85f, 0.85f, 1.0f };

extern const std::string ASSET_DIR = "../assets/";
extern const std::string CONTAINER_PATH = ASSET_DIR + (std::string)"container.jpg";
extern const std::string AWESOMEFACE_PATH = ASSET_DIR + (std::string)"awesomeface.png";

extern const std::string SHADER_DIR = "../shaders/";
extern const std::string VERTEX_SHADER_PATH = SHADER_DIR + (std::string)"vertex_shader.vert";
extern const std::string FRAGMENT_SHADER_PATH = SHADER_DIR + (std::string)"fragment_shader.frag";