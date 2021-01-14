#include <iostream>
#include <cmath>
using namespace std;

class Vector{
    public:
        double x, y, z;
        Vector()
        {
            x = 0;
            y = 0;
            z = 0;
        }

        Vector(double coordX, double coordY, double coordZ)
        {
            x = coordX;
            y = coordY;
            z = coordZ;
        }

        Vector SMul(double alpha)
        {
            double x1 = x;
            double y1 = y;
            double z1 = z;
            x1 *= alpha;
            y1 *= alpha;
            z1 *= alpha;
            Vector v2(x1,y1,z1);
            return v2;
        }

        double DProd(Vector v2)
        {
            double a , b , c;
            a = x * v2.x;
            b = y * v2.y;
            c = z * v2.z;
            return (a+b+c);
        }
        Vector VProd(Vector v2)
        {
            Vector v3;
            v3.x = (y * v2.z - z * v2.y);
            v3.y = (x * v2.z - z * v2.x);
            v3.z = (x * v2.y - y * v2.x);
            return v3;
        }
        double Mod(){
            Vector v1(x,y,z);
            double mod = sqrt(v1.DProd(v1));
            return mod;
        }
        Vector unit(){
            Vector v1(x,y,z);
            double mod = v1.Mod();
            Vector v2; 
            v2 = v1.SMul(1/mod);
            return v2;
        }
};