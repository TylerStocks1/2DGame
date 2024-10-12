#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include <iostream>

int main()
{
    //create our classes
    sf::Font font;
    sf::Text text;
    TileMap map;

    //Character struct
    struct Player
    {
        std::string name;
        int score;
        int deaths;
        int x;
        int y;
    };

    int SCREEN_HEIGHT = 512;
    int SCREEN_WIDTH = 256;
    int CellSize = 32;
    int NumRows = 16;
    int NumCols = 8;
    int GameScore = 0;

    //creating the level with our tile map
    const int level[] =
    {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 3, 3, 3, 0, 0, 3, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    };

    sf::RenderWindow window(sf::VideoMode(SCREEN_HEIGHT, SCREEN_WIDTH), "Tyler's Mini game");
    window.setFramerateLimit(60);

    //load everything
    if (!font.loadFromFile("../Fonts/pacman.ttf"))
        std::cout << "Error in loading font!";

    if (!map.load("../Assets/Tileset/Maze.png", sf::Vector2u(CellSize, CellSize), level, NumRows, NumCols))
        return -1;

    //text settings
    text.setFont(font);
    text.setString("High Score: ");
    text.setCharacterSize(5);
    text.setFillColor(sf::Color::White);
    text.setPosition(20, 20);

    //main game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(map);
        map.drawGrid(window, CellSize, NumCols, NumRows);
        window.display();

    }
    return 0;
}