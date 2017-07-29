/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2017 The PHP Group                                |
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
#include "php_mystr.h"

/* If you declare any globals in php_mystr.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(mystr)
*/

/* True global resources - no need for thread safety here */
static int le_mystr;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("mystr.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_mystr_globals, mystr_globals)
    STD_PHP_INI_ENTRY("mystr.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_mystr_globals, mystr_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_mystr_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_mystr_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "mystr", arg);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_mystr_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_mystr_init_globals(zend_mystr_globals *mystr_globals)
{
	mystr_globals->global_value = 0;
	mystr_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(mystr)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(mystr)
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
PHP_RINIT_FUNCTION(mystr)
{
#if defined(COMPILE_DL_MYSTR) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(mystr)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(mystr)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "mystr support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 * 提取字符串中的所有数字	
 */
PHP_FUNCTION(strnumber)
{
    zend_string *str;
    zend_string *result = NULL;
    size_t	   i,pos=0;

    ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(str)
	ZEND_PARSE_PARAMETERS_END();

	if (ZSTR_LEN(str) == 0) {
		return;
	}
	result = zend_string_safe_alloc(1, ZSTR_LEN(str), 0, 0);
	ZSTR_LEN(result) = 0;

	for(i = 0; i< ZSTR_LEN(str); i++){
		if(ZSTR_VAL(str)[i] >= '0' && ZSTR_VAL(str)[i] <= '9'){
			ZSTR_VAL(result)[pos] = ZSTR_VAL(str)[i];
			pos ++;
		}
	}
	ZSTR_LEN(result) = pos;
	ZSTR_VAL(result)[ZSTR_LEN(result)] = '\0';

	RETURN_NEW_STR(result);
}
/* }}} */

/* {{{ php_reverse_str
 * 反转字符串
 */
static void php_reverse_str(char *str, size_t begin, size_t end)
{
	while(begin < end){
		char tmp = str[begin];
		str[begin] = str[end];
		str[end] = tmp;

		begin ++;
		end --;	
	}
}
/* }}} */

/* {{{ php_reverse_str
 * pos的位置左旋转字符串
 */
PHP_FUNCTION(strlra)
{
	zend_string *str;
    zend_long	 pos, first_begin=0, first_end, second_begin, second_end;
    char *p;

    ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(str)
		Z_PARAM_LONG(pos)
	ZEND_PARSE_PARAMETERS_END();

	if(ZSTR_LEN(str) <= 0 ){
		return;
	}

	if(pos < 0 || pos > ZSTR_LEN(str)){
		return;
	}

	first_end = pos -1;
	second_begin = pos;
	second_end = ZSTR_LEN(str)-1;

	p = ZSTR_VAL(str);
	php_reverse_str(p, first_begin, first_end);
	php_reverse_str(p, second_begin, second_end);
	php_reverse_str(p, first_begin, second_end);

	RETURN_STR_COPY(str);
}
/* }}} */

/* {{{ mystr_functions[]
 *
 * Every user visible function must have an entry in mystr_functions[].
 */
const zend_function_entry mystr_functions[] = {
	PHP_FE(strnumber,	NULL)
	PHP_FE(strlra,	NULL)	
	PHP_FE(confirm_mystr_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in mystr_functions[] */
};
/* }}} */

/* {{{ mystr_module_entry
 */
zend_module_entry mystr_module_entry = {
	STANDARD_MODULE_HEADER,
	"mystr",
	mystr_functions,
	PHP_MINIT(mystr),
	PHP_MSHUTDOWN(mystr),
	PHP_RINIT(mystr),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(mystr),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(mystr),
	PHP_MYSTR_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MYSTR
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(mystr)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
