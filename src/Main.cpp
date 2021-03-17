/**
 * @author Ryan Purse
 * Created On: 17/03/2021
 */

// Vendors
#include "MCG_GFX_Lib.h"
#include "glm.hpp"

// std
#include <iostream>

int main(int argc, char *argv[])
{
    glm::ivec2 windowSize(400, 400);

    if(!mcg::init(windowSize)) { return -1; }

    mcg::setBackground(glm::vec3(1,0,0));

    std::cout << "Hello, World!" << std::endl;

    mcg::showAndHold();
    return 0;
}
