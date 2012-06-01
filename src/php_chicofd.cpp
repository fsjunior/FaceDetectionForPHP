#include "php_chicofd.h"
#include "FaceDetector.h"
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
FaceDetector f;

/*PHP_MINIT_FUNCTION(chicofd)
{
    return SUCCESS;
}

PHP_MSHUTDOWN(chicofd)
{
    delete f;
    return SUCCESS;    
}*/

static zend_function_entry chicofd_functions[] = {
    PHP_FE(chicofd_detect, NULL)
    { NULL, NULL, NULL }
};


zend_module_entry chicofd_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_CHICOFD_EXTNAME,
    chicofd_functions, /* Functions */
    NULL, //PHP_MINIT(chicofd),
    NULL, //PHP_MSHUTDOWN(chicofd), /* MSHUTDOWN */
    NULL, /* RINIT */
    NULL, /* RSHUTDOWN */
    NULL, /* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
    PHP_CHICOFD_EXTVER,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_CHICOFD
extern "C" {
    ZEND_GET_MODULE(chicofd)
}
#endif

PHP_FUNCTION(chicofd_detect)
{

    Mat img;
    std::vector<Rect> objects;
    char *filein, *fileout;
    long fileinlen, fileoutlen;

    if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &filein, &fileinlen, &fileout, &fileoutlen) == FAILURE) {
        RETURN_NULL();
    } 


    img = imread(filein);

    f.detect(img, objects);

    for (vector<Rect>::iterator object = objects.begin(); object != objects.end(); object++) {
        cv::rectangle(img, *object, cv::Scalar(0, 255, 0));
    }

    imwrite(fileout, img);
}

