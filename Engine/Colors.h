/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Colors.h																			  *
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

#include <algorithm>

class Color
{
public:
	unsigned int dword;
public:
	constexpr Color() : dword() {}
	constexpr Color( unsigned int dw )
		:
		dword( dw )
	{}
	constexpr Color( unsigned char x,unsigned char r,unsigned char g,unsigned char b )
		:
		dword( (x << 24u) | (r << 16u) | (g << 8u) | b )
	{}
	constexpr Color( unsigned char r,unsigned char g,unsigned char b )
		:
		dword( (r << 16u) | (g << 8u) | b )
	{}
	constexpr Color( Color col,unsigned char x )
		:
		Color( (x << 24u) | col.dword )
	{}

	Color operator+( const Color &C )const
	{
		return Color( *this ) += C;
	}
	Color &operator+=( const Color &C )
	{
		const auto srcR = static_cast< short >( GetR() );
		const auto srcG = static_cast< short >( GetG() );
		const auto srcB = static_cast< short >( GetB() );

		const auto dstR = static_cast< short >( C.GetR() );
		const auto dstG = static_cast< short >( C.GetG() );
		const auto dstB = static_cast< short >( C.GetB() );

		SetR( std::min<unsigned char>( srcR + dstR, 255ui8 ) );
		SetG( std::min<unsigned char>( srcG + dstG, 255ui8 ) );
		SetB( std::min<unsigned char>( srcB + dstB, 255ui8 ) );

		return *this;
	}
	Color operator-( const Color& C )const
	{
		return Color( *this ) -= C;
	}
	Color& operator-=( const Color& C )
	{
		const auto srcR = static_cast< short >( GetR() );
		const auto srcG = static_cast< short >( GetG() );
		const auto srcB = static_cast< short >( GetB() );

		const auto dstR = static_cast< short >( C.GetR() );
		const auto dstG = static_cast< short >( C.GetG() );
		const auto dstB = static_cast< short >( C.GetB() );

		SetR( std::max<unsigned char>( srcR - dstR, 0ui8 ) );
		SetG( std::max<unsigned char>( srcG - dstG, 0ui8 ) );
		SetB( std::max<unsigned char>( srcB - dstB, 0ui8 ) );

		return *this;
	}
	Color operator*( unsigned char S )const
	{
		return Color( *this ) *= S;
	}
	Color &operator*=( unsigned char S )
	{
		const auto s = static_cast< short >( S );
		const auto srcR = static_cast< short >( GetR() ) * s;
		const auto srcG = static_cast< short >( GetG() ) * s;
		const auto srcB = static_cast< short >( GetB() ) * s;

		SetR( static_cast<unsigned char>( srcR >> 8ui8 ) );
		SetG( static_cast<unsigned char>( srcG >> 8ui8 ) );
		SetB( static_cast<unsigned char>( srcB >> 8ui8 ) );

		return *this;
	}

	constexpr unsigned char GetX() const
	{
		return dword >> 24u;
	}
	constexpr unsigned char GetA() const
	{
		return GetX();
	}
	constexpr unsigned char GetR() const
	{
		return (dword >> 16u) & 0xFFu;
	}
	constexpr unsigned char GetG() const
	{
		return (dword >> 8u) & 0xFFu;
	}
	constexpr unsigned char GetB() const
	{
		return dword & 0xFFu;
	}
	void SetX( unsigned char x )
	{
		dword = (dword & 0xFFFFFFu) | (x << 24u);
	}
	void SetA( unsigned char a )
	{
		SetX( a );
	}
	void SetR( unsigned char r )
	{
		dword = (dword & 0xFF00FFFFu) | (r << 16u);
	}
	void SetG( unsigned char g )
	{
		dword = (dword & 0xFFFF00FFu) | (g << 8u);
	}
	void SetB( unsigned char b )
	{
		dword = (dword & 0xFFFFFF00u) | b;
	}
};

namespace Colors
{
	static constexpr Color MakeRGB( unsigned char r,unsigned char g,unsigned char b )
	{
		return (r << 16) | (g << 8) | b;
	}
	static constexpr Color White = MakeRGB( 255u,255u,255u );
	static constexpr Color Black = MakeRGB( 0u,0u,0u );
	static constexpr Color Gray = MakeRGB( 0x80u,0x80u,0x80u );
	static constexpr Color LightGray = MakeRGB( 0xD3u,0xD3u,0xD3u );
	static constexpr Color Red = MakeRGB( 255u,0u,0u );
	static constexpr Color Green = MakeRGB( 0u,255u,0u );
	static constexpr Color Blue = MakeRGB( 0u,0u,255u );
	static constexpr Color Yellow = MakeRGB( 255u,255u,0u );
	static constexpr Color Cyan = MakeRGB( 0u,255u,255u );
	static constexpr Color Magenta = MakeRGB( 255u,0u,255u );
}