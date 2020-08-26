#include "common.h"
#include "cmath"
#include "string"
#include "Rectangle.h"

Rectangle :: Rectangle(win &gmwin, int centerx, int centery, int width, int height) : gmwin(gmwin), centerx(centerx), centery(centery), width(width), height(height){

}

void Rectangle :: RenderRectangle(int offx, int offy){
    gmwin.DrawRectangle(true, centerx, centery, width, height, {0, 0, 0, 255}, offx, offy);
}

double Rectangle :: SignedDistToRect(double ox, double oy){
    double x = abs(ox - centerx) - width/2;
    double y = abs(oy - centery) - height/2;
    double unsignedDist = sqrt(pow(max(x, 0.0), 2) + pow(max(y, 0.0), 2));
    
    double dstInsideBox = max(min(x, 0.0), min(y, 0.0));
    return unsignedDist + dstInsideBox;
    // double dx = max(abs(ox - centerx) - width / 2, 0.0);
    // double dy = max(abs(oy - centery) - height / 2, 0.0);
    // return sqrt(dx * dx + dy * dy);
}
