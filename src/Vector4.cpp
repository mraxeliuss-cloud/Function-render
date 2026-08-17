#include "Vector4.h"
#include "Vector3.h"

#include <array>

Vector4::Vector4(const Vector3 &vector)
{
    this->x = vector.get_x();
    this->y = vector.get_y();
    this->z = vector.get_z();
}

Vector4::Vector4(std::array<float, 4>& array)
{
    this->x = array[0];
    this->y = array[1];
    this->z = array[2];
    this->w = array[3];
}

Vector3 Vector4::toVector3() const
{
    if (w == 0.f)
    {
        return Vector3(this->x, this->y, this->z);
    }
    if (w == 1.0f)
    {
        return Vector3(this->x, this->y, this->z);
    }
    return Vector3(this->x / this->w, this->y / this->w, this->z / this->w);
}

Vector4 Vector4::operator*(float multiplo)
{
    this->x *= multiplo;
    this->y *= multiplo;
    this->z *= multiplo;
    this->w *= multiplo;
}

std::array<float, 4> Vector4::toArray() const
{
    std::array<float, 4> convertido;
    convertido[0] = this->x;
    convertido[1] = this->y;
    convertido[2] = this->z;
    convertido[3] = this->w;
    return convertido;
}

float Vector4::operator*(float multiplo) const
{
    
    float au1 = this->x * multiplo;
    float au2 = this->y * multiplo;
    float au3 = this->z * multiplo;
    float au4 = this->w * multiplo;
    return (au1 + au2 + au3 + au4);

}
