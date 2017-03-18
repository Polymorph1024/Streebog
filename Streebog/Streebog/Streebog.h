#include <stdint.h>
#include <string.h>
#include <malloc.h>
#include "Streebog_consts.h"

typedef struct HashContext
{
	uint8_t buffer[64];	// буфер для очередного блока хешируемого сообщения
	uint8_t hash[64];	// итоговый результат вычислений
	uint8_t h[64];		// промежуточный результат вычислений
	uint8_t N[64];
	uint8_t Sigma[64];	// контрольная сумма
	uint8_t v_0[64];	// инициализационный вектор
	uint8_t v_512[64];	// инициализационный вектор
	size_t buf_size;	// размер оставшейся части сообщения, (которая оказалась меньше очередных 64 байт)
	int hash_size;		// размер хеш-суммы (512 или 256 бит)
} HashContext;


void Hash_256(HashContext *CTX, const uint8_t *m, size_t len);
void Hash_512(HashContext *CTX, const uint8_t *m, size_t len);