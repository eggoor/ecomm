#include <string.h>
#include <stdlib.h>
#include <wchar.h>

#include <ecomm/strutils.h>

#include "unity.h"

// Test: UTF-8 to Wide String conversion
#ifdef _WIN32
void test_Utf8ToWstr_SimpleASCII(void) {
	int rc = 0;
	const char* utf8_str = "Hello";
	wchar_t* wstr = utf8_to_wstr(utf8_str, &rc);

	TEST_ASSERT_NOT_NULL(wstr);
	TEST_ASSERT_EQUAL_INT(0, rc);

	free(wstr);
}

void test_Utf8ToWstr_EmptyString(void) {
	int rc = 0;
	const char* utf8_str = "";
	wchar_t* wstr = utf8_to_wstr(utf8_str, &rc);

	// Empty string should return NULL and set error code
	TEST_ASSERT_NULL(wstr);
	TEST_ASSERT_NOT_EQUAL(0, rc); // Should have an error
}

// Test: Wide String to UTF-8 conversion
void test_WstrToUtf8_SimpleASCII(void) {
	int rc = 0;
	const wchar_t* wstr = L"World";
	char* utf8_str = wstr_to_utf8(wstr, &rc);

	TEST_ASSERT_NOT_NULL(utf8_str);
	TEST_ASSERT_EQUAL_INT(0, rc);
	TEST_ASSERT_EQUAL_STRING("World", utf8_str);

	free(utf8_str);
}

void test_WstrToUtf8_EmptyString(void) {
	int rc = 0;
	const wchar_t* wstr = L"";
	char* utf8_str = wstr_to_utf8(wstr, &rc);

	// Empty string should return NULL
	TEST_ASSERT_NULL(utf8_str);
}

// Test: UTF-8 to ACP (ANSI Code Page) conversion
void test_Utf8ToAcp_SimpleASCII(void) {
	int rc = 0;
	const char* utf8_str = "Test";
	char* acp_str = utf8_to_acp(utf8_str, &rc);

	TEST_ASSERT_NOT_NULL(acp_str);
	TEST_ASSERT_EQUAL_INT(0, rc);
	TEST_ASSERT_EQUAL_STRING("Test", acp_str);

	free(acp_str);
}

void test_Utf8ToAcp_EmptyString(void) {
	int rc = 0;
	const char* utf8_str = "";
	char* acp_str = utf8_to_acp(utf8_str, &rc);

	// Empty string should return NULL
	TEST_ASSERT_NULL(acp_str);
}

// Test: Round-trip conversions
void test_RoundTrip_Utf8ToWstrToUtf8(void) {
	int rc = 0;
	const char* original = "RoundTrip";

	// Convert UTF-8 to Wide
	wchar_t* wstr = utf8_to_wstr(original, &rc);
	TEST_ASSERT_EQUAL_INT(0, rc);
	TEST_ASSERT_NOT_NULL(wstr);

	// Convert back to UTF-8
	char* converted = wstr_to_utf8(wstr, &rc);
	TEST_ASSERT_EQUAL_INT(0, rc);
	TEST_ASSERT_NOT_NULL(converted);

	TEST_ASSERT_EQUAL_STRING(original, converted);

	free(wstr);
	free(converted);
}
#endif // _WIN32

// Test: String ellipsization (truncation with ...)
void test_Ellipsize_LongString(void) {
	char dst[20];
	const char* src = "This is a very long string that needs truncation";
	int result = es_ellipsize(dst, sizeof(dst), src);

	// Should return 0 or appropriate status
	TEST_ASSERT_GREATER_OR_EQUAL(result, 0);
	TEST_ASSERT_TRUE(strlen(dst) <= sizeof(dst) - 1);
}

void test_Ellipsize_ShortString(void) {
	char dst[50];
	const char* src = "Short";
	int result = es_ellipsize(dst, sizeof(dst), src);

	TEST_ASSERT_GREATER_OR_EQUAL(result, 0);
	TEST_ASSERT_EQUAL_STRING("Short", dst);
}

void test_Ellipsize_ExactSize(void) {
	char dst[10];
	const char* src = "Exact";
	int result = es_ellipsize(dst, sizeof(dst), src);

	TEST_ASSERT_GREATER_OR_EQUAL(result, 0);
	TEST_ASSERT_TRUE(strlen(dst) <= sizeof(dst) - 1);
}

void test_Ellipsize_EmptyString(void) {
	char dst[20];
	const char* src = "";
	int result = es_ellipsize(dst, sizeof(dst), src);

	TEST_ASSERT_GREATER_OR_EQUAL(result, 0);
	TEST_ASSERT_EQUAL_STRING("", dst);
}
