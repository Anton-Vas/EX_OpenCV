
#include <SysParams.hpp>


/////////////////////////////////////////////////////////////////////////////////////////////////////////
///     System connector                                                                              ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////

SysConnector* SysConnector::_instance = nullptr;
SysConnector* SysConnector::get_instance            (){
    if(_instance == nullptr){
        _instance = new SysConnector();
    }
    return _instance;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
///     SysGUI                                                                                        ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////

SysGUI* SysGUI::_instance = nullptr;
SysGUI* SysGUI::get_instance                        (){
    if(_instance == nullptr){
        _instance = new SysGUI();
    }
    return _instance;
}

void SysGUI::show_video_FPS                         (Mat& _frame, const double _fps){
    putText(
        _frame,
        "FPS : " + to_string((int)_fps),
        c_pos_fps,
        c_font,
        1,
        c_clr_BLACK,
        3
    );
    putText(
        _frame,
        "FPS : " + to_string((int)_fps),
        c_pos_fps,
        c_font,
        1,
        c_clr_WHITE,
        1
    );
}

void SysGUI::show_video_TRACK_STAT                  (Mat& _frame,  const int _type, const int _status){

    if      (_type == MIL){
        track_type_name = "TRACK MIL";
        c_pos_track_stat.x = 20;
        c_pos_track_stat.y = 80;
    }
    else if (_type == KCF){
        track_type_name = "TRACK KCF";
        c_pos_track_stat.x = 20;
        c_pos_track_stat.y = 120;
    }
    else if (_type == CSRT){
        track_type_name = "TRACK CSRT";
        c_pos_track_stat.x = 20;
        c_pos_track_stat.y = 160;
    }

    putText(
        _frame,
        track_type_name,
        c_pos_track_stat,
        c_font,
        1,
        set_stat_color(_status),
        2
    );
}

// void SysGUI::show_video_TRACK_AIM                   (Mat& _frame){
//     roi_track_aim.x = (_frame.cols/2) - 40;
//     roi_track_aim.y = (_frame.rows/2) - 40;
//     roi_track_aim.height = 80;
//     roi_track_aim.width = 80;
//     rectangle( 
//         _frame,
//         roi_frame_centre,
//         c_clr_RED,
//         c_thick_STANDARD,
//         1
//     );
// }

void SysGUI::show_video_ERROR_msg                   (Mat& _frame, const string _msg){

	Size text_size = getTextSize(_msg, c_font, c_scale_STANDARD, c_thick_STANDARD, &c_baseline);

    roi_frame_centre.x      = (_frame.cols / 2) - (text_size.width / 2) - 10;
    roi_frame_centre.y      = (_frame.rows / 2) - (text_size.height / 2) - 10;
    roi_frame_centre.height = text_size.height + 20;
    roi_frame_centre.width  = text_size.width + 20;

    rectangle( 
        _frame,
        roi_frame_centre,
        c_clr_RED,
        c_thick_STANDARD,
        1
    );
    putText(
        _frame,
        _msg,
        Point((_frame.cols / 2) - (text_size.width / 2), (_frame.rows / 2) + (text_size.height / 2)),
        c_font,
        c_scale_STANDARD,
        c_clr_RED,
        c_thick_STANDARD,
        8
	);
}

Scalar SysGUI::set_stat_color                       (const int _status){
    if      (_status == OK)   { return c_clr_GREEN; }
    else if (_status == LOST) { return c_clr_RED; }
    else if (_status == WAIT) { return c_clr_GREY; }
    return Scalar(0,0,0);
}