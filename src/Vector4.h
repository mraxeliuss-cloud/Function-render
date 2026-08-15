#ifndef VECTOR4_H
#define VECTOR4_H

class Vector3;

class Vector4
{

    private:

    float x;
    float y; 
    float z;
    float w = 1.f;

    public:

    explicit Vector4(const Vector3& original);
    Vector3 toVector3() const;


};

#endif
