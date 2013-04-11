//
//  OzgDragObjScene.h
//  ozgcc2dxutils
//
//  Created by 欧 志刚 on 13-4-8.
//
//

#ifndef __ozgcc2dxutils__OzgDragObjScene__
#define __ozgcc2dxutils__OzgDragObjScene__

#include "cocos2d.h"

USING_NS_CC;

using namespace cocos2d;

enum SpriteIndex
{
    SpriteIndex1 = 1
};

class OzgDragObjScene : public CCLayer
{
    
public:
    OzgDragObjScene();
    ~OzgDragObjScene();
    
    bool init();
    
    static CCScene* scene();
    
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
};

#endif /* defined(__ozgcc2dxutils__OzgDragObjScene__) */
