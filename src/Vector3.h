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

    
    //Operaciones internas
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
    //Multiplica por un escalar
    Vector3 operator*(float multiplicando) const;
    //Divide el vector por un escalar, y devuelve uno nuevo
    Vector3 operator/(float divisor) const; 


    //Operaciones básicas con vectores
    //Todos devuelven objetos nuevos
    //Suma dos vectores, elemento a elemento
    Vector3 operator+(const Vector3& sumando) const;
    //Resta dos vectores elemento a elemento
    Vector3 operator-(const Vector3& sustraendo) const;
    //Multiplica de forma vectorial
    Vector3 productoVectorial(Vector3 multiplicando);
    //Da el producto escalar de dos vectores
    float productoEscalar (Vector3 multiplicando);

};

#endif