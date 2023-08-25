#include "button.h"
Button::Button( const sf::Vector2f& position, const std::string& label, ClickAction onClick, size_t size)
    : onClickAction(onClick) {
    textsize = size;
    text.setPosition(position);
    // Load the font
    if (font.loadFromFile("resources/EBGaramond-Regular.ttf")) {
        // Set the font if loaded successfully
        text.setString(label);
        text.setFont(font);
        text.setCharacterSize(size);
        text.setOutlineThickness(5.0f);
        text.setOutlineColor(sf::Color::White);
        text.setFillColor(sf::Color(43,23,0));
        text.Bold;
        // Calculate the text bounds
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(position);
    }
    else {
        // Font not loaded, display a default label
        std::cerr << "Font not loaded." << std::endl;
        text.setString("Button");

        // Set default character size and position
        text.setCharacterSize(24);
        text.setPosition(position);
    }
}

void Button::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (text.getGlobalBounds().contains(mousePosition)) {
            onClickAction();
        }
    }
    if (event.type == sf::Event::MouseMoved)
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
        if (text.getGlobalBounds().contains(mousePos))
        {
            text.setCharacterSize(textsize+5);
            text.setFillColor(sf::Color(161,102,47));
        }
        else
        {
       
            text.setCharacterSize(textsize);
            text.setFillColor(sf::Color(43,23,0));
        }
    }
}
void Button::draw(sf::RenderWindow& window) {
    window.draw(text);
}
Button::~Button() {
    // Destructor;
}