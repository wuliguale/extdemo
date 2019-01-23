/*
 * base_object_pool_config.h
 * BaseObjectPoolConfig
 *
 *  Created on: 2019年1月20日
 *      Author: sam
 */

#ifndef EXT_EXTDEMO_BASE_OBJECT_POOL_CONFIG_H_
#define EXT_EXTDEMO_BASE_OBJECT_POOL_CONFIG_H_

#endif /* EXT_EXTDEMO_BASE_OBJECT_POOL_CONFIG_H_ */

#include <php.h>

#ifndef NULL
#define NULL   ((void *) 0)
#endif

long base_object_pool_config_default_lifo = 1;
long base_object_pool_config_default_fairness = 0;
long base_object_pool_config_default_max_wait_millis = -1;
long base_object_pool_config_default_min_evictable_idle_time_millis = 1000L * 60L * 30;
long base_object_pool_config_default_soft_min_evictable_idle_time_millis = -1;
long base_object_pool_config_default_num_tests_per_eviction_run = 3;
long base_object_pool_config_default_test_on_create = 0;
long base_object_pool_config_default_test_on_borrow = 0;
long base_object_pool_config_default_test_on_return = 0;
long base_object_pool_config_default_test_while_idle = 0;
long base_object_pool_config_default_time_between_eviction_runs_millis = -1;
long base_object_pool_config_default_block_when_exhausted = 1;
long base_object_pool_config_default_jmx_enable = 1;
char *base_object_pool_config_default_jmx_name_prefix = "pool";
char *base_object_pool_config_default_jmx_name_base = "null";
char *base_object_pool_config_default_eviction_policy_class_name = "org.apache.commons.pool2.impl.DefaultEvictionPolicy";

zend_class_entry *base_object_pool_config_ce;

PHP_METHOD(base_object_pool_config, getLifo);
PHP_METHOD(base_object_pool_config, setLifo);
PHP_METHOD(base_object_pool_config, getFairness);
PHP_METHOD(base_object_pool_config, setFairness);
PHP_METHOD(base_object_pool_config, getMaxWaitMillis);
PHP_METHOD(base_object_pool_config, setMaxWaitMillis);
PHP_METHOD(base_object_pool_config, getMinEvictableIdleTimeMillis);
PHP_METHOD(base_object_pool_config, setMinEvictableIdleTimeMillis);
PHP_METHOD(base_object_pool_config, getSoftMinEvictableIdleTimeMillis);
PHP_METHOD(base_object_pool_config, setSoftMinEvictableIdleTimeMillis);
PHP_METHOD(base_object_pool_config, getNumTestsPerEvictionRun);
PHP_METHOD(base_object_pool_config, setNumTestsPerEvictionRun);
PHP_METHOD(base_object_pool_config, getTestOnCreate);
PHP_METHOD(base_object_pool_config, setTestOnCreate);
PHP_METHOD(base_object_pool_config, getTestOnBorrow);
PHP_METHOD(base_object_pool_config, setTestOnBorrow);
PHP_METHOD(base_object_pool_config, getTestOnReturn);
PHP_METHOD(base_object_pool_config, setTestOnReturn);
PHP_METHOD(base_object_pool_config, getTestWhileIdle);
PHP_METHOD(base_object_pool_config, setTestWhileIdle);
PHP_METHOD(base_object_pool_config, getTimeBetweenEvictionRunsMillis);
PHP_METHOD(base_object_pool_config, setTimeBetweenEvictionRunsMillis);
PHP_METHOD(base_object_pool_config, getBlockWhenExhausted);
PHP_METHOD(base_object_pool_config, setBlockWhenExhausted);
PHP_METHOD(base_object_pool_config, getJmxEnabled);
PHP_METHOD(base_object_pool_config, setJmxEnabled);
PHP_METHOD(base_object_pool_config, getJmxNameBase);
PHP_METHOD(base_object_pool_config, setJmxNameBase);
PHP_METHOD(base_object_pool_config, getJmxNamePrefix);
PHP_METHOD(base_object_pool_config, setJmxNamePrefix);
PHP_METHOD(base_object_pool_config, getEvictionPolicyClassName);
PHP_METHOD(base_object_pool_config, setEvictionPolicyClassName);





zend_function_entry base_object_pool_config_method[] = {
		PHP_ME(base_object_pool_config, getLifo, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, setLifo, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, getFairness, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, setFairness, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, getMaxWaitMillis, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, setMaxWaitMillis, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, getMinEvictableIdleTimeMillis, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, setMinEvictableIdleTimeMillis, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, getSoftMinEvictableIdleTimeMillis, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, setSoftMinEvictableIdleTimeMillis, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, getNumTestsPerEvictionRun, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, setNumTestsPerEvictionRun, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, getTestOnCreate, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, setTestOnCreate, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, getTestOnBorrow, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, setTestOnBorrow, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, getTestOnReturn, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, setTestOnReturn, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, getTestWhileIdle, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, setTestWhileIdle, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, getTimeBetweenEvictionRunsMillis, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, setTimeBetweenEvictionRunsMillis, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, getBlockWhenExhausted, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, setBlockWhenExhausted, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, getJmxEnabled, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, setJmxEnabled, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, getJmxNameBase, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, setJmxNameBase, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, getJmxNamePrefix, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, setJmxNamePrefix, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, getEvictionPolicyClassName, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(base_object_pool_config, setEvictionPolicyClassName, NULL, ZEND_ACC_PUBLIC)
	    PHP_FE_END
};


PHP_METHOD(base_object_pool_config, getLifo)
{
	zval *ret;
	ret = zend_read_property(base_object_pool_config_ce, getThis(), "lifo", strlen("lifo"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(base_object_pool_config, setLifo)
{
	zend_bool lifo;
	long lifo_long;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &lifo) == FAILURE) {
		RETURN_FALSE;
	}

	lifo_long = lifo ? 1 : 0;
	zend_update_property_bool(base_object_pool_config_ce, getThis(), "lifo", strlen("lifo"), lifo_long TSRMLS_DC);
	RETURN_TRUE;
}


PHP_METHOD(base_object_pool_config, getFairness)
{
	zval *ret;
	ret = zend_read_property(base_object_pool_config_ce, getThis(), "fairness", strlen("fairness"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(base_object_pool_config, setFairness)
{
	zend_bool fairness;
	long fairness_long;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &fairness) == FAILURE) {
		RETURN_FALSE;
	}

	fairness_long = fairness ? 1 : 0;
	zend_update_property_bool(base_object_pool_config_ce, getThis(), "fairness", strlen("fairness"), fairness_long TSRMLS_DC);
	RETURN_TRUE;
}


PHP_METHOD(base_object_pool_config, getMaxWaitMillis)
{
	zval *ret;
	ret = zend_read_property(base_object_pool_config_ce, getThis(), "maxWaitMillis", strlen("maxWaitMillis"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(base_object_pool_config, setMaxWaitMillis)
{
	long max_wait_millis;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &max_wait_millis) == FAILURE) {
		RETURN_FALSE;
	}

	zend_update_property_long(base_object_pool_config_ce, getThis(), "maxWaitMillis", strlen("maxWaitMillis"), max_wait_millis TSRMLS_DC);
	RETURN_TRUE;
}


PHP_METHOD(base_object_pool_config, getMinEvictableIdleTimeMillis)
{
	zval *ret;
	ret = zend_read_property(base_object_pool_config_ce, getThis(), "minEvictableIdleTimeMillis", strlen("minEvictableIdleTimeMillis"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(base_object_pool_config, setMinEvictableIdleTimeMillis)
{
	long min_evictable_idle_time_millis;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &min_evictable_idle_time_millis) == FAILURE) {
		RETURN_FALSE;
	}

	zend_update_property_long(base_object_pool_config_ce, getThis(), "minEvictableIdleTimeMillis", strlen("minEvictableIdleTimeMillis"), min_evictable_idle_time_millis TSRMLS_DC);
	RETURN_TRUE;
}


PHP_METHOD(base_object_pool_config, getSoftMinEvictableIdleTimeMillis)
{
	zval *ret;
	ret = zend_read_property(base_object_pool_config_ce, getThis(), "softMinEvictableIdleTimeMillis", strlen("softMinEvictableIdleTimeMillis"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(base_object_pool_config, setSoftMinEvictableIdleTimeMillis)
{
	long soft_min_evictable_idle_time_millis;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &soft_min_evictable_idle_time_millis) == FAILURE) {
		RETURN_FALSE;
	}

	zend_update_property_long(base_object_pool_config_ce, getThis(), "softMinEvictableIdleTimeMillis", strlen("softMinEvictableIdleTimeMillis"), soft_min_evictable_idle_time_millis TSRMLS_DC);
	RETURN_TRUE;
}


PHP_METHOD(base_object_pool_config, getNumTestsPerEvictionRun)
{
	zval *ret;
	ret = zend_read_property(base_object_pool_config_ce, getThis(), "numTestsPerEvictionRun", strlen("numTestsPerEvictionRun"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(base_object_pool_config, setNumTestsPerEvictionRun)
{
	long num_tests_per_eviction_run;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &num_tests_per_eviction_run) == FAILURE) {
		RETURN_FALSE;
	}

	zend_update_property_long(base_object_pool_config_ce, getThis(), "numTestsPerEvictionRun", strlen("numTestsPerEvictionRun"), num_tests_per_eviction_run TSRMLS_DC);
	RETURN_TRUE;
}


PHP_METHOD(base_object_pool_config, getTestOnCreate)
{
	zval *ret;
	ret = zend_read_property(base_object_pool_config_ce, getThis(), "testOnCreate", strlen("testOnCreate"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(base_object_pool_config, setTestOnCreate)
{
	zend_bool test_on_create;
	long test_on_create_long;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &test_on_create) == FAILURE) {
		RETURN_FALSE;
	}

	test_on_create_long = test_on_create ? 1 : 0;
	zend_update_property_bool(base_object_pool_config_ce, getThis(), "testOnCreate", strlen("testOnCreate"), test_on_create_long TSRMLS_DC);
	RETURN_TRUE;
}


PHP_METHOD(base_object_pool_config, getTestOnBorrow)
{
	zval *ret;
	ret = zend_read_property(base_object_pool_config_ce, getThis(), "testOnBorrow", strlen("testOnBorrow"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(base_object_pool_config, setTestOnBorrow)
{
	zend_bool test_on_borrow;
	long test_on_borrow_long;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &test_on_borrow) == FAILURE) {
		RETURN_FALSE;
	}

	test_on_borrow_long = test_on_borrow ? 1 : 0;
	zend_update_property_bool(base_object_pool_config_ce, getThis(), "testOnBorrow", strlen("testOnBorrow"), test_on_borrow_long TSRMLS_DC);
	RETURN_TRUE;
}


PHP_METHOD(base_object_pool_config, getTestOnReturn)
{
	zval *ret;
	ret = zend_read_property(base_object_pool_config_ce, getThis(), "testOnReturn", strlen("testOnReturn"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(base_object_pool_config, setTestOnReturn)
{
	zend_bool test_on_return;
	long test_on_return_long;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &test_on_return) == FAILURE) {
		RETURN_FALSE;
	}

	test_on_return_long = test_on_return ? 1 : 0;
	zend_update_property_bool(base_object_pool_config_ce, getThis(), "testOnReturn", strlen("testOnReturn"), test_on_return_long TSRMLS_DC);
	RETURN_TRUE;
}


PHP_METHOD(base_object_pool_config, getTestWhileIdle)
{
	zval *ret;
	ret = zend_read_property(base_object_pool_config_ce, getThis(), "testWhileIdle", strlen("testWhileIdle"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(base_object_pool_config, setTestWhileIdle)
{
	zend_bool test_while_idle;
	long test_while_idle_long;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &test_while_idle) == FAILURE) {
		RETURN_FALSE;
	}

	test_while_idle_long = test_while_idle ? 1 : 0;
	zend_update_property_bool(base_object_pool_config_ce, getThis(), "testWhileIdle", strlen("testWhileIdle"), test_while_idle_long TSRMLS_DC);
	RETURN_TRUE;
}

PHP_METHOD(base_object_pool_config, getTimeBetweenEvictionRunsMillis)
{
	zval *ret;
	ret = zend_read_property(base_object_pool_config_ce, getThis(), "timeBetweenEvictionRunsMillis", strlen("timeBetweenEvictionRunsMillis"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(base_object_pool_config, setTimeBetweenEvictionRunsMillis)
{
	long time_between_eviction_runs_millis;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &time_between_eviction_runs_millis) == FAILURE) {
		RETURN_FALSE;
	}

	zend_update_property_long(base_object_pool_config_ce, getThis(), "timeBetweenEvictionRunsMillis", strlen("timeBetweenEvictionRunsMillis"), time_between_eviction_runs_millis TSRMLS_DC);
	RETURN_TRUE;
}


PHP_METHOD(base_object_pool_config, getBlockWhenExhausted)
{
	zval *ret;
	ret = zend_read_property(base_object_pool_config_ce, getThis(), "blockWhenExhausted", strlen("blockWhenExhausted"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(base_object_pool_config, setBlockWhenExhausted)
{
	zend_bool block_when_exhausted;
	long block_when_exhausted_long;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &block_when_exhausted) == FAILURE) {
		RETURN_FALSE;
	}

	block_when_exhausted_long = block_when_exhausted ? 1 : 0;
	zend_update_property_bool(base_object_pool_config_ce, getThis(), "blockWhenExhausted", strlen("blockWhenExhausted"), block_when_exhausted_long TSRMLS_DC);
	RETURN_TRUE;
}


PHP_METHOD(base_object_pool_config, getJmxEnabled)
{
	zval *ret;
	ret = zend_read_property(base_object_pool_config_ce, getThis(), "jmxEnabled", strlen("jmxEnabled"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(base_object_pool_config, setJmxEnabled)
{
	zend_bool jmx_enabled;
	long jmx_enabled_long;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &jmx_enabled) == FAILURE) {
		RETURN_FALSE;
	}

	jmx_enabled_long = jmx_enabled ? 1 : 0;
	zend_update_property_bool(base_object_pool_config_ce, getThis(), "jmxEnabled", strlen("jmxEnabled"), jmx_enabled_long TSRMLS_DC);
	RETURN_TRUE;
}


PHP_METHOD(base_object_pool_config, getJmxNameBase)
{
	zval *ret;
	ret = zend_read_property(base_object_pool_config_ce, getThis(), "jmxNameBase", strlen("jmxNameBase"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(base_object_pool_config, setJmxNameBase)
{
	char *jmx_name_base;
	long jmx_name_base_length;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &jmx_name_base, &jmx_name_base_length) == FAILURE) {
		RETURN_FALSE;
	}

	zend_update_property_string(base_object_pool_config_ce, getThis(), "jmxNameBase", strlen("jmxNameBase"), jmx_name_base TSRMLS_DC);
	RETURN_TRUE;
}


PHP_METHOD(base_object_pool_config, getJmxNamePrefix)
{
	zval *ret;
	ret = zend_read_property(base_object_pool_config_ce, getThis(), "jmxNamePrefix", strlen("jmxNamePrefix"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(base_object_pool_config, setJmxNamePrefix)
{
	char *jmx_name_prefix;
	long jmx_name_prefix_length;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &jmx_name_prefix, &jmx_name_prefix_length) == FAILURE) {
		RETURN_FALSE;
	}

	zend_update_property_string(base_object_pool_config_ce, getThis(), "jmxNamePrefix", strlen("jmxNamePrefix"), jmx_name_prefix TSRMLS_DC);
	RETURN_TRUE;
}


PHP_METHOD(base_object_pool_config, getEvictionPolicyClassName)
{
	zval *ret;
	ret = zend_read_property(base_object_pool_config_ce, getThis(), "evictionPolicyClassName", strlen("evictionPolicyClassName"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(base_object_pool_config, setEvictionPolicyClassName)
{
	char *eviction_policy_class_name;
	long eviction_policy_class_name_length;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &eviction_policy_class_name, &eviction_policy_class_name_length) == FAILURE) {
		RETURN_FALSE;
	}

	zend_update_property_string(base_object_pool_config_ce, getThis(), "evictionPolicyClassName", strlen("evictionPolicyClassName"), eviction_policy_class_name TSRMLS_DC);
	RETURN_TRUE;
}




