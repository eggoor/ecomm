#include "pch.h"

#include <ecomm/defs.h>

#include "file.h"

const char* es_get_file_extension(const char* restrict filename)
{
	if (!filename)
		return NULL;

	const char* dot = strrchr(filename, '.');
	if (!dot || dot == filename)
		return NULL;

	return dot + 1;
}

int es_copy_file(const char* restrict dst_filename,
	const char* restrict src_filename)
{
	if (!src_filename || !*src_filename || !dst_filename || !*dst_filename
		|| strcmp(src_filename, dst_filename) == 0)
		return EINVAL;

	FILE* src = fopen(src_filename, "rb");
	if (!src)
		return errno;

	FILE* dst = fopen(dst_filename, "wb");
	if (!dst) {
		int rc = errno;
		fclose(src);
		return rc;
	}

	return es_do_copy_file(dst, src);
}

char* es_replace_file_extension(const char* restrict_ filename,
	const char* restrict_ new_ext, int* prc)
{
	if (!filename || !*filename || !new_ext || !*new_ext) {
		if (prc)
			*prc = EINVAL;
		return NULL;
	}

	const char *dot = strrchr(filename, '.');
	if (!dot || dot == filename) {
		if (prc)
			*prc = EINVAL;
		return NULL;
	}

	if (*new_ext == '.')
		++new_ext;

	size_t filename_len = dot - filename;
	size_t new_ext_len = strlen(new_ext);

	char* new_filename = malloc(filename_len + new_ext_len + 2);
	if (!new_filename) {
		if (prc)
			*prc = ENOMEM;
		return NULL;
	}

	memcpy(new_filename, filename, filename_len);
	new_filename[filename_len] = '.';
	strcpy(new_filename + filename_len + 1, new_ext);

	if (prc)
		*prc = 0;

	return new_filename;
}

int es_file_read(const char* restrict filename, char* restrict* restrict buffer,
	size_t* size)
{
	if (!filename || !*filename || !buffer || !size)
		return EINVAL;

	FILE* file = fopen(filename, "rb");
	if (!file)
		return errno;

	if (fseek(file, 0, SEEK_END) != 0) {
		int rc = errno;
		fclose(file);
		return rc;
	}

	long file_size = ftell(file);
	if (file_size < 0) {
		int rc = errno;
		fclose(file);
		return rc;
	}

	size_t usize = (size_t)file_size;

	if (fseek(file, 0, SEEK_SET) != 0) {
		int rc = errno;
		fclose(file);
		return rc;
	}

	char* data = malloc(usize + 1);
	if (!data) {
		fclose(file);
		return ENOMEM;
	}

	if (fread(data, 1, usize, file) != usize) {
		int rc = ferror(file) ? (errno ? errno : EIO) : EIO;
		free(data);
		fclose(file);
		return rc;
	}

	data[usize] = '\0';

	if (fclose(file) == EOF) {
		int rc = errno ? errno : EIO;
		free(data);
		return rc;
	}

	*buffer = data;
	*size = usize;

	return 0;
}

const char* es_get_filename_from_path(const char* restrict path) {
	if (!path || !*path)
		return NULL;

	const char* last_slash = strrchr(path, '/');
	const char* last_backslash = strrchr(path, '\\');

	const char* filename = path;
	if (last_slash != NULL && last_backslash != NULL) {
		filename = (last_slash > last_backslash) ? last_slash + 1 : last_backslash + 1;
	}
	else if (last_slash != NULL) {
		filename = last_slash + 1;
	}
	else if (last_backslash != NULL) {
		filename = last_backslash + 1;
	}

	return *filename == '\0' ? NULL : filename;
}

int es_confirm_overwrite(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
        return 1;
    fclose(fp);

    printf("File \"%s\" already exists. Overwrite? [y/N]: ", filename);
    fflush(stdout);

    int answer = getchar();

    int c;
	if (answer != '\n')
		while ((c = getchar()) != '\n' && c != EOF);

    return tolower((unsigned char)answer) == 'y';
}

int es_do_copy_file(FILE* restrict dst, FILE* restrict src)
{
	int rc;
	char buffer[4096];
	size_t bytes_read;

	while ((bytes_read = fread(buffer, 1, sizeof(buffer), src)) > 0) {
		if (fwrite(buffer, 1, bytes_read, dst) != bytes_read) {
			rc = errno ? errno : EIO;
			fclose(src);
			if (fclose(dst) == EOF && rc == 0)
				rc = errno ? errno : EIO;
			return rc;
		}
	}

	if (ferror(src))
		rc = errno ? errno : EIO;
	else
		rc = 0;

	fclose(src);
	if (fclose(dst) == EOF && rc == 0)
		rc = errno ? errno : EIO;

	return rc;
}
