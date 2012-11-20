/* The MIT License (MIT)
 * Copyright (c) 2012 Vittorio Romeo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef PATTERNMANAGER_H_
#define PATTERNMANAGER_H_

#include <iostream>
#include <sstream>
#include <string>
#include <SSVStart.h>
#include <SSVEntitySystem.h>
#include "Components/CPlayer.h"
#include "Components/CWall.h"
#include "Utils/Utils.h"

namespace hg
{
	constexpr float baseSpeed{5};
	constexpr float baseThickness{40};

	class HexagonGame;

	class PatternManager
	{
		friend class HexagonGame;

		private:
			HexagonGame* hgPtr;
			Timeline& timeline;
			Vector2f& centerPos;

			float thickness	{baseThickness};
			float speed 	{baseSpeed};

			float currentSpeedMultiplier;		
			float currentDelayMultiplier;

			float adjDelay{1.0f};
			float adjSpeed{1.0f};
			float adjThickness{1.0f};

			void initalizeTimeline();
			void finalizeTimeline();
			
		public:
			PatternManager(HexagonGame*);			

			void setAdj(float mAdjDelay, float mAdjSpeed, float mAdjThickness);
			void resetAdj();

			int getRandomSide();
			int getRandomDirection();
			float getPerfectThickness	(float mBaseThickness);
			float getPerfectDelay		(float mThickness, float mSpeed);

			void wall					(int mSide, float mThickness);						// simple wall
			void rWall					(int mSide, float mThickness);						// wall + its opposite
			void wallExtra				(int mSide, float mThickness, int mExtra = 0);		// wall + neighbors from 1 side (1=neighbor on the right)(-1=neighbor on the left)
			void rWallExtra				(int mSide, float mThickness, int mExtra = 0);		// wallExtra + its opposite
			void barrage				(int mSide, float mThickness, int mNeighbors = 0);	// all walls except one side (neighbors both from left and right)
			void barrageOnlyNeighbors	(int mSide, float mThickness, int mNeighbors = 1);	// all walls except neighbors
			void altBarrage				(int mSide, float mThickness, int mStep);			// pick a wall every X walls

			void alternateWallBarrage	(int mTimes = 5, int mDiv = 2);						// zig-zag
			void barrageSpiral			(int mTimes, float mDelayMultiplier = 1); 			// spiral of barrages with only 1 free side
			void mirrorSpiral			(int mTimes, int mExtra = 0);						// spiral with touching sides, only 1 closed side
			void extraWallVortex		(int mTimes = 1, int mSteps = 2);					// left-left right-right
			void inverseBarrage			(int mTimes = 1);									// barrage 0° and barrage 180°
			void mirrorWallStrip		(int mTimes = 2, int mExtra = 0);					// several rWalls one after another on the same side
			void tunnelBarrage			(int mTimes = 1);									// tunnel of barrages where you have to zig zag
	};
}
#endif /* PATTERNMANAGER_H_ */