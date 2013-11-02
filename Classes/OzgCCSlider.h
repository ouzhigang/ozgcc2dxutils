//
//  OzgCCSlider.h
//  ozggame_dusk_fantasy
//
//  Created by 欧 志刚 on 13-9-24.
//
//

#ifndef __ozggame_dusk_fantasy__OzgCCSlider__
#define __ozggame_dusk_fantasy__OzgCCSlider__

#include "cocos2d.h"

USING_NS_CC;

class OzgCCSlider : public CCNode
{

private:
    CCSprite* m_bg; //拖动条的背景
    CCSprite* m_slider; //拖动条
    float m_value; //当前百分比0到1之间
    CCRect m_sliderRect; //可拖动区域
    bool m_isDrag; //是否可拖动的状态

protected:
    virtual CCRect computingSliderRect(cocos2d::CCSprite *sliderBg, cocos2d::CCSprite *slider); //计算可拖动的区域
    virtual float computingPercentage(cocos2d::CCSprite *slider, cocos2d::CCRect sliderRect); //计算拖动条在区域内的百分比
    
public:
    virtual ~OzgCCSlider();
    virtual bool init(CCSprite *bg, CCSprite *slider);
    static OzgCCSlider* create(CCSprite *bg, CCSprite *slider);
    
    virtual float getValue();
    virtual void setValue(float value);
    virtual void sliderTouchBegan(CCTouch *pTouch); //在场景的ccTouchBegan事件中调用，以打开拖动状态
    virtual void sliderTouchMoved(CCTouch *pTouch, cocos2d::CCObject *pSelectorTarget, SEL_CallFuncN selector); //在场景的ccTouchMoved事件中调用
    virtual void sliderTouchEnded(); //在场景的ccTouchEnded事件中调用，以关闭拖动状态
    
};

#endif /* defined(__ozggame_dusk_fantasy__OzgCCSlider__) */
