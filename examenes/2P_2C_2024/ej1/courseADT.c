#include "courseADT.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t id;
    const char * name;
    unsigned char * grades;
} Student;

struct courseCDT {
    size_t year;
    size_t subject_count;

    size_t student_count;

    Student * students;
    size_t array_size;
};

// Funciones helper
static bool isValidId(size_t id, size_t year);
static bool isValidGrade(unsigned char grade);
static bool isValidSubject(size_t subjectId, size_t subejctCount);
static int getStudentIndexIfExists(courseADT course, size_t id);

courseADT newCourse(size_t year, size_t subjects) {
    courseADT course = calloc(1, sizeof(struct courseCDT));
    course->year = year;
    course->subject_count = subjects;
    return course;
}

int addStudent(courseADT course, size_t id, const char * name) {
    // Chequeo de precondiciones
    if (!isValidId(id, course->year) || name == NULL) {
        return 0;
    }

    // Obtengo el indice si ya existia, y sino obtengo -1
    if (getStudentIndexIfExists(course, id) != -1) {
        return 0;
    }

    size_t studentIndex = id % ID_YEAR_OFFSET - 1;

    // Agrando el array si es necesario
    if (studentIndex >= course->array_size) {
        course->students = realloc(course->students, (studentIndex + 1) * sizeof(Student));
        for (size_t i = course->array_size; i <= studentIndex; i++) {
            course->students[i].id = 0;                     // ID cero indica estudiante no creado
            course->students[i].name = NULL;
            course->students[i].grades = NULL;
        }
        course->array_size = studentIndex + 1;
    }
    
    // Inicializo al estudiante con todas sus notas en cero
    course->students[studentIndex].id = id;
    course->students[studentIndex].name = strdup(name);
    course->students[studentIndex].grades = calloc(course->subject_count, sizeof(unsigned char));

    // Incremento la cantidad de estudiantes
    (course->student_count)++;

    return 1;
}

char * studentName(const courseADT course, size_t id) {
    size_t studentIndex = getStudentIndexIfExists(course, id);
    return studentIndex == -1 ? NULL : strdup(course->students[studentIndex].name);
}

size_t students(const courseADT course) {
    return course->student_count;
}

int setGrade(courseADT course, size_t id, size_t subject, unsigned char grade) {
    // Nota invalida o materia invalida
    if (!isValidGrade(grade) || !isValidSubject(subject, course->subject_count)) {
        return 0;
    }

    int index = getStudentIndexIfExists(course, id);

    // Estudiante no existe o ID invalido
    if (index == -1) {
        return 0;
    }
    
    // Seteo la nota
    course->students[index].grades[subject / 10 - 1] = grade;

    return 1;
}

int gradeSubject(const courseADT course, size_t id, size_t subject) {
    return 0;   // NO IMPLEMENTADA PORQUE NO SE PIDE
}

int deleteStudent(courseADT course, size_t id) {
    int index = getStudentIndexIfExists(course, id);
    if (index == -1) {
        return 0;
    }

    course->students[index].id = 0;

    free((char *) course->students[index].name);
    course->students[index].name = NULL;

    free(course->students[index].grades);
    course->students[index].grades = NULL;

    (course->student_count)--;

    return 1;
}

void freeCourse(courseADT course) {
    for (size_t i = 0; i < course->array_size; i++) {
        free((char *) course->students[i].name);
        free(course->students[i].grades);
    }
    free(course->students);
    free(course);
}

/*****************************************************************************/

static bool isValidId(size_t id, size_t year) {
    return id / ID_YEAR_OFFSET == year % 100 && id % ID_YEAR_OFFSET > 0;
}

static bool isValidGrade(unsigned char grade) {
    return grade <= MAX_GRADE;
}

static bool isValidSubject(size_t subjectId, size_t subejctCount) {
    return subjectId % 10 == 0 && subjectId / 10 <= subejctCount;
}

// Verifica que el estudiante exista y devuelve su indice. Si su id no es valido o el estudiante
// no esta creado, devuelve -1
static int getStudentIndexIfExists(courseADT course, size_t id) {
    int index = id % ID_YEAR_OFFSET - 1;
    if (isValidId(id, course->year)
        && index < course->array_size 
        && course->students[index].id != 0
    ) {
        return index;
    }
    return -1;
}
