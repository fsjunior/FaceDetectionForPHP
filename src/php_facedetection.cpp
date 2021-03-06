/*
 * php_facedetection.cpp
 * 
 * Copyright (c) 2012 Francisco de Souza Júnior <fsjunior at gmail.com>. 
 * 
 * This file is part of FaceDetectionForPHP.
 * 
 * FaceDetectionForPHP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FaceDetectionForPHP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with FaceDetectionForPHP.  If not, see <http ://www.gnu.org/licenses/>.
 */
#include <opencv2/highgui/highgui.hpp>
#include "php.h"
#include "php_ini.h"
#include "zend_exceptions.h"
#include "standard/info.h"

#include "facedetector.h"
#include "php_facedetection.h"

using namespace cv;

/* Defines */
#define FACEDETECTION_NAMESPACE "Facedetection"

#ifndef PHP_NS_FE
#define PHP_NS_FE ZEND_NS_FE
#endif

/* Persistent Objects*/
FaceDetector f;


/* module functions */
PHP_MINIT_FUNCTION(facedetection);
PHP_MSHUTDOWN_FUNCTION(facedetection);
PHP_MINFO_FUNCTION(facedetection);

/* Functions */
PHP_FUNCTION(detect_draw);
PHP_FUNCTION(cascade_loaded);



/* Configurations */
#define CASCADE_INI_CONFIG "facedetection.cascade"
#define FILE_IN_DIR "facedetection.file_in_dir"
#define FILE_OUT_DIR "facedetection.file_out_dir"


PHP_INI_MH(on_cascade_change);

/* Function List*/
static zend_function_entry facedetection_functions[] = {
    PHP_NS_FE(FACEDETECTION_NAMESPACE, detect_draw, NULL)
    PHP_NS_FE(FACEDETECTION_NAMESPACE, cascade_loaded, NULL)
    {
        NULL, NULL, NULL
    }
};

/* Module Information */
zend_module_entry facedetection_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_FACEDETECTION_EXTNAME,
    facedetection_functions, /* Functions */
    PHP_MINIT(facedetection),
    PHP_MSHUTDOWN(facedetection), /* MSHUTDOWN */
    NULL, /* RINIT */
    NULL, /* RSHUTDOWN */
    PHP_MINFO(facedetection), /* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
    PHP_FACEDETECTION_EXTVER,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_FACEDETECTION
extern "C" {
    ZEND_GET_MODULE(facedetection)
}
#endif

/* Configuration Definition */

/* TODO: add php.ini values as global variables to reduce computation in INI_STR macro */
PHP_INI_BEGIN()
PHP_INI_ENTRY(CASCADE_INI_CONFIG, "", PHP_INI_ALL, on_cascade_change)
PHP_INI_ENTRY(FILE_IN_DIR, "", PHP_INI_ALL, NULL)
PHP_INI_ENTRY(FILE_OUT_DIR, "", PHP_INI_ALL, NULL)
PHP_INI_END()

PHP_INI_MH(on_cascade_change)
{
    //zend_printf("New value: %s\n", new_value);
    if (f.setCascade(new_value))
        return SUCCESS;
    else
        return FAILURE;
}

/* Module Function Definition*/

PHP_MINIT_FUNCTION(facedetection)
{
    REGISTER_INI_ENTRIES();
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(facedetection)
{
    UNREGISTER_INI_ENTRIES();
    return SUCCESS;
}

PHP_MINFO_FUNCTION(facedetection)
{
    php_info_print_table_start();
    php_info_print_table_row(2, "Face detection support", "Enabled");
    php_info_print_table_row(2, "Version", PHP_FACEDETECTION_EXTVER);
    php_info_print_table_end();

    DISPLAY_INI_ENTRIES();
}

/* Function Definitions */

PHP_FUNCTION(cascade_loaded)
{
    RETURN_BOOL(f.cascadeLoaded());
}

PHP_FUNCTION(detect_draw)
{
    Mat img;
    std::vector<Rect> objects;
    char *filein, *fileout;
    long fileinlen, fileoutlen;
    string fpfilein, fpfileout;


    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &filein, &fileinlen, &fileout, &fileoutlen) == FAILURE)
        RETURN_BOOL(false);


    /* Always adds a slash */
    fpfilein = string(INI_STR(FILE_IN_DIR)) + "/" + string(filein);

    img = imread(fpfilein.c_str());

    switch (f.detect(img, objects)) {
        case ERROR_CASCADE_NOT_LOADED:
            zend_throw_exception(zend_exception_get_default(TSRMLS_C),
                    "Cascade train data not loaded", 0 TSRMLS_CC);
            RETURN_BOOL(false);
            break;
        case ERROR_CANNOT_OPEN_IMAGE:
            zend_throw_exception(zend_exception_get_default(TSRMLS_C),
                    "Cannot open the image", 0 TSRMLS_CC);
            RETURN_BOOL(false);
            break;
    }

    for (vector<Rect>::iterator object = objects.begin(); object != objects.end(); object++)
        cv::rectangle(img, *object, cv::Scalar(0, 255, 0));

    /* Always adds a slash */
    fpfileout = string(INI_STR(FILE_OUT_DIR)) + "/" + string(fileout);

    if (imwrite(fpfileout.c_str(), img)) {
        RETURN_BOOL(true);
    } else {
        zend_throw_exception(zend_exception_get_default(TSRMLS_C),
                "Cannot save the image.", 0 TSRMLS_CC);
        RETURN_BOOL(false);
    }
}

