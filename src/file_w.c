#include "pch.h"

int es_copy_file_w(const wchar_t* restrict dst_filename,
	const wchar_t* restrict src_filename)
{
	if (!src_filename || !*src_filename || !dst_filename || !*dst_filename
		|| wcscmp(src_filename, dst_filename) == 0)
		return EINVAL;

	FILE* src = _wfopen(src_filename, L"rb");
	if (!src)
		return errno;

	FILE* dst = _wfopen(dst_filename, L"wb");
	if (!dst) {
		int rc = errno;
		fclose(src);
		return rc;
	}

	return es_do_copy_file(dst, src);
}
