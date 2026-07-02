#ifndef _COURSES_ADT_H_
#define _COURSES_ADT_H_

#include <stdlib.h>

typedef struct coursesCDT * coursesADT;
 
struct courseData { 
    char * name;
    int code; 
    unsigned int students; 
};
 
coursesADT newCourses(void); 
 
void freeCourses(coursesADT course); 
 
/** 
* Agrega -si no estaba- una nueva materia a la carrera. Si ya existe una materia con esa  
* descripción en la carrera, debe tener un código distinto 
* El parámetro students indica cuántos alumnos están inscriptos en esa materia 
* Retorna 1 si se agregó la materia, 0 si no (si la carrera era inválida o ya existía la  
* materia) 
*/ 
int addCourse(coursesADT course, char degree, int courseCode, const char * courseName, unsigned int students); 
 
/** 
* Retorna la cantidad de materias que hay en una carrera. 
*/ 
size_t courses(const coursesADT course, char degree);

/** 
* Retorna la cantidad de alumnos que hay en una carrera.  
* Si la carrera es inválida retorna cero 
*/ 
size_t students(const coursesADT course, char degree); 
 
// Funciones para iterar por carrera, alfabéticamente por materia (en forma eficiente) 
void toBeginByDegree(coursesADT course, char degree);

/** 
* Si hay siguiente materia para una carrera, retorna 1 y deja en data la info sobre la  
* materia. Si no hay más materias para esa carrera retorna 0 y no cambia data 
*/ 
int nextCourse(coursesADT course, char degree, struct courseData * data);

#endif // _COURSES_ADT_H_
