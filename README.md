# Exercise in OpenCV

## Purpose

The core idea of this little repo is to practice the OpenCV fundamentals. 
This repo IS NOT SUITABLE FOR PRODUCTION purposes but rather for general use cases overview. 
With this in mind, the presented code below is easy to edit and even easier to understand.

## Code & File tree

The repo was written in/with:
- VS Code (latest version)
- OpenCV 4.5.5 with appropriate Contrib repo-s.

The base contains a few shell scripts for building / configuring / running cases. All of them are presented for simplification of interaction, although the initial methods were VS Code built-in commands.

Other files are system necessities so it`s not worth the time to overview.
```
EX_OPENCV
│   .gitignore
│   CMakeLists.txt
│   build.sh
│   config.sh
│   run.sh
│   main.cpp
│   main.hpp
│   README.md
│   FIXME.md
│
```
DebugPrint contains a special class for notification via the terminal. 
```
│
├───DebugPrint
│       CMakeLists.txt
│       DebugPrint.cpp
│       DebugPrint.hpp
│
```
SystemDependencies contains resources on which every module relies.

- SysFiles (hpp/cpp) - class for files managemants.
```
│
├───SystemDependencies
│       CMakeLists.txt
│       colors.txt
│       frozen_inference_graph_detseg.pb
│       frozen_inference_graph_objdet.pb
│       FSRCNN-small_x2.pb
│       FSRCNN-small_x3.pb
│       FSRCNN-small_x4.pb
│       FSRCNN_x2.pb
│       FSRCNN_x3.pb
│       FSRCNN_x4.pb
│       mask_rcnn_inception_v2_coco_2018_01_28.pbtxt
│       mask_rcnn_inception_v2_coco_2018_01_28.pbtxt.txt
│       MobileNetSSD_deploy.caffemodel
│       MobileNetSSD_deploy.prototxt.txt
│       object_detection_classes_coco.txt
│       ssd_mobilenet_v2_coco_2018_03_29.pbtxt.txt
│       SysFiles.cpp
│       SysFiles.hpp
│
```
SystemManager has all system classes, such as:

- SystemManager (hpp/cpp) - the core. Define systems API.

- SysHelper (cpp) - non-standard functions.

- SysWindows (cpp)- basic OpenCV operations on a window.

- SysParams (hpp/cpp) - system connector for future updates (the container for system flags) and system GUI parameters (windows names, colours, fonts ...).
```
│
└───SystemManager
        CMakeLists.txt
        SysHelper.cpp
        SysParams.cpp
        SysParams.hpp
        SystemManager.cpp
        SystemManager.hpp
        SysWindow.cpp
```

## Usage

Upon starting, the original video stream begins to display. This original, unenhanced video will always be visible in its own window so a user may use an internal interface.

The internal interface allows the activation of units by choosing the original videos window and pressing specific key.

The list of commands:

 SYSTEM:
- [x] c  : CLOSE all modifications except the original video 
- [x] p  : DEBUG print control options
  
UNIT:
- [x] s  : super-resolution 
- [x] i  : object detection
- [x] t  : single object track
- [x] d  : object detection & img segmentation
- [x] o  : shape recognition 
- [ ] h  : hand recognition   [IN PROGRESS]



## Source materials
- [x] __Super resolution (supres)__

    __Task__: _to enhance frames resolution_

    __Source__:
    
    - code/theory__| https://learnopencv.com/super-resolution-in-opencv/
                    
    - protobuf_____| https://github.com/Saafke/FSRCNN_Tensorflow
    
    __Example__:
    
    - FSRCNN (as one of the fastest algorithms)

- [x] __Single object tracking (track)__ 

    __Task__: _to track specific region (pre-aimed to the screens center)_
    
    __Source__:
    
    - code/theory__| https://learnopencv.com/object-tracking-using-opencv-cpp-python/
    
    __Example__:
    
    - MIL
    
    - KCF
    
    - CSRT

- [x] __Basic geometrical shapes recognition (shrec)__ 

    __Task__: _to recognise geometrical shapes and underline its type_
    
    __Source__:
    
    - code/theory__| https://opencvproject.wordpress.com/projects-files/detection-shape/
    
    - code/theory__| https://github.com/bsdnoobz/opencv-code/blob/master/shape-detect.cpp
    
    - contour det-n_| https://learnopencv.com/contour-detection-using-opencv-python-c/#Drawing-Contours-using-CHAIN_APPROX_SIMPLE

- [ ] __Hand recognition (hrec)__

    __Task__: _to recognise hands numeric gestures with OpenCV internal capabilities_
    
    __Source__:
    
    - code/theory__| https://github.com/ahmetyaylalioglu/Estimation-of-the-number-of-real-time-hand-fingers-with-image-processing/blob/master/ElAlgilaV2.cpp
    
- [X] __Object detection (objdet)__

    __Task__: _to detect and outline the region with observable objects (listed in 'object_detection_classes_coco.txt' list)_

    __Source__:

    - code/theory__| https://learnopencv.com/deep-learning-with-opencvs-dnn-module-a-definitive-guide/#guide-to-image-classification

    - code/theory__| https://learnopencv.com/deep-learning-with-opencvs-dnn-module-a-definitive-guide/

    - code_________| https://github.com/ChiekoN/OpenCV_SSD_MobileNet

- [X] __Object Detection and Instance Segmentation using Mask RCNN  (detseg)__

    __Task__: _to detect objects as in 'objdet' but use Mask RCNN to outline specific objects region_

    __Source__:

    - code/theory__| https://learnopencv.com/deep-learning-based-object-detection-and-instance-segmentation-using-mask-rcnn-in-opencv-python-c/


__Additional info:__

- Different Python examples with interesting implementation was taken as smaples.

    - code/theory__| https://github.com/methylDragon/opencv-python-reference
