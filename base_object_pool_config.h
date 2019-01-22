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

zend_function_entry base_object_pool_config_method[] = {
	    PHP_FE_END
};

