#include <iostream>
#include <string>
#include <filesystem>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "LevelLoader.h"
#include <memory>
#include <string>
#include <stdexcept>

template<typename ... Args>
std::string string_format(const std::string &format, Args ... args) {
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
    auto size = static_cast<size_t>( size_s );
    auto buf = std::make_unique<char[]>(size);
    std::snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

namespace fs = std::__fs::filesystem;
using namespace sf;
using namespace std;

enum LevelStatus {
    LOADING, PLAYING, DONE
};

const float movementTime = 130 * 1000;

const int playerFrames[8] = {5, 4, 1, 0, 6, 9, 3, 2};


class Player {
    int frame = 0;
    Keyboard::Key lastKey;

    bool isPressed(Keyboard::Key k) {
        if (Keyboard::isKeyPressed(k)) { //lastKey != k
            lastKey = k;
            return true;
        }
        return false;
    }

    IntRect getPlayerRect(int nr) {
        return IntRect((nr / 8) * blockWidth, (nr % 8) * blockHeight, blockWidth, blockHeight);
    }

    Vector2i getMovement() {
        if (isPressed(Keyboard::W)) {
            direction = 0;
            return Vector2i(0, -1);
        } else if (isPressed(Keyboard::S)) {
            direction = 1;
            return Vector2i(0, 1);
        } else if (isPressed(Keyboard::A)) {
            direction = 2;
            return Vector2i(-1, 0);
        } else if (isPressed(Keyboard::D)) {
            direction = 3;
            return Vector2i(1, 0);
        }
        return Vector2i(0, 0);
    }

public:
    Vector2i movement;
    Vector2i position;
    int direction;
    IsoSprite *playerSprite;


    Player(Texture *texture) {
        this->playerSprite = new IsoSprite(texture, getPlayerRect(playerFrames[1]));
    }

    void reset(Vector2i position) {
        this->position = position;
        playerSprite->setBlockPosition(position);
    }

    void draw(RenderWindow *window, View *view) {
        window->draw(*playerSprite);
        view->setCenter(playerSprite->getPosition());
    }

    void changeFrame(float duration) {
        frame++;
        int add = frame % 2 == 0 ? 4 : 0;
        //this->playerSprite->setTextureRect(getPlayerRect(playerFrames[direction + add]));
    }

    Vector2i move(float gameTime) {
        this->movement = getMovement();
        return position + movement;
    }

    Movement *makeMove() {
        if (movement.x != 0 || movement.y != 0) {
            position += movement;
            auto dest = playerSprite->getScreenPosition(position);
            return new Movement(playerSprite, dest, playerSprite->getPosition(), movementTime);
        }
        return nullptr;
    }
};

class LevelPlayer {
    Level level;
    View *view;
    Texture *texture;
    LevelLoader loader;
    std::vector<Movement *> moves;
    Player *player;
    //vector<IsoSprite *> end;
    vector<IsoSprite *> sprites;
public:
    LevelStatus status;

    LevelPlayer(View *view, Texture *texture) {
        this->player = new Player(texture);
        this->view = view;
        this->texture = texture;
        this->loader = LevelLoader();
    }

    void load(int nr) {
        status = LevelStatus::LOADING;
        //this->end.clear();
        this->moves.clear();
        this->sprites.clear();
        this->level = this->loader.load("maps/696.txt", nr, this->texture);
        player->reset(level.start);
        this->sprites.push_back(player->playerSprite);

//        for (Vector2f *e:this->level.end) {
//            auto sp = new IsoSprite(texture, IntRect(0, 384, 32, 32));
//            sp->setPosition(*e);
//            this->end.push_back(sp);
//            this->sprites.push_back(sp);
//        }
        for (Block b:level.blocks) {
            this->sprites.push_back(b.sprite);
        }

        status = LevelStatus::PLAYING;
    }

    bool handleAnimations(float elapsed) {
        if (!moves.empty()) {
            bool hasAnimation = false;

            for (Movement *m: moves) {
                if (m->elapsed < m->ms) {
                    m->elapsed += elapsed;
                    float p = min(m->elapsed / m->ms, 1.0f);
                    auto np = m->origin + (m->totalMovement * p);
                    m->sprite->setPosition(np);
                    m->sprite->updateSort(np.y);
                    m->sprite->z = spriteHeight * 2;
                    hasAnimation = true;
                }
            }
            if (hasAnimation) {
                player->changeFrame(elapsed);

            }
            return hasAnimation;
        }
        return false;
    }
    bool same(Vector2i a, Vector2i b) {
        return a.x==b.x && a.y==b.y;
    }

    void update(float elapsed) {

        if (status != LevelStatus::PLAYING)
            return;

        if (handleAnimations(elapsed)) return;
        auto newPosition = player->move(elapsed);
        bool canMove = true;
        for (Block b:level.blocks) {
            if (b.isFloor)
                continue;
            auto collide = *b.position == newPosition;

            if (b.isBox && collide) {
                auto nextPos = *b.position + player->movement;

                for (Block c:level.blocks) {
                    if (*c.position == nextPos && !c.isFloor) {
                        canMove = false;
                    }
                }
                if (canMove) {
                    *b.position += player->movement;
                    auto dest = b.sprite->getScreenPosition(*b.position);
                    moves.push_back(new Movement(b.sprite, dest, b.sprite->getPosition(), movementTime));
                }

            } else if (!b.isFloor && collide) {
                canMove = false;
            }
        }
        if (status == LevelStatus::PLAYING) {
            bool hasAll = true;
            for (Vector2i *p:level.end) {
                bool hasThis = false;
                for (Block b:level.blocks) {
                    if (*b.position == *p && b.isBox) {
                        hasThis = true;
                        break;
                    }
                }
                if (!hasThis) {
                    hasAll = false;
                    break;
                }
            }
            if (hasAll) {
                this->status = LevelStatus::DONE;
            }
            if (canMove) {
                auto move = player->makeMove();
                if (move != nullptr) {
                    moves.push_back(move);
                }
            }
        }
    }

    struct {
        bool operator()(IsoSprite *a, IsoSprite *b) const { return (a->z+1) * (a->sort+1) < (b->z+1) * (b->sort+1); }
    } customLess;

    void draw(RenderWindow *window) {

        if (status != LevelStatus::LOADING) {
            std::sort(sprites.begin(), sprites.end(), customLess);

            for (Sprite *s:this->sprites) {
                window->draw(*s);
            }

        }
        view->setCenter(player->playerSprite->getPosition());
    }
};

int main() {
    // 8-16

    int currentNr = 0;

    Texture spriteMap;

    spriteMap.loadFromFile("tilesheet_complete_2X.png");

    LevelLoader loader;
    sf::View view;
    const int width = 1920;
    const int height = 1080;

    sf::Font font;
    if (!font.loadFromFile("OpenSans-Light.ttf")) {
        // error...
    }


    view.setSize(width, height);
    view.zoom(1);

    LevelPlayer levelPlayer(&view, &spriteMap);

    levelPlayer.load(0);

    VideoMode videoMode(width, height);
    RenderWindow window(videoMode, "Sokoban");
    Event event;

    sf::Clock clock;
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(32);
    text.setFillColor(Color::White);

    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();

        window.clear(Color::Black);

        levelPlayer.update(elapsed.asMicroseconds());

        levelPlayer.draw(&window);
        text.setPosition(10, 10);
        text.setString(string_format("Level: %d", currentNr));
        window.draw(text);

        window.setView(view);
        window.display();
        if (levelPlayer.status == LevelStatus::DONE || Keyboard::isKeyPressed(Keyboard::N)) {
            levelPlayer.load(++currentNr);
        }
        if (Keyboard::isKeyPressed(Keyboard::R)) {
            levelPlayer.load(currentNr);
        }

        while (window.pollEvent(event)) {
            if ((event.type == Event::Closed) ||
                ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape)))
                window.close();

        }
    }
    return EXIT_SUCCESS;
}
