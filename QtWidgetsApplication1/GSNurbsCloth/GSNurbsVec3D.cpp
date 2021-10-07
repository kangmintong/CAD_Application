#include "GSNurbsVec3d.h"
#include <cmath>
GSVec3D::GSVec3D()
{
	setValue(0, 0, 0);
}

GSVec3D::GSVec3D(const double v[3])
{
    setValue(v);
}

GSVec3D::GSVec3D(double a_x, double a_y, double a_z)
{
    setValue(a_x, a_y, a_z);
}

GSVec3D::GSVec3D(const GSVec3D & a_vec)
{
    setValue(a_vec[0], a_vec[1], a_vec[2]);
}

	


GSVec3D::~GSVec3D()
 {
 }

GSVec3D & GSVec3D::setValue(const double v[3])
{
    m_xyz[0] = v[0];
    m_xyz[1] = v[1];
    m_xyz[2] = v[2];

    return *this;
}

GSVec3D & GSVec3D::setValue(double a_x, double a_y, double a_z)
{
    m_xyz[0] = a_x;
    m_xyz[1] = a_y;
    m_xyz[2] = a_z;

    return *this;
}

GSVec3D & GSVec3D::setX(double a_x) {
	m_xyz[0] = a_x;
	return *this;
}
GSVec3D & GSVec3D::setY(double a_y) {
	m_xyz[1] = a_y;
	return *this;
}
GSVec3D & GSVec3D::setZ(double a_z) {
	m_xyz[2] = a_z;
	return *this;
}

//! Returns a pointer to an array containing the coordinates of the vector.
const double * GSVec3D::getValue() const
{
    return &m_xyz[0];
}

//! Calculates and returns the dot product of this vector with \a a_vec.
double GSVec3D::dot(const GSVec3D & a_vec) const
{
    return (m_xyz[0]*a_vec[0] + m_xyz[1]*a_vec[1] + m_xyz[2]*a_vec[2]);
}

//! Return length of vector.
double GSVec3D::length() const
{
    return (double)std::sqrt( sqrLength() );
}

//! Return squared length of vector.
double GSVec3D::sqrLength() const
{
    return (m_xyz[0]*m_xyz[0])+(m_xyz[1]*m_xyz[1])+(m_xyz[2]*m_xyz[2]);
}

//! Normalize the vector to unit length. Return value is the original length of the vector before normalization.
double GSVec3D::normalize()
{
    double magnitude = length();

    if(magnitude != 0.0)
        (*this) *= (double)(1.0 / magnitude);
    else setValue(0.0, 0.0, 0.0);

    return magnitude;
}

//! Returns the cross product of this vector with \a a_vec.
GSVec3D GSVec3D::cross(const GSVec3D & a_vec) const
{
    return GSVec3D(m_xyz[1] * a_vec[2] - a_vec[1] * m_xyz[2],
                        m_xyz[2] * a_vec[0] - a_vec[2] * m_xyz[0],
                        m_xyz[0] * a_vec[1] - a_vec[0] * m_xyz[1]);
}

//! Negate the vector (i.e. point it in the opposite direction).
void GSVec3D::negate()
{
    setValue(-m_xyz[0], -m_xyz[1], -m_xyz[2]);
}

//! Return modifiable x value.
double & GSVec3D::x(){  return m_xyz[0]; }

//! Return modifiable y value.
double & GSVec3D::y(){  return m_xyz[1]; }

//! Return modifiable z value.
double & GSVec3D::z(){  return m_xyz[2]; }

//! Return x value.
const double & GSVec3D::x()const{  return m_xyz[0]; }

//! Return y value.
const double & GSVec3D::y()const{  return m_xyz[1]; }

//! Return z value.
const double & GSVec3D::z()const{  return m_xyz[2]; }

//! Index operator. Returns modifiable x, y or z value.
double &  GSVec3D::operator[](int i) { return m_xyz[i]; }

//! Index operator. Returns x, y or z value.
const double & GSVec3D::operator[](int i) const { return m_xyz[i]; }

//! Multiply components of vector with value \a d. Returns reference to self.
GSVec3D & GSVec3D::operator *=(const double d)
{
    m_xyz[0] *= d;
    m_xyz[1] *= d;
    m_xyz[2] *= d;

    return *this;
}

//! Divides components of vector with value \a d. Returns reference to self.
GSVec3D & GSVec3D::operator /=(const double d)
{
    *this *= (1.0f/d);

    return *this;
}

//! Multiply components of vector with value \a a_vec.
GSVec3D & GSVec3D::operator *=(const GSVec3D & a_vec)
{
    m_xyz[0] *= a_vec.m_xyz[0];
    m_xyz[1] *= a_vec.m_xyz[1];
    m_xyz[2] *= a_vec.m_xyz[2];

    return *this;
}

//! Adds this vector and vector \a a_vec. Returns reference to self.
GSVec3D & GSVec3D::operator +=(const GSVec3D & a_vec)
{
    m_xyz[0] += a_vec.m_xyz[0];
    m_xyz[1] += a_vec.m_xyz[1];
    m_xyz[2] += a_vec.m_xyz[2];

    return *this;
}

//! Subtracts vector \a a_vec from this vector. Returns reference to self.
GSVec3D & GSVec3D::operator -=(const GSVec3D & a_vec)
{
    m_xyz[0] -= a_vec.m_xyz[0];
    m_xyz[1] -= a_vec.m_xyz[1];
    m_xyz[2] -= a_vec.m_xyz[2];

    return *this;
}

//! Non-destructive negation operator.
GSVec3D GSVec3D::operator-() const
{
    return GSVec3D(-m_xyz[0], -m_xyz[1], -m_xyz[2]);
}


