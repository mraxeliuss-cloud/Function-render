#pragma once

#include <SFML/Graphics.hpp>

#include "Vista.h"

class Funcion2d{

    private:
 
    float limiteI;
    float limiteS;
    bool hayLimite;
    sf::VertexArray& funcion;

    public:
    Funcion2d(float limiteI, float limiteS, bool hayLimite, sf::VertexArray& funcion);
    void dibujar2D();
    void dibujarEjes();
    void dibujarCuadrante();
};