
#include <iostream>
#include <array>
#include <filesystem>

#include <DebugPrint.hpp>

using namespace std;

/*  FAQ:
*
*   Q:  Where can i download those dependencies?
*   A:  https://github.com/opencv/opencv_extra/tree/master/testdata/dnn
* 
*   Q:  How to use them?
*   A:  Place them in ./SystemDependencies and create custom elements in enum-s .._FILE.
*       After that, just call 'files->get_path_to([ENUM_UNIT], [ENUM_FILE])'.
*
* */
class SysFiles{
public:
    ///> main interface
    enum UNIT{
        SUPRES,
        DETECT
    };
    enum SUPRES_FILE{
        FSRCNN_x2,
        FSRCNN_x3,
        FSRCNN_x4,
        FSRCNN_small_x2,
        FSRCNN_small_x3,
        FSRCNN_small_x4,

        SUPRES_FILE_END
    };
    enum DETECT_FILE{
        /* classes */
        OBJECT_DETECTION_CLASSES_COCO_txt,                      ///> tst list of objects classes
        COLORS_txt,                                             ///> txt list of colors

        /* model */
        FROZEN_INTERFACE_GRAPH_objdet_pb,                       ///> pre-trained weights
        FROZEN_INTERFACE_GRAPH_detseg_pb,                       ///> pre-trained weights
        MOBILENETSSD_DEPLOY_caffemodel,

        /* config */
        SSD_MOBILENET_V2_COCO_2018_03_29_pbtxt_txt,
        MOBILENETSSD_DEPLOY_prototxt_txt,
        MASK_RCNN_INCEPTION_V2_COCO_2018_01_28_pbtxt,

        DETECT_FILE_END
    };

private:

    ///> system interface
    static SysFiles*    _instance;
    filesystem::path    file                        = {""};

    ///> main interface
    const array<string, SUPRES_FILE_END> file_supres = {
            /* FSRCNN_x2 */                         "FSRCNN_x2.pb",
            /* FSRCNN_x3 */                         "FSRCNN_x3.pb",
            /* FSRCNN_x4 */                         "FSRCNN_x4.pb",
            /* FSRCNN_small_x2 */                   "FSRCNN-small_x2.pb",
            /* FSRCNN_small_x3 */                   "FSRCNN-small_x3.pb",
            /* FSRCNN_small_x4 */                   "FSRCNN-small_x4.pb",
    };
    const array<string, DETECT_FILE_END> file_detect = {
            /* OBJECT_DETECTION_CLASSES_COCO_txt */             "object_detection_classes_coco.txt",
            /* COLORS_txt */                                    "colors.txt",
            
            /* FROZEN_INTERFACE_GRAPH_objdet_pb */              "frozen_inference_graph_objdet.pb",
            /* FROZEN_INTERFACE_GRAPH_detseg_pb */              "frozen_inference_graph_detseg.pb",
            /* MOBILENETSSD_DEPLOY_caffemodel */                "MobileNetSSD_deploy.caffemodel",
            
            /* SSD_MOBILENET_V2_COCO_2018_03_29_pbtxt_txt */    "ssd_mobilenet_v2_coco_2018_03_29.pbtxt.txt",
            /* MOBILENETSSD_DEPLOY_prototxt_txt */              "MobileNetSSD_deploy.prototxt.txt",
            /* MASK_RCNN_INCEPTION_V2_COCO_2018_01_28_pbtxt */  "mask_rcnn_inception_v2_coco_2018_01_28.pbtxt"//.txt"
    };


    ///> debug print
    DebugPrint*         debug                       = DebugPrint::get_instance();



public:

    ///> system interface
    SysFiles();
    SysFiles(SysFiles& _src)                        = delete; ///> Copy semantics
    SysFiles& operator=(SysFiles const&)            = delete;
    SysFiles(SysFiles&& _src)                       = delete; ///> Move semantics
    SysFiles& operator=(SysFiles const&&)           = delete;
    ~SysFiles();

    static SysFiles*     get_instance                   ();

    string               get_path_to                (const int _unit, const int _file);

};