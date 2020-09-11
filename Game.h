#pragma once

#include <iostream>
#include <vector>
#include <time.h>
#include <sstream>

#include <SFML/Graphics.hpp>

class Game
{
private:
    //variables 
    //window
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event ev;
    //mouse pos
    sf::Vector2f mousePosWindow;
    
    //Resources 
    sf::Font font;
    
    //Text 
    sf::Text uiText;
    
    //Game Logic
//    bool add = false;
    bool endGame;
    unsigned points;
    int health;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    bool mouseHeld;
    
    //Game objects 
    sf::RectangleShape enemy;
    std::vector<sf::RectangleShape> enemies;
    
    //Private functions
    void initVariables(); 
    void initWindow();
    void initFonts();
    void initText();
    void initEnemies();
    
public:
    //Constructors / Destructors
    Game();
    virtual ~Game();
    
    //Accessors
    bool running() const;
    bool getEndGame() const;
    
    //Fucnctions
    void spawnEnemy();
    
    void pollEvents();
    void updateMousePositions();
    void updateEnemies();
    void updateText();
    void update();
    
    void renderEnemies(sf::RenderTarget &target);
    void renderText(sf::RenderTarget &target);
    void render();
    
};