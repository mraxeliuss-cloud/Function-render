#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

#include "modelo\Vector3.h"
#include "modelo\Matriz4x4.h"
#include "modelo\Camara.h"
#include "vista\Vista.h"
#include "Utilidades.h"

/*
TBU: para pasar los puntos de controlador->modelo->controlador->vista
usar un std::vector<Vector3> con reserve() para reservar espacio y evitar reasignaciones
tiene que ser std::vector y no std::array porque el array no acepta el reserve y tiene tamaño fijo
*/

/*
Necesito un helper para el controlador, una de las cosas que debe hacer es:
Vector3 -> sf::VertexArray
Esto al final es pipeline, dentro del main 
*/

int main()
{
    // Configuración de ventana
    int ancho_Pantalla = 800;
    int alto_Pantalla = 600;
    int espacio_Entre_Casillas = 10;
    float menorValorPantalla = std::min(ancho_Pantalla, alto_Pantalla);

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
    // Vector de elementos a dibujar
    std::vector<sf::Drawable *> dibujables;
    // Just in case, no creo que haya que dibujar más de 10 funciones juntas.
    dibujables.reserve(10);

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

        // PIPELINE 2D 
        funcion2d( dibujables, menorValorPantalla, alto_Pantalla);
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
        vista.mostrar(dibujables);
    }

    return 0;
}

void funcion2d(std::vector<sf::Drawable *> dibujables, int menorValorPantalla, int alto_Pantalla){
        auto calculada = Matematicas::calcularFuncion(menorValorPantalla);
        sf::VertexArray funcion(sf::PrimitiveType::LineStrip, calculada.size());

        for (size_t i = 0; i < calculada.size(); ++i)
        {
            float enY = (alto_Pantalla / 2) - calculada[i].second;
            funcion[i].position = sf::Vector2f(calculada[i].first, enY);
            funcion[i].color = sf::Color::Green; // Asigna color (opcional)
        }
        dibujables.clear();
        dibujables.push_back(&funcion);
}