//
//  OzgDragObjScene.cpp
//  ozgcc2dxutils
//
//  Created by 欧 志刚 on 13-4-8.
//
//

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
        s->setTag(SpriteIndex1);
        s->setPosition(ccp(100, 100));
        this->addChild(s);
        
        return true;
    }
    return false;
}

CCScene* OzgDragObjScene::scene()
{
    CCScene *scene = CCScene::create();
    OzgDragObjScene *layer = new OzgDragObjScene();
    if(layer->init())
    {
        layer->autorelease();
        scene->addChild(layer);
    }
    
    return scene;
}

bool OzgDragObjScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

    return true;
}

void OzgDragObjScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCSprite *s = (CCSprite*)this->getChildByTag(SpriteIndex1);
    
    CCPoint beginPoint = pTouch->getLocation();
    
    if(s->boundingBox().containsPoint(beginPoint))
    {
        CCPoint endPoint = pTouch->getPreviousLocation();
        
        CCPoint offSet = ccpSub(beginPoint, endPoint);
        CCPoint toPoint = ccpAdd(s->getPosition(), offSet);
        s->setPosition(toPoint);
    }
    
}

void OzgDragObjScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCSprite *s = (CCSprite*)this->getChildByTag(SpriteIndex1);
    CCMoveTo *act = CCMoveTo::create(0.25f, ccp(100, 100));
    s->runAction(CCEaseElasticOut::create(act, 0.5f));
    
}
