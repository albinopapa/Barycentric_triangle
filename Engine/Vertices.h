#pragma once

#include "Colors.h"
#include "Vec2.h"

struct Vertex2D_Color
{
	Vertex2D_Color operator+( const Vertex2D_Color& rhs )const
	{
		Vertex2D_Color result;
		result.position = position + rhs.position;
		result.color = color + rhs.color;

		return result;
	}
	Vertex2D_Color operator*( const float S )const
	{
		Vertex2D_Color result;
		result.position = position * S;

		const uint8_t ui_s = static_cast< uint8_t >( S * 255.f );
		result.color = color * ui_s;

		return result;
	}
	Vec2f position;
	Color color;
};

