#include "Vector3.h"
#include <math.h>

//Obtenemos el módulo
float const Vector3::magnitud()
{
    return (sqrt((x * x) + (y * y) + (z * z)));
}

//Dividimos todo por el módulo
void Vector3::normalizado()
{

    float modulo = this->magnitud();
    this->set_x(x / modulo);
    this->set_y(y / modulo);
    this->set_z(z / modulo);

}

//Dividimos por el módulo, creamos otro vector
Vector3 const Vector3::normalizar()
{

    float modulo = this->magnitud();
    float au1 = this->x / modulo;
    float au2 = this->y / modulo;
    float au3 = this->z / modulo;
    return Vector3(au1, au2, au3);

}

//Multiplicamos todo el vector por el escalar
void Vector3::multiplicacion(float multiplicando)
{

    set_x(x * multiplicando);
    set_y(y * multiplicando);
    set_z(z * multiplicando);

}

//Dividimos todo el vector por el escalar
void Vector3::division(float dividendo)
{

    set_x(x / dividendo);
    set_y(y / dividendo);
    set_z(z / dividendo);

}


Vector3 Vector3::operator+(const Vector3& sumando) const
{

    float x_1 = this->x + sumando.x;
    float y_1 = this->y + sumando.y;
    float z_1 = this->z + sumando.z;
    return Vector3(x_1, y_1, z_1);

}

Vector3 Vector3::operator-(const Vector3& sustraendo) const
{
    
    float x_1 = this->x - sustraendo.x;
    float y_1 = this->y - sustraendo.y;
    float z_1 = this->z - sustraendo.z;
    return Vector3(x_1, y_1, z_1);

}

Vector3 Vector3::productoVectorial(Vector3 multiplicando)
{

    // Por claridad, no hacemos el proceso completo, sino que directamente pasamos a la formula

    float au1 = (this->y * multiplicando.z) - (this->z * multiplicando.y);
    float au2 = (this->z * multiplicando.x) - (this->x * multiplicando.z);
    float au3 = (this->x * multiplicando.y) - (this->y * multiplicando.x);
    return Vector3(au1, au2, au3);

}

float Vector3::productoEscalar(Vector3 multiplicando)
{

    float au1 = this->x * multiplicando.x;
    float au2 = this->y * multiplicando.y;
    float au3 = this->z * multiplicando.z;
    return (au1 + au2 + au3);

}