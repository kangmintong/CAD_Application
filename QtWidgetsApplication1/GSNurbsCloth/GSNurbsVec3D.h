#pragma once
#include <memory>
#include <vector>

class GSVec3D
    {
		public:
        GSVec3D();

        //! Constructs an instance with initial values from \a v.
        GSVec3D(const double v[3]);

        //! Constructs an instance with the initial values from \a a_x, \a a_y and \a a_z.
        GSVec3D(double a_x, double a_y, double a_z);

        //! Constructs an instance with initial values from \a a_vec.
        GSVec3D(const GSVec3D & a_vec);

        //! Default destructor does nothing.
        ~GSVec3D();

        //! Set new x, y and z values for the vector. Returns reference to self.
        GSVec3D & setValue(const double v[3]);

        //! Set new x, y and z values for the vector. Returns reference to self.
        GSVec3D & setValue(double a_x, double a_y, double a_z);

		GSVec3D & setX(double a_x);
		GSVec3D & setY(double a_y);
		GSVec3D & setZ(double a_z);

        //! Returns a pointer to an array containing the coordinates of the vector.
        const double * getValue() const;

        //! Calculates and returns the dot product of this vector with \a a_vec.
        double dot(const GSVec3D & a_vec) const;

        //! Return length of vector.
        double length() const;

        //! Return squared length of vector.
        double sqrLength() const;

        //! Normalize the vector to unit length. Return value is the original length of the vector before normalization.
        double normalize();

        //! Returns the cross product of this vector with \a a_vec.
        GSVec3D cross(const GSVec3D & a_vec) const;

        //! Negate the vector (i.e. point it in the opposite direction).
        void negate();

        //! Return modifiable x value.
        double & x();

        //! Return modifiable y value.
        double & y();

        //! Return modifiable z value.
        double & z();

        //! Return x value.
        const double & x()const;

        //! Return y value.
        const double & y()const;

        //! Return z value.
        const double & z()const;

        //! Index operator. Returns modifiable x, y or z value.
        double &  operator[](int i);

        //! Index operator. Returns x, y or z value.
        const double & operator[](int i) const;

        //! Multiply components of vector with value \a d. Returns reference to self.
        GSVec3D & operator *=(const double d);

        //! Divides components of vector with value \a d. Returns reference to self.
        GSVec3D & operator /=(const double d);

        //! Multiply components of vector with value \a a_vec.
        GSVec3D & operator *=(const GSVec3D & a_vec);

        //! Adds this vector and vector \a a_vec. Returns reference to self.
        GSVec3D & operator +=(const GSVec3D & a_vec);

        //! Subtracts vector \a a_vec from this vector. Returns reference to self.
        GSVec3D & operator -=(const GSVec3D & a_vec);

        //! Non-destructive negation operator.
        GSVec3D operator-() const;

        friend GSVec3D operator *(const GSVec3D & a_vec, const double d)
        { 
            return GSVec3D(a_vec.m_xyz[0] * d, a_vec.m_xyz[1] * d, a_vec.m_xyz[2] * d);
        }

        friend GSVec3D operator *(const double d, const GSVec3D & a_vec)
        { 
            return a_vec * d; 
        }

        friend GSVec3D operator /(const GSVec3D & a_vec, const double d)
        { 
            return GSVec3D(a_vec.m_xyz[0] / d, a_vec.m_xyz[1] / d, a_vec.m_xyz[2] / d);
        }

        friend GSVec3D operator *(const GSVec3D & v1, const GSVec3D & v2)
        {	
            return GSVec3D(v1.m_xyz[0] * v2.m_xyz[0],v1.m_xyz[1] * v2.m_xyz[1],v1.m_xyz[2] * v2.m_xyz[2]);
        }

        friend GSVec3D operator +(const GSVec3D & v1, const GSVec3D & v2)
        {	
            return GSVec3D(v1.m_xyz[0] + v2.m_xyz[0],v1.m_xyz[1] + v2.m_xyz[1],v1.m_xyz[2] + v2.m_xyz[2]);
        }

        friend GSVec3D operator -(const GSVec3D & v1, const GSVec3D & v2)
        {	
            return GSVec3D(v1.m_xyz[0] - v2.m_xyz[0],v1.m_xyz[1] - v2.m_xyz[1],v1.m_xyz[2] - v2.m_xyz[2]);	
        }

        //! Check the two given vector for equality. 
        friend bool operator ==(const GSVec3D & v1, const GSVec3D & v2)
        { 
            return (v1.m_xyz[0]==v2.m_xyz[0] && v1.m_xyz[1]==v2.m_xyz[1] && v1.m_xyz[2]==v2.m_xyz[2]); 
        }

        //! Check the two given vector for inequality. 
        friend bool operator !=(const GSVec3D & v1, const GSVec3D & v2)
        { 
            return !(v1 == v2); 
        }

    private:
        double m_xyz[3];
		
    };

	