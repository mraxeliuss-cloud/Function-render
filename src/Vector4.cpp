#include "Vector4.h"
#include "Vector3.h"

Vector4::Vector4(const Vector3& vector)
{
    this->x = vector.get_x();
    this->y = vector.get_y();
    this->z = vector.get_z();

}

Vector3 Vector4::toVector3() const
{
    if(w == 0.f){
        return Vector3(this->x, this->y, this->z);       
    }
    if(w == 1.0f){
        return Vector3(this->x, this->y, this->z);
    }
    return Vector3(this->x / this->w, this->y / this->w, this->z / this->w );

}