
#include <SysFiles.hpp>


SysFiles::SysFiles                              (){
    /*~~~~~~~~~~~~~~~ ADD ~~~~~~~~~~~~~~~*/
}

SysFiles::~SysFiles                             (){
    delete _instance;
}


    /* singleton */
SysFiles* SysFiles::_instance = nullptr;
SysFiles* SysFiles::get_instance                (){
    if(_instance == nullptr){
        _instance = new SysFiles();
    }
    return _instance;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
///     main interface                                                                                ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////

string  SysFiles::get_path_to                   (const int _unit, const int _file){

    file.clear();
    switch(_unit){
    case SUPRES:
        file = ("SystemDependencies/" + file_supres[_file]);
        debug->print_debug(debug->DONE, debug->SYS_FILE_FOUND, file_supres[_file]);
        break;

    case DETECT:
        file = ("SystemDependencies/" + file_detect[_file]);
        debug->print_debug(debug->DONE, debug->SYS_FILE_FOUND, file_detect[_file]);
        break;

    default:
        debug->print_debug(debug->ERROR, debug->SYS_FILE_ABSENT, " unknown file!");
        break;
    }

    return absolute(file);
}