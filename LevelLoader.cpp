//
// Created by Mats Törnberg on 2021-06-27.
//

#include "LevelLoader.h"

using namespace std;
using namespace sf;

IntRect getSpriteRect(int nr) {
    return IntRect((nr / 8) * blockWidth, (nr % 8) * blockHeight, blockWidth, blockHeight);
}

Block getBlock(Vector2i *pos, int type, bool isBox, bool isFloor, Texture *texture) {
    Block blk;
    blk.isBox = isBox;
    blk.isFloor = isFloor;
    blk.sprite = new IsoSprite(texture, getSpriteRect(type));
    if (!isFloor) {
        blk.sprite->setZ(spriteHeight * 2);

    }
    if (type == 90) {
        blk.isFloor = true;
        blk.sprite->setColor(Color(255, 255, 255, 64));
    }
    blk.id = pos->y * 100 + pos->x;
    blk.sprite->setBlockPosition(*pos);
    blk.position = pos;

    return blk;
}

Level LevelLoader::load(string filename, int nr, Texture *texture) {
    std::ifstream fs;
    string line;
    fs.open(filename);
    Level level;


    int c = 0;
    int x = 0;
    int y = 0;
    if (fs.is_open()) {
        while (getline(fs, line)) {
            x = 0;
            bool addFloor = false;
            if (line[0] == ';') {
                c++;
                continue;
            }
            if (line == "") {
                continue;
            }
            if (c == nr) {
                for (char chr:line) {
                    auto p = new Vector2i(x, y);
                    if (chr == '@' || chr == '+') {
                        level.start = Vector2i(x, y);
                    }
                    if (chr == '.' || chr == '+' || chr == '*') {
                        level.end.push_back(p);
                        level.blocks.push_back(getBlock(p, 90, false, false, texture));
                    }
                    if (chr == '$' || chr == '*') {
                        level.blocks.push_back(getBlock(p, 35, true, false, texture));
                    }
                    if (chr == '#') {
                        addFloor = true;
                        level.blocks.push_back(getBlock(p, 96, false, false, texture));
                    }
                    if (addFloor) {
                        level.blocks.push_back(getBlock(p, 80, false, true, texture));
                    }
                    x++;
                }
                level.width = line.size();
                level.height = ++y;
            }
        }
        fs.close();

    } else cout << "Unable to open file";
    return level;
}