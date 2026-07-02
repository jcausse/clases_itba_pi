#include "coursesADT.h"
#include <ctype.h>
#include <string.h>

#include <stdio.h>

// LISTA DE CURSOS
typedef struct Course {
    struct courseData data;         // La informacion de cada curso (nombre, codigo, cantidad de estudiantes)
    struct Course * next;           // Siguiente materia
} Course;

// CARRERA
typedef struct Degree {
    char id;                        // Letra de la carrera (las guardo siempre en mayuscula)
    size_t course_count;            // Cantidad de materias que tiene esa carrera
    size_t student_count;           // Cantidad de alumnos totales que tiene la carrera (suma de cantidad de estudiantes en todas las materias)
    Course * first;                 // Cursos de la carrera (la lista la libreamos con ESTE puntero porque es el que apunta a la primera materia)
    Course * iterator;              // Iterador de la carrera (no se libera porque solamente es un puntero en stack)
} Degree;

// TAD
struct coursesCDT {
    struct Degree * degrees;        // Arreglo dinamico de carreras (que se realloca de a 1 porque no son tantas como para que justifique el algoritmo de bloques)
    size_t dim;                     // Cantidad de carreras agregadas
};

coursesADT newCourses(void) {
    return calloc(1, sizeof(struct coursesCDT));
}

/// @brief Libera todos los cursos de una carrera, recursivamente
/// @param course   Materia actual a liberar
static void freeCourse(Course * course){
    if (course == NULL) {
        return;
    }

    /* FORMA 1: Libero mientras avanzo */
    // Course * aux = course->next;
    // free(course);
    // freeCourse(aux);

    /* FORMA 2: Voy hasta el final y libero mientras vuelvo */
    freeCourse(course->next);
    free(course->data.name);
    free(course);
}
 
void freeCourses(coursesADT course) {
    for (size_t i = 0; i < course->dim; i++) {  // Libero todas las carreras
        freeCourse(course->degrees[i].first);
    }
    free(course->degrees);                      // Libero el vector de carreras
    free(course);                               // Libero el TAD
}

/// @brief Busca y devuelve una carrera, recursivamente
/// @param current  Carrera por la que busca actualmente
/// @param dim      Cantidad de carreras que me quedan por buscar
/// @param target   Identificador (letra) de la carrera
/// @param index    El indice sobre el array por el que actualmente esta recorriendo
/// @return El indice sobre el arreglo degrees donde se encuentra la carrera, o -1 si no esta
static int findDegree(Degree * degrees, size_t dim, char target, size_t index) {
    // Caso base 1: No la encontre (index alcanzo a dim), devuelvo -1
    if (index >= dim) {
        return -1;
    }

    // Caso base 2: La encontre, devuelvo el puntero del actual
    if (degrees[index].id == target) {
        return (int) index;
    }

    // Caso general: sigo buscando recursivamente
    return findDegree(degrees, dim, target, index + 1);
}

/// @brief Crea una nueva carrera en el ADT
/// @param adt El ADT
/// @param id Letra que identifica a la carrera (en MAYUSCULA)
static void newDegree(coursesADT adt, char id) {
    (adt->dim)++;                                                       // Incremento en 1 la cantidad de Carreras
    adt->degrees = realloc(adt->degrees, adt->dim * sizeof(Degree));    // Realloco (agrega 1 mas)
    adt->degrees[adt->dim - 1].id = id;                                 // Seteo el ID de carrera
    adt->degrees[adt->dim - 1].course_count = 0;                        // La nueva Carrera no tiene cursos ni
    adt->degrees[adt->dim - 1].student_count = 0;                       // alumnos, inicialmente
    adt->degrees[adt->dim - 1].first = NULL;                            // Inicio cursos e iterador en NULL
    adt->degrees[adt->dim - 1].iterator = NULL;
}

/// @brief Crea un nuevo curso
/// @param courseCode Codigo de curso
/// @param courseName Nombre de curso (se copiara en memoria dinamica)
/// @param students Cantidad de estudiantes
/// @return Curso creado
static Course * newCourse(int courseCode, const char * courseName, unsigned int students) {
    Course * ret = malloc(sizeof(Course));
    ret->data.code = courseCode;
    ret->data.name = strdup(courseName);
    ret->data.students = students;
    ret->next = NULL;
    return ret;
}

/// @brief Busca un curso determinado en la lista de cursos, que mantiene ordenada. 
/// @details    1. Si la Materia / Curso existe en la lista *res no se modifica
///             2. Si la materia NO existe *res sera un puntero al nodo anterior en la lista para mantener las materias en orden
///                (que puede ser NULL si la materia a insertar debiera ser la primera)
/// @param current      Nodo actual de la lista en el que estoy parado (NULL si recien empiezo y el siguiente es el primero)
/// @param list         Nodo siguiente en la lista
/// @param courseCode   Codigo de materia
/// @param courseName   Nombre de materia
/// @param res          Variable donde guardar el resultado pedido
/// @return Un valor booleano indicando si la materia existia (false), o debe crearse (true)
static bool findCourse(Course * current, Course * next, int courseCode, const char * courseName, Course ** res) {
    // Si en algun momento dado se me termina la lista, devuelvo el current. Esto sirve para los casos donde la nueva materia
    // la tengo que insertar al final (donde current es el ultimo nodo en la lista y next se me hizo NULL porque se termino la
    // lista), o tambien cuando tengo que insertar al principio, porque como current arranca en NULL entonces si la lista no
    // tiene nodos (no hay materias agregadas aun), retorna NULL que es current
    if (next == NULL) {
        return true;
    }

    int cmp = strcmp(courseName, next->data.name);          // Comparo el nodo siguiente con la materia que quiero agregar
    if (cmp > 0){                                           // Si el nombre en next va antes que yo, sigo
        return findCourse(next, next->next, courseCode, courseName, res);
    }
    else if (cmp == 0){                                     // Encontre una materia que se llama igual. A ver el codigo...
        if (courseCode == next->data.code) {                // Si son iguales, la materia ya existia
            return false;
        }
        *res = courseCode > next->data.code ? next : current;
        return true;
    }
    // Si el nombre actual supera al next, el anterior es el current
    *res = current;
    return true;
}

/// @brief Agrega una Materia (Course) al Degree. Si ya existe, no la agrega
/// @param d            Puntero a la carrera a la cual agregar
/// @param courseCode   Codigo de materia
/// @param courseName   Nombre de materia
/// @param students     Cantidad de estudiantes
static int addCourseToDegree(Degree * d, int courseCode, const char * courseName, unsigned int students) {
    Course * res;
    if (! findCourse(NULL, d->first, courseCode, courseName, &res)){
        return 0;
    }

    Course * new = newCourse(courseCode, courseName, students);
    if (res == NULL) {          // Insercion al principio
        new->next = d->first;
        d->first = new;
    }
    else {                      // Res es el nodo que va antes del nuevo
        new->next = res->next;  // El siguiente al nuevo es el siguiente actual de res (porque se mete en el medio)
        res->next = new;        // El nuevo nodo es el nuevo siguiente a res
    }

    // Cada vez que agrego un curso, la mejor practica seria llevar el iterador al principio
    d->iterator = new;

    // Incremento los contadores
    (d->course_count)++;
    d->student_count += students;
    return 1;
}

int addCourse(coursesADT course, char degree, int courseCode, const char * courseName, unsigned int students) {
    if (! isalpha(degree)) {            // Chequeo de condicion: degree debe ser una letra
        return 0;
    }
    degree = toupper(degree);           // La paso a mayuscula por consistencia

    int index = findDegree(course->degrees, course->dim, degree, 0);
    if (index == -1) {                  // Si la carrera no existe, la agrego
        newDegree(course, degree);
        index = course->dim - 1;        // Seteo el index para agregar la Materia a la Carrera recien creada
    }

    return addCourseToDegree(&(course->degrees[index]), courseCode, courseName, students); // Agrego la materia
}
 
size_t courses(const coursesADT course, char degree) {
    int index = findDegree(course->degrees, course->dim, degree, 0);
    return index == -1 ? 0 : course->degrees[index].course_count;
}

size_t students(const coursesADT course, char degree) {
    int index = findDegree(course->degrees, course->dim, degree, 0);
    return index == -1 ? 0 : course->degrees[index].student_count;
}

void toBeginByDegree(coursesADT course, char degree) {
    int index = findDegree(course->degrees, course->dim, degree, 0);
    if (index == -1) {
        return;
    }
    course->degrees[index].iterator = course->degrees[index].first;
}

int nextCourse(coursesADT course, char degree, struct courseData * data) {
    int index = findDegree(course->degrees, course->dim, degree, 0);
    if (index == -1 || course->degrees[index].iterator == NULL) {
        return 0;
    }
    data->code = course->degrees[index].iterator->data.code;
    data->name = course->degrees[index].iterator->data.name;
    data->students = course->degrees[index].iterator->data.students;
    course->degrees[index].iterator = course->degrees[index].iterator->next;
    return 1;
}
