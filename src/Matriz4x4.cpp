#include "Matriz4x4.h"
#include "Vector3.h"

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

Matriz4x4 Matriz4x4::operator*(const Matriz4x4& multiplo) const
{
    
}
