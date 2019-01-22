/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_extdemo.h"
#include "base_object_pool_config.h"




PHP_FUNCTION(extdemotest);

/* If you declare any globals in php_extdemo.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(extdemo)
*/

/* True global resources - no need for thread safety here */
static int le_extdemo;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("extdemo.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_extdemo_globals, extdemo_globals)
    STD_PHP_INI_ENTRY("extdemo.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_extdemo_globals, extdemo_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_extdemo_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_extdemo_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "extdemo", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_extdemo_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_extdemo_init_globals(zend_extdemo_globals *extdemo_globals)
{
	extdemo_globals->global_value = 0;
	extdemo_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(extdemo)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/

	//BaseObjectPoolConfig constant
	REGISTER_BOOL_CONSTANT("DEFAULT_LIFO", base_object_pool_config_default_lifo, CONST_CS | CONST_PERSISTENT);
	REGISTER_BOOL_CONSTANT("DEFAULT_FAIRNESS", base_object_pool_config_default_fairness, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("DEFAULT_MAX_WAIT_MILLIS", base_object_pool_config_default_max_wait_millis, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("DEFAULT_MIN_EVICTABLE_IDLE_TIME_MILLIS", base_object_pool_config_default_min_evictable_idle_time_millis, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("DEFAULT_SOFT_MIN_EVICTABLE_IDLE_TIME_MILLIS", base_object_pool_config_default_soft_min_evictable_idle_time_millis, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("DEFAULT_NUM_TESTS_PER_EVICTION_RUN", base_object_pool_config_default_num_tests_per_eviction_run, CONST_CS | CONST_PERSISTENT);
	REGISTER_BOOL_CONSTANT("DEFAULT_TEST_ON_CREATE", base_object_pool_config_default_test_on_create, CONST_CS | CONST_PERSISTENT);
	REGISTER_BOOL_CONSTANT("DEFAULT_TEST_ON_BORROW", base_object_pool_config_default_test_on_borrow, CONST_CS | CONST_PERSISTENT);
	REGISTER_BOOL_CONSTANT("DEFAULT_TEST_ON_RETURN", base_object_pool_config_default_test_on_return, CONST_CS | CONST_PERSISTENT);
	REGISTER_BOOL_CONSTANT("DEFAULT_TEST_WHILE_IDLE", base_object_pool_config_default_test_while_idle, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("DEFAULT_TIME_BETWEEN_EVICTION_RUNS_MILLIS", base_object_pool_config_default_time_between_eviction_runs_millis, CONST_CS | CONST_PERSISTENT);
	REGISTER_BOOL_CONSTANT("DEFAULT_BLOCK_WHEN_EXHAUSTED", base_object_pool_config_default_block_when_exhausted, CONST_CS | CONST_PERSISTENT);
	REGISTER_BOOL_CONSTANT("DEFAULT_JMX_ENABLE", base_object_pool_config_default_jmx_enable, CONST_CS | CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("DEFAULT_JMX_NAME_PREFIX", base_object_pool_config_default_jmx_name_prefix, CONST_CS | CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("DEFAULT_JMX_NAME_BASE", base_object_pool_config_default_jmx_name_base, CONST_CS | CONST_PERSISTENT);
	REGISTER_STRING_CONSTANT("DEFAULT_EVICTION_POLICY_CLASS_NAME", base_object_pool_config_default_eviction_policy_class_name, CONST_CS | CONST_PERSISTENT);

	zend_class_entry base_ce;
	INIT_CLASS_ENTRY(base_ce, "BaseObjectPoolConfig", base_object_pool_config_method);
	base_object_pool_config_ce = zend_register_internal_class(&base_ce TSRMLS_CC);

	 //private boolean lifo = DEFAULT_LIFO;
	zend_declare_property_bool(base_object_pool_config_ce, "lifo", strlen("lifo"), base_object_pool_config_default_lifo, ZEND_ACC_PRIVATE);
	//private boolean fairness = DEFAULT_FAIRNESS;
	zend_declare_property_bool(base_object_pool_config_ce, "fairness", strlen("fairness"), base_object_pool_config_default_fairness, ZEND_ACC_PRIVATE);
	//private long maxWaitMillis = DEFAULT_MAX_WAIT_MILLIS;
	zend_declare_property_long(base_object_pool_config_ce, "maxWaitMillis", strlen("maxWaitMillis"), base_object_pool_config_default_max_wait_millis, ZEND_ACC_PRIVATE);
	//private long minEvictableIdleTimeMillis = DEFAULT_MIN_EVICTABLE_IDLE_TIME_MILLIS;
	zend_declare_property_long(base_object_pool_config_ce, "minEvictableIdleTimeMillis", strlen("minEvictableIdleTimeMillis"), base_object_pool_config_default_min_evictable_idle_time_millis, ZEND_ACC_PRIVATE);
	//注意这里不是default soft
	//private long softMinEvictableIdleTimeMillis = DEFAULT_MIN_EVICTABLE_IDLE_TIME_MILLIS;
	zend_declare_property_long(base_object_pool_config_ce, "softMinEvictableIdleTimeMillis", strlen("softMinEvictableIdleTimeMillis"), base_object_pool_config_default_min_evictable_idle_time_millis, ZEND_ACC_PRIVATE);
	//private int numTestsPerEvictionRun = DEFAULT_NUM_TESTS_PER_EVICTION_RUN;
	zend_declare_property_long(base_object_pool_config_ce, "numTestsPerEvictionRun", strlen("numTestsPerEvictionRun"), base_object_pool_config_default_num_tests_per_eviction_run, ZEND_ACC_PRIVATE);
	//private boolean testOnCreate = DEFAULT_TEST_ON_CREATE;
	zend_declare_property_bool(base_object_pool_config_ce, "testOnCreate", strlen("testOnCreate"), base_object_pool_config_default_test_on_create, ZEND_ACC_PRIVATE);
	//private boolean testOnBorrow = DEFAULT_TEST_ON_BORROW;
	zend_declare_property_bool(base_object_pool_config_ce, "testOnBorrow", strlen("testOnBorrow"), base_object_pool_config_default_test_on_borrow, ZEND_ACC_PRIVATE);
	//private boolean testOnReturn = DEFAULT_TEST_ON_RETURN;
	zend_declare_property_bool(base_object_pool_config_ce, "testOnReturn", strlen("testOnReturn"), base_object_pool_config_default_test_on_return, ZEND_ACC_PRIVATE);
	//private boolean testWhileIdle = DEFAULT_TEST_WHILE_IDLE;
	zend_declare_property_bool(base_object_pool_config_ce, "testWhileIdle", strlen("testWhileIdle"), base_object_pool_config_default_test_while_idle, ZEND_ACC_PRIVATE);
	//private long timeBetweenEvictionRunsMillis = DEFAULT_TIME_BETWEEN_EVICTION_RUNS_MILLIS;
	zend_declare_property_long(base_object_pool_config_ce, "timeBetweenEvictionRunsMillis", strlen("timeBetweenEvictionRunsMillis"), base_object_pool_config_default_time_between_eviction_runs_millis, ZEND_ACC_PRIVATE);
	//private boolean blockWhenExhausted = DEFAULT_BLOCK_WHEN_EXHAUSTED;
	zend_declare_property_bool(base_object_pool_config_ce, "blockWhenExhausted", strlen("blockWhenExhausted"), base_object_pool_config_default_block_when_exhausted, ZEND_ACC_PRIVATE);
	//private boolean jmxEnabled = DEFAULT_JMX_ENABLE;
	zend_declare_property_bool(base_object_pool_config_ce, "jmxEnabled", strlen("jmxEnabled"), base_object_pool_config_default_jmx_enable, ZEND_ACC_PRIVATE);
	//private String jmxNamePrefix = DEFAULT_JMX_NAME_PREFIX;
	zend_declare_property_string(base_object_pool_config_ce, "jmxNamePrefix", strlen("jmxNamePrefix"), base_object_pool_config_default_jmx_name_prefix, ZEND_ACC_PRIVATE);
	//private String jmxNameBase = DEFAULT_JMX_NAME_BASE;
	zend_declare_property_string(base_object_pool_config_ce, "jmxNameBase", strlen("jmxNameBase"), base_object_pool_config_default_jmx_name_base, ZEND_ACC_PRIVATE);
	//private String evictionPolicyClassName = DEFAULT_EVICTION_POLICY_CLASS_NAME;
	zend_declare_property_string(base_object_pool_config_ce, "evictionPolicyClassName", strlen("evictionPolicyClassName"), base_object_pool_config_default_eviction_policy_class_name, ZEND_ACC_PRIVATE);






	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(extdemo)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(extdemo)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(extdemo)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(extdemo)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "extdemo support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ extdemo_functions[]
 *
 * Every user visible function must have an entry in extdemo_functions[].
 */
const zend_function_entry extdemo_functions[] = {
	PHP_FE(confirm_extdemo_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(extdemotest, NULL)
	PHP_FE_END	/* Must be the last line in extdemo_functions[] */
};
/* }}} */

/* {{{ extdemo_module_entry
 */
zend_module_entry extdemo_module_entry = {
	STANDARD_MODULE_HEADER,
	"extdemo",
	extdemo_functions,
	PHP_MINIT(extdemo),
	PHP_MSHUTDOWN(extdemo),
	PHP_RINIT(extdemo),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(extdemo),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(extdemo),
	PHP_EXTDEMO_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_EXTDEMO
ZEND_GET_MODULE(extdemo)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */


PHP_FUNCTION(extdemotest)
{
	php_printf("hello world\n");

}
