#include "Camara.h"

#include <cmath>
#include <SFML/Graphics.hpp>

void Camara::update(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        anguloV += dt * velocidadMovimiento;
        if (anguloV >= 1.57f)
        {
            anguloV = 1.57f;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        anguloV -= dt * velocidadMovimiento;
        if (anguloV <= -1.57f)
        {
            anguloV = -1.57f;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        anguloH += dt * velocidadMovimiento;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        anguloH -= dt * velocidadMovimiento;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
    {
        distancia += dt * velocidadMovimiento;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma))
    {
        if (distancia > 0.5f)
        {
            distancia -= dt * velocidadMovimiento;
        }
    }
    updateEye();
}

void Camara::updateEye()
{
    // Por coordenadas esféricas
    this->eye.set_x(distancia * cos(anguloV) * cos(anguloH));
    this->eye.set_y(distancia * sin(anguloV));
    this->eye.set_z(distancia * cos(anguloV) * sin(anguloH));
}
