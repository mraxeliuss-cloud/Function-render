#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    float x = 0;
    float y;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Render de funciones");

    // Tomamos un punto cualquiera
    sf::CircleShape punto(1.f);

    //Primitivo de los ejes
    sf::RectangleShape Eje_x(sf::Vector2f(10000, 2.0));
    sf::RectangleShape Eje_y(sf::Vector2f(2.0, 10000));

    Eje_x.setOrigin(sf::Vector2f(0,0));
    Eje_y.setOrigin(sf::Vector2f(0,0));

    // Dar color a las cosas
    punto.setFillColor(sf::Color::Green);
    Eje_x.setFillColor(sf::Color::Blue);
    Eje_y.setFillColor(sf::Color::Magenta);

    while (window.isOpen())
    {

        
        window.clear();

        //Dibujar la cuadrícula
        for(float i = 0.f; i < 800.f; i += 10.f){
            Eje_x.setPosition(sf::Vector2f(0, i));
            Eje_y.setPosition(sf::Vector2f(i, 0));
        }

        // Pintar objeto
        for (int i = 0; i < 100; i++)
        {
            x = i * 8.0;
            y = 30;
            punto.setPosition(sf::Vector2f(x, y));
            window.draw(punto);
        }
        window.draw(Eje_x);
        window.draw(Eje_y);
        // Mostrar lo pintado
        window.display();
    }
    return 0;
}