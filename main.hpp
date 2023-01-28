#pragma once

#include <iostream>
#include <thread>

#include <SystemManager.hpp>


using namespace std;


int main(int, char**);


    /* choose build option */
SysConnector*       sys_param                   = SysConnector::get_instance();


/*----- SUPER RESOLUTION (supres) --------------------------------------------------------------------------------------
*
*       Task:           to enhance frame resolution
*       Source:         (code + theory)     https://learnopencv.com/super-resolution-in-opencv/
*                       (.pb)               https://github.com/Saafke/FSRCNN_Tensorflow
*
*       Taken example:  
*           1. FSRCNN (as one of the fastest algorithms)
*
*/

/*----- SINGLE OBJ TRACKING (track) ------------------------------------------------------------------------------------
*
*       Task:           to track specific region (pre-aimed to the screens center)
*       Source:         (code + theory)     https://learnopencv.com/object-tracking-using-opencv-cpp-python/
*                   
*       Taken example:  
*           1. MIL
*           2. KCF
*           3. CSRT
*
*/

/*----- SHAPE RECOGNITION (shrec) --------------------------------------------------------------------------------------
*
*       Task:           to recognise geometrical shapes and underline its type
*       Source:         (code + theory)     https://opencvproject.wordpress.com/projects-files/detection-shape/
*                       (code + theory)     https://github.com/bsdnoobz/opencv-code/blob/master/shape-detect.cpp
*                       (contour detection) https://learnopencv.com/contour-detection-using-opencv-python-c/#Drawing-Contours-using-CHAIN_APPROX_SIMPLE
*
*/

/*----- MULTI OBJ TRACKING (multrack) ----------------------------------------------------------------------------------
*
*       Task:           to track multiple objects after obj recognition
*       Source:         ...
*                   
*       Taken example:
*           1.
*
*/

/*----- HANDS RECOGNITION (hrec) ---------------------------------------------------------------------------------------
*
*       Task:           to recognise hands movements/gestures with MediaPipe & OpenCV 
*       Source:         (code + theory)     https://github.com/GasbaouiMohammedAlAmin/Finger-Counter-using-Hand-Tracking-And-Open-cv
*                       (MediaPipe)         https://google.github.io/mediapipe/solutions/hands.html
*                       (theory)            https://www.it-jim.com/blog/mini-tutorial-on-mediapipe/
*                       
*
*/     