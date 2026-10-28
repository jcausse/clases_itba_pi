/**
 * @file listADT.h
 * @brief Abstract Data Type of a generic list which keeps elements in
 *        order and does not accept duplicate elements
 */

#ifndef _LIST_ADT_H_
#define _LIST_ADT_H_

#include <stddef.h> // size_t

typedef struct listCDT * listADT;
typedef char * elemType;
typedef int (* comparator)(elemType, elemType);

/**
 * @brief       Creates a new list.
 * @details     The constructor takes a comparator function pointer because
 *              the elements in the list are kept in order, and the list does
 *              not accept duplicates.
 * @param[in]   cmp     `elemType` comparator function.
 * @return      The newly created list.
 */
listADT newList(comparator cmp);

/**
 * @brief       Cleans-up the list.
 */
void freeList(listADT l);

/**
 * @brief       Add a new element to the list.
 * @param[in]   e   The element to be added.
 * @return      `true` on success, `false` if the element is already present
 *              in the list.
 */
bool add(listADT l, elemType e);

/**
 * @brief       Removes an element from the list.
 * @param[in]   e   The element to be removed.
 * @return      `true` on success, `false` if the element was not present in the list.
 */
bool remove(listADT l, elemType e);

/**
 * @brief       Get the size of the list (number of elements contained).
 * @return      Size of the list.
 */
size_t size(listADT l);

/**
 * @brief       Check whether the list has elements or not.
 * @return      `true` if size == 0, `false` otherwise.
 */
bool isEmpty(listADT l);

/**
 * @brief       Check whether an element belongs to the list.
 * @param[in]   e   The element to check.
 * @param       `true` if `e` is in `l`, `false` otherwise.
 */
bool belongs(listADT l, elemType e);

#endif // _LIST_ADT_H_
