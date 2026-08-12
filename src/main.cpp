#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    float x = 0;
    float y;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Render de funciones");

    // Crear los puntos para la representación discreta
    sf::CircleShape punto(1.f);

    //Primitivo de los ejes
    sf::RectangleShape Eje_x(sf::Vector2f(10000, 2.0));
    sf::RectangleShape Eje_y(sf::Vector2f(2.0, 10000));

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

            window.draw(Eje_x);
            window.draw(Eje_y);
        }

        // Pintar punto (Breve representación de la función)
        for (float i = 0; i < 100.f; i++)
        {
            x = i * 8.0;
            y = i * i;
            punto.setPosition(sf::Vector2f(x, 300 - y));
            window.draw(punto);
        }

        // Mostrar lo pintado
        window.display();
    }
    return 0;
}