#ifndef VECTOR3_H
#define VECTOR3_H

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
    float get_x(){ return this->x; }
    float get_y(){ return this->y; }
    float get_z(){ return this->z; }

    //Modulo 
    //Calcula el módulo "Tamaño" del vector
    float const magnitud();

    //Normalizar
    //Divide cada miembro por el módulo

    //Este devuelve un modificado
    void normalizado();
    //Este devuelve una copia con la operación hecha, mantiene ambos
    Vector3 const normalizar();

    //Operaciones básicas con escalares
    Vector3 operator*(float multiplicando) const;
    Vector3 operator/(float divisor) const; 


    //Operaciones básicas con vectores
    //Todos devuelven objetos nuevos
    Vector3 operator+(const Vector3& sumando) const;
    Vector3 operator-(const Vector3& minuendo) const;

    //Multiplica de forma vectorial
    Vector3 productoVectorial(Vector3 multiplicando);
    //Da el producto escalar de dos vectores
    float productoEscalar (Vector3 multiplicando);

    //Operadores de acumulación
    void operator*=(float multiplo);
    void operator/=(float divisor);
    void operator+=(const Vector3 sumando);
    void operator-=(const Vector3 minuendo);

};

#endif