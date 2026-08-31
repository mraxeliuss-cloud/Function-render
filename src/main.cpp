#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <vector>

#include "Vector3.h"
#include "Matriz4x4.h"
#include "Camara.h"

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
    for (size_t i = 0.f; i < mayor_Valor_Pantalla; i += espacio_Entre_Casillas)
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
    sf::VertexArray funcion(sf::PrimitiveType::LineStrip, mayor_Valor_Pantalla / 10);

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

    // Crear la cámara
    Camara camara;
    camara.eye = {3.0f, 2.0f, 4.0f};
    camara.target = {0.0f, 0.0f, 0.0f};
    camara.up = {0.0f, 1.0f, 0.0f};

    // Temporales para probar las representaciones
    std::vector<Vector3> cubo = {
        {-1.0f, -1.0f, -1.0f}, // 0
        {1.0f, -1.0f, -1.0f},  // 1
        {1.0f, 1.0f, -1.0f},   // 2
        {-1.0f, 1.0f, -1.0f},  // 3
        {-1.0f, -1.0f, 1.0f},  // 4
        {1.0f, -1.0f, 1.0f},   // 5
        {1.0f, 1.0f, 1.0f},    // 6
        {-1.0f, 1.0f, 1.0f}    // 7
    };

    std::vector<std::pair<int, int>> aristas = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // cara frontal (z = -1)
        {4, 5},
        {5, 6},
        {6, 7},
        {7, 4}, // cara trasera (z = 1)
        {0, 4},
        {1, 5},
        {2, 6},
        {3, 7} // unión entre caras
    };
    // Display mode
    static bool Modo3D = false;

    while (window.isOpen())
    {
        while (window.pollEvent(evento))
        {
            // Close window: exit
            if (evento.type == sf::Event::Closed)
                window.close();
            if (evento.type == sf::Event::KeyPressed)
            {
                if (evento.key.code == sf::Keyboard::M)
                {
                    Modo3D = !Modo3D;
                }
            }
        }

        float y_pantalla;

        if (!Modo3D)
        {
            // Modo 2D
            window.clear();
            auto funcion = Pintar_Funcion(alto_Pantalla, mayor_Valor_Pantalla, espacio_Entre_Casillas);
            Pintar_Cuadricula(mayor_Valor_Pantalla, espacio_Entre_Casillas, window);
            window.draw(funcion);

            window.display();
        }
        else
        {
            // 1. Matriz de vista (cámara)
            Matriz4x4 vista = Matriz4x4::lookAt(camara);

            // 2. Rotación del cubo
            static float angulo = 1.0f;
            angulo += 0.1f;
            Matriz4x4 rotacion = Matriz4x4::rotacion_y(angulo);
            std::cout << angulo << std::endl;
            // 3. Transformar y proyectar cada vértice
            std::vector<sf::Vector2f> puntosProyectados;
            puntosProyectados.reserve(cubo.size());

            for (const auto &vertice : cubo)
            {
                // Modelo: rotación
                Vector3 puntoMundo = rotacion * vertice;

                // Vista: pasar a espacio de cámara
                Vector3 puntoCamara = vista * puntoMundo;

                // Proyección ortográfica (escala y centra)
                float x_pantalla = puntoCamara.get_x() * 100.0f + 400.0f;
                float y_pantalla = puntoCamara.get_y() * 100.0f + 300.0f;

                puntosProyectados.push_back(sf::Vector2f(x_pantalla, y_pantalla));
            }

            // 4. Dibujar aristas
            sf::VertexArray lineas(sf::Lines, aristas.size() * 2);
            for (size_t i = 0; i < aristas.size(); ++i)
            {
                int i1 = aristas[i].first;
                int i2 = aristas[i].second;
                lineas[2 * i].position = puntosProyectados[i1];
                lineas[2 * i + 1].position = puntosProyectados[i2];
                lineas[2 * i].color = sf::Color::White;
                lineas[2 * i + 1].color = sf::Color::White;
            }

            // 5. Dibujar en pantalla
            window.clear();
            window.draw(lineas);
            window.display();
        }
    }
    return 0;
}