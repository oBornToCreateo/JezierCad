#pragma once

#include "JC_Shape.h"




// Atempt to write multi point bezier curve



class JC_MP_Bezier : public JC_Shape
{
public:
	JC_MP_Bezier(std::vector<JC_Point2d> point_data, Color color_in = Colors::White)
		:
		JC_Shape(color_in, point_data)
	{}
	void JC_MP_Bezier::DrawOnPoint(Camera cam) override
	{
		if(IsSelected())
		{
			for (int i = 0; i < PointData.size(); ++i)
			{
				cam.DrawCircle(PointData[i], halfwidth / 2, 1, Colors::Red);
			}
		}
	}
	void Draw(Camera cam) override
	{
		cam.DrawMPBezier(PointData, Base_Color);
	}
	bool IsInRange(const JC_Point2d& M) override
	{
		return false;
	}

	std::wstring MakeDescription() override
	{


		return	std::wstring(L"Not yet operatable");

	}

};