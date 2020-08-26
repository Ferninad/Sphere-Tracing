#include "common.h"
#include "cmath"
#include "string"
#include "Circle.h"

Circle :: Circle(win &gmwin, int centerx, int centery, int radius) : gmwin(gmwin), centerx(centerx), centery(centery), radius(radius){

}

double Circle :: SignedDistToCirc(double ox, double oy){
    return sqrt(pow(centerx - ox, 2) + pow(centery - oy, 2)) - radius; //negative if origin is in circle
}

void Circle :: RenderCirc(int offx, int offy){
    gmwin.DrawCircle(true, centerx, centery, radius, {0, 0, 0, 155}, offx, offy);
}
