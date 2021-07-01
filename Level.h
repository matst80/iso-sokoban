//
// Created by Mats Törnberg on 2021-06-27.
//

#ifndef SOKOBAN_LEVEL_H
#define SOKOBAN_LEVEL_H

#include <vector>
#include <SFML/Graphics.hpp>

const int blockWidth = 222;
const int blockHeight = 256;
const float spriteWidth = 109;
const int spriteHeight = 62;
const float spriteFactor = 1.718;

class IsoSprite : public sf::Sprite {


    sf::Vector2f WorldToScreen(sf::Vector2f v)
    {
        return sf::Vector2f(v.x - v.y*spriteFactor, (v.x/spriteFactor + v.y)-z);
    }
public:
    float sort;
    int z=1;
    IsoSprite(const sf::Texture *texture, const sf::IntRect rect) : sf::Sprite(*texture,rect) {

    }
    void setZ(int z) {
        this->z = z;
    }

    sf::Vector2f setPos(sf::Vector2f pos) {
        auto screenPosition = WorldToScreen(pos);
        setPosition(screenPosition);
        this->sort = screenPosition.y;
        return screenPosition;
    }
    sf::Vector2f setBlockPosition(int x, int y) {
        auto screenPosition = WorldToScreen(sf::Vector2f(x*spriteWidth,y*spriteHeight));
        setPosition(screenPosition);
        this->sort = screenPosition.y;
        return screenPosition;
    }
    sf::Vector2f setBlockPosition(sf::Vector2i pos) {
        auto screenPosition = WorldToScreen(sf::Vector2f(pos.x*spriteWidth,pos.y*spriteHeight));
        setPosition(screenPosition);
        this->sort = screenPosition.y;
        return screenPosition;
    }
    sf::Vector2f getScreenPosition(sf::Vector2i pos) {
        return WorldToScreen(sf::Vector2f(pos.x*spriteWidth,pos.y*spriteHeight));
    }
    void updateSort(float d) {
        this->sort = d;
    }
};


struct Block {
    IsoSprite *sprite;
    int id;
    sf::Vector2i *position;
    bool isBox;
    bool isFloor;
};

struct Movement {
    IsoSprite *sprite;
    float elapsed;
    float ms;
    sf::Vector2f totalMovement;
    sf::Vector2f origin;
    Movement(IsoSprite *sprite, sf::Vector2f dest, sf::Vector2f origin, int ms) {
        elapsed = 0;
        this->ms = ms;
        this->sprite = sprite;
        this->origin = origin;
        this->totalMovement = dest-origin;
    }
};

struct Level {
    int width;
    int height;
    sf::Vector2i start;
    std::vector<sf::Vector2i *> end;
    std::vector<Block> blocks;
};


#endif //SOKOBAN_LEVEL_H
