
#include <SystemManager.hpp>




SystemManager::SystemManager                    (){
    /*~~~~~~~~~~~~~~~ ADD ~~~~~~~~~~~~~~~*/
}

SystemManager::~SystemManager                   (){
    delete  sys_param, debug;
    tracker_mil.release();
    tracker_kcf.release();
    tracker_csrt.release();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
///     main interface                                                                                ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void SystemManager::system_loop                 (){
    ///> SETUP .........................................................................................
    if (vid_capture.open(vid_port)) { 
        debug->print_debug(debug->DONE, debug->SYS_VIDEO_CAP_OK, vid_port);
    }
    else {
        debug->print_debug(debug->ERROR, debug->SYS_VIDEO_CAP_ERR, vid_port);
    }

    while(!vid_capture.isOpened()){}

    //> set resolution
    vid_capture.set(CAP_PROP_FRAME_HEIGHT, c_org_h);
    vid_capture.set(CAP_PROP_FRAME_WIDTH,  c_org_w);
    vid_capture.set(CAP_PROP_FOURCC,       VideoWriter::fourcc('M', 'J', 'P', 'G'));
    vid_capture.set(CAP_PROP_FPS,          30);

    setup_video_GUI();

    debug->print_sys_capture_info(&vid_capture);
    // debug->print_sys_opencv_info();



    ///> LOOP START ....................................................................................
    debug->print_debug(debug->INFO, debug->SYS_VIDEO_LOOP);
    debug->print_debug_cmd_options();

    while( getWindowProperty(gui->c_org_wind_name, 0) >= 0 || sys_param->f_video_run == false){

        //> system
        timer_fps = static_cast<double>(getTickCount());

        vid_capture.read(org_frame);
        if(org_frame.empty()){
            debug->print_debug(debug->ERROR, debug->SYS_ORG_FRAME_EMPTY);
            continue;
        }
        
        // fps = getTickFrequency() / ((double)getTickCount() - timer_fps);

        //> video options
        enable_video_GUI();

        fps = getTickFrequency() / ((double)getTickCount() - timer_fps);

        //> waiting & getting command
        get_cmd(waitKey(1));
    }
    ///> LOOP END ......................................................................................
    debug->print_debug(debug->INFO, debug->SYS_GUI_CLOSE);



    destroy_all_windows();

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
///     ENABLE...                                                                                     ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////



void SystemManager::enable_video_GUI            (){
    if (sys_param->f_supres)        {//> supres

        enable_supres();

        gui->show_video_FPS(out_supres_frame, fps);
        imshow( gui->c_fsrcnn_wind_name, out_supres_frame);
    }
    else if (sys_param->f_supres_wind_close){
        destroy_window(gui->c_fsrcnn_wind_name);
        sys_param->f_supres_wind_close = false;
    }

    if (sys_param->f_track)         {//> track

        org_frame.copyTo(out_track_frame);

        enable_track();
        
        gui->show_video_FPS(out_track_frame, fps);
        imshow( gui->c_track_wind_name, out_track_frame);
    }
    else if (sys_param->f_track_wind_close){
        destroy_window(gui->c_track_wind_name);
        sys_param->f_track_wind_close = false;
    }

    if (sys_param->f_shrec)         {//> shrec

        enable_shrec();

        gui->show_video_FPS(out_shrec_frame, fps);
        imshow( gui->c_shrec_wind_name, out_shrec_frame);
    }
    else if (sys_param->f_shrec_wind_close){
        destroy_window(gui->c_shrec_wind_name);
        sys_param->f_shrec_wind_close = false;
    }

    if (sys_param->f_hrec)          {//> hrec
    
        enable_hrec();

        gui->show_video_FPS(out_hrec_frame, fps);
        imshow( gui->c_hrec_wind_name, out_hrec_frame);
    }
    else if (sys_param->f_hrec_wind_close){
        destroy_window(gui->c_hrec_wind_name);
        sys_param->f_hrec_wind_close = false;
    }

    if (sys_param->f_objdet)        {//> objdet
    
        enable_objdet();

        gui->show_video_FPS(out_objdet_frame, fps);
        imshow( gui->c_objdet_wind_name, out_objdet_frame);
    }
    else if (sys_param->f_objdet_wind_close){
        destroy_window(gui->c_objdet_wind_name);
        sys_param->f_objdet_wind_close = false;
    }

    if (sys_param->f_detseg)        {//> detseg
    
        enable_detseg();

        gui->show_video_FPS(out_detseg_frame, fps);
        imshow( gui->c_detseg_wind_name, out_detseg_frame);
    }
    else if (sys_param->f_detseg_wind_close){
        destroy_window(gui->c_detseg_wind_name);
        sys_param->f_detseg_wind_close = false;
    }

    //> original
    gui->show_video_FPS(org_frame, fps);
    imshow( gui->c_org_wind_name, org_frame);
}

void SystemManager::enable_supres               (){
    //> init
    if (sys_param->f_supres_init){
        setup_supres();
    }

    //> run
    if (sys_param->f_supres_enable){
        sr.upsample( org_frame, out_supres_frame);
    }
}

void SystemManager::enable_track                (){
    //> init
    if (sys_param->f_track_init){
        setup_track();
    }

    //> run
    if (sys_param->f_track_enable){
        //> update all trackers
        f_track_mil_status = tracker_mil->update(out_track_frame, roi_mil_rect);
        f_track_kcf_status = tracker_kcf->update(out_track_frame, roi_kcf_rect);
        f_track_csrt_status = tracker_csrt->update(out_track_frame, roi_csrt_rect);

        //> add visualisation
        //> MIL
        if(f_track_mil_status){
            rectangle( out_track_frame, roi_mil_rect, gui->c_clr_TR_MIL, 2, 1);
            putText( out_track_frame, "MIL", {roi_mil_rect.x, roi_mil_rect.y}, FONT_HERSHEY_SIMPLEX, 1, gui->c_clr_TR_MIL, 2);
            gui->show_video_TRACK_STAT(out_track_frame, gui->track_type::MIL, gui->track_stat::OK);
        }
        else{
            gui->show_video_TRACK_STAT(out_track_frame, gui->track_type::MIL, gui->track_stat::LOST);
        }

        //> KCF
        if(f_track_kcf_status){
            rectangle( out_track_frame, roi_kcf_rect, gui->c_clr_TR_KCF, 2, 1 );
            putText( out_track_frame, "KCF", {roi_kcf_rect.x, roi_kcf_rect.y}, FONT_HERSHEY_SIMPLEX, 1, gui->c_clr_TR_KCF, 2);
            gui->show_video_TRACK_STAT(out_track_frame, gui->track_type::KCF, gui->track_stat::OK);
        }
        else{
            gui->show_video_TRACK_STAT(out_track_frame, gui->track_type::KCF, gui->track_stat::LOST);
        }

        //> CSRT
        if(f_track_csrt_status){
            rectangle( out_track_frame, roi_csrt_rect, gui->c_clr_TR_CSRT, 2, 1 );
            putText( out_track_frame, "CSRT", {roi_csrt_rect.x, roi_csrt_rect.y}, FONT_HERSHEY_SIMPLEX, 1, gui->c_clr_TR_CSRT, 2 );
            gui->show_video_TRACK_STAT(out_track_frame, gui->track_type::CSRT, gui->track_stat::OK);
        }
        else{
            gui->show_video_TRACK_STAT(out_track_frame, gui->track_type::CSRT, gui->track_stat::LOST);
        }
    }
}

void SystemManager::enable_shrec                (){
    //> init
    if (sys_param->f_shrec_init){
        setup_shrec();
    }

    //> run
    if (sys_param->f_shrec_enable){

        org_frame.copyTo(tmp_shrec_frame);

        //> convert to grayscale
        cvtColor(org_frame, gray_shrec_frame, COLOR_BGR2GRAY);

        //> get every visible edge
        blur( gray_shrec_frame, edges_shrec_frame, Size(3,3) );
        Canny(gray_shrec_frame, edges_shrec_frame, c_canny_threshold1, c_canny_threshold2, c_canny_apertureSize, c_canny_L2gradient);

        //> search for contours
        findContours(edges_shrec_frame, shrec_contours, c_find_cntr_mode, c_find_cntr_method);

        //> beginning of shape search
        for(int i = 0 ; i < shrec_contours.size(); i++){

            //> approximate contour with accuracy proportional to the contour perimeter
		    approxPolyDP(
                Mat(shrec_contours[i]),
                shrec_approx, 
                arcLength(
                    Mat(shrec_contours[i]),
                    true
                )*0.02,
                true
            );

		    //> skip small or non-convex objects 
		    if (fabs(contourArea(shrec_contours[i])) < 100 || !isContourConvex(shrec_approx)) {
                continue;
            }

            if (shrec_approx.size() == 3){//> triangles
                set_shrec_label(tmp_shrec_frame, "TRI", shrec_contours[i]);
            }
            else if (shrec_approx.size() >= 4 && shrec_approx.size() <= 6){ //> rectangles and more
                
                //> number of vertices of polygonal curve
                shrec_vtc = shrec_approx.size();

                //> get the cosines of all corners
                vector<double> cos;
                for (int j = 2; j < shrec_vtc+1; j++){
                    cos.push_back(
                        get_cosine_angle(
                            shrec_approx[j%shrec_vtc],
                            shrec_approx[j-2],
                            shrec_approx[j-1]
                        )
                    );
                }

                //> sort ascending the cosine values
                sort(cos.begin(), cos.end());

                //> get the lowest and the highest cosine
                shrec_mincos = cos.front();
                shrec_maxcos = cos.back();

                //> use the degrees obtained above and the number of vertices to determine the shape of the contour
                if      (shrec_vtc == 4 && shrec_mincos >= -0.1 && shrec_maxcos <= 0.3)     { //> rectangle
                    set_shrec_label(tmp_shrec_frame, "RECT", shrec_contours[i]);
                }
                else if (shrec_vtc == 5 && shrec_mincos >= -0.34 && shrec_maxcos <= -0.27)  { //> pentagon
                    set_shrec_label(tmp_shrec_frame, "PENTA", shrec_contours[i]);
                }
                else if (shrec_vtc == 6 && shrec_mincos >= -0.55 && shrec_maxcos <= -0.45)  { //> hexagon
                    set_shrec_label(tmp_shrec_frame, "HEXA", shrec_contours[i]);
                }
            }
            else{ //> circles
                //> detect and label circles
                shrec_circle_area = contourArea(shrec_contours[i]);
                shrec_circle_rect = boundingRect(shrec_contours[i]);
                shrec_circle_radius = shrec_circle_rect.width / 2;

                if (abs(1 - ((double)shrec_circle_rect.width / shrec_circle_rect.height)) <= 0.2 &&
                    abs(1 - (shrec_circle_area / (CV_PI * pow(shrec_circle_radius, 2)))) <= 0.2)
                    set_shrec_label(tmp_shrec_frame, "CIR", shrec_contours[i]);
            }
        }

        //> convert 'edges_shrec_frame' from 1 channel into 3
        cvtColor(edges_shrec_frame, edges_tmp_shrec_frame, COLOR_GRAY2BGR);
        
        vconcat(edges_tmp_shrec_frame, tmp_shrec_frame, out_shrec_frame);

        //> debug frames
        // debug->print_frame_type_info(edges_tmp_shrec_frame, GET_VAR_NAME_TO_CHAR(edges_tmp_shrec_frame));
        // debug->print_frame_type_info(tmp_shrec_frame, GET_VAR_NAME_TO_CHAR(tmp_shrec_frame));
        // debug->print_frame_type_info(out_shrec_frame, GET_VAR_NAME_TO_CHAR(out_shrec_frame));
    }
}

void SystemManager::enable_hrec                 (){
    //> init
    if (sys_param->f_hrec_init){
        setup_hrec();
    }

    //> run
    if (sys_param->f_hrec_enable){
        //...
    }

}

void SystemManager::enable_objdet               (){
    //> init
    if (sys_param->f_objdet_init){
        setup_objdet();
    }

    //> run
    if (sys_param->f_objdet_enable){

        org_frame.copyTo(out_objdet_frame);

        blobFromImage(
            out_objdet_frame,
            objdet_blob_frame,
            1.0,
            Size(
                c_objdet_blob_scale, //c_objdet_blob_scale | out_objdet_frame.cols
                c_objdet_blob_scale  //c_objdet_blob_scale | out_objdet_frame.rows
            ),
            Scalar(127.5, 127.5, 127.5),
            true,
            false
        );

        //> feed the blob to network model
        objdet_trained_model.setInput( objdet_blob_frame);
        
        //> forward pass through the model to carry out the detection
        objdet_out_model_frame = objdet_trained_model.forward("detection_out");

        Mat detectionMat(
            objdet_out_model_frame.size[2],
            objdet_out_model_frame.size[3], // 3
            CV_32F,
            objdet_out_model_frame.ptr<float>()
        );

        for (int i = 0; i < detectionMat.rows; i++){
            confidence_id_objdet  = detectionMat.at<float>(i, 2);
  
            //> Check if the detection is of good quality
            if (confidence_id_objdet > c_confidence_max_objdet){
                obj_id_objdet = detectionMat.at<float>(i, 1);
                box_x_objdet = static_cast<int>(detectionMat.at<float>(i, 3) * out_objdet_frame.cols);
                box_y_objdet = static_cast<int>(detectionMat.at<float>(i, 4) * out_objdet_frame.rows);
                box_w_objdet = static_cast<int>(detectionMat.at<float>(i, 5) * out_objdet_frame.cols - box_x_objdet);
                box_h_objdet = static_cast<int>(detectionMat.at<float>(i, 6) * out_objdet_frame.rows - box_y_objdet);
                rectangle(
                    out_objdet_frame,
                    Point(
                        box_x_objdet,
                        box_y_objdet
                    ),
                    Point(
                        box_x_objdet + box_w_objdet,
                        box_y_objdet + box_h_objdet
                    ),
                    gui->c_clr_GREEN,
                    4
                );
                putText(
                    out_objdet_frame,
                    objdet_obj_names[obj_id_objdet] + ": " + to_string(confidence_id_objdet),
                    Point(
                        box_x_objdet,
                        box_y_objdet - 5
                    ),
                    gui->c_font,
                    0.5,
                    gui->c_clr_GREEN,
                    2
                );
            }
            else{
                // gui->show_video_ERROR_msg(out_objdet_frame, "NO OBJDET");
            }
        }
    }

}

void SystemManager::enable_detseg               (){
    //> init
    if (sys_param->f_detseg_init){
        setup_detseg();
    }

    //> run
    if (sys_param->f_detseg_enable){
        
        org_frame.copyTo(out_detseg_frame);

        //> make blob
        blobFromImage(
            out_detseg_frame,
            detseg_blob_frame,
            c_detseg_scale_factor,
            Size(
                out_detseg_frame.cols,
                out_detseg_frame.rows
            ),
            Scalar(),
            c_detseg_swapRB,
            c_detseg_crop,
            c_detseg_depth
        );

        //> feed the net
        detseg_trained_model.setInput(detseg_blob_frame);

        //> get data from the net
        detseg_trained_model.forward(detseg_out_model_frames, detseg_out_layers);

        //> postprocess
        /*  Output size of masks is NxCxHxW where:
        *   N - number of detected boxes
        *   C - number of classes (excluding background)
        *   HxW - segmentation shape
        */
        Mat out_detect_frame    = detseg_out_model_frames.at(0);
        Mat out_masks_frame     = detseg_out_model_frames.at(1);
        detseg_num_detections   = out_detect_frame.size[2];
        detseg_num_classes      = out_masks_frame.size[1];
        out_detect_frame        = out_detect_frame.reshape(1, out_detect_frame.total() / 7);

        for(int i = 0; i < detseg_num_detections; i++){
            confidence_id_detseg = out_detect_frame.at<float>(i, 2);
            
            if(confidence_id_detseg > c_detseg_conf_threshold){

                //> extract the bounding box
                obj_id_detseg = static_cast<int>(out_detseg_frame.at<float>(i, 1));
                int left      = static_cast<int>(out_detseg_frame.cols * out_detect_frame.at<float>(i, 3));
                int top       = static_cast<int>(out_detseg_frame.rows * out_detect_frame.at<float>(i, 4));
                int right     = static_cast<int>(out_detseg_frame.cols * out_detect_frame.at<float>(i, 5));
                int bottom    = static_cast<int>(out_detseg_frame.rows * out_detect_frame.at<float>(i, 6));
    
                left     = max(0, min(left, out_detseg_frame.cols - 1));
                top      = max(0, min(top, out_detseg_frame.rows - 1));
                right    = max(0, min(right, out_detseg_frame.cols - 1));
                bottom   = max(0, min(bottom, out_detseg_frame.rows - 1));
                Rect box = Rect(left, top, right - left + 1, bottom - top + 1);
    
                // extract the mask for the object
                Mat objectMask(
                    out_masks_frame.size[2],
                    out_masks_frame.size[3],
                    CV_32F,
                    out_masks_frame.ptr<float>(
                        i,
                        obj_id_detseg
                    )
                );
    
                //> draw a rectangle displaying the bounding box
                rectangle(
                    out_detseg_frame,
                    Point(box.x, box.y),
                    Point(box.x + box.width, box.y + box.height),
                    Scalar(255, 178, 50),
                    3
                );
        cout<<"bound box"<<endl;
            
                //Get the label for the class name and its confidence
                string label = format("%.2f", confidence_id_detseg);
                if (!detseg_obj_names.empty()){
                    CV_Assert(obj_id_detseg < (int)detseg_obj_names.size());
                    label = detseg_obj_names[obj_id_detseg] + ":" + label;
                }
        cout<<"get label"<<endl;
            
                //Display the label at the top of the bounding box
                int baseLine;
                Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
                box.y = max(box.y, labelSize.height);
                rectangle(out_detseg_frame, Point(box.x, box.y - round(1.5 * labelSize.height)), Point(box.x + round(1.5 * labelSize.width), box.y + baseLine), Scalar(255, 255, 255), FILLED);
                putText(out_detseg_frame, label, Point(box.x, box.y), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,0),1);

        cout<<"display label"<<endl;

                //> apply colors to mask
                if (f_rand_colors){
                    int colorInd = rand() % detseg_colors.size();
                    detseg_color = detseg_colors[colorInd];
                }
                else{
                    detseg_color = detseg_colors[obj_id_detseg % detseg_colors.size()];
                }
        cout<<"apply mask color"<<endl;
                
            
                // Resize the mask, threshold, color and apply it on the image
                resize(objectMask, objectMask, Size(box.width, box.height));
                Mat mask = (objectMask > c_detseg_mask_threshold);
                Mat coloredRoi = (0.3 * detseg_color + 0.7 * out_detseg_frame(box));
                coloredRoi.convertTo(coloredRoi, CV_8UC3);
            
        cout<<"on image"<<endl;
                // Draw the contours on the image
                vector<Mat> contours;
                Mat hierarchy;
                mask.convertTo(mask, CV_8U);
                findContours(mask, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
                drawContours(coloredRoi, contours, -1, detseg_color, 5, LINE_8, hierarchy, 100);
                coloredRoi.copyTo(out_detseg_frame(box), mask);

        cout<<"draw contours"<<endl;
        cout<<"~~~~~~~~~~~~~~~~~~"<<endl;
            }
        }
    }

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
///     SETUP...                                                                                      ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////


void SystemManager::setup_video_GUI             (){
    debug->print_debug(debug->INFO, debug->SYS_GUI_SETUP);

    //> original video
    create_window(gui->c_org_wind_name, gui->c_vid_wind_flag);
}

void SystemManager::setup_supres                (){
    create_window(gui->c_fsrcnn_wind_name, gui->c_vid_wind_flag);
    
    sr.readModel(
        files->get_path_to(
            files->UNIT::SUPRES,
            files->SUPRES_FILE::FSRCNN_x2
        )
    );
    sr.setModel(fsrcnn_model_name, fsrcnn_scale);

    sys_param->f_supres_init        = false;
    sys_param->f_supres_enable      = true;
    sys_param->f_supres_wind_close  = true;

    debug->print_debug(debug->DONE, debug->SYS_SUPRES_OK);
}

void SystemManager::setup_track                 (){
    create_window(gui->c_track_wind_name, gui->c_vid_wind_flag);

    tracker_mil = TrackerMIL::create();
    tracker_mil->init(out_track_frame, roi_mil_rect);

    tracker_kcf = TrackerKCF::create();
    tracker_kcf->init(out_track_frame, roi_kcf_rect);

    tracker_csrt = TrackerCSRT::create();
    tracker_csrt->init(out_track_frame, roi_csrt_rect);

    sys_param->f_track_init         = false;
    sys_param->f_track_enable       = true;
    sys_param->f_track_wind_close   = true;

    debug->print_debug(debug->DONE, debug->SYS_TRACK_OK);
}

void SystemManager::setup_shrec                 (){
    create_window(gui->c_shrec_wind_name, gui->c_vid_wind_flag);

    sys_param->f_shrec_init         = false;
    sys_param->f_shrec_enable       = true;
    sys_param->f_shrec_wind_close   = true;

    debug->print_debug(debug->DONE, debug->SYS_SHREC_OK);
}

void SystemManager::setup_hrec                  (){
    create_window(gui->c_hrec_wind_name, gui->c_vid_wind_flag);
    
    //...

    sys_param->f_hrec_init          = false;
    sys_param->f_hrec_enable        = true;
    sys_param->f_hrec_wind_close    = true;

    debug->print_debug(debug->DONE, debug->SYS_HREC_OK);
}

void SystemManager::setup_objdet                (){
    create_window(gui->c_objdet_wind_name, gui->c_vid_wind_flag);
    
    ifstream ifs((
        files->get_path_to(
            files->DETECT,
            files->DETECT_FILE::OBJECT_DETECTION_CLASSES_COCO_txt
        )).c_str()
    );

    string line;
    while (getline(ifs, line)){
        objdet_obj_names.push_back(line);
    }

   //> load the neural network model
   //> V1
    objdet_trained_model = readNet(
        files->get_path_to(
            files->UNIT::DETECT,
            files->DETECT_FILE::FROZEN_INTERFACE_GRAPH_objdet_pb
        ),
        files->get_path_to(
            files->UNIT::DETECT,
            files->DETECT_FILE::SSD_MOBILENET_V2_COCO_2018_03_29_pbtxt_txt
        ),
        objdet_path_framework
    );
    //> V2
    // objdet_trained_model = readNetFromCaffe(
    //     files->get_path_to(
    //         files->UNIT::OBJDET,
    //         files->OBJDET_FILE::MOBILENETSSD_DEPLOY_prototxt_txt
    //     ),
    //     files->get_path_to(
    //         files->UNIT::OBJDET,
    //         files->OBJDET_FILE::MOBILENETSSD_DEPLOY_caffemodel
    //     )
    // );

    if(objdet_trained_model.empty()){
        debug->print_debug(debug->ERROR, debug->SYS_NET_EMPTY);
    }

    //> aim to CPU
    objdet_trained_model.setPreferableBackend(DNN_BACKEND_OPENCV);
    objdet_trained_model.setPreferableTarget(DNN_TARGET_CPU);

    sys_param->f_objdet_init          = false;
    sys_param->f_objdet_enable        = true;
    sys_param->f_objdet_wind_close    = true;

    debug->print_debug(debug->DONE, debug->SYS_OBJDET_OK);
}

void SystemManager::setup_detseg                (){
    create_window(gui->c_detseg_wind_name, gui->c_vid_wind_flag);
    
    //> parse objects
    ifstream ifs_objects((
        files->get_path_to(
            files->DETECT,
            files->DETECT_FILE::OBJECT_DETECTION_CLASSES_COCO_txt
        )).c_str()
    );
    string line_o;
    while (getline(ifs_objects, line_o)){
        detseg_obj_names.push_back(line_o);
    }
    ifs_objects.close();
    detseg_obj_names.erase(detseg_obj_names.begin(), detseg_obj_names.begin() + 1); // The given onj list is suits for objdet part. For detseg the list must be cleared out of 'unlabeled'

    //> parse colors
    ifstream ifs_colors((
        files->get_path_to(
            files->DETECT,
            files->DETECT_FILE::COLORS_txt
        )).c_str()
    );
    string line_c;
    while(getline(ifs_colors, line_c)){
        char* pEnd;
        double r, g, b;
        r = strtod (line_c.c_str(), &pEnd);
        g = strtod (pEnd, NULL);
        b = strtod (pEnd, NULL);
        detseg_colors.push_back(Scalar(r, g, b, 255.0));
    }
    ifs_colors.close();

    //> load th eneural network model
    detseg_trained_model = readNet(
        files->get_path_to(
            files->UNIT::DETECT,
            files->DETECT_FILE::FROZEN_INTERFACE_GRAPH_detseg_pb
        ),
        files->get_path_to(
            files->UNIT::DETECT,
            files->DETECT_FILE::MASK_RCNN_INCEPTION_V2_COCO_2018_01_28_pbtxt
        )
    );

    //> aim to CPU
    detseg_trained_model.setPreferableBackend(DNN_BACKEND_OPENCV);
    detseg_trained_model.setPreferableTarget(DNN_TARGET_CPU);

    //> set output layers
    detseg_out_layers.push_back("detection_out_final");
    detseg_out_layers.push_back("detection_masks");

    //> sys dependencies
    sys_param->f_detseg_init          = false;
    sys_param->f_detseg_enable        = true;
    sys_param->f_detseg_wind_close    = true;

    debug->print_debug(debug->DONE, debug->SYS_DETSEG_OK);
}



void SystemManager::get_cmd                     (const char _cmd){
    if(_cmd != -1){
        if      (_cmd == 'c'){//> clear all
            clear_all_flags();
            debug->print_debug(debug->INFO, debug->SYS_NEW_CMD, "close all except original video stream");
        }
        else if (_cmd == 'p'){//> debug
            debug->print_debug(debug->INFO, debug->SYS_NEW_CMD, "output all control options");
            debug->print_debug_cmd_options();
        }
        else if (_cmd == 's'){//> supres
            clear_all_flags();
            sys_param->f_supres = !sys_param->f_supres;
            sys_param->f_supres_init   = !sys_param->f_supres_init;
            debug->print_debug(debug->INFO, debug->SYS_NEW_CMD, "super resolution");
        }
        else if (_cmd == 't'){//> track
            clear_all_flags();
            sys_param->f_track         = !sys_param->f_track;
            sys_param->f_track_init    = !sys_param->f_track_init;
            debug->print_debug(debug->INFO, debug->SYS_NEW_CMD, "single object tracking");
        }
        else if (_cmd == 'o'){//> shrec
            clear_all_flags();
            sys_param->f_shrec         = !sys_param->f_shrec;
            sys_param->f_shrec_init    = !sys_param->f_shrec_init;
            debug->print_debug(debug->INFO, debug->SYS_NEW_CMD, "shape recognition");
        }
        else if (_cmd == 'h'){//> hrec
            clear_all_flags();
            sys_param->f_hrec          = !sys_param->f_hrec;
            sys_param->f_hrec_init     = !sys_param->f_hrec_init;
            debug->print_debug(debug->INFO, debug->SYS_NEW_CMD, "hand recognition");
        }
        else if (_cmd == 'i'){//> objdet
            clear_all_flags();
            sys_param->f_objdet        = !sys_param->f_objdet;
            sys_param->f_objdet_init   = !sys_param->f_objdet_init;
            debug->print_debug(debug->INFO, debug->SYS_NEW_CMD, "object detection");
        }
        else if (_cmd == 'd'){//> detseg
            clear_all_flags();
            sys_param->f_detseg        = !sys_param->f_detseg;
            sys_param->f_detseg_init   = !sys_param->f_detseg_init;
            debug->print_debug(debug->INFO, debug->SYS_NEW_CMD, "object det-n & image seg-n");
        }
        //> IN PROGRESS
        // else if (_cmd == '1'){//> START
        //     //...
        //     debug->print_debug(debug->INFO, debug->SYS_NEW_CMD, "START");
        // }
        // else if (_cmd == '0'){//> STOP
        //     //...
        //     debug->print_debug(debug->INFO, debug->SYS_NEW_CMD, "STOP");
        // }
    }
}

void SystemManager::clear_all_flags             (){
    sys_param->f_supres            = false;
    sys_param->f_supres_init       = false;
    sys_param->f_supres_enable     = false;
     sys_param->f_track            = false;
     sys_param->f_track_init       = false;
     sys_param->f_track_enable     = false;
    sys_param->f_shrec             = false;
    sys_param->f_shrec_init        = false;
    sys_param->f_shrec_enable      = false;
     sys_param->f_hrec             = false;
     sys_param->f_hrec_init        = false;
     sys_param->f_hrec_enable      = false;
    sys_param->f_objdet            = false;
    sys_param->f_objdet_init       = false;
    sys_param->f_objdet_enable     = false;
     sys_param->f_detseg           = false;
     sys_param->f_detseg_init      = false;
     sys_param->f_detseg_enable    = false;
}




