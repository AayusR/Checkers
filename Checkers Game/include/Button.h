// Button.h
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Button {
public:
    typedef void (*ClickAction)();

    Button(const sf::Vector2f& position, const std::string& label, ClickAction onClick,size_t size);
    ~Button();

    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    sf::Text text;
    sf::Font font; // Font member to ensure proper management
    ClickAction onClickAction;
    size_t textsize;
};