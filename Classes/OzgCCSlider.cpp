//
//  OzgCCSlider.cpp
//  ozggame_dusk_fantasy
//
//  Created by 欧 志刚 on 13-9-24.
//
//

#include "OzgCCSlider.h"

OzgCCSlider::~OzgCCSlider()
{
    this->m_bg->removeFromParentAndCleanup(true);
    this->m_slider->removeFromParentAndCleanup(true);
    
    //CCLog("OzgCCSlider release");
}

bool OzgCCSlider::init(cocos2d::CCSprite *bg, cocos2d::CCSprite *slider)
{
    if(CCNode::init())
    {
        this->m_bg = bg;
        this->m_slider = slider;
        
        //显示拖动条背景和拖动条
        this->m_bg->setPosition(CCPointZero);
        this->m_slider->setPosition(CCPointZero);
        this->addChild(this->m_bg);
        this->addChild(this->m_slider);
        
        this->m_sliderRect = this->computingSliderRect(this->m_bg, this->m_slider);
        
        //默认值
        this->setValue(0.5);
        
        this->m_isDrag = false;
        
        return true;
    }
    return false;
}

float OzgCCSlider::getValue()
{
    return this->m_value;
}

void OzgCCSlider::setValue(float value)
{
    //传入0到1的值，改变拖动条的百分比位置
    this->m_value = value;
    //超过界限的处理
    if(this->m_value < 0) this->m_value = 0;
    else if(this->m_value > 1) this->m_value = 1;
    
    float x = this->m_sliderRect.size.width * this->m_value;
    x += this->m_bg->getPosition().x - this->m_bg->getPosition().x - (this->m_bg->getContentSize().width * this->m_bg->getAnchorPoint().x) + (this->m_slider->getContentSize().width * this->m_slider->getAnchorPoint().x);
    
    this->m_slider->setPosition(ccp(x, this->m_slider->getPosition().y));
}

void OzgCCSlider::sliderTouchBegan(cocos2d::CCTouch *pTouch)
{
    CCPoint point = this->convertTouchToNodeSpace(pTouch);
    if(this->m_slider->boundingBox().containsPoint(point))
        this->m_isDrag = true; //打开可拖动状态
    
}

void OzgCCSlider::sliderTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCObject *pSelectorTarget, SEL_CallFuncN selector)
{
    if(this->m_isDrag)
    {
        //在可拖动的状态下，拖动条在可拖动区域内移动，并计算百分比后修改value值
        
        CCPoint beginPoint = pTouch->getLocation();
        CCPoint endPoint = pTouch->getPreviousLocation();
        CCPoint offSet = ccpSub(beginPoint, endPoint);
        
        CCPoint toPoint = ccpAdd(this->m_slider->getPosition(), offSet);
        if(this->m_sliderRect.containsPoint(toPoint))
        {
            this->m_slider->setPosition(ccp(toPoint.x, this->m_slider->getPosition().y));
            this->m_value = this->computingPercentage(this->m_slider, this->m_sliderRect);
        }
        
        //修改value值后执行的回调
        (pSelectorTarget->*selector)(this);
    }
}

void OzgCCSlider::sliderTouchEnded()
{
    //关闭可拖动状态
    this->m_isDrag = false;
    
}

//静态方法
OzgCCSlider* OzgCCSlider::create(cocos2d::CCSprite *bg, cocos2d::CCSprite *slider)
{
    OzgCCSlider* obj = new OzgCCSlider();
    if(obj && obj->init(bg, slider))
    {
        obj->autorelease();
        return obj;
    }
    CC_SAFE_DELETE(obj);
    return NULL;
}

//protected
CCRect OzgCCSlider::computingSliderRect(cocos2d::CCSprite *sliderBg, cocos2d::CCSprite *slider)
{
    //以拖动条背景的大小和拖动条的大小来计算可拖动区域
    float x = sliderBg->getPosition().x - (sliderBg->getContentSize().width * sliderBg->getAnchorPoint().x);
    x = x + (slider->getContentSize().width * slider->getAnchorPoint().x);
    float width = sliderBg->getContentSize().width - slider->getContentSize().width;
    CCRect sliderRect = CCRectMake(x, sliderBg->getPosition().y, width, sliderBg->getContentSize().height);
    return sliderRect;
}

float OzgCCSlider::computingPercentage(cocos2d::CCSprite *slider, cocos2d::CCRect sliderRect)
{
    //拖动条在可拖动区域内的百分比（1为100%）
    float curr = slider->getPosition().x - sliderRect.origin.x;
    float percentage = curr / sliderRect.size.width;
    return percentage;
}
//protected end
