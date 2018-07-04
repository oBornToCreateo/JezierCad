#pragma once

#include <vector>

#include "Graphics.h"
#include "Colors.h"
#include "JC_Vector2.h"


class CoordinateTrasformer
{
public:

	CoordinateTrasformer (Graphics& gfx)
		:
		gfx(gfx)
	{}

	void DrawCircle(JC_Point2d pos, double radius, Color c)
	{
		JC_Vector2d offset = { double(Graphics::ScreenWidth / 2),double(Graphics::ScreenHeight / 2) };

		pos.y *= -1.0;
		pos += offset;

		gfx.DrawCircle(pos, radius, c);
	}


	void DrawClosedPolyline(std::vector<JC_Point2d> poly, Color c)
	{
		JC_Vector2d offset = { double(Graphics::ScreenWidth / 2),double(Graphics::ScreenHeight / 2) };
		for (auto& v : poly)
		{
			v.y *= -1.0;
			v += offset;
		}
		gfx.DrawClosedPolyline(poly, c);
	}
	


private:
	Graphics& gfx;



};