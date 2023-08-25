#include "MainMenu.h"
#include<SFML/Window/Mouse.hpp>
#include <iostream>
#include<game.h>


sf::RenderWindow window;


//win button
Button whitewins(sf::Vector2f(700, 500), "White Wins!!", []() {}, 120);
Button redwins(sf::Vector2f(700, 500), "Red Wins!!", []() {}, 120);
//back button
void onBackButtonClick() {
    std::cout << "Back button clicked!" << std::endl;
    window.clear();
    MainMenu mainmenu;
}
Button BackButton(sf::Vector2f(860, 900), "->Back", onBackButtonClick, 70);

sf::Vector2i get_mouse_position();
// Define lambda functions
void onPlayButtonClick() {
    Game game(&window);
    window.setFramerateLimit(10);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            sf::Vector2i row_col = sf::Vector2i(0, 1);

            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {

                row_col = get_mouse_position();
                game.select(row_col.x, row_col.y);

            }
            if (!game.isRunning()) {
                int win = game.board->winner();
                if (win == 1) {
                    std::cout << "white wins";
                    whitewins.draw(window);
                    BackButton.draw(window);
                    window.display();
                    BackButton.handleEvent(event, window);
                }
                else if (win == -1) {
                    std::cout << "red wins";
                    redwins.draw(window);
                    BackButton.draw(window);
                    window.display();
                    BackButton.handleEvent(event, window);    
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {

                game.update();
            }
        }
    }
}


void onExitButtonClick() {
    std::cout << "Exit button clicked!" << std::endl;
    exit(1);
}

MainMenu::MainMenu(){
    // Load textures and font
    window.create(sf::VideoMode(1920, 1080), "Checkers Game", sf::Style::Titlebar | sf::Style::Close);
    sf::Texture menuBgTexture;
    if (!menuBgTexture.loadFromFile("resources/menu2.jpg")) {
        std::cerr << "Error loading textures." << std::endl;
        return;
    }

    // Set up the main menu background
    sf::Sprite menuBgSprite(menuBgTexture);
    menuBgSprite.setScale((float)window.getSize().x / menuBgTexture.getSize().x, (float)window.getSize().y / menuBgTexture.getSize().y);

    size_t buttonSize= 100;

    // Create "Play" and "Exit" buttons
    Button playButton(sf::Vector2f(900, 400), "Play", onPlayButtonClick, buttonSize);
    Button exitButton(sf::Vector2f(900, 550), "Exit", onExitButtonClick, buttonSize);

    // Create the title button
    Button titleButton(sf::Vector2f(700, 100), "CHECKERS", []() {}, 120);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Pass events to the buttons
            playButton.handleEvent(event, window);
            exitButton.handleEvent(event, window);
            titleButton.handleEvent(event, window);
        }

        window.clear();

        // Draw the main menu background
        window.draw(menuBgSprite);

        // Draw buttons
        titleButton.draw(window);
        playButton.draw(window);
        exitButton.draw(window);

        window.display();
    }
}

sf::Vector2i get_mouse_position() {



    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        int i = 1;
        while (i)
        {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            if (pixelPos.x < 1417 and pixelPos.x > 512 && pixelPos.y > 88 and pixelPos.y < 976) {
                int row = (pixelPos.y - 88) / (900 / 8);
                int col = (pixelPos.x - 512) / (900 / 8);

                sf::Vector2i row_col;
                row_col = sf::Vector2i(row, col);

                i = 0;

                return row_col;

            }
            else
            {
                continue;
            }
        }

    }
}