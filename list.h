#include <stdint.h>

typedef struct {
  size_t Length, capacity;
  // not using zero-length struct
  // because we want to be able to allocate more memory
  // without having the end user to having to worry
  // about the address of the data structure changing
  uint32_t* data;
} List_ui32;

List_ui32* NewList_ui32(void);
void DestroyList_ui32(List_ui32* list);
int ListInsert_ui32(List_ui32* list, size_t index, uint32_t value);
int ListAppend_ui32(List_ui32* list, uint32_t value);
uint32_t ListGet_ui32(List_ui32* list, size_t index);
void ListRemove_ui32(List_ui32* list, size_t index);
char* ListString_ui32(List_ui32* list);
