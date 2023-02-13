
#include <SystemManager.hpp>


/////////////////////////////////////////////////////////////////////////////////////////////////////////
///     OTHER...                                                                                      ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////

double SystemManager::get_cosine_angle          (const Point _pt1, const Point _pt2, const Point _pt0){
	double dx1 = _pt1.x - _pt0.x;
	double dy1 = _pt1.y - _pt0.y;
	double dx2 = _pt2.x - _pt0.x;
	double dy2 = _pt2.y - _pt0.y;
	return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

void SystemManager::set_shrec_label             (const Mat& _im, const string _label, vector<Point>& _contour){
	int fontface = FONT_HERSHEY_SIMPLEX;
	double scale = 3;//0.4;
	int thickness = 1;
	int baseline = 0;

	Size text = getTextSize(_label, fontface, scale, thickness, &baseline);
	Rect r = boundingRect(_contour);

	Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
	rectangle(
        _im,
        pt + Point(0, baseline),
        pt + Point(text.width, -text.height),
        CV_RGB(255,255,255),
        FILLED
    );
    putText(
        _im,
        _label,
        pt,
        fontface,
        scale,
        gui->c_clr_RED,
        thickness,
        8
	);
}
