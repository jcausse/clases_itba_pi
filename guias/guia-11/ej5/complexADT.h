#ifndef _COMPLEX_ADT_H_
#define _COMPLEX_ADT_H_

typedef struct complexCDT * complexADT;

/**
 * @brief       Crea un numero complejo
 * @param re    Parte real
 * @param im    Parte imaginaria
 */
complexADT nuevoComp(double re, double im);

/**
 * @brief       Devuelve la parte real del complejo
 * @param z     Complejo
 */
double parteRealComp(const complexADT z);

/**
 * @brief       Devuelve la parte imaginaria del complejo
 * @param z     Complejo
 */
double parteImagComp(const complexADT z);

/**
 * @brief       Suma ambos numeros complejos y devuelve el complejo resultante
 * @param z1    Complejo z1
 * @param z2    Complejo z2
 * @return      Complejo z1 + z2
 */
complexADT sumaComp(const complexADT z1, const complexADT z2);

/**
 * @brief       Resta ambos numeros complejos y devuelve el complejo resultante
 * @param z1    Complejo z1
 * @param z2    Complejo z2
 * 
 * @return      Complejo z1 - z2
 */
complexADT restaComp(const complexADT z1, const complexADT z2);

/**
 * @brief       Multiplica ambos numeros complejos y devuelve el complejo resultante
 * @param z1    Complejo z1
 * @param z2    Complejo z2
 * 
 * @return      Complejo z1 * z2
 */
complexADT multiplicaComp(const complexADT z1, const complexADT z2);

/**
 * @brief       Divide ambos numeros complejos y devuelve el complejo resultante
 * @param z1    Complejo z1
 * @param z2    Complejo z2
 * 
 * @return      Complejo z1 / z2
 */
complexADT divideComp(const complexADT z1, const complexADT z2);

/**
 * @brief       Devuelve el conjugado del numero complejo
 * @param z     El numero complejo a conjugar
 */
complexADT conjugadoComp(const complexADT z);

/**
 * @brief       Elimina un complejo
 * @param z     El complejo a eliminar
 */
void liberaComp(complexADT z);

#endif // _COMPLEX_ADT_H_
