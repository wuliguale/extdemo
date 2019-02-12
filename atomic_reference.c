/*
 * atomic_reference.c
 *
 *  Created on: 2019年2月12日
 *      Author: sam
 */


#include "common.h"
#include "Zend/zend_interfaces.h"
#include "Zend/zend_API.h"
#include "php_extdemo.h"


zend_class_entry *atomic_reference_ce;

PHP_METHOD(AtomicReference, __construct);
PHP_METHOD(AtomicReference, set);
PHP_METHOD(AtomicReference, get);

zend_function_entry atomic_reference_method[] = {
		PHP_ME(AtomicReference, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
		PHP_ME(AtomicReference, set, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(AtomicReference, get, NULL, ZEND_ACC_PUBLIC)
		PHP_FE_END
};


EXTDEMO_STARTUP_FUNCTION(AtomicReference) {
	zend_class_entry AtomicReferencece;
	INIT_CLASS_ENTRY(AtomicReferencece, "AtomicReference", atomic_reference_method);
	atomic_reference_ce = zend_register_internal_class(&AtomicReferencece TSRMLS_CC);

	//todo private volatile V value;
	zend_declare_property_null(atomic_reference_ce, "value", strlen("value"), ZEND_ACC_PRIVATE);
	return SUCCESS;
}


PHP_METHOD(AtomicReference, __construct)
{
	RETURN_TRUE;
}


PHP_METHOD(AtomicReference, get)
{
	zval *ret;
	ret = zend_read_property(atomic_reference_ce, getThis(), "value", strlen("value"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}



PHP_METHOD(AtomicReference, set)
{
	zval *value;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "o", &value) == FAILURE) {
		RETURN_FALSE;
	}

	zend_update_property(atomic_reference_ce, getThis(), "value", strlen("value"), value TSRMLS_DC);
	RETURN_TRUE;
}

