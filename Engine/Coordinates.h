#pragma once

#include "Colors.h"
#include "Vec2.h"

struct Coordinates
{
	Coordinates( const Vec2f& A, const Vec2f& B, const Vec2f& C )
		:
		a( A ), b( B ), c( C ),
		ca( A - C ), ab( B - A ), bc( C - B ),
		recip_total_area( 1.f / CrossProduct( B - A, C - A ) )
	{}

	void Calculate( const Vec2f& P )
	{

		const auto ap = P - a;
		const auto bp = P - b;
		const auto cp = P - c;

		const float areaA = ( ca.y * cp.x - ca.x * cp.y ) * .5f;
		const float areaB = ( ab.y * ap.x - ab.x * ap.y ) * .5f;
		const float areaC = ( bc.y * bp.x - bc.x * bp.y ) * .5f;

		u = areaA * recip_total_area;
		v = areaB * recip_total_area;
		w = areaC * recip_total_area;
	}

	bool IsInTriangle()const
	{
		return
			( u >= 0.f && u <= 1.f ) &&
			( v >= 0.f && v <= 1.f ) &&
			( w >= 0.f && w <= 1.f );
	}

	template<class T>
	T Interpolate( const T& Value0, const T& Value1, const T& Value2 )
	{
		return ( Value0 * u ) + ( Value1 * v ) + ( Value2 * w );
	}
	template<>
	Color Interpolate( const Color& Value0, const Color& Value1, const Color& Value2 )
	{
		const unsigned char cu = static_cast< unsigned char >( u * 255.f );
		const unsigned char cv = static_cast< unsigned char >( v * 255.f );
		const unsigned char cw = static_cast< unsigned char >( w * 255.f );

		return ( Value0 * cu ) + ( Value1 * cv ) + ( Value2 * cw );
	}

	Vec2f a, b, c;
	Vec2f ca, ab, bc;
	float recip_total_area;
	float u, v, w;
};
