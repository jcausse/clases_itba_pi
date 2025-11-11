#ifndef _BUS_DRIVER_ADT_H_
#define _BUS_DRIVER_ADT_H_

typedef struct busDriverCDT * busDriverADT; 
 
busDriverADT newBusDriverADT(); 
 
void freeBusDriverADT(busDriverADT adt);
 
/** 
* Agrega (si no existía) una línea de colectivos 
* retorna 1 si la agrega, 0 si no la agrega (ya estaba) 
*/ 
int newBusLine(busDriverADT adt, unsigned int busLine); /* !!! */
 
/** 
* Retorna la cantidad de líneas de colectivos 
*/ 
int busLinesCount(const busDriverADT adt);  /* !!! */
 
/** 
* Retorna la cantidad de choferes que hay en la línea busLine 
* Si no existe la línea, retorna 0 
*/ 
int driversCount(const busDriverADT adt, unsigned int busLine);  /* !!! */
 
/** 
* Retorna un vector con la copia de los nombres de los choferes de una línea 
* en orden alfabético (ascendente). La dimensión se obtiene con la función driversCount 
* Si la línea no existe o no tiene choferes retorna NULL 
*/ 
char ** drivers(const busDriverADT adt, unsigned int busLine); 
 
/** 
* Agrega un chofer a una línea. 
* Si la línea no existe o el chofer ya estaba en esa línea, no hace nada 
*/   
void addDriver(busDriverADT adt, unsigned int busLine, const char * driver);

/** 
* Si existe el chofer para esa línea, lo elimina 
*/ 
void removeDriver(busDriverADT adt, unsigned int busLine, const char * driver);

#endif // _BUS_DRIVER_ADT_H_
