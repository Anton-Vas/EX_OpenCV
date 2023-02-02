
#include <SystemManager.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
///     WINDOW ACTION                                                                                 ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void SystemManager::destroy_all_windows         (){
    destroyAllWindows();
    debug->print_debug(debug->DONE, debug->SYS_WIND_CLOSE, "ALL");
}

void SystemManager::create_window               (const string& _win_name, const int _win_flag){
    namedWindow(_win_name, _win_flag);
    debug->print_debug(debug->DONE, debug->SYS_WIND_OPEN, _win_name);
}

void SystemManager::destroy_window              (const string& _win_name){
    destroyWindow(_win_name);
    debug->print_debug(debug->DONE, debug->SYS_WIND_CLOSE, _win_name);
}

void SystemManager::resize_window               (const string& _win_name, const int _w, const int _h){
    resizeWindow(_win_name, _w, _h);
}

