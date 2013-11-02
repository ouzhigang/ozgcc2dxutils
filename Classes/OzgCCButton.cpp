//
//  OzgCCButton.cpp
//  ozggame_dusk_fantasy
//
//  Created by 欧 志刚 on 13-9-24.
//
//

#include "OzgCCButton.h"

OzgCCButton::~OzgCCButton()
{
    this->m_normalSprite->removeFromParentAndCleanup(true);
    this->m_disabledSprite->removeFromParentAndCleanup(true);
    
}

bool OzgCCButton::init(CCSprite* normalSprite, CCSprite* disabledSprite, cocos2d::CCObject *target, SEL_CallFuncN selector)
{
    if(CCNode::init())
    {
        this->m_enabled = true;
        this->m_normalSprite = normalSprite;
        this->m_disabledSprite = disabledSprite;
        this->m_target = target;
        this->m_selector = selector;
        
        this->m_isMoveout = false;
        
        this->addChild(this->m_normalSprite);
        
        this->m_disabledSprite->setVisible(false);
        this->addChild(this->m_disabledSprite);
        
        return true;
    }
    return false;
}

OzgCCButton* OzgCCButton::create(CCSprite* normalSprite, CCSprite* disabledSprite, cocos2d::CCObject *target, SEL_CallFuncN selector)
{
    OzgCCButton* obj = new OzgCCButton();
    if(obj && obj->init(normalSprite, disabledSprite, target, selector))
    {
        obj->autorelease();
        return obj;
    }
    CC_SAFE_DELETE(obj);
    return NULL;
}

void OzgCCButton::setEnabled(bool enabled)
{
    this->m_enabled = enabled;
    
    //改变显示精灵
    this->m_normalSprite->setVisible(this->m_enabled);
    this->addChild(this->m_normalSprite);
    
    this->m_disabledSprite->setVisible(!this->m_enabled);
    this->addChild(this->m_disabledSprite);
    
}

bool OzgCCButton::isEnabled()
{
    return this->m_enabled;
}

void OzgCCButton::buttonTouchBegan(cocos2d::CCTouch *pTouch)
{
    if(!this->m_enabled)
        return;
    
    CCPoint point = pTouch->getLocation();
    point = this->convertToNodeSpace(point);
    
    this->m_isMoveout = false;
    
    if(this->m_normalSprite->boundingBox().containsPoint(point))
        this->m_normalSprite->runAction(CCScaleTo::create(0.1, 1.2));
}

void OzgCCButton::buttonTouchMoved(cocos2d::CCTouch *pTouch)
{
    if(!this->m_enabled)
        return;
    
    CCPoint point = pTouch->getLocation();
    point = this->convertToNodeSpace(point);
    
    if(!this->m_normalSprite->boundingBox().containsPoint(point))
    {
        this->m_normalSprite->stopAllActions();
        this->m_normalSprite->runAction(CCScaleTo::create(0.1, 1.0));
        this->m_isMoveout = true;
    }
    
}

void OzgCCButton::buttonTouchEnded(cocos2d::CCTouch *pTouch)
{
    if(!this->m_enabled || this->m_isMoveout)
        return;
    
    CCPoint point = pTouch->getLocation();
    point = this->convertToNodeSpace(point);
    
    this->m_normalSprite->stopAllActions();
    if(this->m_normalSprite->boundingBox().containsPoint(point))
        this->m_normalSprite->runAction(CCSequence::createWithTwoActions(CCScaleTo::create(0.1, 1.0), CCCallFunc::create(this, callfunc_selector(OzgCCButton::buttonTouched))));
    else
        this->m_normalSprite->runAction(CCScaleTo::create(0.1, 1.0));
    
}

void OzgCCButton::buttonTouched()
{
    (this->m_target->*this->m_selector)(this);
    
}
