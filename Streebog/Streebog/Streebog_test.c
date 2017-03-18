#include <stdio.h>
#include <string.h>
#include "Streebog.h"
#include "Streebog_test.h"

#define FILE_BUFFER_SIZE 4096
#define DEFAULT_HASH_SIZE 512

HashContext *CTX;

static void HashPrint(HashContext *CTX)
{
	printf("%d bit hash sum: \n", CTX->hash_size);
	if (CTX->hash_size == 256)
		for (int i = 32; i < 64; i++)
			printf("%02x", CTX->hash[i]);
	else
		for (int i = 0; i < 64; i++)
			printf("%02x", CTX->hash[i]);
	printf("\n\n");
}

static void GetHashString(const char *str, int hash_size)
{
	uint8_t *buffer;
	buffer = malloc(strlen(str));
	memcpy(buffer, str, strlen(str));
	Init(CTX, hash_size);
	Update(CTX, buffer, strlen(str));
	Final(CTX);
	printf("\n\nString: %s\n", str);
	HashPrint(CTX);
}

static void GetHashFile(const char *file_name, int hash_size)
{
	FILE *file;
	uint8_t *buffer;
	size_t len;
	Init(CTX, hash_size);
	if ((file = fopen(file_name, "rb")) != NULL)
	{
		buffer = malloc((size_t)FILE_BUFFER_SIZE);
		while ((len = fread(buffer, (size_t)1, (size_t)FILE_BUFFER_SIZE, file)))
			Update(CTX, buffer, len);
		free(buffer);
		Final(CTX);
		fclose(file);
		printf("\n\nFile name: %s\n", file_name);
		HashPrint(CTX);
	}
	else
		printf("File error: %s\n", file_name);
}

int main()
{
	CTX = (HashContext*)(malloc(sizeof(HashContext)));

	printf("GOST 34.11 - 2012 \"Streebog\"\n");

	GetHashString(test_string_1, 512);
	GetHashString(test_string_1, 256);
	GetHashString(test_string_2, 512);
	GetHashString(test_string_2, 256);
	GetHashFile(test_file_name, 512);
	GetHashFile(test_file_name, 256);
	
	return 0;
}