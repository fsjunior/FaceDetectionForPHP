/* 
 * File:   facedetector.h
 * Author: linuxer
 *
 * Created on May 31, 2012, 12:57 PM
 */

#ifndef FACEDETECTOR_H
#define	FACEDETECTOR_H

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>


class FaceDetector {
protected:
    cv::Ptr<cv::CascadeClassifier> pClassifier;   
public:
    std::string cf;
    FaceDetector(const char *cascadefilename = NULL);
    
    bool setCascade(const char *cascadefilename);
    
    bool cascadeLoaded();
    
    int detect(cv::Mat &img, std::vector<cv::Rect> &objects);
    
    int detect(const std::string &filename, std::vector<cv::Rect> &objects);
};


#endif	/* FACEDETECTOR_H */

