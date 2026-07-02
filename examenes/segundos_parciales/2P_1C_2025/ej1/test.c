#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "coursesADT.h"

int main(void) { 
    coursesADT course = newCourses(); 
    // No es válida la carrera '2', sólo letras 
    assert(addCourse(course, '2', 10, "Economia", 90)==0); 
    assert(students(course, 's')==0); // Aún no hay cursos para la carrera 'S' 
    assert(students(course, 'S')==0); 
    assert(students(course, '+')==0); // carrera inválida 
    
    // Dos materias con el mismo nombre pero distinto código 
    assert(addCourse(course, 'S', 10, "Economia", 90)==1); 
    assert(addCourse(course, 'S', 5, "Economia", 20)==1); 
    assert(students(course, 's')==110); 
    
    // Ya existe "Economia" con el código 10 
    assert(addCourse(course, 'S', 10, "Economia", 20)==0); 
    // "Economia" con código 10 pero para otra carrera, es válido 
    assert(addCourse(course, 'X', 10, "Economia", 90)==1);
    
    // Si bien no deberia pasar que tenga el mismo código que "Economia",  
    // el TAD no lo valida 
    assert(addCourse(course, 's', 10, "Programacion Imperativa", 40)==1); 
    assert(students(course, 'S')==150); 
    
    char s[100] = "Optativa 1"; 
    assert(addCourse(course, 'S', 400, s, 0)==1); // Agregamos "Optativa 1", sin alumnos 
    strcpy(s,"Optativa regalada"); 
    assert(addCourse(course, 'S', 110, s, 120)==1); 
    
    toBeginByDegree(course, 'S'); 
    struct courseData aux; 
    assert(nextCourse(course, 'S', &aux)==1); 
    assert(aux.code == 5 && aux.students == 20 && strcmp(aux.name, "Economia")==0); 
    free(aux.name); 
    assert(nextCourse(course, 'S', &aux)==1); 
    assert(aux.code == 10 && strcmp(aux.name, "Economia")==0);  
    free(aux.name); 
    assert(nextCourse(course, 'S', &aux)==1); 
    assert(strcmp(aux.name, "Optativa 1")==0); 
    free(aux.name); 
    assert(nextCourse(course, 'S', &aux)==1); 
    assert(strcmp(aux.name, "Optativa regalada")==0); 
    free(aux.name); 
    assert(nextCourse(course, 'S', &aux)==1);
    assert(strcmp(aux.name, "Programacion Imperativa")==0); 
    free(aux.name); 
    assert(nextCourse(course, 'S', &aux)==0); 
    
    assert(courses(course, 'S')==5); assert(courses(course, 's')==5); 
    assert(courses(course, 'T')==0); assert(courses(course, '?')==0); 
        
    freeCourses(course); 
    puts("OK"); 
    return 0; 
}
