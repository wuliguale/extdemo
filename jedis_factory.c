/*
 * jedis_factory.c
 *
 *  Created on: 2019年2月12日
 *      Author: sam
 */

#include "common.h"
#include "Zend/zend_interfaces.h"
#include "Zend/zend_API.h"
#include "php_extdemo.h"


zend_class_entry *jedis_factory_ce;

PHP_METHOD(JedisFactory, __construct);
PHP_METHOD(JedisFactory, setHostAndPort);
PHP_METHOD(JedisFactory, activateObject);
PHP_METHOD(JedisFactory, destroyObject);
PHP_METHOD(JedisFactory, makeObject);
PHP_METHOD(JedisFactory, passivateObject);
PHP_METHOD(JedisFactory, validateObject);


zend_function_entry jedis_factory_method[] = {
		PHP_ME(JedisFactory, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
		PHP_ME(JedisFactory, setHostAndPort, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(JedisFactory, activateObject, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(JedisFactory, destroyObject, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(JedisFactory, makeObject, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(JedisFactory, passivateObject, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(JedisFactory, validateObject, NULL, ZEND_ACC_PUBLIC)
		PHP_FE_END
};


EXTDEMO_STARTUP_FUNCTION(JedisFactory) {
	zend_class_entry jedisfactoryce;
	INIT_CLASS_ENTRY(jedisfactoryce, "JedisFactory", jedis_factory_method);
	jedis_factory_ce = zend_register_internal_class(&jedisfactoryce TSRMLS_CC);

	//private final AtomicReference<HostAndPort> hostAndPort = new AtomicReference<HostAndPort>();
	zend_declare_property_null(jedis_factory_ce, "hostAndPort", strlen("hostAndPort"), ZEND_ACC_PRIVATE);

	//private final int connectionTimeout;
	zend_declare_property_null(jedis_factory_ce, "connectionTimeout", strlen("connectionTimeout"), ZEND_ACC_PRIVATE);
	//private final int soTimeout;
	zend_declare_property_null(jedis_factory_ce, "soTimeout", strlen("soTimeout"), ZEND_ACC_PRIVATE);
	//private final String password;
	zend_declare_property_null(jedis_factory_ce, "password", strlen("password"), ZEND_ACC_PRIVATE);
	//private final int database;
	zend_declare_property_null(jedis_factory_ce, "database", strlen("database"), ZEND_ACC_PRIVATE);
	//private final String clientName;
	zend_declare_property_null(jedis_factory_ce, "clientName", strlen("clientName"), ZEND_ACC_PRIVATE);
	//private final boolean ssl;
	zend_declare_property_null(jedis_factory_ce, "ssl", strlen("ssl"), ZEND_ACC_PRIVATE);
	//private final SSLSocketFactory sslSocketFactory;
	zend_declare_property_null(jedis_factory_ce, "sslSocketFactory", strlen("sslSocketFactory"), ZEND_ACC_PRIVATE);
	//private SSLParameters sslParameters;
	zend_declare_property_null(jedis_factory_ce, "sslParameters", strlen("sslParameters"), ZEND_ACC_PRIVATE);
	//private HostnameVerifier hostnameVerifier;
	zend_declare_property_null(jedis_factory_ce, "hostnameVerifier", strlen("hostnameVerifier"), ZEND_ACC_PRIVATE);


	return SUCCESS;
}


PHP_METHOD(JedisFactory, __construct)
{
	zval *host, *port;
	char *password, *clientName;
	long password_len, clientName_len;
	long connectionTimeout, soTimeout, database;
	zend_bool ssl;
	long ssl_long;
	zval *sslSocketFactory, *sslParameters, *hostnameVerifier;
	zval *atomicReference, *hostAndPort;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz|llslsbooo",
			&host, &port, &connectionTimeout, &soTimeout, &password, &password_len, &database,
			&clientName, &clientName_len, &ssl, &sslSocketFactory, &sslParameters, &hostnameVerifier)
			== FAILURE) {
		RETURN_FALSE;
	}

	//this.hostAndPort.set(new HostAndPort(host, port));
	MAKE_STD_ZVAL(hostAndPort);
	object_init_ex(hostAndPort, host_and_port_ce);
	zend_call_method_with_2_params(&hostAndPort, host_and_port_ce, NULL, "__construct", NULL, host, port);

	MAKE_STD_ZVAL(atomicReference);
	object_init_ex(atomicReference, atomic_reference_ce);
	zend_call_method_with_0_params(&atomicReference, atomic_reference_ce, NULL, "__construct", NULL);
	zend_call_method_with_1_params(&atomicReference, atomic_reference_ce, NULL, "set", NULL, hostAndPort);
	zend_update_property(jedis_factory_ce, getThis(), "hostAndPort", strlen("hostAndPort"), atomicReference TSRMLS_DC);

	zend_update_property_long(jedis_factory_ce, getThis(), "connectionTimeout", strlen("connectionTimeout"), connectionTimeout TSRMLS_DC);
	zend_update_property_long(jedis_factory_ce, getThis(), "soTimeout", strlen("soTimeout"), soTimeout TSRMLS_DC);
	zend_update_property_long(jedis_factory_ce, getThis(), "database", strlen("database"), database TSRMLS_DC);

	if (password_len > 0) {
		zend_update_property_string(jedis_factory_ce, getThis(), "password", strlen("password"), password TSRMLS_DC);
	}

	if (clientName_len > 0) {
		zend_update_property_string(jedis_factory_ce, getThis(), "clientName", strlen("clientName"), clientName);
	}

	ssl_long = ssl ? 1 : 0;
	zend_update_property_bool(jedis_factory_ce, getThis(), "ssl", strlen("ssl"), ssl TSRMLS_DC);

	//TODO
	//this.sslSocketFactory = sslSocketFactory;
    //this.sslParameters = sslParameters;
    //this.hostnameVerifier = hostnameVerifier;

	RETURN_TRUE;
}


PHP_METHOD(JedisFactory, setHostAndPort)
{
	zval *obj, *atomicReference;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "o", &obj) == FAILURE) {
		RETURN_FALSE;
	}

	atomicReference = zend_read_property(jedis_factory_ce, getThis(), "hostAndPort", strlen("hostAndPort"), 0 TSRMLS_DC);
	zend_call_method_with_1_params(&atomicReference, atomic_reference_ce, NULL, "set", NULL, obj);
	zend_update_property(jedis_factory_ce, getThis(), "hostAndPort", strlen("hostAndPort"), atomicReference TSRMLS_DC);

	RETURN_TRUE;
}


PHP_METHOD(JedisFactory, activateObject)
{

}


PHP_METHOD(JedisFactory, destroyObject)
{

}


PHP_METHOD(JedisFactory, makeObject)
{

}


PHP_METHOD(JedisFactory, passivateObject)
{

}


PHP_METHOD(JedisFactory, validateObject)
{

}

