#ifndef VECTOR2
#define VECTOR2

#include <array>
#include <iostream>
#include <cmath>


//std::array wrapper
class Vector2{
private: 
    std::array<double, 2> array;
public:
    Vector2(double x, double y){
        array[0] = x;
        array[1] = y;
    }
    Vector2(const Vector2& other){ //copy Constructor
        array[0] = other.getX();
        array[1] = other.getY();
    }

    Vector2(std::initializer_list<double> init){
        const int size = init.size();
        
        if(size != 2){
            std::cerr << "incorrect initializer list dimension" << std::endl;
        }else{
            int i = 0;
            for(const double& elem: init){
                switch(i){
                    case 0:
                        array[0] = elem;
                        break;
                    case 1:
                        array[1] = elem;
                        break;
                }
                ++i;
            }
        }

    }

    Vector2& operator=(const Vector2& other){
        x() = other.getX();
        y() = other.getY();
        return *this;
    }

    Vector2 operator+(const Vector2& other) const{
        Vector2 sum(getX() + other.getX(), getY() + other.getY());
        return sum;
    }
    
    Vector2 operator-(const Vector2& other) const{
        Vector2 sum(getX() - other.getX(), getY() - other.getY());
        return sum;
    }

    Vector2& operator+=(const Vector2& other) {
        *this = *this + other;
        return *this;
    }

    Vector2& operator -=(const Vector2& other){
        *this = *this - other;
        return *this;
    }

    Vector2 operator*(const double scalar) const{ //scalar multiplication
        return Vector2(getX() * scalar, getY() * scalar);
    }

    Vector2 operator/(const double div) const{
        return Vector2(getX() / div, getY() / div);
    }

    friend Vector2 operator*(const double scalar, const Vector2& vec){
        return Vector2(scalar * vec.getX(), scalar * vec.getY());
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
        os << "(" << vec.getX() << ", " << vec.getY() << ")";
        return os;
    }

    double distance(const Vector2& other) const{ //computes euclidian distance
        return sqrt(pow(getX() - other.getX(), 2) + pow(getY() - other.getY(), 2));
    }

    double magnitude() const{
        return sqrt(pow(getX(), 2) + pow(getY(), 2));
    }

    //returns a unit Direction Vector from [this] to [other]
    Vector2 unitDirection(const Vector2& other) const{
        Vector2 direction = other - *this;
        Vector2 unitdirection = direction / direction.magnitude();
        return unitdirection;
    }
    
    double& x(){
        return array[0];
    }

    double& y(){
        return array[1];
    }

    double getX() const{
        return array[0];
    }

    double getY() const{
        return array[1];
    }
};

#endif