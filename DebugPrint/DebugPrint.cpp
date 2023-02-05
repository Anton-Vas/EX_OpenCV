
#include <DebugPrint.hpp>



DebugPrint::DebugPrint                          (){
    /*~~~~~~~~~~~~~~~ ADD ~~~~~~~~~~~~~~~*/
}

DebugPrint::~DebugPrint                         (){
    delete _instance;
}


    /* singleton */
DebugPrint* DebugPrint::_instance = nullptr;
DebugPrint* DebugPrint::get_instance            (){
    if(_instance == nullptr){
        _instance = new DebugPrint();
    }
    return _instance;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
///     main interface                                                                                ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*   cout << "" << c_new_line;
*   cout << endl;
*/

void DebugPrint::print_sys_capture_info         (VideoCapture* _cap){
    cout << c_INFO_header + "Video capture" << c_new_line;
    
    int fourcc = _cap->get(CAP_PROP_FOURCC);
    cout << "             | FOURCC  : " << format("%c%c%c%c", fourcc & 255, (fourcc >> 8) & 255, (fourcc >> 16) & 255, (fourcc >> 24) & 255) << c_new_line;
    cout << "             | FPS     : " << _cap->get(CAP_PROP_FPS) << c_new_line;
    cout << "             | Frame H : " << _cap->get(CAP_PROP_FRAME_HEIGHT) << c_new_line;
    cout << "             |_Frame W : " << _cap->get(CAP_PROP_FRAME_WIDTH) << c_new_line;
    cout << endl;
}

void DebugPrint::print_sys_opencv_info          (){
    cout << "> Opencv info:" << c_new_line;
    cout << getBuildInformation() << c_new_line;
    cout << endl;
}

void DebugPrint::print_frame_type_info          (const Mat& _frame, const char* _frame_name){
    string  txt_type;
    int     code_type = _frame.type();

    uchar   depth = code_type & CV_MAT_DEPTH_MASK;
    uchar   chans = 1 + (code_type >> CV_CN_SHIFT);

    switch ( depth ) {
    case CV_8U:  txt_type = "8U"; break;
    case CV_8S:  txt_type = "8S"; break;
    case CV_16U: txt_type = "16U"; break;
    case CV_16S: txt_type = "16S"; break;
    case CV_32S: txt_type = "32S"; break;
    case CV_32F: txt_type = "32F"; break;
    case CV_64F: txt_type = "64F"; break;
    default:     txt_type = "USER"; break;
    }

    txt_type += "C";
    txt_type += (chans + "C");

    cout << c_INFO_header + "Frame analyze" << endl;
    cout << "             | Name   : " << _frame_name       << c_new_line;
    cout << "             | Type   : " << txt_type          << c_new_line;
    cout << "             | Chan-s : " << _frame.channels() << c_new_line;
    cout << "             | Depth  : " << _frame.depth()    << c_new_line;
    cout << "             |_WxH    : " << _frame.cols << "x" << _frame.rows << c_new_line;
    cout << endl;
}

void DebugPrint::print_debug                    (const int _type, const int _msg_i){
    switch(_type){
    case DONE:
        cout << c_DONE_header << msg_done[_msg_i] << endl;
        break;

    case ERROR:
        cout << c_ERROR_header << msg_error[_msg_i] << endl;
        break;

    case INFO:
        cout << c_INFO_header << msg_info[_msg_i] << endl;
        break;
    }
}

void DebugPrint::print_debug                    (const int _type, const int _msg_i, const string& _msg){
    switch(_type){
    case DONE:
        cout << c_DONE_header << msg_done[_msg_i] << ": " << _msg << endl;
        break;

    case ERROR:
        cout << c_ERROR_header << msg_error[_msg_i] << ": " << _msg << endl;
        break;

    case INFO:
        cout << c_INFO_header << msg_info[_msg_i] << "> " << _msg << endl;
        break;
    }
}

void DebugPrint::print_debug_msg                (const string& _msg){
    cout << c_sub_header << _msg << endl;
}

void DebugPrint::print_debug_cmd_options        (){
    cout << "      +-------------------------------------------------------------------+" << c_new_line;
    cout << "      |   All options cancel automaticaly before applying users command.  |" << c_new_line;
    cout << "      |                  (Choose video window and press)                  |" << c_new_line;
    cout << "      +-------------------------------------------------------------------+" << c_new_line;
    cout << "      | SYSTEM:                                                           |" << c_new_line;
    cout << "      |   c  : CLOSE all modifications except the original video          |" << c_new_line;
    cout << "      |   d  : DEBUG output control options                               |" << c_new_line;
    cout << "      |                                                                   |" << c_new_line;
    cout << "      | MODIFICATIONS:                                                    |" << c_new_line;
    cout << "      |   s  : super resolution          | h  : hand recognition          |" << c_new_line;
    cout << "      |   t  : single object tracking    | i  : object detection          |" << c_new_line;
    cout << "      |   o  : shape recognition         | ?  :                           |" << c_new_line;
    cout << "      |                                  | ?  :                           |" << c_new_line;
    cout << "      +-------------------------------------------------------------------+" << c_new_line;
    cout << endl;
}