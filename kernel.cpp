//
// kernel.cpp
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2014-2024  R. Stange <rsta2@o2online.de>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include "kernel.h"
#include "Ball.h"

CKernel::CKernel (void)
:
#ifdef SPI_DISPLAY
	m_SPIMaster (SPI_CLOCK_SPEED, SPI_CPOL, SPI_CPHA, SPI_MASTER_DEVICE),
	m_SPIDisplay (&m_SPIMaster, DISPLAY_PARAMETERS),
	m_2DGraphics (&m_SPIDisplay)
#elif defined (I2C_DISPLAY)
	m_I2CMaster (I2C_MASTER_DEVICE, TRUE),			// TRUE: I2C fast mode
	m_I2CDisplay (&m_I2CMaster, DISPLAY_PARAMETERS),
	m_2DGraphics (&m_I2CDisplay)
#else
	m_2DGraphics (m_Options.GetWidth (), m_Options.GetHeight (), TRUE)
#endif
{
	m_ActLED.Blink (5);
}

CKernel::~CKernel (void)
{
}

boolean CKernel::Initialize (void)
{
#ifdef SPI_DISPLAY
	if (!m_SPIMaster.Initialize ())
	{
		return FALSE;
	}

#ifdef DISPLAY_ROTATION
	m_SPIDisplay.SetRotation (DISPLAY_ROTATION);
#endif

	if (!m_SPIDisplay.Initialize ())
	{
		return FALSE;
	}

#elif defined (I2C_DISPLAY)
	if (!m_I2CMaster.Initialize ())
	{
		return FALSE;
	}

#ifdef DISPLAY_ROTATION
	m_I2CDisplay.SetRotation (DISPLAY_ROTATION);
#endif

	if (!m_I2CDisplay.Initialize ())
	{
		return FALSE;
	}
#endif

	return m_2DGraphics.Initialize ();
}

TShutdownMode CKernel::Run (void)
{
	const int numBalls = 10000; 
	Ball myBall; 
	Ball myList[numBalls];
	for(int i = 0; i < numBalls; i++) {
		myList[i] = Ball(); 
		myList[i].x = m_Random.GetNumber() >> 24; 
		myList[i].y = m_Random.GetNumber() >> 24; 
		// generate non 0 X velocities.  
		bool xVelDone = false; 
		int newXVel = 0; 
		while(xVelDone == false) {
			newXVel = m_Random.GetNumber() >> 29;
			if (newXVel != 0) {
				xVelDone = true; 
			}
		}
		myList[i].xvel = newXVel; 
		// generate non zero Y velocities. 
		bool yVelDone = false;
		int newYVel = 0; 
		while(yVelDone == false) {
			newYVel = m_Random.GetNumber() >> 29; 
			if (newYVel != 0) {
				yVelDone = true; 
			}
		}
		myList[i].yvel = newYVel; 
		myList[i].size = m_Random.GetNumber()>>28; 
	} 
	while (1)
	{
		m_2DGraphics.ClearScreen(CDisplay::Black);
	
		for(int i = 0; i < numBalls-1; i++) {
			myList[i].Update(); 
			m_2DGraphics.DrawCircleOutline(myList[i].x,myList[i].y,myList[i].size,CDisplay::BrightWhite);
		}
		//for(Ball currentBall : myList) {
			//currentBall.Update(); 
		//	myBall.Update(); 
		//	m_2DGraphics.DrawCircle(myBall.x,myBall.y,20,CDisplay::BrightWhite);
			//m_2DGraphics.DrawCircle(currentBall.x,currentBall.y,20,CDisplay::BrightWhite);	
		//}
		//m_2DGraphics.DrawCircle(x,y,200,CDisplay::BrightWhite); 
		//m_2DGraphics.DrawText(700, 300, CDisplay::BrightWhite, "Hello, world!", C2DGraphics::AlignCenter);
		m_2DGraphics.UpdateDisplay();
	}
	return ShutdownHalt;
}

