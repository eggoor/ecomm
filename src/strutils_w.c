#include "pch.h"

char* wstr_to_utf8(const wchar_t* const restrict wstr, int* prc)
{	
	char* str = NULL;
	int rc = 0;

	if (!wstr || !*wstr) {
		rc = EINVAL;
		goto end;
	}

	int buf_size = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);

	if (!buf_size) {
		rc = EILSEQ;
		goto end;
	}

	str = malloc(buf_size);

	if (!str) {
		rc = ENOMEM;
		goto end;
	}

	buf_size = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, buf_size, NULL, NULL);

	if (!buf_size) {
		free(str);
		str = NULL;
		rc = EILSEQ;
	}

end:
	if (prc)
		*prc = rc;

	return str;
}

wchar_t* utf8_to_wstr(const char* const restrict str, int* prc)
{
	wchar_t* wstr = NULL;
	int rc = 0;

	if (!str || !*str) {
		rc = EINVAL;
		goto end;
	}

	int max_char = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);

	if (!max_char) {
		rc = EILSEQ;
		goto end;
	}

	wstr = malloc(sizeof(wchar_t) * max_char);

	if (!wstr) {
		rc = ENOMEM;
		goto end;
	}

	max_char = MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, max_char);

	if (0 == max_char) {
		free(wstr);
		wstr = NULL;
		rc = EILSEQ;
	}

end:
	if (prc)
		*prc = rc;

	return wstr;
}

char* utf8_to_acp(const char* const restrict str, int* prc)
{
	char* acp = NULL;
	int rc = 0;

	if (!str || !*str) {
		rc = EINVAL;
		goto end;
	}

	int max_char = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS,
		str, -1, NULL, 0);

	if (!max_char) {
		rc = EILSEQ;
		goto end;
	}

	wchar_t* wstr = malloc(sizeof(*wstr) * max_char);

	if (!wstr) {
		rc = ENOMEM;
		goto end;
	}

	if (!MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS,
		str, -1, wstr, max_char))
	{
		free(wstr);
		wstr = NULL;
		rc = EILSEQ;
		goto end;
	}

	int alen = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);

	if (alen <= 0) {
		free(wstr);
		rc = EILSEQ;
		goto end;
	}

	acp = malloc(alen);
	if (!acp) {
		free(wstr);
		rc = ENOMEM;
		goto end;
	}

	if (!WideCharToMultiByte(CP_ACP, 0, wstr, -1, acp, alen, NULL, NULL)) {
		free(wstr);
		free(acp);
		rc = EILSEQ;
		goto end;
	}

	free(wstr);

end:
	if (prc)
		*prc = rc;

	return acp;
}

