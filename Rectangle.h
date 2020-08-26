#include "common.h"
#include "cmath"
#include "string"
#include "window.h"

class Rectangle{
    public:
        int centerx, centery, width, height;

        win &gmwin;
        Rectangle(win &gmwin, int centerx, int centery, int width, int height);
        double SignedDistToRect(double ox, double oy);
        void RenderRectangle(int offx, int offy);
    private:
};