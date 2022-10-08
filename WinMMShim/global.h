#pragma once

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int patch_return_zero(void);
int patch_return_one(void);
void patch_memory_nop(void* addr, unsigned int sz);
void patch_memory_buffer(void* addr, unsigned char* buffer, unsigned int sz);
void detour_jmp(void* new_addr, void* addr);
void detour_call(void* new_addr, void* addr);
void detour_function_ds(void* new_adr, void* addr);
void patch_memory_str(void* addr, char* str);
BOOL Hook_IAT_Name(char* dll_name, char* func_name, DWORD replacement_function_ptr);
BOOL Hook_IAT_Ordinal(char* dll_name, char* func_name, unsigned int ordinal, DWORD replacement_function_ptr);
