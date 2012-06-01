#ifndef PHP_FACEDETECTION_H
#define PHP_FACEDETECTION_H

#define PHP_FACEDETECTION_EXTNAME  "facedetection"
#define PHP_FACEDETECTION_EXTVER   "0.1"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif 

#include "php.h"

PHP_FUNCTION(face_detect_draw);
//PHP_FUNCTION(face_detect);


extern zend_module_entry facedetection_module_entry;

//#define phpext_chicofd_ptr &chicofd_module_entry;




#endif /* PHP_FACEDETECTION_H */
