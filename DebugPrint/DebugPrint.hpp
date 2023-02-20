#pragma once

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

#include <SysParams.hpp>


using namespace std;
using namespace cv;



#define GET_VAR_NAME_TO_CHAR(name) #name



class DebugPrint{
public:

    enum                msg{
        DONE,
        ERROR,
        INFO,

        MSG_END
    };
    enum                msg_ok_index{
        SYS_VIDEO_CAP_OK,
        SYS_SUPRES_OK,
        SYS_TRACK_OK,
        SYS_SHREC_OK,
        SYS_HREC_OK,
        SYS_OBJDET_OK,
        SYS_DETSEG_OK,
        SYS_FILE_FOUND,
        SYS_WIND_CLOSE,
        SYS_WIND_OPEN,

        MSG_OK_END
    };
    enum                msg_err_index{
        SYS_VIDEO_CAP_ERR,
        SYS_ORG_FRAME_EMPTY,
        SYS_FILE_ABSENT,
        SYS_NET_EMPTY,

        MSG_ERR_END
    };
    enum                msg_info_index{
        SYS_APP_SETUP,
        SYS_GUI_SETUP,
        SYS_VIDEO_LOOP,
        SYS_GUI_CLOSE,
        SYS_NEW_CMD,

        MSG_INFO_END
    };


private:

    ///> system interface
    static DebugPrint*  _instance;

    ///> main interface
    const string        c_new_line                  = "\n";
    const string        c_ERROR_header              = "[ERROR] : ";
    const string        c_DONE_header               = "[DONE]  : ";
    const string        c_INFO_header               = "[INFO]  : ";
    const string        c_sub_header                = "             - ";
    const array<string, MSG_OK_END>     msg_done    = {
            /* SYS_VIDEO_CAP_OK */                  "video port           READY ",
            /* SYS_SUPRES_OK */                     "supres               READY ",
            /* SYS_TRACK_OK */                      "single track         READY ",
            /* SYS_SHREC_OK */                      "shrec                READY ",
            /* SYS_HREC_OK */                       "hrec                 READY ",
            /* SYS_OBJDET_OK */                     "objdet               READY ",
            /* SYS_DETSEG_OK */                     "detseg               READY ",
            /* SYS_FILE_FOUND */                    "file                 FOUND ",
            /* SYS_WIND_CLOSE */                    "window              CLOSED ",
            /* SYS_WIND_OPEN */                     "window              OPENED "
    };
    const array<string, MSG_ERR_END>    msg_error   = {
            /* SYS_VIDEO_CAP_ERR */                 "video port       NOT READY ",
            /* SYS_ORG_FRAME_EMPTY */               "org frame            EMPTY ",
            /* SYS_FILE_ABSENT */                   "file             NOT FOUND ",
            /* SYS_NET_EMPTY */                     "trained net          EMPTY "
    };
    const array<string, MSG_INFO_END>   msg_info    = {
            /* SYS_APP_SETUP */                     "~~~~~~~~~~~~~ App START ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",
            /* SYS_GUI_SETUP */                     "~~~~~~~~~~~~~ SetUp GUI ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",
            /* SYS_VIDEO_LOOP */                    "~~~~~~~~~~~~~ Video Loop ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",
            /* SYS_GUI_CLOSE */                     "~~~~~~~~~~~~~ App END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",
            /* SYS_NEW_CMD */                       "command                    "
    };



public:

    ///> system interface
    DebugPrint();
    DebugPrint(DebugPrint& _src)                    = delete; ///> Copy semantics
    DebugPrint& operator=(DebugPrint const&)        = delete;
    DebugPrint(DebugPrint&& _src)                   = delete; ///> Move semantics
    DebugPrint& operator=(DebugPrint const&&)       = delete;
    ~DebugPrint();

    static DebugPrint* get_instance                 ();


    ///> main interface
    void                print_sys_capture_info      (VideoCapture* _cap);
    void                print_sys_opencv_info       ();
    void                print_frame_type_info       (const Mat& _frame, const char* _frame_name);
    void                print_debug                 (const int _type, const int _msg_i);
    void                print_debug                 (const int _type, const int _msg_i, const string& _msg);
    void                print_debug_msg             (const string& _msg);
    void                print_debug_cmd_options     ();

};