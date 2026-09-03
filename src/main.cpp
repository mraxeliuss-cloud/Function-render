#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <vector>

#include "modelo\Vector3.h"
#include "modelo\Matriz4x4.h"
#include "modelo\Camara.h"
#include "vista\Vista.h"

/*
TBU: para pasar los puntos de controlador->modelo->controlador->vista
usar un std::vector<Vector3> con reserve() para reservar espacio y evitar reasignaciones
tiene que ser std::vector y no std::array porque el array no acepta el reserve y tiene tamaño fijo
*/

/*
Necesito un helper para el controlador, una de las cosas que debe hacer es:
Vector3 -> sf::VertexArray
*/

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
        // Cada vector2f es una posición de VertexArray
        funcion[i].position = sf::Vector2f(x, (alto_Pantalla / 2) - y);
        funcion[i].color = sf::Color::Green;
    }
    return funcion;
}

int main()
{
    // Configuración de ventana
    int ancho_Pantalla = 800;
    int alto_Pantalla = 600;
    int espacio_Entre_Casillas = 10;
    float mayor_Valor_Pantalla = std::max(ancho_Pantalla, alto_Pantalla);

    sf::RenderWindow window(sf::VideoMode(ancho_Pantalla, alto_Pantalla), "Render de funciones");

    Vista vista(ancho_Pantalla, alto_Pantalla, window);

    window.setFramerateLimit(60);

    sf::Event evento;
    sf::Clock reloj;

    // --- INICIALIZACIÓN CORRECTA DE LA CÁMARA ---
    Camara camara;
    camara.anguloH = 0.0f;
    camara.anguloV = 0.2f;
    camara.distancia = 5.0f;
    camara.target = {0.0f, 0.0f, 0.0f};
    camara.up = {0.0f, 1.0f, 0.0f};
    camara.velocidadMovimiento = 2.0f;
    camara.updateEye(); // Calcula eye inicial

    // Datos del cubo
    std::vector<Vector3> cubo = {
        {-1.0f, -1.0f, -1.0f},
        {1.0f, -1.0f, -1.0f},
        {1.0f, 1.0f, -1.0f},
        {-1.0f, 1.0f, -1.0f},
        {-1.0f, -1.0f, 1.0f},
        {1.0f, -1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {-1.0f, 1.0f, 1.0f}};

    std::vector<std::pair<int, int>> aristas = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 5}, {5, 6}, {6, 7}, {7, 4}, {0, 4}, {1, 5}, {2, 6}, {3, 7}};

    static int modoEjes = 0;

    while (window.isOpen())
    {
        // 1. Procesar eventos
        while (window.pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
                window.close();

            if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::M)
                vista.invertirModo3d();
            if (!vista.getModo3d() && evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::E)
            {
                vista.cambioEjes();
            }
        }

        // 2. Delta time
        float dt = reloj.restart().asSeconds();
        camara.update(dt);

        // Modo 2D
        auto funcion = Pintar_Funcion(alto_Pantalla, mayor_Valor_Pantalla, espacio_Entre_Casillas);
        vista.mostrar(funcion);
        /*
            // 4. Matriz de vista
            Matriz4x4 vista = Matriz4x4::lookAt(camara);

            // 5. Rotación del cubo
            static float angulo = 0.0f;
            angulo += 1.0f * dt;
            Matriz4x4 rotacion = Matriz4x4::rotacion_y(angulo);

            // 6. Transformar y proyectar
            std::vector<sf::Vector2f> puntosProyectados;
            puntosProyectados.reserve(cubo.size());

            for (const auto& vertice : cubo)
            {
                Vector3 puntoMundo = rotacion * vertice;
                Vector3 puntoCamara = vista * puntoMundo;

                float x_pantalla = puntoCamara.get_x() * 100.0f + 400.0f;
                float y_pantalla = puntoCamara.get_y() * 100.0f + 300.0f;
                puntosProyectados.push_back(sf::Vector2f(x_pantalla, y_pantalla));
            }

            // 7. Dibujar aristas
            sf::VertexArray lineas(sf::Lines, aristas.size() * 2);
            for (size_t i = 0; i < aristas.size(); ++i)
            {
                int i1 = aristas[i].first;
                int i2 = aristas[i].second;
                lineas[2*i].position = puntosProyectados[i1];
                lineas[2*i+1].position = puntosProyectados[i2];
                lineas[2*i].color = sf::Color::White;
                lineas[2*i+1].color = sf::Color::White;
            }

            window.clear();
            window.draw(lineas);
            window.display();
        */
    }

    return 0;
}