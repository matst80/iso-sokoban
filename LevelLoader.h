//
// Created by Mats Törnberg on 2021-06-27.
//

#ifndef SOKOBAN_LEVELLOADER_H
#define SOKOBAN_LEVELLOADER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Level.h"

class LevelLoader {
public:
    Level load(std::string filename, int nr, sf::Texture *texture);
};


#endif //SOKOBAN_LEVELLOADER_H
