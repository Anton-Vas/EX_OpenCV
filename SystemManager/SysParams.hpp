#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
// #include <mutex>


using namespace std;
using namespace cv;



/////////////////////////////////////////////////////////////////////////////////////////////////////////
///     System connector                                                                              ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////

class SysConnector{
private:
    static SysConnector*  _instance;

public:
    bool                f_video_run                 = true;

        /* super resolution */
    bool                f_supres                    = false;    ///> general
    bool                f_supres_init               = false;    ///> INIT
    bool                f_supres_enable             = false;    ///> RUN
    bool                f_supres_wind_close         = false;    ///> widow close

        /* tracking */
    bool                f_track                     = false;    ///> general
    bool                f_track_init                = false;    ///> INIT
    bool                f_track_enable              = false;    ///> RUN
    bool                f_track_wind_close          = false;    ///> widow close

        /* shape recognition */
    bool                f_shrec                     = false;    ///> general
    bool                f_shrec_init                = false;    ///> INIT
    bool                f_shrec_enable              = false;    ///> RUN
    bool                f_shrec_wind_close          = false;    ///> widow close

        /* hand recognition */
    bool                f_hrec                      = false;    ///> general
    bool                f_hrec_init                 = false;    ///> INIT
    bool                f_hrec_enable               = false;    ///> RUN
    bool                f_hrec_wind_close           = false;    ///> widow close

        /* image classification */
    bool                f_objdet                      = false;    ///> general
    bool                f_objdet_init                 = false;    ///> INIT
    bool                f_objdet_enable               = false;    ///> RUN
    bool                f_objdet_wind_close           = false;    ///> widow close



    static SysConnector* get_instance               ();
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////
///     SysGUI                                                                                        ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////

class SysGUI{
private:
    static SysGUI*      _instance;

public:
    enum track_stat{
        OK,
        LOST,
        WAIT
    };
    enum track_type{
        MIL,
        KCF,
        CSRT
    };
    string              track_type_name;



    ///>.. GUI ...........................................................................................
                                                    /*  b    g    r    A*/
        /* General */
    const Scalar        c_clr_WHITE                 = {255, 255, 255,  0};
    const Scalar        c_clr_BLACK                 = {  0,   0,   0,  0};
        /* Status */
    const Scalar        c_clr_RED                   = {  0,   0, 255,  0};
    const Scalar        c_clr_GREEN                 = { 51, 255,   0,  0};
    const Scalar        c_clr_GREY                  = {118, 118, 118,  0};
        /* Tracking */
    const Scalar        c_clr_TR_MIL                = {  0, 230, 255,  0};
    const Scalar        c_clr_TR_KCF                = {255, 222,   0,  0};
    const Scalar        c_clr_TR_CSRT               = {255,   0, 196,  0};

        /* positions */
    const Point2i       c_pos_fps                   = {20, 50};
    Point2i             c_pos_track_stat            = {0, 0};


    
    ///>.. Windows Names .................................................................................
        /* video window */
    const string        c_org_wind_name             = "ORG";
    const int           c_vid_wind_flag             = WINDOW_AUTOSIZE;

        /* super resolution window */
    const string        c_fsrcnn_wind_name          = "SupRes-FSRCNN";

        /* tracking window */
    const string        c_track_wind_name           = "Single Track";

        /* shape recognition */
    const string        c_shrec_wind_name           = "Shape Recognition";

        /* hand recognition */
    const string        c_hrec_wind_name            = "Hand Recognition";

        /* hand recognition */
    const string        c_objdet_wind_name          = "Image Classification";



    ///> main interface
    void                show_video_FPS              (Mat& _frame, const double _fps);
    void                show_video_TRACK_STAT       (Mat& _frame, const int _type, const int _status);
    Scalar              set_stat_color              (const int _status);

    static SysGUI*      get_instance                ();

};