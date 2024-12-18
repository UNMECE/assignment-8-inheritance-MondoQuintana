#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;

class Field
{
private:
    double *value;
public:
    Field(){
        value = (double*)malloc(3*sizeof(double));
        this->value[0]=0;
        this->value[1]=0;
        this->value[2]=0;
        cout<<"Default Field value set to 0"<<endl;
    };
    Field(double x, double y, double z){
        value = (double*)malloc(3*sizeof(double));
        this->value[0]=x;
        this->value[1]=y;
        this->value[2]=z;
    };
    Field(Field &field){
        value = (double*)malloc(3*sizeof(double));
        this->value[0]=field.FieldX();
        this->value[1]=field.FieldY();
        this->value[2]=field.FieldZ();
    }
    double FieldX(){
        return value[0];
    }
    double FieldY(){
        return value[1];
    }
    double FieldZ(){
        return value[2];
    }
    double getMagnitude(){
        return sqrt(pow(value[0],2)+pow(value[1],2)+pow(value[2],2));
    }
    double calculateInnerProduct(){
        return pow(value[0],2)+pow(value[1],2)+pow(value[2],2);
    }
    void setField(double x, double y, double z){
        this->value[0] = x;
        this->value[1] = y;
        this->value[2] = z;
        cout<<"Values Set"<<endl;
    }
    Field operator+(Field &field){
        //value = (double*)malloc(3*sizeof(double));
        Field F(this->value[0]+field.FieldX(), this->value[1]+field.FieldY(), this->value[2]+field.FieldZ());
        return F;
    }
    ~Field(){
        free(value);
        cout<<"Memory Free"<<endl;
    };
};

ostream &operator<<(ostream &os, Field &field){
    os<<"X = "<<field.FieldX()<<". Y = "<<field.FieldY()<<". Z = "<<field.FieldZ()<<endl;
    return os;
};

class Electric_Field:public Field{
    private:
        double E;
        double r;
        double Q;
    public:
        Electric_Field():Field(){};
        Electric_Field(double x, double y, double z):Field(x,y,z){};
        Electric_Field operator+(Electric_Field &field){
            Electric_Field F(this->FieldX()+field.FieldX(), this->FieldY()+field.FieldY(), this->FieldZ()+field.FieldZ());
            return F;
        }
        double calculateE(){
            double e = Q/4*M_PI*pow(r,2)*8.854e-12;
            return e;
        }
        void setE(double electricField){
            this->E = electricField;
        };
        void setr(double radius){
            this->r = radius;
        };
        void setQ(double charge){
            this->Q = charge;
        };
        double getE(){
            return E;
        }
        ~Electric_Field(){
        }
};

class Magnetic_Field:public Field{
    private:
        double B;
        double r;
        double I;
    public:
        Magnetic_Field():Field(){};
        Magnetic_Field(double x, double y, double z):Field(x,y,z){};
        Magnetic_Field operator+(Magnetic_Field &field){
            Magnetic_Field F(this->FieldX()+field.FieldX(), this->FieldY()+field.FieldY(), this->FieldZ()+field.FieldZ());
            return F;
        }
        double calculateB(){
            double b = I/2*M_PI*r*12.533e-7;
            return b;
        }
        void setB(double magneticField){
            this->B = magneticField;
        };
        void setr(double radius){
            this->r = radius;
        };
        void setI(double current){
            this->I = current;
        };
        double getB(){
            return B;
        }
        ~Magnetic_Field(){
        }
};

int main()
{
    
    Electric_Field Electric_Field1;
    cout<<"EF1 has x = "<<Electric_Field1.FieldX()<<" y = "<<Electric_Field1.FieldY()<< " and z = "<<Electric_Field1.FieldZ()<<endl;
    Electric_Field Electric_Field2(1,2,3);
    cout<<"EF2 has x = "<<Electric_Field2.FieldX()<<" y = "<<Electric_Field2.FieldY()<< " and z = "<<Electric_Field2.FieldZ()<<endl;
    cout<<"EF2 has Magnitude of "<<Electric_Field2.getMagnitude()<<endl;
    Electric_Field2.setQ(1e5);
    Electric_Field2.setr(10.9);
    double EFVALUE = Electric_Field2.calculateE();
    Electric_Field2.setE(EFVALUE);
    cout<<"E is "<<Electric_Field2.getE()<<endl;
    Magnetic_Field Magnetic_Field1(1,2,3);
    cout<<"Mag Field 1 = "<<Magnetic_Field1<<endl;
    Magnetic_Field1.setI(1e5);
    Magnetic_Field1.setr(10.9);
    double MFVALUE = Magnetic_Field1.calculateB();
    Magnetic_Field1.setB(MFVALUE);
    cout<<"B is "<<Magnetic_Field1.getB()<<endl;
    Electric_Field e;
    cout<<"Electric Field e has x = "<<e.FieldX()<<" y = "<<e.FieldY()<< " and z = "<<e.FieldZ()<<endl;
    e = Electric_Field2;
    cout<<"e has been set to EF2 "<<e<<endl;
    Magnetic_Field m;
    cout<<"Mag Field M "<<m<<endl;
    m = Magnetic_Field1;
    cout<<"M has been set to MF1"<<m<<endl;
    Electric_Field z;
    Magnetic_Field x;
    cout<<"Elec Field z and Mag Field x initialized with default values"<<endl;
    z = Electric_Field2 + e;
    x = Magnetic_Field1 + m;
    cout<<"z = EF2 + e "<<z<<endl;
    cout<<"x = MF1 + m "<<x<<endl;


    return 0;
}