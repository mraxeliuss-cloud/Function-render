#pragma once

#include <cmath>

namespace Matematicas{
    // El inline resuelve el problema del linker, si no se pone, el código se duplica y el linker da error
    // En clases, structs y templates las funciones son implicitamente inline 
    inline bool floatIguales(float i, float j){
        return(std::abs(i - j) < 1e-6f);
    }
}