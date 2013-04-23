//
//  OzgBox2DEdgeTestScene.h
//  ozgccs
//
//  Created by Tpwid on 13-4-12.
//
//

#ifndef __ozgccs__OzgBox2DEdgeTestScene__
#define __ozgccs__OzgBox2DEdgeTestScene__

#include "OzgBox2DBaseTestScene.h"

USING_NS_CC;

class OzgBox2DEdgeTestScene : public OzgBox2DBaseTestScene
{

private:    
    b2Body *groundBody;
    b2Body *circleBody;
    b2Body *polygonBody;
    
    b2Fixture *circleFixture;
    b2MouseJoint *circleMouseJoint;
    
    b2Fixture *polygonFixture;
    b2MouseJoint *polygonMouseJoint;
    
public:
    
    OzgBox2DEdgeTestScene();
    virtual ~OzgBox2DEdgeTestScene();
    bool init();
    
    static CCScene* scene();
    
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
};

#endif /* defined(__ozgccs__OzgBox2DEdgeTestScene__) */
