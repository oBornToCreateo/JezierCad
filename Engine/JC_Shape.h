#pragma once
#include "JC_Vector2.h"
#include "Camera.h"
#include "Graphics.h"
class JC_Shape

{
public:


	virtual void Draw(Camera cam) = 0;
	virtual bool IsInRange(const JC_Point2d& M) = 0;
	virtual std::wstring MakeDescription() = 0;
	//virtual void DrawOnPoint() = 0;

	void UpdateColor()
	{
		if (SelectionFlag)
			Base_Color = Colors::Yellow;
		else
			Base_Color = Colors::White;
	}

	void SetSelectionFlag(bool flag)
	{
		SelectionFlag = flag;
	}

	bool ReadyForRemoval() const
	{
		return SelectionFlag;
	}

	bool IsSelected() const
	{
		return SelectionFlag;
	}
	
protected:

	JC_Shape( Color& color_in, std::vector<JC_Point2d> PointData)
		:
		Base_Color(color_in),
		PointData(PointData)
	{}


	std::vector<JC_Point2d> PointData;
	Color Base_Color;
	static constexpr double halfwidth = 20.0;


private:
	bool SelectionFlag = false;
};
