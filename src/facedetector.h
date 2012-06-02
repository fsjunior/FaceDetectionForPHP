/*
 * facedetector.h
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

