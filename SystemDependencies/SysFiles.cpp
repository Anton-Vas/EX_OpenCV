
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
    // if(_file.find("FSRCNN")){
    // 	file = ("SystemDependencies/" + _file + ".pb");
    // }
    // return absolute(file);

    switch(_unit){
    case SUPRES:
        file = ("SystemDependencies/" + file_supres[_file]);
        debug->print_debug(debug->INFO, debug->SYS_FILE_FOUND/*, file_supres[_file]*/);
        break;

    case OBJDET:
        file = ("SystemDependencies/" + file_objdet[_file]);
        debug->print_debug(debug->INFO, debug->SYS_FILE_FOUND/*, file_objdet[_file]*/);
        break;

    default:
        debug->print_debug(debug->ERROR, debug->SYS_TRACK_OK, " unknown file!");
        break;
    }

    return absolute(file);
}