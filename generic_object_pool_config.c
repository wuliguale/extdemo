/*
 * generic_object_pool_config.c
 *
 *  Created on: 2019-1-23
 *      Author: sam
 */


#include "common.h"

long generic_object_pool_config_default_max_total = 8;
long generic_object_pool_config_default_max_idle = 8;
long generic_object_pool_config_default_min_idle = 0;


zend_class_entry *generic_object_pool_config_ce;


PHP_METHOD(generic_object_pool_config, getMaxTotal);
PHP_METHOD(generic_object_pool_config, setMaxTotal);
PHP_METHOD(generic_object_pool_config, getMaxIdle);
PHP_METHOD(generic_object_pool_config, setMaxIdle);
PHP_METHOD(generic_object_pool_config, getMinIdle);
PHP_METHOD(generic_object_pool_config, setMinIdle);


zend_function_entry generic_object_pool_config_method[] = {
		PHP_ME(generic_object_pool_config, getMaxTotal, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(generic_object_pool_config, setMaxTotal, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(generic_object_pool_config, getMaxIdle, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(generic_object_pool_config, setMaxIdle, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(generic_object_pool_config, getMinIdle, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(generic_object_pool_config, setMinIdle, NULL, ZEND_ACC_PUBLIC)
	    PHP_FE_END
};


PHP_METHOD(generic_object_pool_config, getMaxTotal)
{
	zval *ret;
	ret = zend_read_property(generic_object_pool_config_ce, getThis(), "maxTotal", strlen("maxTotal"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(generic_object_pool_config, setMaxTotal)
{
	long max_total;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &max_total) == FAILURE) {
		RETURN_FALSE;
	}

	zend_update_property_long(generic_object_pool_config_ce, getThis(), "maxTotal", strlen("maxTotal"), max_total TSRMLS_DC);
	RETURN_TRUE;
}


PHP_METHOD(generic_object_pool_config, getMaxIdle)
{
	zval *ret;
	ret = zend_read_property(generic_object_pool_config_ce, getThis(), "maxIdle", strlen("maxIdle"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(generic_object_pool_config, setMaxIdle)
{
	long max_idle;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &max_idle) == FAILURE) {
		RETURN_FALSE;
	}

	zend_update_property_long(generic_object_pool_config_ce, getThis(), "maxIdle", strlen("maxIdle"), max_idle TSRMLS_DC);
	RETURN_TRUE;
}


PHP_METHOD(generic_object_pool_config, getMinIdle)
{
	zval *ret;
	ret = zend_read_property(generic_object_pool_config_ce, getThis(), "minIdle", strlen("minIdle"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(generic_object_pool_config, setMinIdle)
{
	long min_idle;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &min_idle) == FAILURE) {
		RETURN_FALSE;
	}

	zend_update_property_long(generic_object_pool_config_ce, getThis(), "minIdle", strlen("minIdle"), min_idle TSRMLS_DC);
	RETURN_TRUE;
}

