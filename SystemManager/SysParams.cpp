
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
        FONT_HERSHEY_SIMPLEX,
        1,
        c_clr_BLACK,
        3
    );
    putText(
        _frame,
        "FPS : " + to_string((int)_fps),
        c_pos_fps,
        FONT_HERSHEY_SIMPLEX,
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
        FONT_HERSHEY_SIMPLEX,
        1,
        set_stat_color(_status),
        2
    );
}

Scalar SysGUI::set_stat_color                       (const int _status){
    if      (_status == OK)   { return c_clr_GREEN; }
    else if (_status == LOST) { return c_clr_RED; }
    else if (_status == WAIT) { return c_clr_GREY; }
    return Scalar(0,0,0);
}