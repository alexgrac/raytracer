#include "camera.h"



Camera::Camera() :
_lowerLeft(glm::vec3(-2.0, -1.0, -1.0)),
_horizontal(glm::vec3(4.0, 0.0, 0.0)),
_vertical(glm::vec3(0.0, 2.0, 0.0)),
_origin(glm::vec3(0.0)) {
}
