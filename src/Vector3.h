#ifndef VECTOR3_H
#define VECTOR3_H

class Vector4;

class Vector3
{
    private:

    float x;
    float y; 
    float z;

    public: 
    //Constructor
    Vector3(float x, float y, float z);
    
    //Setters
    void set_x(float cambio){x = cambio;}
    void set_y(float cambio){y = cambio;}
    void set_z(float cambio){z = cambio;}
    //Getters
    float get_x() const { return this->x; }
    float get_y() const { return this->y; }
    float get_z() const { return this->z; }

    //Modulo 
    //Calcula el módulo "Tamaño" del vector
    float magnitud() const;

    //Normalizar
    //Divide cada miembro por el módulo

    //Este devuelve un modificado
    void normalizado();
    //Este devuelve una copia con la operación hecha, mantiene ambos
    Vector3 normalizar()const;

    //Operaciones básicas con escalares
    Vector3 operator*(float multiplicando) const;
    Vector3 operator/(float divisor) const; 


    //Operaciones básicas con vectores
    //Todos devuelven objetos nuevos
    Vector3 operator+(const Vector3& sumando) const;
    Vector3 operator-(const Vector3& minuendo) const;

    //Multiplica de forma vectorial
    Vector3 productoVectorial(const Vector3& multiplicando)const;
    //Da el producto escalar de dos vectores
    float productoEscalar (const Vector3& multiplicando)const;

    //Operadores de acumulación
    void operator*=(float multiplo);
    void operator/=(float divisor);
    void operator+=(const Vector3 sumando);
    void operator-=(const Vector3 minuendo);

    //Para la multiplicación con matrices
    Vector4 homogeneizar() const;
};

#endif