#pragma once
#include "JC_Shape.h"

class JC_Circle : public JC_Shape
{
public:

	JC_Circle(std::vector<JC_Point2d> Point_Data, Color color = Colors::White);

	
	void Draw(Camera cam_in) override;
	bool IsInRange(const JC_Point2d& mouse_in) override;
		


	std::wstring MakeDescription() override
	{
		return	false;
	}

private:
	JC_Point2d O;
	double radius;


};