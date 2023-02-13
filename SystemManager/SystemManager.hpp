#pragma once

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

#include <DebugPrint.hpp>
#include <SysParams.hpp>
#include <SysFiles.hpp>

using namespace std;
using namespace cv;


    /* super resolution */
#include <opencv2/dnn_superres.hpp>
using namespace dnn_superres;

    /* tracking */
#include <opencv2/tracking.hpp>

    /* image classification */
using namespace dnn;





class DebugPrint;


/////////////////////////////////////////////////////////////////////////////////////////////////////////
///     SystemManager                                                                                 ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////

class SystemManager{
private:

    ///> system interface
    string              vid_port                    = {"/dev/video0"};
    VideoCapture        vid_capture;
    double              timer_fps;
    double              fps;
    const int           c_org_w                     = 1280;
    const int           c_org_h                     = 720;
    Mat                 org_frame                   = {c_org_w, c_org_h, CV_8U, { 0, 0, 255, 255}};
    SysConnector*       sys_param                   = SysConnector::get_instance();
    SysGUI*             gui                         = SysGUI::get_instance();
    SysFiles*           files                       = SysFiles::get_instance();

    ///> main interface
        /* (supres) super resolution */
    DnnSuperResImpl     sr;
    Mat                 out_supres_frame;
    const string        fsrcnn_model_file           = "FSRCNN_x2";
    const string        fsrcnn_model_name           = "fsrcnn";
    const int           fsrcnn_scale                = 2;


        /* (track) tracking */
    const int           c_tr_rect_dif               = 40;
    Rect                roi_mil_rect                = {
        (c_org_w/2) - c_tr_rect_dif, 
        (c_org_h/2) - c_tr_rect_dif,
        c_tr_rect_dif*2,
        c_tr_rect_dif*2
    };
    Rect                roi_kcf_rect                = {
        (c_org_w/2) - c_tr_rect_dif, 
        (c_org_h/2) - c_tr_rect_dif,
        c_tr_rect_dif*2,
        c_tr_rect_dif*2
    };
    Rect                roi_csrt_rect               = {
        (c_org_w/2) - c_tr_rect_dif, 
        (c_org_h/2) - c_tr_rect_dif,
        c_tr_rect_dif*2,
        c_tr_rect_dif*2
    };
    bool                f_track_mil_status          = false;
    bool                f_track_kcf_status          = false;
    bool                f_track_csrt_status         = false;
    Ptr<Tracker>        tracker_mil                 = nullptr;
    Ptr<Tracker>        tracker_kcf                 = nullptr;
    Ptr<Tracker>        tracker_csrt                = nullptr;
    Mat                 out_track_frame;


        /* (shrec) shape recognition */
    const double        c_canny_threshold1          = 60;//0 80;                        // cv::Canny |> 1-st threshold for the hysteresis procedure
    const double        c_canny_threshold2          = 200;//50 240;                     //           |> 2-nd threshold for the hysteresis procedure
    const int           c_canny_apertureSize        = 3;//5 3;                          //           |> aperture size for the Sobel operator
    const bool          c_canny_L2gradient          = false;                            //           |> a flag, indicating whether a more accurate should be used to calculate the image gradient magnitude (TRUE), or whether the default (FALSE)
    const int           c_find_cntr_mode            = RETR_EXTERNAL;                    // cv::findContour |> mode of the contour retrieval algorithm
    const int           c_find_cntr_method          = CHAIN_APPROX_SIMPLE;              //                 |> the contour approximation algorithm
	int                 shrec_vtc;                                                      //> number of vertices of polygonal curve
    double              shrec_mincos;                                                   //> lowest cosine
    double              shrec_maxcos;                                                   //> highest cosine
    double              shrec_circle_area;                                              // circle (shape) |> area
    int                 shrec_circle_radius;                                            //                |> radius
    Rect                shrec_circle_rect;                                              //                |> rectangle around giver circle
    vector<vector<Point>>   shrec_contours;                                             //> contours container
	vector<Point>           shrec_approx;                                               //> approximation container for 'shrec_contours'
    Mat                 out_shrec_frame;                                                //> FINAL frame
    Mat                 tmp_shrec_frame;                                                //>     + shape labels
    Mat                 gray_shrec_frame;                                               //>     + 1st frame rework (gray)
    Mat                 edges_shrec_frame;                                              //>     + 2nd frame rework (edges 1 channel)
    Mat                 edges_tmp_shrec_frame;                                          //>     + 3nd frame rework (edges 3 channel)


        /* (hrec) hand recognition */
    Mat                 out_hrec_frame;


        /* (objdet) image classification */
    vector<string>      objdet_obj_names;
    Net                 objdet_trained_model;
    string              objdet_path_framework       = "TensorFlow";
    const int           c_objdet_blob_scale         = 720;                              //> 224 | 300 | 720
    int                 box_x_objdet;
    int                 box_y_objdet;
    int                 box_w_objdet;
    int                 box_h_objdet;
    int                 obj_id_objdet;
    int                 confidence_id_objdet;
    Mat                 objdet_blob_frame;
    Mat                 objdet_out_model_frame;
    Mat                 out_objdet_frame;


    ///> debug print
    DebugPrint*         debug                       = DebugPrint::get_instance();

public:

    ///> system interface
    SystemManager();
    SystemManager(SystemManager& _src)              = delete;                           ///> Copy semantics
    SystemManager& operator=(SystemManager const&)  = delete;
    SystemManager(SystemManager&& _src)             = delete;                           ///> Move semantics
    SystemManager& operator=(SystemManager const&&) = delete;
    ~SystemManager();

    ///> main interface
    void                system_loop                 ();

    void                enable_video_GUI            ();
    void                enable_supres               ();
    void                enable_track                ();
    void                enable_shrec                ();
    void                enable_hrec                 ();
    void                enable_objdet               ();

    void                setup_video_GUI             ();
    void                setup_supres                ();
    void                setup_track                 ();
    void                setup_shrec                 ();
    void                setup_hrec                  ();
    void                setup_objdet                ();

    void                get_cmd                     (const char _cmd);
    void                clear_all_flags             ();

    /* DESCRIPTION: additional functions
    *
    *   File:               SysHelper.cpp
    *  
    *   ! SPECIFICALLY FOR SHAPE RECOGNITION !
    *
    *   get_cosine_angle()  - find a cosine of angle between vectors from pt0->pt1 and pt0->pt2
    *   set_shrec_label()   - display text in the center of a contour
    * 
    */
    double              get_cosine_angle            (const Point _pt1, const Point _pt2, const Point _pt0);
    void                set_shrec_label             (const Mat& _im, const string _label, vector<Point>& _contour);

    /* DESCRIPTION: window settings
    *
    *   File:               SysWindow.cpp
    * 
    */
    void                create_window               (const string& _win_name, const int _win_flag);
    void                destroy_all_windows         ();
    void                destroy_window              (const string& _win_name);
    void                resize_window               (const string& _win_name, const int _w, const int _h);



};



