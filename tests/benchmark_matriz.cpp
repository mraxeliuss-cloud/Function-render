#include <chrono>
#include <iostream>

#include "../src/modelo/Vector3.h"
#include "../src/modelo/Matriz4x4.h"

int main()
{
    // Preparación
    Vector3 vector(1.0f, 2.0f, 3.0f);
    Matriz4x4 matriz({1.2f, 0.3f, 2.1f, 0.7f,
                      0.5f, 1.8f, 0.4f, 1.1f,
                      2.3f, 0.6f, 1.5f, 0.2f,
                      0.9f, 1.4f, 0.8f, 1.7f});
    constexpr int iteraciones = 10'000'000;

    auto inicio = std::chrono::steady_clock::now();

    for (int i = 0; i < iteraciones; ++i)
    {
        Vector3 resultado = matriz * vector;

        // Evitar que el compilador elimine el cálculo
        vector = resultado;
    }

    auto final = std::chrono::steady_clock::now();

    std::chrono::duration<double> tiempo = final - inicio;

    std::cout << "Tiempo: "
              << tiempo.count()
              << " s\n";

    std::cout << "Tiempo por operacion: "
              << (tiempo.count() / iteraciones) * 1e9
              << " ns\n";
}