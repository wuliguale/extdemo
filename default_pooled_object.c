/*
 * default_pooled_object.c
 *
 *  Created on: 2019-1-23
 *      Author: sam
 */

#include "common.h"

zend_class_entry *comparable_ce;

zend_function_entry comparable_method[] = {
		ZEND_ABSTRACT_ME(comparable_ce, compareTo, NULL)
		PHP_FE_END
};


zend_class_entry *pooled_object_ce;

zend_function_entry pooled_object_method[] = {
		ZEND_ABSTRACT_ME(pooled_object_ce, getObject, NULL)
		ZEND_ABSTRACT_ME(pooled_object_ce, getCreateTime, NULL)
		ZEND_ABSTRACT_ME(pooled_object_ce, getActiveTimeMillis, NULL)
		ZEND_ABSTRACT_ME(pooled_object_ce, getIdleTimeMillis, NULL)
		ZEND_ABSTRACT_ME(pooled_object_ce, getLastBorrowTime, NULL)
		ZEND_ABSTRACT_ME(pooled_object_ce, getLastReturnTime, NULL)
		ZEND_ABSTRACT_ME(pooled_object_ce, getLastUsedTime, NULL)
		ZEND_ABSTRACT_ME(pooled_object_ce, compareTo, NULL)
		ZEND_ABSTRACT_ME(pooled_object_ce, equals, NULL)
		ZEND_ABSTRACT_ME(pooled_object_ce, hashCode, NULL)
		ZEND_ABSTRACT_ME(pooled_object_ce, toString, NULL)
		ZEND_ABSTRACT_ME(pooled_object_ce, startEvictionTest, NULL)
		ZEND_ABSTRACT_ME(pooled_object_ce, endEvictionTest, NULL)
		ZEND_ABSTRACT_ME(pooled_object_ce, allocate, NULL)
		ZEND_ABSTRACT_ME(pooled_object_ce, deallocate, NULL)
		ZEND_ABSTRACT_ME(pooled_object_ce, invalidate, NULL)
		ZEND_ABSTRACT_ME(pooled_object_ce, setLogAbandoned, NULL)
		ZEND_ABSTRACT_ME(pooled_object_ce, use, NULL)
		ZEND_ABSTRACT_ME(pooled_object_ce, printStackTrace, NULL)
		ZEND_ABSTRACT_ME(pooled_object_ce, getState, NULL)
		ZEND_ABSTRACT_ME(pooled_object_ce, markAbandoned, NULL)
		ZEND_ABSTRACT_ME(pooled_object_ce, markReturning, NULL)
		PHP_FE_END
};


//enum PooledObjectState
//idle
long pooled_object_state_idle = 1;
//In use
long pooled_object_state_allocated = 1;
//In the queue, currently being tested for possible eviction
long pooled_object_state_eviction = 1;
/**
 * Not in the queue, currently being tested for possible eviction. An
 * attempt to borrow the object was made while being tested which removed it
 * from the queue. It should be returned to the head of the queue once
 * eviction testing completes.
 */
long pooled_object_state_eviction_return_to_head = 1;
//In the queue, currently being validated.
long pooled_object_state_validation = 1;
/**
 * Not in queue, currently being validated. The object was borrowed while
 * being validated and since testOnBorrow was configured, it was removed
 * from the queue and pre-allocated. It should be allocated once validation
 * completes.
 */
long pooled_object_state_validation_preallocated = 1;
/**
 * Not in queue, currently being validated. An attempt to borrow the object
 * was made while previously being tested for eviction which removed it from
 * the queue. It should be returned to the head of the queue once validation
 * completes.
 */
long pooled_object_state_validation_return_to_head = 1;
//Failed maintenance (e.g. eviction test or validation) and will be / has been destroyed
long pooled_object_state_invalid = 1;
//Deemed abandoned, to be invalidated.
long pooled_object_state_abandoned = 1;
//Returning to the pool
long pooled_object_state_returning = 1;


//class DefaultPooledObject
zend_class_entry *default_pooled_object_ce;

PHP_METHOD(default_pooled_object, __construct);
PHP_METHOD(default_pooled_object, getObject);
PHP_METHOD(default_pooled_object, getCreateTime);
PHP_METHOD(default_pooled_object, getActiveTimeMillis);

zend_function_entry default_pooled_object_method[] = {
		PHP_ME(default_pooled_object, __construct, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(default_pooled_object, getObject, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(default_pooled_object, getCreateTime, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(default_pooled_object, getActiveTimeMillis, NULL, ZEND_ACC_PUBLIC)
//		PHP_ME(default_pooled_object, getIdleTimeMillis, NULL, ZEND_ACC_PUBLIC)
//		PHP_ME(default_pooled_object, getLastBorrowTime, NULL, ZEND_ACC_PUBLIC)
//		PHP_ME(default_pooled_object, getLastReturnTime, NULL, ZEND_ACC_PUBLIC)
//		PHP_ME(default_pooled_object, getLastUsedTime, NULL, ZEND_ACC_PUBLIC)
//		PHP_ME(default_pooled_object, compareTo, NULL, ZEND_ACC_PUBLIC)
//		PHP_ME(default_pooled_object, equals, NULL, ZEND_ACC_PUBLIC)
//		PHP_ME(default_pooled_object, hashCode, NULL, ZEND_ACC_PUBLIC)
//		PHP_ME(default_pooled_object, toString, NULL, ZEND_ACC_PUBLIC)
//		PHP_ME(default_pooled_object, startEvictionTest, NULL, ZEND_ACC_PUBLIC)
//		PHP_ME(default_pooled_object, endEvictionTest, NULL, ZEND_ACC_PUBLIC)
//		PHP_ME(default_pooled_object, allocate, NULL, ZEND_ACC_PUBLIC)
//		PHP_ME(default_pooled_object, deallocate, NULL, ZEND_ACC_PUBLIC)
//		PHP_ME(default_pooled_object, invalidate, NULL, ZEND_ACC_PUBLIC)
//		PHP_ME(default_pooled_object, setLogAbandoned, NULL, ZEND_ACC_PUBLIC)
//		PHP_ME(default_pooled_object, use, NULL, ZEND_ACC_PUBLIC)
//		PHP_ME(default_pooled_object, printStackTrace, NULL, ZEND_ACC_PUBLIC)
//		PHP_ME(default_pooled_object, getState, NULL, ZEND_ACC_PUBLIC)
//		PHP_ME(default_pooled_object, markAbandoned, NULL, ZEND_ACC_PUBLIC)
//		PHP_ME(default_pooled_object, markReturning, NULL, ZEND_ACC_PUBLIC)
		PHP_FE_END
};


PHP_METHOD(default_pooled_object, __construct)
{
	zval *obj;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "o", &obj) == FAILURE) {
		RETURN_FALSE;
	}

	//type object property should declare null then set object
	zend_update_property(default_pooled_object_ce, getThis(), "object", strlen("object"), obj TSRMLS_DC);
	RETURN_TRUE;
}


PHP_METHOD(default_pooled_object, getObject)
{
	zval *ret;
	ret = zend_read_property(default_pooled_object_ce, getThis(), "object", strlen("object"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(default_pooled_object, getCreateTime)
{
	zval *ret;
	ret = zend_read_property(default_pooled_object_ce, getThis(), "createTime", strlen("createTime"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(default_pooled_object, getActiveTimeMillis)
{
	long rTime, bTime;
	rTime = zend_read_property(default_pooled_object_ce, getThis(), "lastReturnTime", strlen("lastReturnTime"), 0 TSRMLS_DC);
	bTime = zend_read_property(default_pooled_object_ce, getThis(), "lastBorrowTime", strlen("lastBorrowTime"), 0 TSRMLS_DC);

	if (rTime > bTime) {
		RETURN_LONG(rTime - bTime);
	} else {
		RETURN_LONG(get_time_mills() - bTime);
	}
}

