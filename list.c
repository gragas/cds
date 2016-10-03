#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define INITIAL_CAPACITY 8

List_ui32* NewList_ui32() {
  List_ui32* list = calloc(sizeof(List_ui32), 1);
  list->Length = 0;
  list->capacity = INITIAL_CAPACITY;
  list->data = calloc(sizeof(uint32_t), list->capacity);
  return list;
}

void DestroyList_ui32(List_ui32* list) {
  free(list->data);
  free(list);
}

// ListVerifyCapacity sets `list->Length` to newLength and
// allocates and zeros new memory if `list->Length` > `list->capacity`
// Returns an int: if an error occured, the return value is non-zero
static int ListVerifyCapacity_ui32(List_ui32* list, size_t newLength) {
  if (newLength > list->capacity) {
    // allocate more memory
    if (list->capacity < 512) {
      list->capacity *= 2;
    } else {
      list->capacity = (size_t)(list->capacity * 1.1);
    }
    // verify that we've allocated enough
    if (newLength > list->capacity) {
      list->capacity = newLength;
    }
    uint32_t *new_mem = calloc(list->capacity, sizeof(uint32_t));
    if (new_mem == NULL) {
      return 1;
    }
    memcpy(new_mem, list->data, list->Length * sizeof(uint32_t));
    if (new_mem == NULL) {
      return 1;
    }
    free(list->data);
    list->data = new_mem;
  }
  list->Length = newLength;
  return 0;
}

// ListInsert inserts `value` at `index` in `list`
// Inserting beyond `list->Length` fills the region with zeros
// Returns an int: if an error occured, the return value is non-zero
int ListInsert_ui32(List_ui32* list, size_t index, uint32_t value) {
  size_t newLength = (index <= list->Length) ? list->Length+1 : index+1;
  int err = ListVerifyCapacity_ui32(list, newLength);
  if (err) {
    return err;
  }
  uint32_t len = list->Length;
  if (index < len-1) {
    for (size_t j = len-1; j > index; j--) {
      list->data[j] = list->data[j-1];
      
    }
  }
  list->data[index] = value;
  return 0;
}

// ListInsert appends `value` to the end of `list`
// Returns an int: if an error occured, the return value is non-zero
int ListAppend_ui32(List_ui32* list, uint32_t value) {
  return ListInsert_ui32(list, list->Length, value);
}

// ListGet returns the value at `index` in the given `list`
uint32_t ListGet_ui32(List_ui32* list, size_t index) {
  assert(index < list->Length);
  return list->data[index];
}

// ListRemoves the value at `index` in `list`
// Returns an int: if an error occured, the return value is non-zero
// `index` < `list->Length` is an assertion and failure is not
// considered an error
void ListRemove_ui32(List_ui32* list, size_t index) {
  uint32_t len = list->Length;
  assert(index < len);
  if (len == 0) return;
  if (index == len-1) {
    list->data[index] = 0; // zero it
  } else {
    for (size_t i = index; i+1 < len; i++) {
      list->data[i] = list->data[i+1];
    }
    list->data[len-1] = 0; // zero the chopped-off element
  }
  list->Length--;
}

char* ListString_ui32(List_ui32* list) {
  char* str = malloc(1);
  str[0] = '[';
  size_t end = 1, len = list->Length;
  for (size_t i = 0; i < len; i++) {
    size_t numBytes = 0;
    uint32_t value = ListGet_ui32(list, i);
    uint32_t copy = value;
    if (copy == 0) {
      numBytes = 1;
    } else {
      while (copy > 0) {
	numBytes++;
	copy /= 10;
      }
    }
    if (i < len - 1) {
      str = realloc(str, end + numBytes + 2);
      snprintf(&str[end], numBytes + 3, "%u, ", value);
      end += numBytes + 2;
    } else {
      str = realloc(str, end + numBytes);
      snprintf(&str[end], numBytes + 1, "%u", value);
      end += numBytes;
    }
  }
  str = realloc(str, end + 2);
  str[end] = ']';
  str[end+1] = '\0';
  return str;
}
