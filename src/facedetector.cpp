/*
 * facedetector.cpp
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