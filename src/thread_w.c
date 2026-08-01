#include "pch.h"

#include <ecomm/strutils.h>

int es_set_current_thread_name(const char* restrict name)
{
	int rc;
	if (!name || !*name)
		return EINVAL;

	wchar_t* wname = utf8_to_wstr(name, &rc);

	if (!wname)
		return rc;

	HRESULT hr = SetThreadDescription(GetCurrentThread(), wname);

	free(wname);

	if (FAILED(hr))
		return hr != E_NOTIMPL ? EIO : ENOSYS;

	return 0;
}
