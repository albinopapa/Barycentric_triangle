#pragma once

#include "Vertices.h"

struct Coordinates
{
	Coordinates( const Vertex2D_Color& A, const Vertex2D_Color& B, const Vertex2D_Color& C )
		:
		a( A ), b( B ), c( C ),
		ca( A.position - C.position ), ab( B.position - A.position ), bc( C.position - B.position ),
		recip_total_area( 1.f / ( CrossProduct( B.position - A.position, C.position - A.position ) * .5f ) )
	{}

	void Calculate( const Vec2f& P )
	{
		const auto ap = P - a.position;
		const auto bp = P - b.position;
		const auto cp = P - c.position;		
		
		const float areaA = CrossProduct( bc, bp ) * .5f;
		const float areaB = CrossProduct( ca, cp ) * .5f;
		const float areaC = CrossProduct( ab, ap ) * .5f;

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

	Vertex2D_Color a, b, c;
	Vec2f ca, ab, bc;
	float recip_total_area;
	float u, v, w;
};

