//
//  OzgBox2DJointTestScene.cpp
//  ozgcc2dxutils
//
//  Created by Tpwid on 13-4-23.
//
//

#include "OzgBox2DJointTestScene.h"

OzgBox2DJointTestScene::OzgBox2DJointTestScene()
{
    
}

OzgBox2DJointTestScene::~OzgBox2DJointTestScene()
{
    
}

bool OzgBox2DJointTestScene::init()
{
    if(OzgBox2DBaseTestScene::init())
    {
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
                
        //圆
        b2BodyDef circleBodyDef;
        circleBodyDef.position.Set(500 / PTM_RATIO, 500 / PTM_RATIO);
        circleBodyDef.type = b2_staticBody;
        circleBodyDef.allowSleep = false;
        
        b2Body *circleBody = this->world->CreateBody(&circleBodyDef);
        
        b2CircleShape circleShape;
        circleShape.m_radius = 20.0f / PTM_RATIO;
        
        circleBody->CreateFixture(&circleShape, 1.0f);
        
        //正方型
        b2BodyDef squareBodyDef;
        squareBodyDef.type = b2_dynamicBody;
        squareBodyDef.position = b2Vec2(400.0f / PTM_RATIO, 600.0f / PTM_RATIO);
        squareBodyDef.allowSleep = false;
        //squareBodyDef.fixedRotation = false; //禁止旋转
        b2Body *squareBody = this->world->CreateBody(&squareBodyDef);
         
        b2PolygonShape square;
        square.SetAsBox(20.0f / PTM_RATIO, 20.0f / PTM_RATIO);
         
        squareBody->CreateFixture(&square, 0.1f);
                
        b2DistanceJointDef distanceJointDef;
        distanceJointDef.length = 100.0f / PTM_RATIO;
        distanceJointDef.frequencyHz = 0.0f;
        distanceJointDef.dampingRatio = 0.0f;
        distanceJointDef.collideConnected = true;
        distanceJointDef.bodyA = circleBody;
        distanceJointDef.bodyB = squareBody;
        this->world->CreateJoint(&distanceJointDef);
        
        return true;
    }
    
    return false;
}

CCScene* OzgBox2DJointTestScene::scene()
{
    CCScene *scene = CCScene::create();
    
    OzgBox2DJointTestScene *layer = new OzgBox2DJointTestScene();
    if(layer->init())
    {
        layer->autorelease();
        scene->addChild(layer);
    }
    return scene;
}

bool OzgBox2DJointTestScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint point = pTouch->getLocation();
    b2Vec2 vec = b2Vec2(point.x / PTM_RATIO, point.y / PTM_RATIO); //转换为box2d的坐标
        
    return true;
}

void OzgBox2DJointTestScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint point = pTouch->getLocation();
    b2Vec2 vec = b2Vec2(point.x / PTM_RATIO, point.y / PTM_RATIO); //转换为box2d的坐标
        
}

void OzgBox2DJointTestScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    
}
