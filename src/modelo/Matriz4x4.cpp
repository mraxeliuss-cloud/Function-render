#include "Matriz4x4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Utilidades.h"

#include <cmath>
#include <array>
#include <stdexcept>
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
    if (valores.size() != 16)
    {
        throw std::invalid_argument("La lista de elementos debe tener 16 elementos");
    }
    int fila = 0;
    int columna = -1;
    if (valores.size() == 16)
    {
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

    float r0 = matriz[0][0] * multiplo.get_x() + matriz[0][1] * multiplo.get_y() +
               matriz[0][2] * multiplo.get_z() + matriz[0][3];
    float r1 = matriz[1][0] * multiplo.get_x() + matriz[1][1] * multiplo.get_y() +
               matriz[1][2] * multiplo.get_z() + matriz[1][3];
    float r2 = matriz[2][0] * multiplo.get_x() + matriz[2][1] * multiplo.get_y() +
               matriz[2][2] * multiplo.get_z() + matriz[2][3];
    float r3 = matriz[3][0] * multiplo.get_x() + matriz[3][1] * multiplo.get_y() +
               matriz[3][2] * multiplo.get_z() + matriz[3][3];

    if (Matematicas::floatIguales(r3, 0) || Matematicas::floatIguales(r3, 1))
    {
        return Vector3(r0, r1, r2);
    }
    else
    {

        Vector4 final(r0, r1, r2, r3);
        return final.toVector3();
    }
}

Matriz4x4 Matriz4x4::traslacion(float tx, float ty, float tz)
{

    Matriz4x4 resultado;

    // Sustitucon en el Row-Major
    resultado.matriz[0][3] = tx;
    resultado.matriz[1][3] = ty;
    resultado.matriz[2][3] = tz;
    return resultado;
}

Matriz4x4 Matriz4x4::escalado(float sx, float sy, float sz)
{

    Matriz4x4 resultado;

    // Sustitución de la DP por los valores de escalado
    resultado.matriz[0][0] = sx;
    resultado.matriz[1][1] = sy;
    resultado.matriz[2][2] = sz;
    return resultado;
}

Matriz4x4 Matriz4x4::rotacion_x(float angulo)
{

    Matriz4x4 resultado;

    // Rotación sobre el eje horizontal
    resultado.matriz[1][1] = cos(angulo);
    resultado.matriz[1][2] = -(sin(angulo));
    resultado.matriz[2][1] = sin(angulo);
    resultado.matriz[2][2] = cos(angulo);
    return resultado;
}

Matriz4x4 Matriz4x4::rotacion_y(float angulo)
{

    Matriz4x4 resultado;

    // Rotación sobre el eje vertical
    resultado.matriz[0][0] = cos(angulo);
    resultado.matriz[0][2] = -(sin(angulo));
    resultado.matriz[2][0] = sin(angulo);
    resultado.matriz[2][2] = cos(angulo);
    return resultado;
}

Matriz4x4 Matriz4x4::rotacion_z(float angulo)
{

    Matriz4x4 resultado;

    // Rotación sobre el eje de profundidad
    resultado.matriz[0][0] = cos(angulo);
    resultado.matriz[0][1] = -(sin(angulo));
    resultado.matriz[1][0] = sin(angulo);
    resultado.matriz[1][1] = cos(angulo);
    return resultado;
}

Matriz4x4 Matriz4x4::lookAt(const Camara &camara)
{

    // Esto es muy caro, hay que revisar si es necesario reconstruir la base o hay floritura
    Vector3 delante = (camara.target - camara.eye).normalizar();
    Vector3 derecha = delante.productoVectorial(camara.up).normalizar();
    Vector3 arriba = derecha.productoVectorial(delante).normalizar();

    Matriz4x4 resultado;

    resultado.matriz[0][0] = derecha.get_x();
    resultado.matriz[0][1] = derecha.get_y();
    resultado.matriz[0][2] = derecha.get_z();
    resultado.matriz[0][3] = -(camara.eye.productoEscalar(derecha));
    resultado.matriz[1][0] = arriba.get_x();
    resultado.matriz[1][1] = arriba.get_y();
    resultado.matriz[1][2] = arriba.get_z();
    resultado.matriz[1][3] = -(camara.eye.productoEscalar(arriba));
    resultado.matriz[2][0] = -delante.get_x();
    resultado.matriz[2][1] = -delante.get_y();
    resultado.matriz[2][2] = -delante.get_z();
    resultado.matriz[2][3] = -(camara.eye.productoEscalar(delante));
    resultado.matriz[3][0] = 0;
    resultado.matriz[3][1] = 0;
    resultado.matriz[3][2] = 0;
    resultado.matriz[3][3] = 1;

    return resultado;
}

float Matriz4x4::getElemento(int fila, int columna) const
{
    return this->matriz[fila][columna];
}