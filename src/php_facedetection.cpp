#include "php_facedetection.h"
#include "facedetector.h"
#include <opencv2/highgui/highgui.hpp>
#include "php_ini.h"


using namespace cv;

/* Persistent Objects*/
FaceDetector f;


/* Functions */
PHP_MINIT_FUNCTION(facedetection);
PHP_MSHUTDOWN_FUNCTION(facedetection);
PHP_MINFO_FUNCTION(facedetection);

PHP_FUNCTION(fd_detect_draw);
PHP_FUNCTION(fd_cascade_loaded);



/* Configurations */
#define CASCADE_INI_CONFIG "facedetection.cascade"
#define FILE_IN_DIR "facedetection.file_in_dir"
#define FILE_OUT_DIR "facedetection.file_out_dir"
PHP_INI_MH(on_cascade_change);

/* Function List*/
static zend_function_entry facedetection_functions[] = {
    PHP_FE(fd_detect_draw, NULL)
    PHP_FE(fd_cascade_loaded, NULL)
    { NULL, NULL, NULL}
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

PHP_INI_BEGIN()
PHP_INI_ENTRY(CASCADE_INI_CONFIG, "", PHP_INI_ALL, on_cascade_change)
PHP_INI_ENTRY(FILE_IN_DIR, "", PHP_INI_ALL, NULL)
PHP_INI_ENTRY(FILE_OUT_DIR, "", PHP_INI_ALL, NULL)
PHP_INI_END()

PHP_INI_MH(on_cascade_change)
{
    //zend_printf("New value: %s\n", new_value);
    if(f.setCascade(new_value))
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
    DISPLAY_INI_ENTRIES();
}

/* Function Definitions */

PHP_FUNCTION(fd_cascade_loaded)
{
    RETURN_BOOL(f.cascadeLoaded());
}

PHP_FUNCTION(fd_detect_draw)
{
    Mat img;
    std::vector<Rect> objects;
    char *filein, *fileout;
    long fileinlen, fileoutlen;  
    string fpfilein, fpfileout;
    

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &filein, &fileinlen, &fileout, &fileoutlen) == FAILURE) {
        RETURN_BOOL(false);
    }
    
    fpfilein = string(INI_STR(FILE_IN_DIR)) + string(filein);
    
    img = imread(fpfilein.c_str());

    if(f.detect(img, objects) < 0)
        RETURN_BOOL(false);

    for(vector<Rect>::iterator object = objects.begin(); object != objects.end(); object++) {
        cv::rectangle(img, *object, cv::Scalar(0, 255, 0));
    }
    
    fpfileout = string(INI_STR(FILE_OUT_DIR)) + string(fileout);

    imwrite(fpfileout.c_str(), img);
    RETURN_BOOL(true);
}

