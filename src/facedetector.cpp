#include "facedetector.h"
//#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class CascadeClassifierOpenException : Exception {

    const char* what() const throw ()
    {
    };
};

FaceDetector::FaceDetector(const char *cascadefilename)
{
    if(cascadefilename)
        setCascade(cascadefilename);
}

bool FaceDetector::setCascade(const char *cascadefilename)
{
    cf = cascadefilename;
    if(!cascadefilename || strlen(cascadefilename) == 0)
        return false;

    if(!pClassifier.empty())
        pClassifier.delete_obj();


    pClassifier = new CascadeClassifier(cascadefilename);

    return !pClassifier->empty();
}

int FaceDetector::detect(Mat &img, vector<Rect> &objects)
{
    if(!img.data)
        return -1;
    if(pClassifier.empty())
        return -2;

    /* Resize image if needed */

    /* if(img.cols > 500 || img.rows > 500) {
        float factor = 500.0 / (float)((img.cols > img.rows)? img.cols : img.rows);
        
        resize(img, img, Size(factor * (float) img.cols, factor * (float) img.rows));
    } */

    pClassifier->detectMultiScale(img, objects);
    return objects.size();
}

int FaceDetector::detect(const string &filename, std::vector<cv::Rect> &objects)
{
    Mat image;
    image = imread(filename);
    return detect(image, objects);
}

bool FaceDetector::cascadeLoaded()
{
    return !pClassifier.empty() && !pClassifier->empty();
}