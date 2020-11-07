#ifndef LAMP_HPP
#define LAMP_HPP

#include "cube.hpp"
#include "../material.h"
#include "../shader.h"

class Lamp : public Cube {
public:
	glm::vec3 lightColour;
};

#endif