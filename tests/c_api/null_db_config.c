// SPDX-License-Identifier: BSD-3-Clause
/* Copyright 2020, Intel Corporation */

#include <libpmemkv.h>

#include "unittest.h"
#include <string.h>

/* Test if null can be passed as db to pmemkv_* functions */
void check_null_db_test()
{
	size_t cnt;
	const char *key1 = "key1";
	const char *value1 = "value1";
	const char *key2 = "key2";
	char val[10];

	int s = pmemkv_count_all(NULL, &cnt);
	(void)s;
	UT_ASSERT(s == PMEMKV_STATUS_INVALID_ARGUMENT);

	s = pmemkv_count_above(NULL, key1, strlen(key1), &cnt);
	UT_ASSERT(s == PMEMKV_STATUS_INVALID_ARGUMENT);

	s = pmemkv_count_below(NULL, key1, strlen(key1), &cnt);
	UT_ASSERT(s == PMEMKV_STATUS_INVALID_ARGUMENT);

	s = pmemkv_count_between(NULL, key1, strlen(key1), key2, strlen(key2), &cnt);
	UT_ASSERT(s == PMEMKV_STATUS_INVALID_ARGUMENT);

	s = pmemkv_get_all(NULL, NULL, NULL);
	UT_ASSERT(s == PMEMKV_STATUS_INVALID_ARGUMENT);

	s = pmemkv_get_above(NULL, key1, strlen(key1), NULL, NULL);
	UT_ASSERT(s == PMEMKV_STATUS_INVALID_ARGUMENT);

	s = pmemkv_get_below(NULL, key1, strlen(key1), NULL, NULL);
	UT_ASSERT(s == PMEMKV_STATUS_INVALID_ARGUMENT);

	s = pmemkv_get_between(NULL, key1, strlen(key1), key2, strlen(key2), NULL, NULL);
	UT_ASSERT(s == PMEMKV_STATUS_INVALID_ARGUMENT);

	s = pmemkv_exists(NULL, key1, strlen(key1));
	UT_ASSERT(s == PMEMKV_STATUS_INVALID_ARGUMENT);

	s = pmemkv_get(NULL, key1, strlen(key1), NULL, NULL);
	UT_ASSERT(s == PMEMKV_STATUS_INVALID_ARGUMENT);

	s = pmemkv_get_copy(NULL, key1, strlen(key1), val, 10, &cnt);
	UT_ASSERT(s == PMEMKV_STATUS_INVALID_ARGUMENT);

	s = pmemkv_put(NULL, key1, strlen(key1), value1, strlen(value1));
	UT_ASSERT(s == PMEMKV_STATUS_INVALID_ARGUMENT);

	s = pmemkv_remove(NULL, key1, strlen(key1));
	UT_ASSERT(s == PMEMKV_STATUS_INVALID_ARGUMENT);

	s = pmemkv_defrag(NULL, 0, 100);
	UT_ASSERT(s == PMEMKV_STATUS_INVALID_ARGUMENT);
}

void null_config_test(const char *engine)
{
	pmemkv_config *empty_cfg = NULL;
	pmemkv_db *db = NULL;
	int s = pmemkv_open(engine, empty_cfg, &db);
	UT_ASSERT(s == PMEMKV_STATUS_INVALID_ARGUMENT);
}

int main(int argc, char *argv[])
{
	START();

	if (argc < 2)
		UT_FATAL("usage %s: engine", argv[0]);

	check_null_db_test();
	null_config_test(argv[1]);

	return 0;
}
