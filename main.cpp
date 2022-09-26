#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include <iostream>

// global constants
int BrushRadius = 32;
sf::Color BrushColor = sf::Color::White;
bool Outline = false;
int OutlineThick = 0;
sf::Color OutlineColor = sf::Color::Black;

int main()
{
    // creates the window pop-up
    sf::RenderWindow window(sf::VideoMode(800, 600), "Gummy Worms!");
    
    // sets the brush shape and color initially
    sf::CircleShape shape(BrushRadius);
    shape.setFillColor(BrushColor);
    
    // the program loop
    while (window.isOpen())
    {
        // checks for events that occur
        sf::Event event;
        while (window.pollEvent(event))
        {
            // window close event
            if (event.type == sf::Event::Closed)
                window.close();

            // change brush points event
            if (event.key.code == sf::Keyboard::Left && BrushRadius > 0)
                BrushRadius -= 4; 
            if (event.key.code == sf::Keyboard::Right && BrushRadius < 128)
                BrushRadius += 4;
            shape.setRadius(BrushRadius);

            // change brush color event
            if (event.key.code == sf::Keyboard::Space) {
                BrushColor = sf::Color(rand() % 255, rand() % 255, rand() % 255);
                OutlineColor = sf::Color(rand() % 255, rand() % 255, rand() % 255);
            }
            shape.setFillColor(BrushColor);
            shape.setOutlineColor(OutlineColor);

            // add/remove outline event
            if (event.key.code == sf::Keyboard::O)
                Outline = true;
            if (event.key.code == sf::Keyboard::P)
                Outline = false;
            if (Outline)
                OutlineThick = BrushRadius / 4;
            else
                OutlineThick = 0;
            shape.setOutlineThickness(OutlineThick);

            // screenshot event
            if (event.key.code == sf::Keyboard::Enter) {
                sf::Texture texture;
                texture.create(window.getSize().x, window.getSize().y);
                texture.update(window);
                if (texture.copyToImage().saveToFile("PaintingScreenshot.png"))
                    std::cout << "Screenshot saved. Previous screenshot overwritten." << std::endl;
            }
        }

        // sets the position of the brush to the user's mouse
        shape.setPosition(sf::Mouse::getPosition(window).x - BrushRadius,
                          sf::Mouse::getPosition(window).y - BrushRadius);
       
        // draws with the brush
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) window.draw(shape);
        window.display();
    }
    return 0;
}