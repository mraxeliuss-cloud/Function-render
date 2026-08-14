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

    
    //Operaciones internas
    //Modulo 
    //Calcula el módulo "Tamaño" del vector
    float const magnitud();

    //Normalizar
    //Divide cada miembro por el módulo
    Vector3 normalizar();

    //Operaciones básicas con escalares
    //Modifican el vector actual
    //Multiplica cada miembro por un escalar
    Vector3 multiplicacion ( float multiplicando );
    //Divide cada miembro por un escalar
    Vector3 division( float divisor);

    //Operaciones básicas con vectores
    //Todos devuelven objetos nuevos
    //Suma dos vectores, elemento a elemento
    Vector3 suma( Vector3 sumando);
    //Resta dos vectores elemento a elemento
    Vector3 resta( Vector3 sustraendo);
    //Multiplica de forma vectorial
    Vector3 productoVectorial(Vector3 multiplicando);
    //Da el producto escalar de dos vectores
    float productoEscalar (Vector3 sumando);

};

#endif