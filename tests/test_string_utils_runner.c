#include "unity.h"

// Forward declare test functions
#ifdef _WIN32
extern void test_Utf8ToWstr_SimpleASCII(void);
extern void test_Utf8ToWstr_EmptyString(void);
extern void test_WstrToUtf8_SimpleASCII(void);
extern void test_WstrToUtf8_EmptyString(void);
extern void test_Utf8ToAcp_SimpleASCII(void);
extern void test_Utf8ToAcp_EmptyString(void);
extern void test_RoundTrip_Utf8ToWstrToUtf8(void);
#endif

extern void test_Ellipsize_LongString(void);
extern void test_Ellipsize_ShortString(void);
extern void test_Ellipsize_ExactSize(void);
extern void test_Ellipsize_EmptyString(void);

// Setup and teardown functions required by Unity
void setUp(void) {
}

void tearDown(void) {
}

int main(int argc, char *argv[]) {
	UNITY_BEGIN();

#ifdef _WIN32
	RUN_TEST(test_Utf8ToWstr_SimpleASCII);
	RUN_TEST(test_Utf8ToWstr_EmptyString);
	RUN_TEST(test_WstrToUtf8_SimpleASCII);
	RUN_TEST(test_WstrToUtf8_EmptyString);
	RUN_TEST(test_Utf8ToAcp_SimpleASCII);
	RUN_TEST(test_Utf8ToAcp_EmptyString);
	RUN_TEST(test_RoundTrip_Utf8ToWstrToUtf8);
#endif

	RUN_TEST(test_Ellipsize_LongString);
	RUN_TEST(test_Ellipsize_ShortString);
	RUN_TEST(test_Ellipsize_ExactSize);
	RUN_TEST(test_Ellipsize_EmptyString);

	return UNITY_END();
}
