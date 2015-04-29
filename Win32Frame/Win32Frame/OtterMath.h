#ifndef __OTTERVECTOR_H__
#define __OTTERVECTOR_H__

#include <cmath>

template<typename T>
class OtterVector2
{
public:
	template<typename U>
	OtterVector2( const OtterVector2<U> other );
	OtterVector2();
	OtterVector2( T x, T y );
	~OtterVector2();

	bool Set( T x , T y );

	T GetLength();
	
	template<typename U>
	void operator +=( const OtterVector2<U> a );
	template<typename U>
	void operator -=( const OtterVector2<U> a );

public:
	T x, y;
};

template<typename T, typename U>
OtterVector2<T> operator+( const OtterVector2<T> a, const OtterVector2<U> b );

template<typename T, typename U>
OtterVector2<T> operator-( const OtterVector2<T> a, const OtterVector2<U> b );

template<typename T, typename U>
OtterVector2<T> operator*( const OtterVector2<T> a, const U b );



template<typename T>
class OtterRect2
{
public:
	OtterRect2( T x1, T y1, T x2, T y2 );
	OtterRect2( OtterVector2<T> point1, OtterVector2<T> point2 );
	OtterRect2();
	~OtterRect2();

	void operator +=( const OtterVector2<T> trans );
	void operator -=( const OtterVector2<T> trans );

public:
	OtterVector2<T> point[2];
};

typedef OtterVector2<double> OtterVector2d;
typedef OtterVector2<float> OtterVector2f;
typedef OtterVector2<int> OtterVector2i;
typedef OtterVector2<unsigned int> OtterVector2ui;

typedef OtterRect2<double> OtterRect2d;
typedef OtterRect2<float> OtterRect2f;
typedef OtterRect2<int> OtterRect2i;
typedef OtterRect2<unsigned int> OtterRect2ui;

#endif

#ifndef __OTTERVECTOR_CPP__
#define __OTTERVECTOR_CPP__

// ---------------------------- OtterVector2 ----------------------------
template<typename T>
template<typename U>
OtterVector2<T>::OtterVector2( const OtterVector2<U> other )
{
	this->x = other.x;
	this->y = other.y;
}

template<typename T>
OtterVector2<T>::OtterVector2( T x, T y )
{
	this->x = x;
	this->y = y;
}

template<typename T>
OtterVector2<T>::OtterVector2()
{
	this->x = 0;
	this->y = 0;
}

template<typename T>
OtterVector2<T>::~OtterVector2()
{
}

template<typename T>
bool OtterVector2<T>::Set( T x, T y )
{
	this->x = x;
	this->y = y;
}

template<typename T>
T OtterVector2<T>::GetLength()
{
	return std::sqrt( ( x * x ) + ( y * y ) );
}

template<typename T>
template<typename U>
void OtterVector2<T>::operator +=( const OtterVector2<U> a )
{
	this->x += a.x;
	this->y += a.y;
}

template<typename T>
template<typename U>
void OtterVector2<T>::operator -=( const OtterVector2<U> a )
{
	this->x -= a.x;
	this->y -= a.y;
}

template<typename T, typename U>
OtterVector2<T> operator +( const OtterVector2<T> a, const OtterVector2<U> b )
{
	OtterVector2<T> temp;
	temp.x = a.x + b.x;
	temp.y = a.y + b.y;
	return temp;
}

template<typename T, typename U>
OtterVector2<T> operator-( const OtterVector2<T> a, const OtterVector2<U> b )
{
	OtterVector2<T> temp;
	temp.x = a.x - b.x;
	temp.y = a.y - b.y;
	return temp;
}

template<typename T, typename U>
OtterVector2<T> operator*( const OtterVector2<T> a, const U b )
{
	OtterVector2<T> temp = a;
	temp.x *= b;
	temp.y *= b;
	return temp;
}


// ---------------------------- OtterRect2 ----------------------------
template<typename T>
OtterRect2<T>::OtterRect2( T x1, T y1, T x2, T y2 )
{
	point[0].x = x1;
	point[0].y = y1; 
	point[1].x = x2;
	point[1].y = y2; 
}

template<typename T>
OtterRect2<T>::OtterRect2( OtterVector2<T> point1, OtterVector2<T> point2 )
{
	point[0] = point1;
	point[1] = point2;
}
template<typename T>
OtterRect2<T>::OtterRect2()
{
}
template<typename T>
OtterRect2<T>::~OtterRect2()
{
}

template<typename T>
void OtterRect2<T>::operator +=( const OtterVector2<T> trans )
{
	point[0] += trans;
	point[1] += trans;
}

template<typename T>
void OtterRect2<T>::operator -=( const OtterVector2<T> trans )
{
	point[0] -= trans;
	point[1] -= trans;
}


#endif 