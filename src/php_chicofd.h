#ifndef PHP_CHICOFD_H
#define PHP_CHICOFD_H

#define PHP_CHICOFD_EXTNAME  "chicofd"
#define PHP_CHICOFD_EXTVER   "0.1"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif 

#include "php.h"

PHP_FUNCTION(chicofd_detect);


extern zend_module_entry chicofd_module_entry;

//#define phpext_chicofd_ptr &chicofd_module_entry;




#endif /* PHP_CHICOFD_H */
