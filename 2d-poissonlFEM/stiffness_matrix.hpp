#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>
#include "grad_shape.hpp"
#include "coordinate_transform.hpp"
#include "integrate.hpp"
#include "shape.hpp"

//----------------compMatrixBegin----------------
//! Evaluate the stiffness matrix on the triangle spanned by
//! the points (a, b, c).
//!
//! Here, the stiffness matrix A is a 3x3 matrix
//! 
//! $$A_{ij} = \int_{K} ( \nabla \lambda_i^K(x, y) \cdot  \nabla \lambda_j^K(x, y)\; dV$$
//! 
//! where $K$ is the triangle spanned by (a, b, c).
//!
//! @param[out] stiffnessMatrix should be a 3x3 matrix
//!                        At the end, will contain the integrals above.
//!
//! @param[in] a the first corner of the triangle
//! @param[in] b the second corner of the triangle
//! @param[in] c the third corner of the triangle
template<class MatrixType, class Point>
void computeStiffnessMatrix(MatrixType& stiffnessMatrix,
                            const Point& a,
                            const Point& b,
                            const Point& c)
{
    Eigen::Matrix2d coordinateTransform = makeCoordinateTransform(b - a, c - a);
    double volumeFactor = std::abs(coordinateTransform.determinant());
    Eigen::Matrix2d elementMap = coordinateTransform.inverse().transpose();
    for (int i=0; i < 3; i++){
        for (int j = 0; j < 3; j++) {
            auto ak = [i, j, a, elementMap, coordinateTransform, volumeFactor] (double x, double y) {
                Eigen::Vector2d Di = gradientLambda(i, x, y);
                Eigen::Vector2d Dj = gradientLambda(j, x, y);
                Eigen::Vector2d X;
                X(0) = x;
                X(1) = y;
                return (elementMap *  Di * coordinateTransform.inverse()).transpose() * (X -a) * (elementMap * Dj * coordinateTransform.inverse()).transpose() * (X-a) * volumeFactor;};

            stiffnessMatrix = integrate(ak);

        }

    }
// (write your solution here)

    
}
//----------------compMatrixEnd----------------
