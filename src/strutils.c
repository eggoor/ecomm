#include "pch.h"

int es_ellipsize(char* restrict dst, size_t dst_size,
	const char* restrict src)
{
	if (!dst || !src || dst_size < 2)
		return EINVAL;

	size_t src_len = strlen(src);

	if (src_len < dst_size) {
		memcpy(dst, src, src_len + 1);
		return 0;
	}

	/* Cannot even fit "..." */
	if (dst_size <= 4) {
		memcpy(dst, src, dst_size - 1);
		dst[dst_size - 1] = '\0';
		return 0;
	}

	const size_t dots = 3;
	const size_t avail = dst_size - 1 - dots;

	const size_t prefix = (avail + 1) / 2;
	const size_t suffix = avail / 2;

	memcpy(dst, src, prefix);
	memcpy(dst + prefix, "...", dots);
	memcpy(dst + prefix + dots, src + src_len - suffix, suffix);

	dst[dst_size - 1] = '\0';

	return 0;
}
