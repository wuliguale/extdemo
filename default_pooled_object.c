/*
 * default_pooled_object.c
 *
 *  Created on: 2019-1-23
 *      Author: sam
 */

#include "common.h"
#include "Zend/zend_interfaces.h"
#include "Zend/zend_API.h"
#include "php_extdemo.h"


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

PHP_METHOD(DefaultPooledObject, __construct);
PHP_METHOD(DefaultPooledObject, getObject);
PHP_METHOD(DefaultPooledObject, getCreateTime);
PHP_METHOD(DefaultPooledObject, getActiveTimeMillis);
PHP_METHOD(DefaultPooledObject, getIdleTimeMillis);
PHP_METHOD(DefaultPooledObject, getLastBorrowTime);
PHP_METHOD(DefaultPooledObject, getLastReturnTime);
PHP_METHOD(DefaultPooledObject, getBorrowedCount);
PHP_METHOD(DefaultPooledObject, getLastUsedTime);
PHP_METHOD(DefaultPooledObject, compareTo);

//TODO
PHP_METHOD(DefaultPooledObject, equals);
PHP_METHOD(DefaultPooledObject, hashCode);

PHP_METHOD(DefaultPooledObject, toString);
PHP_METHOD(DefaultPooledObject, startEvictionTest);
PHP_METHOD(DefaultPooledObject, endEvictionTest);
PHP_METHOD(DefaultPooledObject, allocate);
PHP_METHOD(DefaultPooledObject, deallocate);
PHP_METHOD(DefaultPooledObject, invalidate);
PHP_METHOD(DefaultPooledObject, use);
PHP_METHOD(DefaultPooledObject, printStackTrace);
PHP_METHOD(DefaultPooledObject, getState);
PHP_METHOD(DefaultPooledObject, markAbandoned);
PHP_METHOD(DefaultPooledObject, markReturning);
PHP_METHOD(DefaultPooledObject, setLogAbandoned);


zend_function_entry default_pooled_object_method[] = {
		PHP_ME(DefaultPooledObject, __construct, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, getObject, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, getCreateTime, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, getActiveTimeMillis, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, getIdleTimeMillis, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, getLastBorrowTime, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, getLastReturnTime, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, getBorrowedCount, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, getLastUsedTime, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, compareTo, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, equals, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, hashCode, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, toString, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, startEvictionTest, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, endEvictionTest, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, allocate, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, deallocate, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, invalidate, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, use, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, printStackTrace, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, getState, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, markAbandoned, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, markReturning, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(DefaultPooledObject, setLogAbandoned, NULL, ZEND_ACC_PUBLIC)
		PHP_FE_END
};


EXTDEMO_STARTUP_FUNCTION(DefaultPooledObject) {
	//class DefaultPooledObject
	zend_class_entry default_pooled_obj_ce;
	INIT_CLASS_ENTRY(default_pooled_obj_ce, "DefaultPooledObject", default_pooled_object_method);
	default_pooled_object_ce = zend_register_internal_class(&default_pooled_obj_ce TSRMLS_CC);
	//zend_class_implements(default_pooled_object_ce TSRMLS_CC, 1, pooled_object_ce);

	zend_declare_property_null(default_pooled_object_ce, "object", strlen("object"), ZEND_ACC_PRIVATE);
	zend_declare_property_null(default_pooled_object_ce, "state", strlen("state"), ZEND_ACC_PRIVATE);
	//TODO volatile
	zend_declare_property_null(default_pooled_object_ce, "createTime", strlen("createTime"), ZEND_ACC_PRIVATE);
	//TODO volatile
	zend_declare_property_null(default_pooled_object_ce, "lastBorrowTime", strlen("lastBorrowTime"), ZEND_ACC_PRIVATE);
	//TODO volatile
	zend_declare_property_null(default_pooled_object_ce, "lastUseTime", strlen("lastUseTime"), ZEND_ACC_PRIVATE);
	//TODO volatile
	zend_declare_property_null(default_pooled_object_ce, "lastReturnTime", strlen("lastReturnTime"), ZEND_ACC_PRIVATE);
	//TODO volatile
	zend_declare_property_null(default_pooled_object_ce, "logAbandoned", strlen("logAbandoned"), ZEND_ACC_PRIVATE);
	//TODO volatile
	zend_declare_property_null(default_pooled_object_ce, "borrowedBy", strlen("borrowedBy"), ZEND_ACC_PRIVATE);
	//TODO volatile
	zend_declare_property_null(default_pooled_object_ce, "usedBy", strlen("usedBy"), ZEND_ACC_PRIVATE);
	//TODO volatile
	zend_declare_property_null(default_pooled_object_ce, "borrowedCount", strlen("borrowedCount"), ZEND_ACC_PRIVATE);

	return SUCCESS;
}


PHP_METHOD(DefaultPooledObject, __construct)
{
	zval *obj;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "o", &obj) == FAILURE) {
		RETURN_FALSE;
	}

	//type object property should declare null then set object
	zend_update_property(default_pooled_object_ce, getThis(), "object", strlen("object"), obj TSRMLS_DC);
	zend_update_property_long(default_pooled_object_ce, getThis(), "state", strlen("state"), pooled_object_state_idle TSRMLS_DC);
	long create_time = get_time_mills();
	zend_update_property_long(default_pooled_object_ce, getThis(), "createTime", strlen("createTime"), create_time TSRMLS_DC);
	zend_update_property_long(default_pooled_object_ce, getThis(), "lastBorrowTime", strlen("lastBorrowTime"), create_time TSRMLS_DC);
	zend_update_property_long(default_pooled_object_ce, getThis(), "lastUseTime", strlen("lastUseTime"), create_time TSRMLS_DC);
	zend_update_property_long(default_pooled_object_ce, getThis(), "lastReturnTime", strlen("lastReturnTime"), create_time TSRMLS_DC);
	zend_update_property_bool(default_pooled_object_ce, getThis(), "logAbandoned", strlen("logAbandoned"), 0 TSRMLS_DC);
	zend_update_property_long(default_pooled_object_ce, getThis(), "borrowedCount", strlen("borrowedCount"), 0 TSRMLS_DC);

	RETURN_TRUE;
}


PHP_METHOD(DefaultPooledObject, getObject)
{
	zval *ret;
	ret = zend_read_property(default_pooled_object_ce, getThis(), "object", strlen("object"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(DefaultPooledObject, getCreateTime)
{
	zval *ret;
	ret = zend_read_property(default_pooled_object_ce, getThis(), "createTime", strlen("createTime"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(DefaultPooledObject, getActiveTimeMillis)
{
	zval *rTime_zval, *bTime_zval;
	long rTime, bTime;
	rTime_zval = zend_read_property(default_pooled_object_ce, getThis(), "lastReturnTime", strlen("lastReturnTime"), 0 TSRMLS_DC);
	bTime_zval = zend_read_property(default_pooled_object_ce, getThis(), "lastBorrowTime", strlen("lastBorrowTime"), 0 TSRMLS_DC);

	rTime = Z_LVAL_P(rTime_zval);
	bTime = Z_LVAL_P(bTime_zval);

	if (rTime > bTime) {
		RETURN_LONG(rTime - bTime);
	} else {
		RETURN_LONG(get_time_mills() - bTime);
	}
}


PHP_METHOD(DefaultPooledObject, getIdleTimeMillis)
{
	zval *rTime_zval;
	long rTime;
	rTime_zval = zend_read_property(default_pooled_object_ce, getThis(), "lastReturnTime", strlen("lastReturnTime"), 0 TSRMLS_DC);
	rTime = Z_LVAL_P(rTime_zval);
	long elapsed = get_time_mills() - rTime;

	// elapsed may be negative if:
	// - another thread updates lastReturnTime during the calculation window
	// - System.currentTimeMillis() is not monotonic (e.g. system time is set back)
	if (elapsed >= 0) {
		RETURN_LONG(elapsed);
	} else {
		RETURN_LONG(0);
	}
}


PHP_METHOD(DefaultPooledObject, getLastBorrowTime)
{
	zval *ret;
	ret = zend_read_property(default_pooled_object_ce, getThis(), "lastBorrowTime", strlen("lastBorrowTime"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(DefaultPooledObject, getLastReturnTime)
{
	zval *ret;
	ret = zend_read_property(default_pooled_object_ce, getThis(), "lastReturnTime", strlen("lastReturnTime"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(DefaultPooledObject, getBorrowedCount)
{
	zval *ret;
	ret = zend_read_property(default_pooled_object_ce, getThis(), "borrowedCount", strlen("borrowedCount"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(DefaultPooledObject, getLastUsedTime)
{
	//TODO TrackedUse check
	zval *ret;
	ret = zend_read_property(default_pooled_object_ce, getThis(), "lastUseTime", strlen("lastUseTime"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(DefaultPooledObject, compareTo)
{
	zval *this_zval, *other_zval, *this_last_return_time, *other_last_return_time;
	//TODO time max check
	long thisLastReturnTime, otherLastReturnTime, lastActiveDiff;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &other_zval) == FAILURE) {
		RETURN_FALSE;
	}

	this_zval = getThis();
	//ce传NULL,或method_name 小写
	zend_call_method_with_0_params(&this_zval, default_pooled_object_ce, NULL, "getlastreturntime", &this_last_return_time);
	zend_call_method_with_0_params(&other_zval, default_pooled_object_ce, NULL, "getlastreturntime", &other_last_return_time);

	thisLastReturnTime = Z_LVAL_P(this_last_return_time);
	otherLastReturnTime = Z_LVAL_P(other_last_return_time);

	lastActiveDiff = thisLastReturnTime- otherLastReturnTime;
	php_printf("%d, %d\n", thisLastReturnTime, otherLastReturnTime);

	//TODO check lastActiveDiff == 0
	RETURN_LONG(lastActiveDiff);
}


PHP_METHOD(DefaultPooledObject, equals)
{


}


PHP_METHOD(DefaultPooledObject, hashCode)
{

}


PHP_METHOD(DefaultPooledObject, toString)
{

}
/*
    public String toString() {
        StringBuilder result = new StringBuilder();
        result.append("Object: ");
        result.append(object.toString());
        result.append(", State: ");
        synchronized (this) {
            result.append(state.toString());
        }
        return result.toString();
        // TODO add other attributes
    }
    */

PHP_METHOD(DefaultPooledObject, startEvictionTest)
{

}
/*
    @Override
    public synchronized boolean startEvictionTest() {
        if (state == PooledObjectState.IDLE) {
            state = PooledObjectState.EVICTION;
            return true;
        }

        return false;
    }
    */

PHP_METHOD(DefaultPooledObject, endEvictionTest)
{

}

/*
    @Override
    public synchronized boolean endEvictionTest(
            Deque<PooledObject<T>> idleQueue) {
        if (state == PooledObjectState.EVICTION) {
            state = PooledObjectState.IDLE;
            return true;
        } else if (state == PooledObjectState.EVICTION_RETURN_TO_HEAD) {
            state = PooledObjectState.IDLE;
            if (!idleQueue.offerFirst(this)) {
                // TODO - Should never happen
            }
        }

        return false;
    }
    */

    PHP_METHOD(DefaultPooledObject, allocate)
    {

    }
    /**
     * Allocates the object.
     *
     * @return {@code true} if the original state was {@link PooledObjectState#IDLE IDLE}
     */
    /*
    @Override
    public synchronized boolean allocate() {
        if (state == PooledObjectState.IDLE) {
            state = PooledObjectState.ALLOCATED;
            lastBorrowTime = System.currentTimeMillis();
            lastUseTime = lastBorrowTime;
            borrowedCount++;
            if (logAbandoned) {
                borrowedBy = new AbandonedObjectCreatedException();
            }
            return true;
        } else if (state == PooledObjectState.EVICTION) {
            // TODO Allocate anyway and ignore eviction test
            state = PooledObjectState.EVICTION_RETURN_TO_HEAD;
            return false;
        }
        // TODO if validating and testOnBorrow == true then pre-allocate for
        // performance
        return false;
    }
    */

    PHP_METHOD(DefaultPooledObject, deallocate)
    {

    }
    /**
     * Deallocates the object and sets it {@link PooledObjectState#IDLE IDLE}
     * if it is currently {@link PooledObjectState#ALLOCATED ALLOCATED}.
     *
     * @return {@code true} if the state was {@link PooledObjectState#ALLOCATED ALLOCATED}
     */
    /*
    @Override
    public synchronized boolean deallocate() {
        if (state == PooledObjectState.ALLOCATED ||
                state == PooledObjectState.RETURNING) {
            state = PooledObjectState.IDLE;
            lastReturnTime = System.currentTimeMillis();
            borrowedBy = null;
            return true;
        }

        return false;
    }
    */


    PHP_METHOD(DefaultPooledObject, invalidate)
    {

    }
    /**
     * Sets the state to {@link PooledObjectState#INVALID INVALID}
     */
    /*
    @Override
    public synchronized void invalidate() {
        state = PooledObjectState.INVALID;
    }
    */

    PHP_METHOD(DefaultPooledObject, use)
    {

    }

    /*
    @Override
    public void use() {
        lastUseTime = System.currentTimeMillis();
        usedBy = new Exception("The last code to use this object was:");
    }
    */


    PHP_METHOD(DefaultPooledObject, printStackTrace)
    {

    }
    /*
    @Override
    public void printStackTrace(PrintWriter writer) {
        boolean written = false;
        Exception borrowedByCopy = this.borrowedBy;
        if (borrowedByCopy != null) {
            borrowedByCopy.printStackTrace(writer);
            written = true;
        }
        Exception usedByCopy = this.usedBy;
        if (usedByCopy != null) {
            usedByCopy.printStackTrace(writer);
            written = true;
        }
        if (written) {
            writer.flush();
        }
    }
*/

    PHP_METHOD(DefaultPooledObject, getState)
    {

    }
    /**
     * Returns the state of this object.
     * @return state
     */
    /*
    @Override
    public synchronized PooledObjectState getState() {
        return state;
    }
*/

    PHP_METHOD(DefaultPooledObject, markAbandoned)
    {

    }
    /**
     * Marks the pooled object as abandoned.
     */
    /*
    @Override
    public synchronized void markAbandoned() {
        state = PooledObjectState.ABANDONED;
    }
    */


    PHP_METHOD(DefaultPooledObject, markReturning)
    {

    }
    /**
     * Marks the object as returning to the pool.
     */
    /*
    @Override
    public synchronized void markReturning() {
        state = PooledObjectState.RETURNING;
    }
    */


    PHP_METHOD(DefaultPooledObject, setLogAbandoned)
    {

    }
    /*
    @Override
    public void setLogAbandoned(boolean logAbandoned) {
        this.logAbandoned = logAbandoned;
    }
*/


