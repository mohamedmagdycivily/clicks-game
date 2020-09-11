#include "Game.h"

//Private functions
void Game::initVariables()
{
    window = NULL;
    
    //Game logic
    endGame = false;
    points = 0;
    health = 25;
    enemySpawnTimerMax = 20.f;
    enemySpawnTimer =enemySpawnTimerMax; 
    maxEnemies = 20;
    mouseHeld = false;
}

void Game::initWindow()
{
//    videoMode = sf::VideoMode::getDesktopMode();
    videoMode.height = 600;
    videoMode.width = 800;
    window = new sf::RenderWindow(videoMode,"Game 1", sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(60);
}

void Game::initFonts()
{
    if(!font.loadFromFile("/home/mohamed/Desktop/MY_CODE/Game_Project/Files/SFML_C-_Simple_Games-master/SFML_C++_Simple_Games/SFML_C++_Simple_Games/Fonts/Dosis-Light.ttf"))
    {
        std::cout << "ERROR : Game.cpp : initFonts() :: cant load from file" << std::endl;
    }
}

void Game::initText()
{
    uiText.setFont(font);
    uiText.setString("NONE");
//    uiText.setColor(sf::Color::White);
    uiText.setCharacterSize(24);
}


void Game::initEnemies()
{
    enemy.setFillColor(sf::Color::Blue);
    enemy.setSize(sf::Vector2f(100.f, 100.f));
    enemy.setPosition(0.f, 0.f);
}

//Constructors / Destructors
Game::Game()
{
    std::srand(time(0));
    initVariables();
    initWindow();
    initEnemies();
    initFonts();
    initText();
}

Game::~Game()
{
    delete window;
}

//Accessors
bool Game::running() const
{
    return window->isOpen();
}

bool Game::getEndGame() const
{
    return endGame;
}

//Fucnctions
void Game::spawnEnemy()
{    
    //Randomize enemy type
    int type = rand() % 5;
    
    switch (type)
    {
    case 0:
        this->enemy.setSize(sf::Vector2f(10.f, 10.f));
        enemy.setPosition((std::rand() % (window->getSize().x - (int)enemy.getSize().x)), 0.f);
        this->enemy.setFillColor(sf::Color::Magenta);
        break;
    case 1:
        this->enemy.setSize(sf::Vector2f(30.f, 30.f));
        enemy.setPosition((std::rand() % (window->getSize().x - (int)enemy.getSize().x)), 0.f);
        this->enemy.setFillColor(sf::Color::Blue);
        break;
    case 2:
        this->enemy.setSize(sf::Vector2f(50.f, 50.f));
        enemy.setPosition((std::rand() % (window->getSize().x - (int)enemy.getSize().x)), 0.f);
        this->enemy.setFillColor(sf::Color::Cyan);
        break;
    case 3:
        this->enemy.setSize(sf::Vector2f(70.f, 70.f));
        enemy.setPosition((std::rand() % (window->getSize().x - (int)enemy.getSize().x)), 0.f);
        this->enemy.setFillColor(sf::Color::Red);
        break;
    case 4:
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));
        enemy.setPosition((std::rand() % (window->getSize().x - (int)enemy.getSize().x)), 0.f);
        this->enemy.setFillColor(sf::Color::Green);
        break;
    default:
        break;
    }
    
//    if(!add) // i was testing for only one rectangular shape
//    {
//        enemy.setPosition(50.f, 0.f);
        enemies.push_back(enemy);
//        add = true;
//    }
}

void Game::pollEvents()
{
    while(window->pollEvent(ev))
    {
        switch(ev.type)
        {
        case(sf::Event::Closed):
            window->close();
            break;
        case (sf::Event::KeyPressed):
            if(ev.key.code == sf::Keyboard::Escape)
                window->close();
            break;
        default:
        break;
        }
    }
}

void Game::updateMousePositions()
{
    mousePosWindow.x = sf::Mouse::getPosition(*window).x;
    mousePosWindow.y = sf::Mouse::getPosition(*window).y;
//    std::cout << mousePosWindow.x << " " << mousePosWindow.y << std::endl;
}

void Game::updateEnemies()
{
    if(enemies.size() < (float)maxEnemies)
    {
        if(enemySpawnTimer >= enemySpawnTimerMax)
        {
            spawnEnemy();
            enemySpawnTimer = 0.f;
        }
        else
            enemySpawnTimer++;
    }
    //Moving and updating enemies
    for(size_t i{0}; i < enemies.size(); i++)
    {
        enemies[i].move(0.f, 5.f);
        if(enemies[i].getPosition().y > window->getSize().y)
        {
            enemies.erase(enemies.begin() + i);
            health--;
        }
    }
    
    //Check if clicked upon
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        //still key pressed & mouseHold true do nothing
        if(mouseHeld == false)
        {
            bool deleted = false;
            mouseHeld = true;
            for(size_t i{}; i < enemies.size() && !deleted ; i++)
            {
                if(enemies[i].getGlobalBounds().contains(mousePosWindow))
                {
                    //Gain points
                    if(this->enemies[i].getFillColor() == sf::Color::Magenta)
                        this->points += 10;
                    else if (this->enemies[i].getFillColor() == sf::Color::Blue)
                        this->points += 7;
                    else if(this->enemies[i].getFillColor() == sf::Color::Cyan)
                        this->points += 5;
                    else if (this->enemies[i].getFillColor() == sf::Color::Red)
                        this->points += 3;
                    else if (this->enemies[i].getFillColor() == sf::Color::Green)
                        this->points += 1;
                        
                    enemies.erase(enemies.begin() + i);
                    deleted = true;
                    /*
                    std::cout << "global : " 
                              << enemies[i].getGlobalBounds().width << " "
                              << enemies[i].getGlobalBounds().height 
                              << "local : "
                              << enemies[i].getLocalBounds().width << " "
                              << enemies[i].getLocalBounds().height
                              <<std::endl;
                    */
                }
            }
        }
    }
    else
    {
        //key not pressed -> make MouseHeld false 
        mouseHeld = false;
    }
}

void Game::updateText()
{
    std::stringstream ss;
    if(!endGame)
    {
        ss << "Points: " << points << "\n"
           << "Health: " << health << std::endl;
        uiText.setString(ss.str());
    }
    else
    {
        ss << "Your score is: " << points << std::endl;
        uiText.setString(ss.str());
        
        sf::Vector2f textSize; 
        textSize.x = uiText.getGlobalBounds().width;
        textSize.y = uiText.getGlobalBounds().height;
        uiText.setOrigin(textSize.x/2, textSize.y/2);
        
        uiText.setCharacterSize(50);
        uiText.setColor(sf::Color::Black);
        uiText.setPosition(window->getSize().x/2, window->getSize().y/2);
    }
}

void Game::update()
{
    pollEvents();
    /*
    to be done :
    -update enemies (done)
    -update Text 
    -update mouse pos
    */
    if(!endGame)
    {
        updateEnemies();
        updateMousePositions();
        updateText();
    }
    if(health <= 0)
        endGame = true;
//    std::cout << "health :" << health << "\n" <<"points :" << points << std::endl;
}

void Game::renderEnemies(sf::RenderTarget &target)
{
    for(auto &e : enemies)
        target.draw(e);
}

void Game::renderText(sf::RenderTarget &target)
{
    target.draw(uiText);
}

void Game::render()
{
    if(!endGame)
    {
        window->clear(sf::Color::Black);
        
        /*
        to be done :
        -render enemies (done)
        -render text 
        */
        
        renderEnemies(*window);
        renderText(*window);
        
        window->display();
    }
    else
    {
        window->clear(sf::Color::Cyan);
        updateText();
        renderText(*window);
        window->display();
    }
}
