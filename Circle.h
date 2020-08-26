#include "common.h"
#include "cmath"
#include "string"
#include "window.h"

class Circle{
    public:
        int centerx, centery, radius;

        win &gmwin;
        Circle(win &gmwin, int centerx, int centery, int radius);
        double SignedDistToCirc(double ox, double oy);
        void RenderCirc(int offx, int offy);
    private:
};