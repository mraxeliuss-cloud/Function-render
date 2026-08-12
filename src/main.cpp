#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    float x = 0;
    float y;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Render de funciones");

    // LineStrip usa cada vértice como inicio del siguiente
    // Lo que permite representaciones continuas, no solo discretas
    sf::VertexArray funcion(sf::PrimitiveType::LineStrip, 100);

    //Primitivo de los ejes
    sf::RectangleShape Eje_x(sf::Vector2f(10000.f, 2.f));
    sf::RectangleShape Eje_y(sf::Vector2f(2.f, 10000.f));

    // Dar color a los ejes
    Eje_x.setFillColor(sf::Color::Blue);
    Eje_y.setFillColor(sf::Color::Magenta);

    while (window.isOpen())
    {

        window.clear();

        //Dibujar la cuadrícula
        for(float i = 0.f; i < 800.f; i += 10.f){
            //Espaciamos los ejes 10 px, para poder hacer un análisis de los resultados
            Eje_x.setPosition(sf::Vector2f(0, i));
            Eje_y.setPosition(sf::Vector2f(i, 0));

            window.draw(Eje_x);
            window.draw(Eje_y);
        }

        // Pintar funcion
        for (float i = 0; i < 800.f; i++)
        {
            x = i;
            // Función
            y = (x * x)  ;

            // Dar a cada eje su posición
            // 300 - y hace que la función inicie en mitad de la pantalla
            float posicion = 0;
            funcion[i].position = sf::Vector2f(posicion , 300 - y);
            funcion[i].color = sf::Color::Green;
            window.draw(funcion);
            posicion+= 10;
        }

        // Mostrar lo pintado
        window.display();
    }
    return 0;
}