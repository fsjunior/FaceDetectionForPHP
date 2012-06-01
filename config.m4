PHP_ARG_ENABLE(facedetection,
    [Whether to enable the "Chico's Face Detection" extension],
    [  --enable-facedetection      Enable "Chico's Face Detection" extension support])

if test $PHP_FACEDETECTION != "no"; then
    PHP_REQUIRE_CXX()
    PHP_SUBST(FACEDETECTION_SHARED_LIBADD)
    PHP_ADD_LIBRARY(stdc++, 1, FACEDETECTION_SHARED_LIBADD)
    PHP_ADD_LIBRARY(opencv_core, 1, FACEDETECTION_SHARED_LIBADD)
    PHP_ADD_LIBRARY(opencv_imgproc, 1, FACEDETECTION_SHARED_LIBADD)
    PHP_ADD_LIBRARY(opencv_highgui, 1, FACEDETECTION_SHARED_LIBADD)
    PHP_ADD_LIBRARY(opencv_objdetect, 1, FACEDETECTION_SHARED_LIBADD)
    PHP_NEW_EXTENSION(facedetection, src/facedetector.cpp src/php_facedetection.cpp, $ext_shared)
fi
