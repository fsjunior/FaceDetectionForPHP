PHP_ARG_ENABLE(chicofd,
    [Whether to enable the "Chico's Face Detection" extension],
    [  --enable-chicofd      Enable "Chico's Face Detection" extension support])

if test $PHP_CHICOFD != "no"; then
    PHP_REQUIRE_CXX()
    PHP_SUBST(CHICOFD_SHARED_LIBADD)
    PHP_ADD_LIBRARY(stdc++, 1, CHICOFD_SHARED_LIBADD)
    PHP_ADD_LIBRARY(opencv_core, 1, CHICOFD_SHARED_LIBADD)
    PHP_ADD_LIBRARY(opencv_imgproc, 1, CHICOFD_SHARED_LIBADD)
    PHP_ADD_LIBRARY(opencv_highgui, 1, CHICOFD_SHARED_LIBADD)
    PHP_ADD_LIBRARY(opencv_objdetect, 1, CHICOFD_SHARED_LIBADD)
    PHP_NEW_EXTENSION(chicofd, src/FaceDetector.cpp src/php_chicofd.cpp, $ext_shared)
fi
