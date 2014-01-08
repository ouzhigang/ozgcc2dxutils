
#ifndef __ozgcc2dxutils__OzgJoystickLayer__
#define __ozgcc2dxutils__OzgJoystickLayer__

/*
 demo
 
 bool HelloWorld::init()
 {
 if ( !CCLayer::init() )
 {
 return false;
 }
 
 CCSprite *spJoystick = CCSprite::create("CloseSelected.png");
 CCSprite *joystickBg = CCSprite::create("CloseSelected.png");
 OzgJoystickLayer *joystick = OzgJoystickLayer::layer(ccp(210.0f, 130.0f), 50.0f, spJoystick, joystickBg, false);
 joystick->setTag(1);
 this->addChild(joystick);
 
 this->scheduleUpdate();
 
 return true;
 }
 
 void HelloWorld::update(float dt)
 {
 OzgJoystickLayer *joystick = (OzgJoystickLayer*)this->getChildByTag(1);
 if(joystick->m_trigger)
 CCLog("%f %f %f %f %f", joystick->m_centerPoint.x, joystick->m_centerPoint.y, joystick->m_currentPoint.x, joystick->m_currentPoint.y, dt);
 
 }
 
 */

#include "cocos2d.h"

USING_NS_CC;

class OzgJoystickLayer : public CCLayer
{
    
public:
    
    CCPoint m_centerPoint; //摇杆中心
    
    CCPoint m_currentPoint; //摇杆当前位置
    
    bool m_trigger; //是否正在触发摇杆
    
    bool m_active; //是否激活摇杆
    
    float m_radius; //摇杆半径
    
    CCSprite* m_jsSprite;
    
    bool m_isFollowRole; //是否跟随用户点击
    
    //初始化 aPoint是摇杆中心 aRadius是摇杆半径 aJsSprite是摇杆控制点 aJsBg是摇杆背景
    static OzgJoystickLayer* layer(CCPoint aPoint, float aRadius, CCSprite* aJsSprite, CCSprite* aJsBg, bool _isFollowRole);
    
    OzgJoystickLayer* initWithCenter(CCPoint aPoint, float aRadius, CCSprite* aJsSprite, CCSprite* aJsBg, bool _isFollowRole);
    
    //启动摇杆
    void active();
    
    //解除摇杆
    void inactive();    
    
    CCPoint getDirection();
    float getVelocity();
    void updatePos(float dt);
    
    CREATE_FUNC(OzgJoystickLayer);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
};

#endif /* defined(__ozgcc2dxutils__OzgJoystickLayer__) */
