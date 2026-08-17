#include "Matriz4x4.h"
#include "Vector3.h"
#include "Vector4.h"

#include <array>
#include <initializer_list>

Matriz4x4::Matriz4x4()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i == j)
            {
                matriz[i][j] = 1.f;
            }
            else
                matriz[i][j] = 0.f;
        }
    }
}

Matriz4x4::Matriz4x4(std::initializer_list<float> valores)
{
    if (valores.size() == 16)
    {

        int fila = 0;
        int columna = -1;
        for (float i : valores)
        {
            columna++;
            matriz[fila][columna] = i;
            if (columna == 3)
            {
                columna = 0;
                fila++;
            }
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (i == j)
                {
                    matriz[i][j] = 1.f;
                }
                else
                    matriz[i][j] = 0.f;
            }
        }
    }
}

Matriz4x4::Matriz4x4(const std::array<float, 16> &valores)
{
    int contador = 0;
    for (int fila = 0; fila < 4; fila++)
    {
        for (int columna = 0; columna < 4; columna++)
        {
            matriz[fila][columna] = valores[contador];
            contador++;
        }
    }
}

Matriz4x4 Matriz4x4::operator*(const Matriz4x4 &multiplo) const
{
    std::array<float, 16> resultado;
    float au = 0;
    int contador = 0;

    for (int fila = 0; fila < 4; fila++)
    {
        for (int columna_a = 0; columna_a < 4; columna_a++)
        {
            for (int comun = 0; comun < 4; comun++)
            {
                au += this->matriz[fila][comun] * multiplo.matriz[comun][columna_a];
            }
            resultado[contador] = au;
            au = 0;
            contador++;
        }
    }
    return Matriz4x4(resultado);
}

Vector3 Matriz4x4::operator*(const Vector3 &multiplo) const
{

    Vector4 original = multiplo.homogeneizar();
    std::array<float,4> aMultiplicar = original.toArray();


    std::array<float, 4> resultado = {0,0,0,0};


    for(int i = 0; i < 4; i++){
        float au = 0;
        for(int j = 0; j < 4; j++){
            au += this->matriz[i][j] * aMultiplicar[j];
        }
        resultado[i] = au;
    }

    Vector4 final(resultado);
    return final.toVector3();
}