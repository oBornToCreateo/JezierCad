#include "JC_Circle.h"

JC_Circle::JC_Circle(std::vector<JC_Point2d> PointData, Color color)
	:
	JC_Shape(color,PointData),
	O(PointData.size() == 2 ? 
		//Get Centre of 2point Circle
		PointData[0] : 
		//Get Centre of 3Point Circle
		CalculateCentre(PointData[0], PointData[1], PointData[2])),

	radius(PointData.size() == 2 ?
		//Get Radius of 2point Circle
		GetDistanceTo(O ,PointData[1]):
		//Get Radius of 2point Circle
		GetDistanceTo(CalculateCentre(PointData[0], PointData[1], PointData[2]), PointData[2]))
{}


void JC_Circle::Draw(Camera cam_in)
{
	cam_in.DrawCircle(O, radius, 2, Base_Color);
}


bool JC_Circle::IsInRange(const JC_Point2d& mouse_in)
{
	double distance = GetDistanceTo(O, mouse_in);
	return (distance <= (radius + halfwidth) &&
		distance >= (radius - halfwidth));
}
