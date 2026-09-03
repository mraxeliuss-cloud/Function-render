#pragma once

#include <SFML/Graphics.hpp>

#include "Funciones2d.h"

class Vista
{
    private:
    int ResolucionH;
    int ResolucionV;
    // Ventana pasa como referencia
    // No es valor, porque no es copiable, no es puntero por seguridad, evita nullptr
    sf::RenderWindow& ventana;

    public:
    Vista(int ResolucionH, int ResolucionV, sf::RenderWindow& ventana);
    void dibujar2D(Funcion2d& funcion);
    void dibujar3D();
};