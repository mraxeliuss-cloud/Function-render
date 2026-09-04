#pragma once

#include <cmath>
#include <vector>
#include <utility>

namespace Matematicas
{
    // El inline resuelve el problema del linker, si no se pone, el código se duplica y el linker da error
    // En clases, structs y templates las funciones son implicitamente inline
    inline bool floatIguales(float i, float j)
    {
        return (std::abs(i - j) < 1e-6f);
    }

    inline std::vector<std::pair<float, float>> calcularFuncion(int limite)
    {
        std::vector<std::pair<float, float>> funcion;
        funcion.resize(100);
        float x = 0;
        float y;

        // / 10 para no hacer una burrada de puntos, pero hacer una curva suave
        for(int i = 0; i < limite / 10; i++)
        {
            x = i * 10;
            y = i * (-i);
            funcion[i] = {x, y};
        }
    return funcion;
    }
}