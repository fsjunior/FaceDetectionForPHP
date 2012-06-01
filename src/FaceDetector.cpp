#include "FaceDetector.h"
//#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

const char HAARCASCADEFILE[] = "frontface.xml";


class CascadeClassifierOpenException : Exception { const char* what() const throw() {}; };


FaceDetector::FaceDetector():classifier(HAARCASCADEFILE)
{   
    if(classifier.empty()) 
        throw CascadeClassifierOpenException();
}

int FaceDetector::detect(Mat &img, vector<Rect> &objects)
{
    if(!img.data)
        return -1;
    
    /* Resize image if needed */
    
    /* if(img.cols > 500 || img.rows > 500) {
        float factor = 500.0 / (float)((img.cols > img.rows)? img.cols : img.rows);
        
        resize(img, img, Size(factor * (float) img.cols, factor * (float) img.rows));
    } */
    
    classifier.detectMultiScale(img, objects);
    return objects.size();
}


int FaceDetector::detect(const string &filename, std::vector<cv::Rect> &objects)
{
    Mat image;
    image = imread(filename);
    return detect(image, objects);
}

