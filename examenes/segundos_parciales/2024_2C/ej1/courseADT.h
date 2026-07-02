#ifndef _COURSE_ADT_H_
#define _COURSE_ADT_H_

#include <stddef.h>

#define ID_YEAR_OFFSET  10000   // Digito a partir del cual empieza el año en el ID 250003 -> a partir del 10^4
#define MAX_GRADE       10      // Nota maxima que un alumno puede tener en una materia

typedef struct courseCDT * courseADT;

/* Crea un sistema de administración del curso de ingreso para un año #year
* con una cantidad #subjects de materias
*/
courseADT newCourse(size_t year, size_t subjects);

/* Agrega un alumno al curso
* Si el id es inválido para el año no lo agrega y retorna cero
* Si ya existía un alumno con ese id no hace nada y retorna cero
* En cualquier otro caso lo agrega con todas las notas en cero y retorna 1
*/
int addStudent(courseADT course, size_t id, const char * name);

/* Retorna una copia del nombre del estudiante o NULL si el id es inválido o no existe */
char * studentName(const courseADT course, size_t id);

/* Retorna la cantidad de estudiantes en el curso */
size_t students(const courseADT course);

/* Establece la nota en una materia para un estudiante
* Si el legajo del estudiante es incorrecto o no existe el estudiante retorna 0
* Si el código de materia es incorrecto o la nota no está entre 0 y 10 retorna 0
* En ambos casos no realiza ningún cambio
* En caso contrario registra la nota y retorna 1
* Si la materia ya tenía una nota, la pisa con la nueva nota recibida
*/
int setGrade(courseADT course, size_t id, size_t subject, unsigned char grade);

/* Retorna la nota de un estudiante en una materia. La nota de una materia es cero
* hasta tanto se registre una nueva nota
* Si el legajo del estudiante es incorrecto o no existe el estudiante retorna -1
* Si el código de materia es incorrecto retorna -1
*/
int gradeSubject(const courseADT course, size_t id, size_t subject);

/* Si el id es válido y existe el alumno, lo elimina del curso y retorna 1
* En otro caso no hace nada y retorna cero
*/
int deleteStudent(courseADT course, size_t id);

/* Libera los recursos utilizados por el TAD */
void freeCourse(courseADT course);

#endif // _COURSE_ADT_H_
