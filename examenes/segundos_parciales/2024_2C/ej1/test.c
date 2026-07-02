#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "courseADT.h"

int main(void) {
    // Curso de ingreso para el 2025 con 3 materias
    courseADT course = newCourse(2025, 3);
    // El id es inválido
    assert(addStudent(course, 1, "Jose")==0);
    assert(addStudent(course, 250002, "Han")==1);
    assert(addStudent(course, 250001, "Felix")==1);
    assert(addStudent(course, 250101, "Lisa")==1);
    assert(addStudent(course, 250101, "Otra Lisa")==0);
    char name[] = "Radames";
    assert(addStudent(course, 250020, name)==1);
    strcpy(name, "Tosca");
    assert(addStudent(course, 250022, name)==1);
    assert(students(course)==5);
    assert(studentName(course, 250900)==NULL);
    char * s = studentName(course, 250020);
    assert(strcmp(s, "Radames")==0);
    free(s);
    assert(deleteStudent(course, 250020)==1);
    assert(studentName(course, 250020)==NULL);
    assert(students(course)==4);
    // Las 3 notas de "Han"
    assert(setGrade(course, 250002, 10, 2)==1);
    assert(setGrade(course, 250002, 20, 9)==1);
    assert(setGrade(course, 250002, 30, 8)==1);
    assert(setGrade(course, 250002, 10, 6)==1); // Era un 2, ahora es 6
    // Códigos inválidos de materia
    assert(setGrade(course, 250002, 15, 5)==0);
    assert(setGrade(course, 250002, 40, 5)==0);
    freeCourse(course);
    puts("OK!");
    return 0;
}
