#include "unity.h"
#include "../include/es_file.h"
#include <string.h>
#include <stdlib.h>

// Test: Extract filename from full path
void test_GetFilenameFromPath_SimpleFile(void) {
	const char* path = "C:\\Users\\test\\document.txt";
	const char* result = es_get_filename_from_path(path);
	TEST_ASSERT_NOT_NULL(result);
	TEST_ASSERT_EQUAL_STRING("document.txt", result);
}

void test_GetFilenameFromPath_WithoutPath(void) {
	const char* filename = "test.txt";
	const char* result = es_get_filename_from_path(filename);
	TEST_ASSERT_NOT_NULL(result);
	TEST_ASSERT_EQUAL_STRING("test.txt", result);
}

void test_GetFilenameFromPath_UnixPath(void) {
	const char* path = "/home/user/file.c";
	const char* result = es_get_filename_from_path(path);
	TEST_ASSERT_NOT_NULL(result);
	TEST_ASSERT_EQUAL_STRING("file.c", result);
}

void test_GetFilenameFromPath_EmptyString(void) {
	const char* path = "";
	const char* result = es_get_filename_from_path(path);
	// Empty string should return NULL
	TEST_ASSERT_NULL(result);
}

// Test: Extract file extension
void test_GetFileExtension_TxtFile(void) {
	const char* filename = "document.txt";
	const char* result = es_get_file_extension(filename);
	TEST_ASSERT_NOT_NULL(result);
	TEST_ASSERT_EQUAL_STRING("txt", result);
}

void test_GetFileExtension_WithPath(void) {
	const char* path = "C:\\Users\\test\\archive.tar.gz";
	const char* result = es_get_file_extension(path);
	TEST_ASSERT_NOT_NULL(result);
	// Should return the last extension
	TEST_ASSERT_EQUAL_STRING("gz", result);
}

void test_GetFileExtension_NoExtension(void) {
	const char* filename = "Makefile";
	const char* result = es_get_file_extension(filename);
	// File with no extension should return NULL
	TEST_ASSERT_NULL(result);
}

void test_GetFileExtension_CSourceFile(void) {
	const char* filename = "library.c";
	const char* result = es_get_file_extension(filename);
	TEST_ASSERT_NOT_NULL(result);
	TEST_ASSERT_EQUAL_STRING("c", result);
}

// Test: File operations return appropriate error codes
void test_CopyFile_ReturnsInt(void) {
	// This test verifies the function returns non-zero for non-existent source
	const char* dst = "dst.txt";
	const char* src = "nonexistent_source.txt";
	int result = es_copy_file(dst, src);
	// Should return non-zero for non-existent source file
	TEST_ASSERT_NOT_EQUAL(0, result);
}
