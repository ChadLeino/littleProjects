#include <iostream>
#include <cmath>


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

        Object(double m, double r) {
            mass = m;
            radius = r;
        }

        double calcVelX(double deltaT) {
            return Vel.velX + (Accel.accelX * deltaT);
        }
        double calcVelY(double deltaT) {
            return Vel.velY + (Accel.accelY * deltaT);
        }

        double calcPosX(double deltaT) {
            return Pos.x + (Vel.velX * deltaT) + (0.5 * (Accel.accelX * std::pow(deltaT, 2)));
        }
        double calcPosY(double deltaT) {
            return Pos.y + (Vel.velY * deltaT) + (0.5 * (Accel.accelY * std::pow(deltaT, 2)));
        }

        double calcAccel(double force) {
            return force / mass;
        }

        double getXForce(double force, double theta) {
            return std::cos(theta) * force;
        }

        double getYForce(double force, double theta) {
            return std::cos(theta) * force;
        }

        void updateAll(double deltaT, double force, double theta) {
            double forceX = getXForce(force, theta);
            double forceY = getYForce(force, theta);
            Accel.accelX = calcAccel(forceX);
            Accel.accelY = calcAccel(forceY);
            Vel.velX = calcVelX(deltaT);
            Vel.velY = calcVelY(deltaT);
            Pos.x = calcPosX(deltaT);
            Pos.y = calcPosY(deltaT);
        }


};

bool detectCollision(Object obj1, Object obj2) {
    double x1 = obj1.Pos.x;
    double y1 = obj2.Pos.y;

    double x2 = obj2.Pos.x;
    double y2 = obj2.Pos.y;

    double x1RightEdge = x1 + obj1.radius;
    double x1LeftEdge = x1 - obj1.radius;

    double y1TopEdge  = y1 + obj1.radius;
    double y1BottomEdge = y1 - obj1.radius;


    double x2RightEdge = x2 + obj2.radius;
    double x2LeftEdge = x2 - obj2.radius;

    double y2TopEdge  = y2 + obj2.radius;
    double y2BottomEdge = y2 - obj2.radius;

    // 2 cases for x, 2 cases for y
    // for x, x1RightEdge >= x2LeftEdge
        // or x1LeftEdge >= x2RightEdge

    bool xCollision;

    if (x1RightEdge > x2LeftEdge || x1LeftEdge > x2RightEdge) {
        xCollision = true;
    }

    // 2 cases for y
        // y1 bottom > y1top
        // or y1top > y1bottom
    
    bool yCollision;

    if (y1TopEdge > y2BottomEdge || y1BottomEdge > y2TopEdge) {
        yCollision = true;
    }

    return (xCollision && yCollision);

}

double degreeToRadian(int theta) {
    double pi = 3.141592653589793;
    return theta * pi / 180;
}

struct Force {
    double force;
    double theta;
    // this is meant to be in radians, but I will use degrees and use the function
        // degreeToRadian to convert
};


int main() {

    Object p1(1, 1);
    Object p2(1, 1);

    Force f1;
    Force f2;
    f1.force = 10;
    f1.theta = 0;
    f2.force = 9.8;
    f2.theta = degreeToRadian(-90);


    p1.setPos(0, 0);
    p2.setPos(1, 0);
    p1.setVel(0, 0);
    p2.setVel(1, 1);

    std::cout << detectCollision(p1, p2) << "\n";

    int i = 10;
    int deltaT = 1;
    for (i = 0; i < 10; i++) {
       p1.updateAll(deltaT, f1.force, f1.theta);
       p2.updateAll(deltaT, f2.force, f2.theta);
       std::cout << p1.Pos.x << " " << p1.Vel.velX << " " << p1.Vel.velY << "\n";
       std::cout << p2.Pos.y << " " << p2.Accel.accelY << "\n";
    }

    return 0;


}