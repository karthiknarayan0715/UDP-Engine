#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>
#include <cmath>
#include <vector>
#include <LinearMath/btVector3.h>

#include "models/constants/constants.h"
#include "string_utils/string_utils.h"

class Vector3 {
    private:
        float magnitude;
    public:
        float x, y, z;
        Vector3(float x = 0, float y = 0, float z = 0) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        Vector3(std::string inputString) {
            std::vector<std::string> vectorString = split(inputString, VECTOR_SEPERATOR);
            this->x = std::stof(vectorString[0]);
            this->y = std::stof(vectorString[1]);
            this->z = std::stof(vectorString[2]);
        }

        float getMagnitude() {
            return std::sqrt(x * x + y * y + z * z);
        }

        Vector3 operator+(const Vector3& other) const {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }

        bool operator==(const Vector3& other) const {
            return (x == other.x && y==other.y && z==other.z);
        }

        Vector3 operator-(const Vector3& other) const {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }

        Vector3 operator-() const {
            return Vector3(-x, -y, -z);
        }        

        Vector3 operator*(const float other) const {
            return Vector3(x * other, y * other, z * other);
        }

        Vector3 normalized() {
            float mag = getMagnitude();
            if (mag == 0) return Vector3(0, 0, 0);
            return Vector3(x / mag, y / mag, z / mag);
        }

        void normalize() {
            float mag = getMagnitude();
            x = x / mag;
            y = y / mag;
            z = z / mag;
        }

        std::string ToString() {
            return std::to_string(this->x) + "," + std::to_string(this->y) + "," + std::to_string(this->z);
        }

        Vector3 getForwardVector() {
            if (getMagnitude() == 0) {
                return Vector3::DEFAULT_FORWARD;
            }
            Vector3 forwardVector = Vector3(x, y, z);
            return forwardVector.normalized();
        }

        Vector3 getRightVector() {
            Vector3 forwardVector = Vector3(x, y, z);
            Vector3 rightVector = Vector3::cross(WORLD_UP, forwardVector);
            if (rightVector.getMagnitude() == 0) {
                return Vector3::DEFAULT_RIGHT;
            }
            return rightVector.normalized();
        }

        
        // STATIC FUNCTIONS
        
        static const Vector3 WORLD_UP;
        
        static const Vector3 ZERO;
        
        static const Vector3 DEFAULT_FORWARD;
        
        static const Vector3 DEFAULT_RIGHT;
        
        static Vector3 cross(Vector3 a, Vector3 b){
            Vector3 crossProduct = Vector3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
            return crossProduct;
        } // Does a X b
        
        static Vector3 GetPlayerForwardVector(Vector3 playerRotation){
            Vector3 newVector = Vector3(sin(playerRotation.y * M_PI/180), 0, cos(playerRotation.y * M_PI/180));
            return newVector;
        }

        static float dot(Vector3 a, Vector3 b) {
            return a.x * b.x + a.y * b.y + a.z * b.z;
        }

        static btVector3 getBtVector3(Vector3 vector3) {
            return btVector3(vector3.x, vector3.y, vector3.z);
        }

        static Vector3 getVector3FromBtVector3(btVector3 vector3) {
            return Vector3(vector3.getX(), vector3.getY(), vector3.getZ());
        }
    };

#endif