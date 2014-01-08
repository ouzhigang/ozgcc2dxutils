
#ifndef __ozgcc2dxutils__OzgDragObjScene__
#define __ozgcc2dxutils__OzgDragObjScene__

#include "cocos2d.h"

USING_NS_CC;

enum kOzgDragObjSpriteIndex
{
    kOzgDragObjSpriteIndex1 = 1
};

class OzgDragObjScene : public CCLayer
{
    
private:
    bool spriteIndex1Move = false;
    
public:
    OzgDragObjScene();
    ~OzgDragObjScene();
    
    CREATE_FUNC(OzgDragObjScene);
    
    bool init();
    
    static CCScene* scene();
    
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
};

#endif /* defined(__ozgcc2dxutils__OzgDragObjScene__) */
