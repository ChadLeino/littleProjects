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

        Position Pos;
        VelocitY Vel;
        Acceleration Acc;
        

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
            Pos.X = 0;
            Pos.Y = 0;
            Vel.X = 0;
            Vel.Y = 0;
            Acc.X = 0;
            Acc.Y = 0;          
        }
        Object(double m, double r) {
            mass = m;
            radius = r;
            Pos.X = 0;
            Pos.Y = 0;
            Vel.X = 0;
            Vel.Y = 0;
            Acc.X = 0;
            Acc.Y = 0;
        }

        // double calcX(double deltaT) {
        //     return 
        // }
        // double calcY(double deltaT) {
        //     return Vel.Y + (Acc.Y * deltaT);
        // }

        // double calcPosX(double deltaT) {
        //     return Pos.X + (Vel.X * deltaT) + (0.5 * (Acc.X * std::pow(deltaT, 2)));
        // }
        // double calcPosY(double deltaT) {
        //     return Pos.Y + (Vel.Y * deltaT) + (0.5 * (Acc.Y * std::pow(deltaT, 2)));
        // }

        // double calcAcc(double force) {
        //     return force / mass;
        // }

        // double getXForce(double force, double theta) {
        //     return std::cos(theta) * force;
        // }

        // double getYForce(double force, double theta) {
        //     return std::sin(theta) * force;
        // }

        void updateAll(double deltaT, double force, double theta) { // updates all with old velocitY, then finds Acc and new velocitY
            double forceX = std::cos(theta) * force;
            double forceY = std::sin(theta) * force;
            Acc.X = forceX / mass;
            Acc.Y = forceY / mass;

            Vel.X += Acc.X * deltaT;
            Vel.Y += Acc.Y * deltaT;

            Pos.X += Vel.X * deltaT;
            Pos.Y += Vel.Y * deltaT;

        }
        void printAll(std::string name) {
            std::cout << std::fixed << std::setprecision(3);
            std::cout << "Object " << name << std::endl;
            std::cout << "Pos X: " << Pos.X << " Pos Y: " << Pos.Y << "\n";
            std::cout << "Vel X: " << Vel.X << " Vel Y: " << Vel.Y << "\n";
            std::cout << "Acc X: " << Acc.X << " Acc Y: " << Acc.Y << "\n";
        }


};



bool detectCollision(const Object& obj1,const Object& obj2) {
    double dX = obj1.Pos.X - obj2.Pos.X;
    double dY = obj1.Pos.Y - obj2.Pos.Y;
    double rsum = obj1.radius + obj2.radius;

    return (dX * dX + dY * dY) <= (rsum * rsum);

}

void detectGround(Object& obj) {
    if (obj.Pos.Y - obj.radius <= 0) {
        obj.Pos.Y = obj.radius;

    
        if (obj.Vel.Y < 0){
            obj.Vel.Y *= -.9;
        }
        else {
            obj.Vel.Y = 0;
        }
        obj.Acc.Y = 0;
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
                // first we need to move the objects so theY do not get stuck
                
                // first lets get the points of the 2 objects
                double X1 = vec1[i].Pos.X;
                double Y1 = vec1[i].Pos.Y;
                double X2 = vec1[j].Pos.X;
                double Y2 = vec1[j].Pos.Y;

                // now lets get our new vector, c
                double cX = X1 - X2;
                double cY = Y1 - Y2;

                // now lets get the magnitude of c
                double magnitudeC = std::sqrt((cX * cX) + (cY * cY));
                
                // now lets get the sum of the radii
                double rsum = vec1[i].radius + vec1[j].radius;

                // now lets see how much larger the sum of the radii are than c
                double larger = rsum - magnitudeC;

                // now we have a magnitude of how much in total both need to be moved
                // I can multiplY this magnitude bY the normal vector between them
                // we get the unit vector bY dividing c bY its magnitude
                double unitCX = cX / magnitudeC;
                double unitCY = cY / magnitudeC;

                double moveIX = 1 * unitCX * larger * .5;
                double moveIY = 1 * unitCY * larger * .5;
                double moveJX = unitCX * larger * -.5;
                double moveJY = unitCY * larger * -.5;

                // now cant we just multiplY both of these bY larger, with vec1[i] being negative since
                // the vector goes from a TO b, then we add those to the positions of i and j
                // plus lets saY a verY small buffer?

                // now we just move both of the vectors
                vec1[i].Pos.X = vec1[i].Pos.X + moveIX;
                vec1[i].Pos.Y = vec1[i].Pos.Y + moveIY;
                vec1[j].Pos.X = vec1[j].Pos.X + moveJX;
                vec1[j].Pos.Y = vec1[j].Pos.Y + moveJY;


                // double Xm = vec1[j].Pos.X - vec1[i].Pos.X;
                // double Ym = vec1[j].Pos.Y - vec1[i].Pos.Y;
                // double thetam = std::atan2(Xm, Ym);
                // double rsum = vec1[i].radius + vec1[j].radius;
                // move both of them? or just one of them. one is easier
                // add move feature later

                // ok unfortunatelY we need to make this monster of a function
                    // I can rewrite later, but that will take fundamental resturcturing of the code

                    // I have i and j

                    double aX = vec1[i].Vel.X;
                    double aY = vec1[i].Vel.Y;
                    double bX = vec1[j].Vel.X;
                    double bY = vec1[j].Vel.Y;

                    vec1[i].Vel.X = (aX * (vec1[i].mass - vec1[j].mass) + (2 * vec1[j].mass * bX))
                    / (vec1[i].mass + vec1[j].mass);
                    vec1[i].Vel.Y = (aY * (vec1[i].mass - vec1[j].mass) + (2 * vec1[j].mass * bY))
                    / (vec1[i].mass + vec1[j].mass);
                    vec1[j].Vel.X = (bX * (vec1[j].mass - vec1[i].mass) + (2 * vec1[i].mass * aX))
                    / (vec1[j].mass + vec1[i].mass);
                    vec1[j].Vel.Y = (bY * (vec1[j].mass - vec1[i].mass) + (2 * vec1[i].mass * aY))
                    / (vec1[j].mass + vec1[i].mass);
            }
        }
    }
}



struct Force { // a struct for forces applied to objects. TheY have a direction and magnitude
    double force;
    double theta;
    // this is meant to be in radians, but I will use degrees and use the function
        // degreeToRadian to convert
};

Force sumForces(Force f1, Force f2) { // for finding the total sum of 2 forces, run until all forces applied to one object then applY
    Force f3;
    double X1 = std::cos(f1.theta) * f1.force;
    double Y1 = std::sin(f1.theta) * f1.force;

    double X2 = std::cos(f2.theta) * f2.force;
    double Y2 = std::sin(f2.theta) * f2.force;
    double X3 = X1 + X2;
    double Y3 = Y1 + Y2;

    double theta3 = std::atan2(Y3, X3);
    double force3 = std::sqrt(X3 * X3 + Y3 * Y3);

    f3.force = force3;
    f3.theta = theta3;
    return f3;
}





int main() {



    // Simple test ---------------------

    Object pt1(10, 50);
    Object pt2(20, 50);

    Object pt3(20, 20);
    Object pt4(100, 25);

    Force ft1;
    Force ft2;
    Force ft3;
    Force ft4;

    ft1.force = 0;
    ft1.theta = 0;

    ft2.force = 0;
    ft2.theta = 0;

    ft3.force = 0;
    ft3.theta = 0;

    ft4.force = 9.8;
    ft4.theta = degreeToRadian(-90);

    pt1.setPos(200, 200);
    pt2.setPos(500, 200);

    pt1.setVel(2, 0);
    pt2.setVel(-4, 0);

    pt3.setPos(100, 100);
    pt4.setPos(500, 300);

    pt3.setVel(2,-2);
    pt4.setVel(-4, -4);

    std::vector<Force> arrForces;
    std::vector<Object> Objects;


    arrForces.push_back(ft1);
    arrForces.push_back(ft2);
    arrForces.push_back(ft3);
    arrForces.push_back(ft4);

    Objects.push_back(pt1);
    Objects.push_back(pt2);
    Objects.push_back(pt3);
    Objects.push_back(pt4);

    // Simple test end --------------------



    // Object p1(1, 50);
    // Object p2(1, 50); // initialize 2 objects
    // Object p3(1, 25);
    // Object p4(1, 40);
    // Object p5(1, 25);
    // Force f1;
    // Force f2;
    // Force f3;
    // Force f4;
    // Force f5;
    // f1.force = 4;
    // f1.theta = 0; // force 1 is 10 in the X direction
    // f2.force = 9.8; // f2 is gravitY
    // f2.theta = degreeToRadian(-90); // initialize 2 forces
    // f3.force = (10.58);
    // f3.theta = degreeToRadian(340);
    // f4.force = (10.58);
    // f4.theta = degreeToRadian(340);
    // f5.theta = degreeToRadian(-90); // force 1 is 10 in the X direction
    // f5.force = 9.8; // f2 is gravitY


    // p1.setPos(100, 100);
    // p2.setPos(200, 300);
    // p1.setVel(0, 0);
    // p2.setVel(1, 1);
    // p3.setPos(100, 200);
    // p3.setVel(-5, -10);
    // p4.setPos(80, 80);
    // p4.setVel(5, -10);
    // p5.setPos(40, 40);
    // p5.setVel(0, 5);

    // std::cout << detectCollision(p1, p2) << "\n";
    // std::vector<Object> Objects;
    // Objects.push_back(p1);
    // Objects.push_back(p2);
    // Objects.push_back(p3);
    // Objects.push_back(p4);
    // Objects.push_back(p5);


    // std::vector<Force> arrForces;
    // arrForces.push_back(f1);
    // arrForces.push_back(f2);
    // arrForces.push_back(f3);
    // arrForces.push_back(f4);
    // arrForces.push_back(f5);

    std::vector<Color> colors;
    colors.push_back(RED);
    colors.push_back(BLUE);
    colors.push_back(YELLOW);
    colors.push_back(GREEN);

    double deltaT = 0.1;

    InitWindow(800, 600, "Physics");
    SetTargetFPS(120);

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
                Objects[j].Pos.X,
                600 - Objects[j].Pos.Y,
                Objects[j].radius,
                colors[j % colors.size()]
            );
        }

        DrawText("Simulation Active, change if statement to alter conditions", 20, 20, 20, BLACK);
        DrawCircle(400, 300, 20, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}