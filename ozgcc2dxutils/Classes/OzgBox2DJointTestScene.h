//
//  OzgBox2DJointTestScene.h
//  ozgcc2dxutils
//
//  Created by Tpwid on 13-4-23.
//
//

#ifndef __ozgcc2dxutils__OzgBox2DJointTestScene__
#define __ozgcc2dxutils__OzgBox2DJointTestScene__

#include "OzgBox2DBaseTestScene.h"

USING_NS_CC;

class OzgBox2DJointTestScene : public OzgBox2DBaseTestScene
{
    
private:
    b2Body *groundBody;
    
public:
    
    OzgBox2DJointTestScene();
    virtual ~OzgBox2DJointTestScene();
    bool init();
    
    static CCScene* scene();
    
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
};

#endif /* defined(__ozgcc2dxutils__OzgBox2DJointTestScene__) */
