#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <vector>

#include "Vector3.h"
#include "Matriz4x4.h"

// Pinta la cuadrícula
void Pintar_Cuadricula(int mayor_Valor_Pantalla, int espacio_Entre_Casillas, sf::RenderWindow &window)
{

    // Ejes
    static sf::RectangleShape Eje_x(sf::Vector2f(10000.f, 1.f));
    static sf::RectangleShape Eje_y(sf::Vector2f(1.f, 10000.f));

    // Color
    Eje_x.setFillColor(sf::Color::Blue);
    Eje_y.setFillColor(sf::Color::Magenta);

    // Dibujar la cuadrícula
    for (float i = 0.f; i < mayor_Valor_Pantalla; i += espacio_Entre_Casillas)
    {
        // Espaciamos los ejes 10 px, para poder hacer un análisis de los resultados
        Eje_x.setPosition(sf::Vector2f(0, i));
        Eje_y.setPosition(sf::Vector2f(i, 0));

        window.draw(Eje_x);
        window.draw(Eje_y);
    }
}

sf::VertexArray Pintar_Funcion(int alto_Pantalla, int mayor_Valor_Pantalla, int espacio_Entre_Casillas)
{
    // Declaracion de la funcion
    // LineStrip usa cada vértice como inicio del siguiente
    // Lo que permite representaciones continuas, no solo discretas

    static sf::VertexArray funcion(sf::PrimitiveType::LineStrip, mayor_Valor_Pantalla / 10);

    float x = 0;
    float y;

    // Pintar funcion
    for (float i = 0; i < mayor_Valor_Pantalla / 10; i++)
    {

        x = i * 10;
        // Función
        y = i * (-i);

        // alto_Pantalla / 2 ubica el inicio de la función en el centro de la pantalla
        funcion[i].position = sf::Vector2f(x, (alto_Pantalla / 2) - y);
        funcion[i].color = sf::Color::Green;

        // Movemos el paso para que cada punto sea un '1'
        x += espacio_Entre_Casillas;
    }
    return funcion;
}

int main()
{

    // Introducir eventualmente el videomod, pero revisar como ubicar el centro de la pantalla
    int ancho_Pantalla = 800;
    int alto_Pantalla = 600;

    // Espacio entre casillas
    int espacio_Entre_Casillas = 10;

    // Variable de representacion, la usamos como valor máximo
    // Si bien podríamos asimismo, usar el elemento menor de ambos, de momento prefiero usar el mayor
    float mayor_Valor_Pantalla = std::max(ancho_Pantalla, alto_Pantalla);

    // Variables matemáticas
    float x = 0;
    float y;

    // Evento
    sf::Event evento;

    // Crear la ventana del programa
    sf::RenderWindow window(sf::VideoMode(ancho_Pantalla, alto_Pantalla), "Render de funciones");

    // Temporales para probar las representaciones
    Vector3 punto(1.0f, 0.0f, 0.0f);

    while (window.isOpen())
    {
        static float angulo = 0.0f;
        angulo += 0.01f;
        Matriz4x4 rotacion = Matriz4x4::rotacion_y(angulo);
        Vector3 puntoRotado = rotacion.operator*(punto);
        float x_pantalla = puntoRotado.get_x() * 100.0f + 400.0f;
        float y_pantalla = puntoRotado.get_y() * 100.0f + 300.0f;
        // Process events
        while (window.pollEvent(evento))
        {
            // Close window: exit
            if (evento.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        sf::CircleShape drawPoint(5.0f);
        drawPoint.setFillColor(sf::Color::Red);
        drawPoint.setPosition(x_pantalla, y_pantalla);
        window.draw(drawPoint);

        auto funcion = Pintar_Funcion(alto_Pantalla, mayor_Valor_Pantalla, espacio_Entre_Casillas);
        // Pintar_Cuadricula(mayor_Valor_Pantalla, espacio_Entre_Casillas, window);
        window.draw(funcion);

        // Mostrar lo pintado
        window.display();
    }
    return 0;
}