/*
 * host_and_port.c
 *
 *  Created on: 2019年2月11日
 *      Author: sam
 */

#include "common.h"
#include "Zend/zend_interfaces.h"
#include "Zend/zend_API.h"
#include "php_extdemo.h"


zend_class_entry *host_and_port_ce;

PHP_METHOD(HostAndPort, __construct);
PHP_METHOD(HostAndPort, getHost);
PHP_METHOD(HostAndPort, getPort);
PHP_METHOD(HostAndPort, equals);
PHP_METHOD(HostAndPort, hashCode);
PHP_METHOD(HostAndPort, toString);
PHP_METHOD(HostAndPort, extractParts);
PHP_METHOD(HostAndPort, parseString);
PHP_METHOD(HostAndPort, convertHost);
PHP_METHOD(HostAndPort, getLocalHostQuietly);


zend_function_entry host_and_port_method[] = {
		PHP_ME(HostAndPort, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
		PHP_ME(HostAndPort, getHost, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(HostAndPort, getPort, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(HostAndPort, equals, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(HostAndPort, hashCode, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(HostAndPort, toString, NULL, ZEND_ACC_PUBLIC)
		PHP_ME(HostAndPort, extractParts, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
		PHP_ME(HostAndPort, parseString, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
		PHP_ME(HostAndPort, convertHost, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
		PHP_ME(HostAndPort, getLocalHostQuietly, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
		PHP_FE_END
};


EXTDEMO_STARTUP_FUNCTION(HostAndPort) {
	zend_class_entry hostandportce;
	INIT_CLASS_ENTRY(hostandportce, "HostAndPort", host_and_port_method);
	host_and_port_ce = zend_register_internal_class(&hostandportce TSRMLS_CC);

	//private static final long serialVersionUID = -519876229978427751L;
	zend_declare_class_constant_long(host_and_port_ce, "serialVersionUID", strlen("serialVersionUID"), 0);
	//public static final String LOCALHOST_STR = getLocalHostQuietly();
	zend_declare_class_constant_string(host_and_port_ce, "LOCALHOST_STR", strlen("LOCALHOST_STR"), "");
	//protected static Logger log = Logger.getLogger(HostAndPort.class.getName());
	zend_declare_property_null(host_and_port_ce, "log", strlen("log"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC);

	//private String host;
	zend_declare_property_null(host_and_port_ce, "host", strlen("host"), ZEND_ACC_PRIVATE);
	//private int port;
	zend_declare_property_null(host_and_port_ce, "port", strlen("port"), ZEND_ACC_PRIVATE);

	return SUCCESS;
}


PHP_METHOD(HostAndPort, __construct)
{
	char *host;
	unsigned long host_len, port;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &host, &host_len, &port) == FAILURE) {
		RETURN_FALSE;
	}

	zend_update_property_string(host_and_port_ce, getThis(), "host", strlen("host"), host);
	zend_update_property_long(host_and_port_ce, getThis(), "port", strlen("port"), port TSRMLS_DC);

	RETURN_TRUE;
}


PHP_METHOD(HostAndPort, getHost)
{
	zval *ret;
	ret = zend_read_property(host_and_port_ce, getThis(), "host", strlen("host"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(HostAndPort, getPort)
{
	zval *ret;
	ret = zend_read_property(host_and_port_ce, getThis(), "port", strlen("port"), 0 TSRMLS_DC);
	RETURN_ZVAL(ret, 1, 0);
}


PHP_METHOD(HostAndPort, equals)
{

}


PHP_METHOD(HostAndPort, hashCode)
{

}


PHP_METHOD(HostAndPort, toString)
{
	zval *host, *port, *middle;

	host = zend_read_property(host_and_port_ce, getThis(), "host", strlen("host"), 0 TSRMLS_DC);
	port = zend_read_property(host_and_port_ce, getThis(), "port", strlen("port"), 0 TSRMLS_DC);
	convert_to_string(port);

	MAKE_STD_ZVAL(middle);
	ZVAL_STRING(middle, ":", 1);

	add_string_to_string(return_value, host, middle);
	add_string_to_string(return_value, return_value, port);
}


PHP_METHOD(HostAndPort, extractParts)
{

}


PHP_METHOD(HostAndPort, parseString)
{

}


PHP_METHOD(HostAndPort, convertHost)
{

}


PHP_METHOD(HostAndPort, getLocalHostQuietly)
{

}




