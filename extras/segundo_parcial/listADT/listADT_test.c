/* Workaround for stdio.h declaring int remove(const char *) */
#define remove stdio_remove
#include <stdio.h>
#undef remove

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <assert.h>
#include "listADT.h"

/* =========================================================================
 * Comparators
 * ========================================================================= */

static int str_cmp(elemType s1, elemType s2) {
    return strcmp(s1, s2);
}

static int strcasecmp_wrapper(elemType s1, elemType s2) {
    return strcasecmp(s1, s2);
}

static int strlen_cmp(elemType s1, elemType s2) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    if (len1 < len2) return -1;
    if (len1 > len2) return 1;
    return 0;
}

/* =========================================================================
 * Test Suites
 * ========================================================================= */

/**
 * Edge cases on an empty list:
 * - Newly created list must be empty (size 0, isEmpty true)
 * - belongs() must return false for any element
 * - remove() must return false for any element
 * - size and isEmpty must remain intact after failed removals
 * - freeList on empty list
 */
static void test_empty_list(void) {
    printf("Running test_empty_list... ");
    listADT l = newList(str_cmp);

    assert(size(l) == 0);
    assert(isEmpty(l) == true);

    // Belongs on empty list
    assert(belongs(l, "hello") == false);
    assert(belongs(l, "") == false);
    assert(belongs(l, "nonexistent") == false);

    // Remove on empty list
    assert(remove(l, "hello") == false);
    assert(remove(l, "") == false);

    // State should still be empty
    assert(size(l) == 0);
    assert(isEmpty(l) == true);

    freeList(l);
    printf("PASSED\n");
}

/**
 * Single element lifecycle:
 * - Adding one element: success, size becomes 1, isEmpty becomes false
 * - Duplicate insertion: rejected, size remains 1
 * - Query belongs: true for inserted, false for others
 * - Remove non-existent: rejected, size remains 1
 * - Remove existing: success, size back to 0, isEmpty becomes true
 * - Remove again after already removed: rejected
 */
static void test_single_element(void) {
    printf("Running test_single_element... ");
    listADT l = newList(str_cmp);

    // Add first element
    assert(add(l, "alpha") == true);
    assert(size(l) == 1);
    assert(isEmpty(l) == false);
    assert(belongs(l, "alpha") == true);
    assert(belongs(l, "beta") == false);

    // Adding duplicate element
    assert(add(l, "alpha") == false);
    assert(size(l) == 1);
    assert(isEmpty(l) == false);

    // Removing non-existent element
    assert(remove(l, "beta") == false);
    assert(size(l) == 1);
    assert(belongs(l, "alpha") == true);

    // Removing the only element
    assert(remove(l, "alpha") == true);
    assert(size(l) == 0);
    assert(isEmpty(l) == true);
    assert(belongs(l, "alpha") == false);

    // Removing already removed element
    assert(remove(l, "alpha") == false);
    assert(size(l) == 0);
    assert(isEmpty(l) == true);

    freeList(l);
    printf("PASSED\n");
}

/**
 * Multiple insertions in various orders:
 * - Ascending order
 * - Descending order
 * - Arbitrary / interleaved order
 * Verifying size, belongs for all, rejection of duplicates.
 */
static void test_multiple_elements_insertion_orders(void) {
    printf("Running test_multiple_elements_insertion_orders... ");

    // 1. Ascending insertion order
    {
        listADT l = newList(str_cmp);
        const char *items[] = {"apple", "banana", "cherry", "date", "fig"};
        size_t count = sizeof(items) / sizeof(items[0]);

        for (size_t i = 0; i < count; i++) {
            assert(add(l, (elemType)items[i]) == true);
            assert(size(l) == i + 1);
            assert(isEmpty(l) == false);
            assert(belongs(l, (elemType)items[i]) == true);
        }

        // Duplicates must be rejected
        for (size_t i = 0; i < count; i++) {
            assert(add(l, (elemType)items[i]) == false);
            assert(size(l) == count);
        }

        // Check belongs for all and for missing elements
        for (size_t i = 0; i < count; i++) {
            assert(belongs(l, (elemType)items[i]) == true);
        }
        assert(belongs(l, "aardvark") == false); // smaller than min
        assert(belongs(l, "blueberry") == false); // between items
        assert(belongs(l, "grape") == false); // larger than max

        freeList(l);
    }

    // 2. Descending insertion order
    {
        listADT l = newList(str_cmp);
        const char *items[] = {"fig", "date", "cherry", "banana", "apple"};
        size_t count = sizeof(items) / sizeof(items[0]);

        for (size_t i = 0; i < count; i++) {
            assert(add(l, (elemType)items[i]) == true);
            assert(size(l) == i + 1);
        }

        for (size_t i = 0; i < count; i++) {
            assert(belongs(l, (elemType)items[i]) == true);
        }

        freeList(l);
    }

    // 3. Interleaved / random insertion order
    {
        listADT l = newList(str_cmp);
        const char *items[] = {"cherry", "apple", "fig", "banana", "date"};
        size_t count = sizeof(items) / sizeof(items[0]);

        for (size_t i = 0; i < count; i++) {
            assert(add(l, (elemType)items[i]) == true);
            assert(size(l) == i + 1);
        }

        for (size_t i = 0; i < count; i++) {
            assert(belongs(l, (elemType)items[i]) == true);
        }

        freeList(l);
    }

    printf("PASSED\n");
}

/**
 * Removals at boundaries and middle:
 * - Remove head (smallest element)
 * - Remove tail (largest element)
 * - Remove interior / middle element
 * - Empty the list completely through removals
 * - Re-add elements to emptied list to ensure reuse
 */
static void test_removals_head_middle_tail(void) {
    printf("Running test_removals_head_middle_tail... ");
    listADT l = newList(str_cmp);

    const char *words[] = {"b", "d", "a", "e", "c"};
    size_t count = sizeof(words) / sizeof(words[0]);

    for (size_t i = 0; i < count; i++) {
        assert(add(l, (elemType)words[i]) == true);
    }
    assert(size(l) == 5);

    // Sorted elements are: "a", "b", "c", "d", "e"

    // 1. Remove Head ("a")
    assert(remove(l, "a") == true);
    assert(size(l) == 4);
    assert(belongs(l, "a") == false);
    assert(belongs(l, "b") == true);
    assert(belongs(l, "c") == true);
    assert(belongs(l, "d") == true);
    assert(belongs(l, "e") == true);

    // 2. Remove Tail ("e")
    assert(remove(l, "e") == true);
    assert(size(l) == 3);
    assert(belongs(l, "e") == false);
    assert(belongs(l, "b") == true);
    assert(belongs(l, "c") == true);
    assert(belongs(l, "d") == true);

    // 3. Remove Middle ("c")
    assert(remove(l, "c") == true);
    assert(size(l) == 2);
    assert(belongs(l, "c") == false);
    assert(belongs(l, "b") == true);
    assert(belongs(l, "d") == true);

    // 4. Remove Remaining elements
    assert(remove(l, "b") == true);
    assert(size(l) == 1);
    assert(belongs(l, "b") == false);
    assert(belongs(l, "d") == true);

    assert(remove(l, "d") == true);
    assert(size(l) == 0);
    assert(isEmpty(l) == true);
    assert(belongs(l, "d") == false);

    // 5. Re-add elements to previously emptied list
    assert(add(l, "reborn") == true);
    assert(size(l) == 1);
    assert(isEmpty(l) == false);
    assert(belongs(l, "reborn") == true);

    assert(remove(l, "reborn") == true);
    assert(size(l) == 0);
    assert(isEmpty(l) == true);

    freeList(l);
    printf("PASSED\n");
}

/**
 * Value equality vs Pointer equality:
 * Verifies that the ADT uses the comparator function to check for equality
 * rather than comparing raw pointer addresses.
 */
static void test_pointer_vs_value_equality(void) {
    printf("Running test_pointer_vs_value_equality... ");
    listADT l = newList(str_cmp);

    char buf1[32];
    char buf2[32];
    char buf3[32];
    strcpy(buf1, "target");
    strcpy(buf2, "target");
    strcpy(buf3, "target");

    char *p1 = buf1;
    char *p2 = buf2;
    char *p3 = buf3;

    // Ensure distinct memory addresses
    assert(p1 != p2);
    assert(p2 != p3);
    assert(p1 != p3);

    // Add using p1
    assert(add(l, p1) == true);
    assert(size(l) == 1);

    // Try adding duplicate using p2 (different address, same content)
    assert(add(l, p2) == false);
    assert(size(l) == 1);

    // Belongs check using p3 (different address, same content)
    assert(belongs(l, p3) == true);

    // Remove using p2 (different address, same content)
    assert(remove(l, p2) == true);
    assert(size(l) == 0);
    assert(isEmpty(l) == true);

    // Verify p1 is no longer found
    assert(belongs(l, p1) == false);

    freeList(l);
    printf("PASSED\n");
}

/**
 * Custom comparator tests:
 * 1. Case-insensitive comparator:
 *    - "hello" and "HELLO" must be considered duplicates
 *    - belongs("Hello") finds "hello"
 *    - remove("hElLo") removes "hello"
 * 2. Length-based comparator:
 *    - Strings with equal length are considered equal
 */
static void test_custom_comparators(void) {
    printf("Running test_custom_comparators... ");

    // 1. Case-insensitive comparator
    {
        listADT l = newList(strcasecmp_wrapper);

        assert(add(l, "case") == true);
        assert(size(l) == 1);

        // Duplicate under case-insensitive comparison
        assert(add(l, "CASE") == false);
        assert(add(l, "Case") == false);
        assert(size(l) == 1);

        assert(belongs(l, "CASE") == true);
        assert(belongs(l, "CaSe") == true);
        assert(belongs(l, "other") == false);

        assert(remove(l, "CASE") == true);
        assert(size(l) == 0);
        assert(isEmpty(l) == true);
        assert(belongs(l, "case") == false);

        freeList(l);
    }

    // 2. Length-based comparator
    {
        listADT l = newList(strlen_cmp);

        assert(add(l, "cat") == true);       // length 3
        assert(size(l) == 1);

        // "dog" has length 3, so under strlen_cmp it is considered duplicate!
        assert(add(l, "dog") == false);
        assert(size(l) == 1);

        // "elephant" has length 8
        assert(add(l, "elephant") == true);
        assert(size(l) == 2);

        // "bat" has length 3, so belongs() must return true
        assert(belongs(l, "bat") == true);
        // "bird" has length 4, not present
        assert(belongs(l, "bird") == false);

        // Remove element with length 3 using "pig"
        assert(remove(l, "pig") == true);
        assert(size(l) == 1);
        assert(belongs(l, "cat") == false);
        assert(belongs(l, "elephant") == true);

        freeList(l);
    }

    printf("PASSED\n");
}

/**
 * Edge cases on strings:
 * - Empty string ""
 * - Strings with common prefixes ("a", "aa", "aaa", "ab")
 * - Strings with spaces, numbers, and special characters
 */
static void test_special_strings(void) {
    printf("Running test_special_strings... ");
    listADT l = newList(str_cmp);

    // Empty string ""
    assert(add(l, "") == true);
    assert(size(l) == 1);
    assert(isEmpty(l) == false);
    assert(belongs(l, "") == true);
    assert(add(l, "") == false);

    // Prefixes
    assert(add(l, "a") == true);
    assert(add(l, "aa") == true);
    assert(add(l, "aaa") == true);
    assert(add(l, "ab") == true);
    assert(size(l) == 5);

    assert(belongs(l, "") == true);
    assert(belongs(l, "a") == true);
    assert(belongs(l, "aa") == true);
    assert(belongs(l, "aaa") == true);
    assert(belongs(l, "ab") == true);
    assert(belongs(l, "aaaa") == false);

    // Strings with spaces, punctuation, digits
    assert(add(l, "hello world") == true);
    assert(add(l, "12345") == true);
    assert(add(l, "!@#$%^&*()") == true);
    assert(size(l) == 8);

    assert(belongs(l, "hello world") == true);
    assert(belongs(l, "12345") == true);
    assert(belongs(l, "!@#$%^&*()") == true);

    // Remove empty string
    assert(remove(l, "") == true);
    assert(size(l) == 7);
    assert(belongs(l, "") == false);

    // Remove others
    assert(remove(l, "aaa") == true);
    assert(remove(l, "hello world") == true);
    assert(size(l) == 5);

    freeList(l);
    printf("PASSED\n");
}

/**
 * Stress test:
 * - Insert 1000 dynamically formatted elements
 * - Check size and duplicate rejection
 * - Check belongs for all 1000
 * - Remove every even-numbered element (500 removals)
 * - Verify size = 500, even absent, odd present
 * - Remove remaining 500 elements
 * - Verify size = 0, isEmpty = true
 */
#define STRESS_SIZE 1000

static void test_stress(void) {
    printf("Running test_stress (%d elements)... ", STRESS_SIZE);
    listADT l = newList(str_cmp);

    char items[STRESS_SIZE][16];
    for (int i = 0; i < STRESS_SIZE; i++) {
        snprintf(items[i], sizeof(items[i]), "key_%04d", i);
    }

    // Insert all in reverse order to test sorted insertion behavior
    for (int i = STRESS_SIZE - 1; i >= 0; i--) {
        assert(add(l, items[i]) == true);
    }
    assert(size(l) == STRESS_SIZE);
    assert(isEmpty(l) == false);

    // Duplicate rejection
    for (int i = 0; i < STRESS_SIZE; i++) {
        assert(add(l, items[i]) == false);
    }
    assert(size(l) == STRESS_SIZE);

    // Belongs verification
    for (int i = 0; i < STRESS_SIZE; i++) {
        assert(belongs(l, items[i]) == true);
    }

    // Remove even-indexed elements
    for (int i = 0; i < STRESS_SIZE; i += 2) {
        assert(remove(l, items[i]) == true);
    }
    assert(size(l) == STRESS_SIZE / 2);

    // Verify even are gone, odd are present
    for (int i = 0; i < STRESS_SIZE; i++) {
        if (i % 2 == 0) {
            assert(belongs(l, items[i]) == false);
            assert(remove(l, items[i]) == false);
        } else {
            assert(belongs(l, items[i]) == true);
        }
    }

    // Remove odd-indexed elements
    for (int i = 1; i < STRESS_SIZE; i += 2) {
        assert(remove(l, items[i]) == true);
    }
    assert(size(l) == 0);
    assert(isEmpty(l) == true);

    freeList(l);
    printf("PASSED\n");
}

/* =========================================================================
 * Main entry point
 * ========================================================================= */

int main(void) {
    puts("=== Running listADT tests ===");

    test_empty_list();
    test_single_element();
    test_multiple_elements_insertion_orders();
    test_removals_head_middle_tail();
    test_pointer_vs_value_equality();
    test_custom_comparators();
    test_special_strings();
    test_stress();

    puts("All listADT tests passed successfully!");
    return 0;
}
