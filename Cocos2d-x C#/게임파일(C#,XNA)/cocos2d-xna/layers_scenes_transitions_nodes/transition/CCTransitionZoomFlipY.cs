/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011 Zynga Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace cocos2d
{
    public class CCTransitionZoomFlipY : CCTransitionSceneOriented
    {
        public override void onEnter()
        {
            base.onEnter();

            CCActionInterval inA, outA;
            m_pInScene.visible = false;

            float inDeltaZ, inAngleZ;
            float outDeltaZ, outAngleZ;

            if (m_eOrientation == tOrientation.kOrientationUpOver)
            {
                inDeltaZ = 90;
                inAngleZ = 270;
                outDeltaZ = 90;
                outAngleZ = 0;
            }
            else
            {
                inDeltaZ = -90;
                inAngleZ = 90;
                outDeltaZ = -90;
                outAngleZ = 0;
            }

            inA = (CCActionInterval)CCSequence.actions
                (
                    CCDelayTime.actionWithDuration(m_fDuration / 2),
                    CCSpawn.actions
                    (
                        CCOrbitCamera.actionWithDuration(m_fDuration / 2, 1, 0, inAngleZ, inDeltaZ, 90, 0),
                        CCScaleTo.actionWithDuration(m_fDuration / 2, 1),
                        CCShow.action()
                    ),
                    CCCallFunc.actionWithTarget(this, base.finish)
                );

            outA = (CCActionInterval)CCSequence.actions
                (
                    CCSpawn.actions
                    (
                        CCOrbitCamera.actionWithDuration(m_fDuration / 2, 1, 0, outAngleZ, outDeltaZ, 90, 0),
                        CCScaleTo.actionWithDuration(m_fDuration / 2, 0.5f)
                    ),
                    CCHide.action(),
                    CCDelayTime.actionWithDuration(m_fDuration / 2)
                );

            m_pInScene.scale = 0.5f;
            m_pInScene.runAction(inA);
            m_pOutScene.runAction(outA);
        }

        public static CCTransitionZoomFlipY transitionWithDuration(float t, CCScene s, tOrientation o)
        {
            CCTransitionZoomFlipY pScene = new CCTransitionZoomFlipY();
            pScene.initWithDuration(t, s, o);

            return pScene;
        }
    }
}
