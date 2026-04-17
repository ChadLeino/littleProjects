#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <vector>
#include "raylib.h"



class Object {
    public:

        double mass;
        double radius;

        struct Position {
            double x;
            double y;
        };

        struct Velocity {
            double velX;
            double velY;
        };

        struct Acceleration {
            double accelX;
            double accelY;
        };

        Position Pos;
        Velocity Vel;
        Acceleration Accel;
        

        // Setters ---------------------------

        void setPos(double posx, double posy) {
            Pos.x = posx;
            Pos.y = posy;
        }

        void setVel(double vX, double vY) {
            Vel.velX = vX;
            Vel.velY = vY;
        }

        void setAccel(double aX, double aY) {
            Accel.accelX = aX;
            Accel.accelY = aY;
        }


        // Constructor - Need mass and radius

        Object() {
            mass = 1;
            radius = 1;
            Pos.x = 0;
            Pos.y = 0;
            Vel.velX = 0;
            Vel.velY = 0;
            Accel.accelX = 0;
            Accel.accelY = 0;          
        }
        Object(double m, double r) {
            mass = m;
            radius = r;
            Pos.x = 0;
            Pos.y = 0;
            Vel.velX = 0;
            Vel.velY = 0;
            Accel.accelX = 0;
            Accel.accelY = 0;
        }

        // double calcVelX(double deltaT) {
        //     return 
        // }
        // double calcVelY(double deltaT) {
        //     return Vel.velY + (Accel.accelY * deltaT);
        // }

        // double calcPosX(double deltaT) {
        //     return Pos.x + (Vel.velX * deltaT) + (0.5 * (Accel.accelX * std::pow(deltaT, 2)));
        // }
        // double calcPosY(double deltaT) {
        //     return Pos.y + (Vel.velY * deltaT) + (0.5 * (Accel.accelY * std::pow(deltaT, 2)));
        // }

        // double calcAccel(double force) {
        //     return force / mass;
        // }

        // double getXForce(double force, double theta) {
        //     return std::cos(theta) * force;
        // }

        // double getYForce(double force, double theta) {
        //     return std::sin(theta) * force;
        // }

        void updateAll(double deltaT, double force, double theta) { // updates all with old velocity, then finds accel and new velocity
            double forceX = std::cos(theta) * force;
            double forceY = std::sin(theta) * force;
            Accel.accelX = forceX / mass;
            Accel.accelY = forceY / mass;

            Vel.velX += Accel.accelX * deltaT;
            Vel.velY += Accel.accelY * deltaT;

            Pos.x += Vel.velX * deltaT;
            Pos.y += Vel.velY * deltaT;

        }
        void printAll(std::string name) {
            std::cout << std::fixed << std::setprecision(3);
            std::cout << "Object " << name << std::endl;
            std::cout << "Pos X: " << Pos.x << " Pos Y: " << Pos.y << "\n";
            std::cout << "Vel X: " << Vel.velX << " Vel Y: " << Vel.velY << "\n";
            std::cout << "Acc X: " << Accel.accelX << " Acc Y: " << Accel.accelY << "\n";
        }


};



bool detectCollision(const Object& obj1,const Object& obj2) {
    double dx = obj1.Pos.x - obj2.Pos.x;
    double dy = obj1.Pos.y - obj2.Pos.y;
    double rsum = obj1.radius + obj2.radius;

    return (dx * dx + dy * dy) <= (rsum * rsum);

}

void detectGround(Object& obj) {
    if (obj.Pos.y - obj.radius <= 0) {
        obj.Pos.y = obj.radius;

    
        if (obj.Vel.velY < 0){
            obj.Vel.velY *= -.9;
        }
        else {
            obj.Vel.velY = 0;
        }
        obj.Accel.accelY = 0;
    }

}

double degreeToRadian(double theta) {
    double pi = 3.141592653589793;
    return theta * pi / 180;
}

void collisionHandle(std::vector<Object>& vec1) {
    for(int i = 0; i < vec1.size(); i++) {
        detectGround(vec1[i]);
        for(int j = i + 1; j < vec1.size(); j++) {
            if (detectCollision(vec1[i], vec1[j])) {
                // first we need to move the objects so they do not get stuck
                
                // first lets get the points of the 2 objects
                double x1 = vec1[i].Pos.x;
                double y1 = vec1[i].Pos.y;
                double x2 = vec1[j].Pos.x;
                double y2 = vec1[j].Pos.y;

                // now lets get our new vector, c
                double cx = x1 - x2;
                double cy = y1 - y2;

                // now lets get the magnitude of c
                double magnitudeC = std::sqrt((cx * cx) + (cy * cy));
                
                // now lets get the sum of the radii
                double rsum = vec1[i].radius + vec1[j].radius;

                // now lets see how much larger the sum of the radii are than c
                double larger = rsum - magnitudeC;

                // now we have a magnitude of how much in total both need to be moved
                // I can multiply this magnitude by the normal vector between them
                // we get the unit vector by dividing c by its magnitude
                double unitCx = cx / magnitudeC;
                double unitCy = cy / magnitudeC;

                double moveIx = 1 * unitCx * larger * .5;
                double moveIy = 1 * unitCy * larger * .5;
                double moveJx = unitCx * larger * -.5;
                double moveJy = unitCy * larger * -.5;

                // now cant we just multiply both of these by larger, with vec1[i] being negative since
                // the vector goes from a TO b, then we add those to the positions of i and j
                // plus lets say a very small buffer?

                // now we just move both of the vectors
                vec1[i].Pos.x = vec1[i].Pos.x + moveIx;
                vec1[i].Pos.y = vec1[i].Pos.y + moveIy;
                vec1[j].Pos.x = vec1[j].Pos.x + moveJx;
                vec1[j].Pos.y = vec1[j].Pos.y + moveJy;


                // double xm = vec1[j].Pos.x - vec1[i].Pos.x;
                // double ym = vec1[j].Pos.y - vec1[i].Pos.y;
                // double thetam = std::atan2(xm, ym);
                // double rsum = vec1[i].radius + vec1[j].radius;
                // move both of them? or just one of them. one is easier
                // add move feature later
            }
        }
    }
}

struct Force { // a struct for forces applied to objects. They have a direction and magnitude
    double force;
    double theta;
    // this is meant to be in radians, but I will use degrees and use the function
        // degreeToRadian to convert
};

Force sumForces(Force f1, Force f2) { // for finding the total sum of 2 forces, run until all forces applied to one object then apply
    Force f3;
    double x1 = std::cos(f1.theta) * f1.force;
    double y1 = std::sin(f1.theta) * f1.force;

    double x2 = std::cos(f2.theta) * f2.force;
    double y2 = std::sin(f2.theta) * f2.force;
    double x3 = x1 + x2;
    double y3 = y1 + y2;

    double theta3 = std::atan2(y3, x3);
    double force3 = std::sqrt(x3 * x3 + y3 * y3);

    f3.force = force3;
    f3.theta = theta3;
    return f3;
}


#include "raylib.h"
#include <vector>
#include <string>
#include <iostream>

// assumes you already have:
// std::vector<Object> Objects;
// std::vector<Force> arrForces;
// collisionHandle(Objects);

int main() {
    Object p1(1, 50);
    Object p2(1, 50); // initialize 2 objects

    Force f1;
    Force f2;
    f1.force = 10;
    f1.theta = 0; // force 1 is 10 in the x direction
    f2.force = 9.8; // f2 is gravity
    f2.theta = degreeToRadian(-90); // initialize 2 forces


    p1.setPos(100, 100);
    p2.setPos(200, 300);
    p1.setVel(0, 0);
    p2.setVel(1, 1);

    std::cout << detectCollision(p1, p2) << "\n";
    std::vector<Object> Objects;
    Objects.push_back(p1);
    Objects.push_back(p2);


    std::vector<Force> arrForces;
    arrForces.push_back(f1);
    arrForces.push_back(f2);

    std::vector<Color> colors;
    colors.push_back(RED);
    colors.push_back(BLUE);

    double deltaT = 0.1;

    InitWindow(800, 600, "Physics");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        // one simulation step per space press
        if (true) {
            for (int j = 0; j < Objects.size(); j++) {
                Objects[j].updateAll(deltaT, arrForces[j].force, arrForces[j].theta);
            }

            collisionHandle(Objects);

            for (int j = 0; j < Objects.size(); j++) {
                std::string s = std::to_string(j);
                std::cout << "Object " << s << "\n";
                Objects[j].printAll(s);
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int j = 0; j < Objects.size(); j++) {
            DrawCircle(
                Objects[j].Pos.x,
                600 - Objects[j].Pos.y,
                Objects[j].radius,
                colors[j % colors.size()]
            );
        }

        DrawText("Press SPACE to advance one frame", 20, 20, 20, BLACK);
        DrawCircle(400, 300, 20, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}