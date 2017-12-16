/******************************************************************************************
*	Chili DirectX Framework Version 16.10.01											  *
*	Vec2.h																				  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#pragma once

#include "ChiliMath.h"
#include "ChiliWin.h"

template <typename T>
class _Vec2
{
public:
	constexpr _Vec2()
		:
		x( 0 ), y( 0 )
	{}
	constexpr _Vec2( T x,T y )
		:
		x( x ),
		y( y )
	{}
	constexpr _Vec2( const POINTS& Pt )
		:
		x( static_cast< T >( Pt.x ) ),
		y( static_cast< T >( Pt.y ) )
	{}

	template <typename T2>
	constexpr explicit operator _Vec2<T2>() const
	{
		return{ (T2)x,(T2)y };
	}

	// Unary operator
	constexpr _Vec2	operator-() const
	{
		return _Vec2( -x,-y );
	}

	// Assignment operators
	_Vec2&	operator=( const _Vec2 &rhs )
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}
	_Vec2&	operator+=( const _Vec2 &rhs )
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	_Vec2&	operator-=( const _Vec2 &rhs )
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	_Vec2&	operator*=( const T &rhs )
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}
	_Vec2&	operator/=( const T &rhs )
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}

	// Binary operators
	constexpr _Vec2	operator+( const _Vec2 &rhs ) const
	{
		return _Vec2( *this ) += rhs;
	}
	constexpr _Vec2	operator-( const _Vec2 &rhs ) const
	{
		return _Vec2( *this ) -= rhs;
	}
	constexpr _Vec2	operator*( const T &rhs ) const
	{
		return _Vec2( *this ) *= rhs;
	}
	constexpr T		operator*( const _Vec2 &rhs ) const
	{
		return x * rhs.x + y * rhs.y;
	}
	constexpr _Vec2	operator/( const T &rhs ) const
	{
		return _Vec2( *this ) /= rhs;
	}

	constexpr bool	operator==( const _Vec2 &rhs ) const
	{
		return x == rhs.x && y == rhs.y;
	}
	constexpr bool	operator!=( const _Vec2 &rhs ) const
	{
		return !(*this == rhs);
	}

	constexpr T		LenSq() const
	{
		return sq( *this );
	}
	constexpr T		Len() const
	{
		return sqrt( LenSq() );
	}

	_Vec2&	Normalize()
	{
		const auto len = Len();
		*this *= ( len != static_cast< T >( 0 ) ? 1.f / len : len );
		return *this;
	}
	constexpr _Vec2	Normalize() const
	{
		return _Vec2( *this ).Normalize();
	}

	constexpr _Vec2	InterpolateTo( const _Vec2& dest,T alpha ) const
	{
		return _Vec2( *this ).InterpolateTo( dest, alpha );
	}
	_Vec2 &InterpolateTo( const _Vec2 &dest, T alpha )
	{
		*this += ( ( dest - *this ) * alpha );
		return *this;
	}

public:
	T x;
	T y;
};

template<class T>
_Vec2<T> Reflect( const _Vec2<T> &Direction, const _Vec2<T> &Normal )
{
	return Direction - ( Normal * ( 2.f * ( Direction * Normal ) ) );
}
template<class T>
float CrossProduct( const _Vec2<T>& lhs, const _Vec2<T>& rhs )
{
	return ( lhs.y * rhs.x ) - ( lhs.x * rhs.y );
}

using Vec2f = _Vec2<float>;
using Vec2d = _Vec2<double>;
using Vec2i = _Vec2<int>;
using Vec2s = _Vec2<short>;
