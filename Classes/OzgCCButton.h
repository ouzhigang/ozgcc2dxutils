
#ifndef __ozgcc2dxutils__OzgCCButton__
#define __ozgcc2dxutils__OzgCCButton__

#include "cocos2d.h"

USING_NS_CC;

class OzgCCButton : public CCNode
{
    
private:
    bool m_enabled; //开启
    CCSprite* m_normalSprite; //开启时显示的精灵
    CCSprite* m_disabledSprite; //禁用时显示的精灵
    CCObject* m_target; //回调的对象
    SEL_CallFuncN m_selector; //回调的方法
    bool m_isMoveout; //是否在buttonTouchMoved中把事件触发点移出了本按钮，如果移出了则不会触发后面的事件，直到下一次点击为止
    
    void buttonTouched(); //buttonTouchEnded里面的动作执行完毕后执行的方法
    
public:
    virtual ~OzgCCButton();
    virtual bool init(CCSprite* normalSprite, CCSprite* disabledSprite, cocos2d::CCObject *target, SEL_CallFuncN selector);
    static OzgCCButton* create(CCSprite* normalSprite, CCSprite* disabledSprite, cocos2d::CCObject *target, SEL_CallFuncN selector);
    
    void setEnabled(bool enabled);
    bool isEnabled();
    
    virtual void buttonTouchBegan(CCTouch *pTouch); //在场景的ccTouchBegan事件中调用，以打开拖动状态
    virtual void buttonTouchMoved(CCTouch *pTouch); //在场景的ccTouchMoved事件中调用
    virtual void buttonTouchEnded(CCTouch *pTouch); //在场景的ccTouchEnded事件中调用
    
};

#endif /* defined(__ozgcc2dxutils__OzgCCButton__) */
