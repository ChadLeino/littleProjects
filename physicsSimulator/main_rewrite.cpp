#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <vector>
#include "raylib.h"


class Object {
    public:

        double mass;
        double radius; // essentially farthest point
        bool dynamic;

            struct Position {
                double X;
                double Y;
            };


            struct VelocitY {
                double X;
                double Y;
            };

            struct Acceleration {
                double X;
                double Y;
            };

            enum Shape {
                CIRCLE,
                SQUARE,
                TRIANGLE,
                PLANE
            };

            Position Pos;
            VelocitY Vel;
            Acceleration Acc;
            Shape Shp;
            

            // Setters ---------------------------

            void setPos(double posX, double posY) {
                Pos.X = posX;
                Pos.Y = posY;
            }

            void setVel(double vX, double vY) {
                Vel.X = vX;
                Vel.Y = vY;
            }

            void setAcc(double aX, double aY) {
                Acc.X = aX;
                Acc.Y = aY;
            }


            // Constructor - Need mass and radius

            Object() {
                mass = 1;
                radius = 1;
                dynamic = true;
                Pos.X = 0;
                Pos.Y = 0;
                Vel.X = 0;
                Vel.Y = 0;
                Acc.X = 0;
                Acc.Y = 0;
                Shp = CIRCLE;
            }
            Object(double m, double r, bool mov, Shape s) {
                mass = m;
                radius = r;
                dynamic = mov;
                Shp = s;
                Pos.X = 0;
                Pos.Y = 0;
                Vel.X = 0;
                Vel.Y = 0;
                Acc.X = 0;
                Acc.Y = 0;
            }

            void updateAll(double deltaT, double force, double theta, bool mov) { // updates all with old velocitY, then finds Acc and new velocitY
                if (mov == true) {
                    double forceX = std::cos(theta) * force;
                    double forceY = std::sin(theta) * force;
                    Acc.X = forceX / mass;
                    Acc.Y = forceY / mass;

                    Vel.X += Acc.X * deltaT;
                    Vel.Y += Acc.Y * deltaT;

                    Pos.X += Vel.X * deltaT;
                    Pos.Y += Vel.Y * deltaT;
                }

            }
            void printAll(std::string name) {
                std::cout << std::fixed << std::setprecision(3);
                std::cout << "Object " << name << std::endl;
                std::cout << "Pos X: " << Pos.X << " Pos Y: " << Pos.Y << "\n";
                std::cout << "Vel X: " << Vel.X << " Vel Y: " << Vel.Y << "\n";
                std::cout << "Acc X: " << Acc.X << " Acc Y: " << Acc.Y << "\n";
            }


};

void handleBoxCollision(Object& Obj1, Object& Obj2) {
    if (Obj1.Shp == Object::SQUARE && Obj2.Shp == Object::SQUARE) {

            // ok so, hmmmm
            // we have the problem of us now having multiple possible distances
            // first lets get the points of the 2 objects
            double X1 = Obj1.Pos.X;
            double Y1 = Obj1.Pos.Y;
            double X2 = Obj2.Pos.X;
            double Y2 = Obj2.Pos.Y; 

            double XL1 = X1 - Obj1.radius;
            double XR1 = X1 + Obj1.radius;
            double YT1 = Y1 + Obj1.radius;
            double YB1 = Y1 + Obj1.radius;

            double XL2 = X2 - Obj2.radius;
            double XR2 = X2 + Obj2.radius;
            double YT2 = Y2 + Obj2.radius;
            double YB2 = Y2 + Obj2.radius;

            // find which kind of overlap
            // we dont need to do both because we already know that they have collided
            int Xoverlap = 0;
            int Yoverlap = 0;

            if (XR1 >= XL2 && XL1 <= XR2) { // 1 to the left of 2   |1||2|
                Xoverlap = 1;
            }
            if (XR2 >= XL1 && XL2 <= XR1) { // 2 to the left of 1  |2||1|
                Xoverlap = 2;
            }

            if (YB1 >= YT2 && YT1 <= YB2)




            // all we need to do is to find the overlap of x, the overlap of y, then move both by 1/2 that

            // first identify what kind of collsion of the 4 kinds





            // // now lets get our new vector, c -> this is the line from b to a!!
            // double cX = X1 - X2;
            // double cY = Y1 - Y2;

            // // now lets get the magnitude of c
            // double magnitudeC = std::sqrt((cX * cX) + (cY * cY)); //  ->
            
            // // now lets get the sum of the radii
            // double rsum = Obj1.radius + Obj2.radius;

            // // now lets see how much larger the sum of the radii are than c
            // double larger = rsum - magnitudeC;

            // // now we have a magnitude of how much in total both need to be moved
            // // I can multiplY this magnitude bY the normal vector between them
            // // we get the unit vector bY dividing c bY its magnitude
            // double unitCX = cX / magnitudeC;
            // double unitCY = cY / magnitudeC;

            // double moveIX = 1 * unitCX * larger * .5;
            // double moveIY = 1 * unitCY * larger * .5;
            // double moveJX = unitCX * larger * -.5;
            // double moveJY = unitCY * larger * -.5;

            // // now cant we just multiplY both of these bY larger, with Obj1 being negative since
            // // the vector goes from a TO b, then we add those to the positions of i and j
            // // plus lets saY a verY small buffer?

            // // now we just move both of the vectors
            // Obj1.Pos.X = Obj1.Pos.X + moveIX;
            // Obj1.Pos.Y = Obj1.Pos.Y + moveIY;
            // Obj2.Pos.X = Obj2.Pos.X + moveJX;
            // Obj2.Pos.Y = Obj2.Pos.Y + moveJY;
//=======================================================
            double aX = Obj1.Vel.X;
            double aY = Obj1.Vel.Y;
            double bX = Obj2.Vel.X;
            double bY = Obj2.Vel.Y;

            Obj1.Vel.X = (aX * (Obj1.mass - Obj2.mass) + (2 * Obj2.mass * bX))
            / (Obj1.mass + Obj2.mass);

            Obj1.Vel.Y = (aY * (Obj1.mass - Obj2.mass) + (2 * Obj2.mass * bY))
            / (Obj1.mass + Obj2.mass);

            Obj2.Vel.X = (bX * (Obj2.mass - Obj1.mass) + (2 * Obj1.mass * aX))
            / (Obj2.mass + Obj1.mass);

            Obj2.Vel.Y = (bY * (Obj2.mass - Obj1.mass) + (2 * Obj1.mass * aY))
            / (Obj2.mass + Obj1.mass);
    }
    else if (Obj1.Shp == Object::SQUARE && Obj2.Shp == Object::CIRCLE) {

    }
    {
        /* code */
    }
    
}

bool detectBoundingBox(std::vector<Object>& Obj) {
    for (int i = 0; i < Obj.size(); i++) {
        for (int j = i + 1; j < Obj.size(); j++) {
            double x1 = Obj[i].Pos.X;
            double y1 = Obj[i].Pos.Y;

            double x2 = Obj[j].Pos.X;
            double y2 = Obj[j].Pos.Y;

            double xr1 = x1 + Obj[i].radius;
            double xl1 = x1 - Obj[i].radius;
            double yt1 = y1 + Obj[i].radius;
            double yb1 = y1 - Obj[i].radius;

            double xr2 = x2 + Obj[j].radius;
            double xl2 = x2 - Obj[j].radius;
            double yt2 = y2 + Obj[j].radius;
            double yb2 = y2 - Obj[j].radius;

            bool flag = false;

            if (((xr1 >= xl2 && xl1 <= xr2) ||
                (xr2 >= xl1 && xl2 <= xr1) ) &&
                (yt1 >= yb2 && yb1 <= yt2) ||
                (yt2 >= yb1 && yb2 <= yt1)) {
                    return true
                }


            // how to detect box collsisions



        }
    }
}

// ok how do I create unmovable objects that are not circles
// and sqaures that can move?

// remove radius from the main class?
// then how do I detect collisions

// ok determine the sqare of a point
// we can make checks of what kind of object

// naaah ok so lets just do this to add static objects
// add a new function called static object
// and make a new object
// and do another check......
// ahhhhhhhhhhhhhhhhhhhh