#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct {
  char* testName;
  int (*testFunc)(void);
} TestCase;

void test(TestCase* t) {
  int err = t->testFunc();
  if (err) {
    fprintf(stderr, "error: %s had return value %d\n", t->testName, err);
  }
}

// In all tests, the return value represents an error:
// If the return value is non-zero, an error occured
int TestNewList_ui32() {
  List_ui32* list = NewList_ui32();
  if (list->Length != 0) {
    fprintf(stderr, "expected list->Length == 0, got list->Length == %zu\n", list->Length);
    return 1;
  }
  if (list->capacity < list->Length) {
    fprintf(stderr, "expected list->Length <= list->capacity, ");
    fprintf(stderr, "got list->Length == %zu and ", list->Length);
    fprintf(stderr, "list->capacity == %zu\n", list->capacity);
    return 2;
  }
  DestroyList_ui32(list);
  return 0;
}

// In all tests, the return value represents an error:
// If the return value is non-zero, an error occured
int TestListAppendAndGetFew_ui32() {
  List_ui32* list = NewList_ui32();
  if (list->Length != 0) {
    fprintf(stderr, "expected list->Length == 0, got list->Length == %zu\n", list->Length);
    return 1;
  }
  if (list->capacity < list->Length) {
    fprintf(stderr, "expected list->Length <= list->capacity, ");
    fprintf(stderr, "got list->Length == %zu and ", list->Length);
    fprintf(stderr, "list->capacity == %zu\n", list->capacity);
    return 2;
  }
  for (uint32_t i = 0; i < 8; i++) {
    ListAppend_ui32(list, i);
  }
  for (uint32_t i = 0; i < 8; i++) {
    if (ListGet_ui32(list, i) != i) {
      char* errstr = ListString_ui32(list);
      fprintf(stderr, "expected [0, 1, 2, 3, 4, 5, 6, 7] got %s\n", errstr);
      free(errstr);
      return 3;
    }
  }  
  DestroyList_ui32(list);
  return 0;
}

// In all tests, the return value represents an error:
// If the return value is non-zero, an error occured
int TestListAppendAndGetMany_ui32() {
  List_ui32* list = NewList_ui32();
  if (list->Length != 0) {
    fprintf(stderr, "expected list->Length == 0, got list->Length == %zu\n", list->Length);
    return 1;
  }
  if (list->capacity < list->Length) {
    fprintf(stderr, "expected list->Length <= list->capacity, ");
    fprintf(stderr, "got list->Length == %zu and ", list->Length);
    fprintf(stderr, "list->capacity == %zu\n", list->capacity);
    return 2;
  }
  for (uint32_t i = 0; i < 1000000; i++) {
    ListAppend_ui32(list, 2*i);
  }
  for (uint32_t i = 0; i < 1000000; i++) {
    if (ListGet_ui32(list, i) != 2*i) {
      char* errstr = ListString_ui32(list);
      fprintf(stderr, "expected [0, 2, 4, ..., 19998] got %s\n", errstr);
      free(errstr);
      return 3;
    }
  }
  DestroyList_ui32(list);
  return 0;
}

// In all tests, the return value represents an error:
// If the return value is non-zero, an error occured
int TestListInsert_ui32() {
  List_ui32* list = NewList_ui32();
  if (list->Length != 0) {
    fprintf(stderr, "expected list->Length == 0, got list->Length == %zu\n", list->Length);
    return 1;
  }
  if (list->capacity < list->Length) {
    fprintf(stderr, "expected list->Length <= list->capacity, ");
    fprintf(stderr, "got list->Length == %zu and ", list->Length);
    fprintf(stderr, "list->capacity == %zu\n", list->capacity);
    return 2;
  }
  for (uint32_t i = 0; i < 10; i++) {
    ListAppend_ui32(list, i);
  }
  ListInsert_ui32(list, 0, 5);
  ListInsert_ui32(list, 0, 6);
  ListInsert_ui32(list, 4, 6);
  uint32_t expected[] = {6, 5, 0, 1, 6, 2, 3, 4, 5, 6, 7, 8, 9};
  if (list->Length != 13) {
    fprintf(stderr, "expected list->Length == 0, got list->Length == %zu\n", list->Length);    
    return 3;
  }
  for (uint32_t i = 0; i < 13; i++) {
    if (ListGet_ui32(list, i) != expected[i]) {
      char* errstr = ListString_ui32(list);
      fprintf(stderr, "expected [");
      for (size_t j = 0; j < 12; j++) {
	fprintf(stderr, "%u, ", expected[j]);
      }
      fprintf(stderr, "%u] got %s\n", expected[12], errstr);
      free(errstr);
      return 4;
    }
  }
  DestroyList_ui32(list);
  return 0;
}

// In all tests, the return value represents an error:
// If the return value is non-zero, an error occured
int TestListRemove_ui32() {
  List_ui32* list = NewList_ui32();
  if (list->Length != 0) {
    fprintf(stderr, "expected list->Length == 0, got list->Length == %zu\n", list->Length);
    return 1;
  }
  if (list->capacity < list->Length) {
    fprintf(stderr, "expected list->Length <= list->capacity, ");
    fprintf(stderr, "got list->Length == %zu and ", list->Length);
    fprintf(stderr, "list->capacity == %zu\n", list->capacity);
    return 2;
  }
  for (uint32_t i = 0; i < 10; i++) {
    ListAppend_ui32(list, i);
  }
  ListRemove_ui32(list, 0);
  ListRemove_ui32(list, 2);
  ListRemove_ui32(list, 3);
  ListRemove_ui32(list, 6);
  uint32_t expected[] = {1, 2, 4, 6, 7, 8};
  if (list->Length != 6) {
    fprintf(stderr, "expected list->Length == 7, got list->Length == %zu\n", list->Length);    
    return 3;
  }
  for (uint32_t i = 0; i < 6; i++) {
    if (ListGet_ui32(list, i) != expected[i]) {
      char* errstr = ListString_ui32(list);
      fprintf(stderr, "expected [");
      for (size_t j = 0; j < 5; j++) {
	fprintf(stderr, "%u, ", expected[j]);
      }
      fprintf(stderr, "%u] got %s\n", expected[5], errstr);
      free(errstr);
      return 4;
    }
  }
  DestroyList_ui32(list);
  return 0;
}

int main() {
  TestCase testCases[] = {
    (TestCase){"TestNewList_ui32", &TestNewList_ui32},
    (TestCase){"TestListAppendAndGetFew_ui32", &TestListAppendAndGetFew_ui32},
    (TestCase){"TestListAppendAndGetMany_ui32", &TestListAppendAndGetMany_ui32},
    (TestCase){"TestListInsert_ui32", &TestListInsert_ui32},
    (TestCase){"TestListRemove_ui32", &TestListRemove_ui32},
  };
  size_t len = sizeof(testCases) / sizeof(TestCase);
  printf("Located %zu tests. Running tests...\n", len);
  for (size_t i = 0; i < len; i++) {
    test(&testCases[i]);
  }
  printf("All tests have completed!\n");
}
