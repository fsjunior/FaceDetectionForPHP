#include "php_facedetection.h"
#include "facedetector.h"
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
FaceDetector f;

/*PHP_MINIT_FUNCTION(facedetection)
{
    return SUCCESS;
}

PHP_MSHUTDOWN(facedetection)
{
    delete f;
    return SUCCESS;    
}*/

static zend_function_entry facedetection_functions[] = {
    PHP_FE(face_detect_draw, NULL)
    { NULL, NULL, NULL }
};


zend_module_entry facedetection_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_FACEDETECTION_EXTNAME,
    facedetection_functions, /* Functions */
    NULL, //PHP_MINIT(facedetection),
    NULL, //PHP_MSHUTDOWN(facedetection), /* MSHUTDOWN */
    NULL, /* RINIT */
    NULL, /* RSHUTDOWN */
    NULL, /* MINFO */
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

PHP_FUNCTION(face_detect_draw)
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

