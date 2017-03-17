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

static void GetHashTest()
{
	printf("\n\nTest String 1: "
		"323130393837363534333231303938373635343332313039383736353433323130393837363534333231303938373635343332313039383736353433323130\n\n");
	Init(CTX, 512);
	Update(CTX, test_string_1, sizeof test_string_1);
	Final(CTX);
	HashPrint(CTX);
	Init(CTX, 256);
	Update(CTX, test_string_1, sizeof test_string_1);
	Final(CTX);
	HashPrint(CTX);

	printf("\n\nTest String 2: "
		"fbe2e5f0eee3c820fbeafaebef20fffbf0e1e0f0f520e0ed20e8ece0ebe5f0f2f120fff0eeec20f120faf2fee5e2202ce8f6f3ede220e8e6eee1e8f0f2d1202ce8f0f2e5e220e5d1\n\n");
	Init(CTX, 512);
	Update(CTX, test_string_1, sizeof test_string_2);
	Final(CTX);
	HashPrint(CTX);
	Init(CTX, 256);
	Update(CTX, test_string_1, sizeof test_string_2);
	Final(CTX);
	HashPrint(CTX);
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

	GetHashTest();
	GetHashFile("test.txt", 512);
	GetHashFile("test.txt", 256);
	
	return 0;
}