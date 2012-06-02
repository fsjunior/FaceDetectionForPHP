/*
 * php_facedetection.h
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

#ifndef PHP_FACEDETECTION_H
#define PHP_FACEDETECTION_H

#define PHP_FACEDETECTION_EXTNAME  "facedetection"
#define PHP_FACEDETECTION_EXTVER   "0.1"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif 

#include "php.h"


extern zend_module_entry facedetection_module_entry;


#endif /* PHP_FACEDETECTION_H */
