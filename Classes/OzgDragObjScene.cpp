
#include "OzgDragObjScene.h"

OzgDragObjScene::OzgDragObjScene()
{

}

OzgDragObjScene::~OzgDragObjScene()
{

}

bool OzgDragObjScene::init()
{
    if(CCLayer::init())
    {
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
        
        CCSprite *s = CCSprite::create("Icon.png");
        s->setTag(kOzgDragObjSpriteIndex1);
        s->setPosition(ccp(300, 300));
        this->addChild(s);
        
        return true;
    }
    return false;
}

CCScene* OzgDragObjScene::scene()
{
    CCScene *scene = CCScene::create();
    OzgDragObjScene *layer = OzgDragObjScene::create();
    scene->addChild(layer);
    return scene;
}

bool OzgDragObjScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCSprite *s = (CCSprite*)this->getChildByTag(kOzgDragObjSpriteIndex1);
    CCPoint point = pTouch->getLocation();
    
    if(s->boundingBox().containsPoint(point))
        this->spriteIndex1Move = true;
    
    return true;
}

void OzgDragObjScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCSprite *s = (CCSprite*)this->getChildByTag(kOzgDragObjSpriteIndex1);
    
    if(this->spriteIndex1Move)
    {
        CCPoint beginPoint = pTouch->getLocation();
        CCPoint endPoint = pTouch->getPreviousLocation();
        
        CCPoint offSet = ccpSub(beginPoint, endPoint);
        CCPoint toPoint = ccpAdd(s->getPosition(), offSet);
        s->setPosition(toPoint);
    }
    
}

void OzgDragObjScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCSprite *s = (CCSprite*)this->getChildByTag(kOzgDragObjSpriteIndex1);
    CCMoveTo *act = CCMoveTo::create(0.25f, ccp(300, 300));
    s->runAction(CCEaseElasticOut::create(act, 0.5f));
    
    this->spriteIndex1Move = false;
    
}
