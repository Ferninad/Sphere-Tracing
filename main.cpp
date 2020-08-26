#include "common.h"
#include "cmath"
#include "string"
#include "vector"
#include "window.h"
#include "Rectangle.h"
#include "Circle.h"
#include "chrono"

void Run(win &gmwin);
double calcMinDist(double ox, double oy);
void renderShapes();
void RenderTrace(win &gmwin);
double sphereTracing(bool draw, win &gmwin, double ang);

int mx, my, pmx, pmy;
double ox, oy, pox, poy;
double minDist;
double viewAng = M_PI/4;
double viewRange = M_PI/2;
int rays = 500;
int step = 150;
bool w, s, a, d, l, r;

vector<Circle> circles;
vector<Rectangle> rectangles;
vector<double> minDistances;

int main()
{
    win gmwin = win(1000, 600);

    Run(gmwin);

    gmwin.~win();
    return 0;
}

void Run(win &gmwin)
{
    bool gameLoop = true;
    srand(time(NULL));
    cout << std::boolalpha;

    circles.push_back(Circle(gmwin, 100, 100, 60));
    rectangles.push_back(Rectangle(gmwin, 400, 500, 100, 100));
    // circles.push_back(Circle(gmwin, 400, 100, 50));
    // rectangles.push_back(Rectangle(gmwin, 60, 440, 50, 50));
    ox = 250;
    oy = 300;

    auto start = chrono::system_clock::now();
    auto end = chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds;
    while (gameLoop)
    {   
        start = chrono::system_clock::now();

        SDL_RenderPresent(gmwin.renderer);
        gmwin.ClearWindow();

        pmx = mx;
        pmy = my;
        SDL_GetMouseState(&mx, &my);
        // ox = mx;
        // oy = my;
        if(mx >= 500){
            circles[0].centerx = mx-500;
            circles[0].centery = my;
        }
        else{
            circles[0].centerx = 400;
            circles[0].centery = 500;
        }
        
        pox = ox;
        poy = oy;           
        if(l){
            viewAng -= (2*M_PI)/4*elapsed_seconds.count();
            if(viewAng < 0)
                viewAng += 2*M_PI;
        }
        if(r){
            viewAng += (2*M_PI)/4*elapsed_seconds.count();
            if(viewAng >= 2*M_PI)
                viewAng -= 2*M_PI;
        }
        if(w){
            ox += cos(viewAng)*step*elapsed_seconds.count();
            oy += sin(viewAng)*step*elapsed_seconds.count();
        }
        if(s){
            ox -= cos(viewAng)*step*elapsed_seconds.count();
            oy -= sin(viewAng)*step*elapsed_seconds.count();
        }
        if(a){
            ox += cos(viewAng-M_PI/2)*step*elapsed_seconds.count();
            oy += sin(viewAng-M_PI/2)*step*elapsed_seconds.count();
        }
        if(d){
            ox += cos(viewAng+M_PI/2)*step*elapsed_seconds.count();
            oy += sin(viewAng+M_PI/2)*step*elapsed_seconds.count();
        }

        minDistances.clear();
        sphereTracing(true, gmwin, viewAng);
        renderShapes();
        RenderTrace(gmwin);
        SDL_RenderDrawLine(gmwin.renderer, 500, 0, 500, gmwin.screenHeight);

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameLoop = false;
            }
            if(event.type == SDL_MOUSEBUTTONDOWN){
                if(event.button.button == SDL_BUTTON_LEFT){
                    
                }
                else if(event.button.button == SDL_BUTTON_RIGHT){
                    
                }
            }
            if(event.type == SDL_MOUSEBUTTONUP){
                if(event.button.button == SDL_BUTTON_LEFT){
                    
                }
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        gameLoop = false;
                        break;
                    case SDLK_LEFT:
                        l = true;
                        break;
                    case SDLK_RIGHT:
                        r = true;
                        break;
                    case SDLK_w:
                        w = true;
                        break;
                    case SDLK_a:
                        a = true;
                        break;
                    case SDLK_s:
                        s = true;
                        break;
                    case SDLK_d:
                        d = true;
                        break;
                    default:
                        break;
                }
            }

            if (event.type == SDL_KEYUP)
            {
                switch (event.key.keysym.sym){
                    case SDLK_LEFT:
                        l = false;
                        break;
                    case SDLK_RIGHT:
                        r = false;
                        break;
                    case SDLK_w:
                        w = false;
                        break;
                    case SDLK_a:
                        a = false;
                        break;
                    case SDLK_s:
                        s = false;
                        break;
                    case SDLK_d:
                        d = false;
                        break;
                    default:
                        break;
                }
            }
        }
        end = chrono::system_clock::now();
        elapsed_seconds = end-start;
    }
}

double calcMinDist(double ox, double oy){
    // double minDist = 10000;
    // for(Circle &circ : circles){
    //     if(circ.SignedDistToCirc(ox, oy) < minDist)
    //         minDist = circ.SignedDistToCirc(ox, oy);
    // }
    // for(Rectangle &sq : rectangles){
    //     if(sq.SignedDistToRect(ox, oy) < minDist)
    //         minDist = sq.SignedDistToRect(ox, oy);
    // }

    // return minDist;
    double dstToSquare = rectangles[0].SignedDistToRect(ox, oy);
    double dstToCircle = circles[0].SignedDistToCirc(ox, oy);

    return max(dstToSquare, dstToCircle*-1);
}

void renderShapes(){
    for(Circle &circ : circles){
        circ.RenderCirc(500, 0);
    }
    for(Rectangle &sq : rectangles){
        sq.RenderRectangle(500, 0);
    }
}

void RenderTrace(win &gmwin){
    gmwin.DrawCircle(true, ox, oy, 3, {155, 155, 155, 255}, 500, 0);
    for(double i = viewAng-viewRange/2; i <= viewAng+viewRange/2; i+=viewRange/rays){
        minDistances.push_back(sphereTracing(false, gmwin, i));
    }
    SDL_SetRenderDrawColor(gmwin.renderer, 255, 255, 255, 255);
    for(int x = 0; x < rays; x++){
        int h;
        if(minDistances[x] == 10000){
            h = 0;
        }
        else{
            h = 500*1/(minDistances[x]/35);
            if(h > 500)
                h = 500;
            SDL_RenderDrawLine(gmwin.renderer, x, gmwin.screenHeight/2 - h/2, x, gmwin.screenHeight/2 + h/2);
        }
    }
}

double sphereTracing(bool draw, win &gmwin, double ang){
    double minDist = calcMinDist(ox, oy);
    double stepox = ox;
    double stepoy = oy;
    double pstepox = ox;
    double pstepoy = oy;
    while(stepox >= 0 && stepox < 500 && stepoy >= 0 && stepoy < gmwin.screenHeight && minDist > .01){
        minDist = calcMinDist(stepox, stepoy);
        if(draw){
            gmwin.DrawCircle(true, stepox, stepoy, 3, {155, 155, 155, 255}, 500, 0);
            gmwin.DrawCircle(false, stepox, stepoy, minDist, {155, 155, 155, 255}, 500, 0);
        }
        if(draw && pstepox+500 >= 500 && stepox+500 >= 500)
            SDL_RenderDrawLine(gmwin.renderer, pstepox+500, pstepoy, stepox+500, stepoy);
        pstepox = stepox;
        pstepoy = stepoy;
        stepox = stepox + minDist*cos(ang);
        stepoy = stepoy + minDist*sin(ang);
    }
    if(minDist <= .01)
        return sqrt(pow(stepox-ox, 2) + pow(stepoy-oy, 2));
    else
        return 10000;
}