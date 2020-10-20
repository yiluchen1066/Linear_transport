#pragma once
#include <Eigen/Core>


//! The gradient of the shape function (on the reference element)
//! 
//! We have three shape functions
//!
//! @param i integer between 0 and 2 (inclusive). Decides which shape function to return.
//! @param x x coordinate in the reference element.
//! @param y y coordinate in the reference element.
inline Eigen::Vector2d gradientLambda(const int i, double x, double y) {
// (write your solution here)
    Eigen::Vector2d Di;
    switch (i) {
        case 0:
            Di[x,y] = (-1, -1);
            break;
        case 1:
            Di(x,y)= (1,0);
            break;
        case 2:
            Di(x,y) = (0,1);
            break;
    }
    return Eigen::Vector2d Di(x,y); //remove when implemented
}
