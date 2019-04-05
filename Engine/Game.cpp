/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
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
#include "MainWindow.h"
#include "Game.h"
#include "Mouse.h"
#include "CordinateTrasformerh.h"
#include "ChiliUtil.h"
#include <functional>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ct(gfx),
	cam(ct)
	//,
	//camCtrl(wnd.mouse,cam)

{	
}

void Game::Go()
{
	gfx.BeginFrame();	
	ProcesInput();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::ProcesInput()
{
	switch (wnd.ShapeState)
	{
	case MainWindow::MWShapeState::TwoPointCircle:
	{
		while (!wnd.mouse.IsEmpty())
		{
			const auto e = wnd.mouse.Read();

			if (e.GetType() == Mouse::Event::Type::LPress)
			{
				if (input == 0)
				{
					
					first_point_engagement = true;
					P = cam.TrasformPoint(wnd.mouse.GetPos());
					PointData.emplace_back(P);

				}
				if (input == 1)
				{
					
					Q = cam.TrasformPoint(wnd.mouse.GetPos());
					PointData.emplace_back(Q);
					Shapes.push_back(std::make_unique<JC_Circle>(PointData));
					//Shapes.push_back(std::make_unique<JC_Line>(P, Q));
				}

				input++;

				if (input >= 2)
				{
					input = 0;
					first_point_engagement = false;
					PointData.clear();

				}
			}
			if (e.GetType() == Mouse::Event::Type::RPress)
			{
				input = 0;
				first_point_engagement = false;
				PointData.clear();

			}
		}
		if (first_point_engagement)
		{
			
			Q = cam.TrasformPoint(wnd.mouse.GetPos());
		
			cam.DrawCircle(P , GetDistanceTo(P,Q), 2, Colors::Red);
			cam.DrawPoliLine(PointData, Colors::Red);
		}
		break;
	}
	case MainWindow::MWShapeState::ThreePointCircle:
	{
		while (!wnd.mouse.IsEmpty())
		{
			const auto e = wnd.mouse.Read();

			if (e.GetType() == Mouse::Event::Type::LPress)
			{
				if (input == 0)
				{
					first_point_engagement = true;
					P = cam.TrasformPoint(wnd.mouse.GetPos());
					PointData.emplace_back(P);
				}

				if (input == 1)
				{
					second_point_engagement = true;
					Q = cam.TrasformPoint(wnd.mouse.GetPos());
					PointData.emplace_back(Q);

				}

				if (input == 2)
				{
					R = cam.TrasformPoint(wnd.mouse.GetPos());
					PointData.emplace_back(R);
					if (P != Q && Q != R && !(LineSlopeBetween2Points(P, R) == LineSlopeBetween2Points(R, Q)))
						Shapes.push_back(std::make_unique<JC_Circle>(PointData));
				}

				input++;

				if (input >= 3)
				{
					input = 0;
					second_point_engagement = false;
					PointData.clear();
				}
			}
			if (e.GetType() == Mouse::Event::Type::RPress)
			{
				input = 0;
				first_point_engagement = false;
				second_point_engagement = false;
				PointData.clear();

			}
		}
		//Draw circle from two points when left mouse button is pressed for the first time
		if (first_point_engagement)
		{
			Q = cam.TrasformPoint(wnd.mouse.GetPos());
			auto Temp = GetMidPoint(P, Q);
			cam.DrawCircle(Temp, GetDistanceTo(Temp, Q), 2, Colors::Red);
		}
		if (second_point_engagement)
		{
			first_point_engagement = false;
			R = cam.TrasformPoint(wnd.mouse.GetPos());
			if (P == Q)
			{
				input = 0;
				second_point_engagement = false;
			}
			else if (Q != R && !(LineSlopeBetween2Points(P, R) == LineSlopeBetween2Points(R, Q)))
			{
				auto Temp = CalculateCentre(P, Q, R);
				cam.DrawCircle(Temp, GetDistanceTo(Temp, R), 2, Colors::Red);
				cam.DrawCircle(P, 10, 1, Colors::Red);
				cam.DrawCircle(Q, 10, 1, Colors::Red);
				cam.DrawCircle(R, 10, 1, Colors::Red);
				//cam.DrawLine(CalculateCentre(P, Q, R), R, Colors::Red);
			}
				
		}
		break;
	}

	case MainWindow::MWShapeState::PoliLine:
	{
		while (!wnd.mouse.IsEmpty())
		{
			const auto e = wnd.mouse.Read();

			if (e.GetType() == Mouse::Event::Type::LPress)
			{
				if(input==0)
					first_point_engagement = true;
				if (input>0)
				{
					first_point_engagement = false;
					second_point_engagement = true;
				}

				P = cam.TrasformPoint(wnd.mouse.GetPos());
				PointData.push_back(P);
				input++;

				
			}
			if (second_point_engagement)
			{
				if (e.GetType() == Mouse::Event::Type::RPress)
				{

					if (PointData.size() > 1)
					{
						Shapes.push_back(std::make_unique<JC_Poliline>(PointData));
						input = 0;
						first_point_engagement = false;
						second_point_engagement = false;
						PointData.clear();

					}

				}

			}
		
		}
		if (first_point_engagement)
		{
			Q = cam.TrasformPoint(wnd.mouse.GetPos());
			cam.DrawLine(P, Q, Colors::Red);
		}
		if (second_point_engagement)
		{
			cam.DrawPoliLine(PointData, Colors::Red);
			Q = cam.TrasformPoint(wnd.mouse.GetPos());
			cam.DrawLine(P, Q, Colors::Red);

		}
		break;

	}


	case MainWindow::MWShapeState::Null:
	{
		while (!wnd.mouse.IsEmpty())
		{
			const auto e = wnd.mouse.Read();

			if (e.GetType() == Mouse::Event::Type::LPress)
			{
				for (auto& i : Shapes)
				{
					if (wnd.kbd.KeyIsPressed(VK_SHIFT))
					{
						if (i.get()->IsInRange(static_cast<JC_Point2d>(cam.TrasformPoint(wnd.mouse.GetPos()))))
							i.get()->SetSelectionFlag(false);
					}
					else
					{
						if (i.get()->IsInRange(static_cast<JC_Point2d>(cam.TrasformPoint(wnd.mouse.GetPos()))))
							i.get()->SetSelectionFlag(true);
					}
				}
			}
		}
		break;
	}
	break;
	}

	if (wnd.kbd.KeyIsPressed(VK_ESCAPE))
	{

		wnd.ShapeState = MainWindow::MWShapeState::Null;

		input = 0;
		first_point_engagement = false;
		second_point_engagement = false;

		for (auto &c : Shapes)
		{
			c.get()->SetSelectionFlag(false);
		}
	}

	if (wnd.kbd.KeyIsPressed(VK_DELETE))
	{
		remove_erase_if(Shapes, std::mem_fn(&JC_Shape::ReadyForRemoval));
	}

	if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		for (auto& i : Shapes)
		{
			if (i.get()->IsSelected())
			{
				wnd.ShowMessageBox(L"Description", L"Only single shape wil be show \n\n " + i.get()->MakeDescription());
				break;
			}
		}
		
	}
}

void Game::UpdateModel()
{
	for (auto &c : Shapes)
	{
		c.get()->UpdateColor();
		c.get()->DrawOnPoint(cam);
	}
}

void Game::ComposeFrame()
{
	for (auto &c : Shapes)
	{
		c.get()->Draw(cam);
	}

}

