#include "unity.h"

// Forward declare test functions
extern void test_GetFilenameFromPath_SimpleFile(void);
extern void test_GetFilenameFromPath_WithoutPath(void);
extern void test_GetFilenameFromPath_UnixPath(void);
extern void test_GetFilenameFromPath_EmptyString(void);
extern void test_GetFileExtension_TxtFile(void);
extern void test_GetFileExtension_WithPath(void);
extern void test_GetFileExtension_NoExtension(void);
extern void test_GetFileExtension_CSourceFile(void);
extern void test_CopyFile_ReturnsInt(void);

// Setup and teardown functions required by Unity
void setUp(void) {
}

void tearDown(void) {
}

int main(int argc, char *argv[]) {
	UNITY_BEGIN();

	RUN_TEST(test_GetFilenameFromPath_SimpleFile);
	RUN_TEST(test_GetFilenameFromPath_WithoutPath);
	RUN_TEST(test_GetFilenameFromPath_UnixPath);
	RUN_TEST(test_GetFilenameFromPath_EmptyString);
	RUN_TEST(test_GetFileExtension_TxtFile);
	RUN_TEST(test_GetFileExtension_WithPath);
	RUN_TEST(test_GetFileExtension_NoExtension);
	RUN_TEST(test_GetFileExtension_CSourceFile);
	RUN_TEST(test_CopyFile_ReturnsInt);

	return UNITY_END();
}
