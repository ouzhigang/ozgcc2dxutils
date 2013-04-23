//
//  OzgEdgeTestScene.cpp
//  ozgccs
//
//  Created by Tpwid on 13-4-12.
//
//

#include "OzgBox2DEdgeTestScene.h"

OzgBox2DEdgeTestScene::OzgBox2DEdgeTestScene()
{
    
}

OzgBox2DEdgeTestScene::~OzgBox2DEdgeTestScene()
{
    
}

bool OzgBox2DEdgeTestScene::init()
{
    if(OzgBox2DBaseTestScene::init())
    {
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
        
        //边界body
        b2BodyDef groundBodyDef;
        this->groundBody = this->world->CreateBody(&groundBodyDef);
        
        vector<b2Vec2>edgeVec2Data;
        edgeVec2Data.push_back(b2Vec2(200.0f / PTM_RATIO, 500.0f / PTM_RATIO)); //边界1
        edgeVec2Data.push_back(b2Vec2(500.0f / PTM_RATIO, 490.0f / PTM_RATIO));
        edgeVec2Data.push_back(b2Vec2(500.0f / PTM_RATIO, 490.0f / PTM_RATIO)); //边界2
        edgeVec2Data.push_back(b2Vec2(700.0f / PTM_RATIO, 450.0f / PTM_RATIO));
        edgeVec2Data.push_back(b2Vec2(700.0f / PTM_RATIO, 450.0f / PTM_RATIO)); //边界3
        edgeVec2Data.push_back(b2Vec2(900.0f / PTM_RATIO, 500.0f / PTM_RATIO));
        
        for (unsigned int i = 0; i < (int)edgeVec2Data.capacity(); i += 2)
        {
            b2Vec2 dataItem1 = edgeVec2Data[i];
            b2Vec2 dataItem2 = edgeVec2Data[i + 1];
            
            b2EdgeShape edgeShape;
            edgeShape.Set(dataItem1, dataItem2);
            
            this->groundBody->CreateFixture(&edgeShape, 0.0f);
        }
        
        //圆
        b2BodyDef circleBodyDef;
        circleBodyDef.type = b2_dynamicBody;
        circleBodyDef.position = b2Vec2(250.0f / PTM_RATIO, 600.0f / PTM_RATIO); //位置
        circleBodyDef.allowSleep = false;
        this->circleBody = this->world->CreateBody(&circleBodyDef);
        
        b2CircleShape circleShape;
        circleShape.m_radius = 20.0f / PTM_RATIO; //半径
        
        b2FixtureDef circleFixtureDef;
        circleFixtureDef.density = 1.0f; //密度
        circleFixtureDef.restitution = 0.5f; //弹力
        circleFixtureDef.friction = 1.0f; //摩擦力
        circleFixtureDef.shape = &circleShape;
        
        this->circleFixture = this->circleBody->CreateFixture(&circleFixtureDef);
        
        this->circleMouseJoint = NULL;
                
        //多边形
        b2BodyDef polygonBodyDef;
        polygonBodyDef.type = b2_dynamicBody;
        polygonBodyDef.position = b2Vec2(600.0f / PTM_RATIO, 600.0f / PTM_RATIO);
        polygonBodyDef.allowSleep = false;
        this->polygonBody = this->world->CreateBody(&polygonBodyDef);
        b2PolygonShape polygon;
        
        int num = 4;
        b2Vec2 vertices[] = {
            b2Vec2(0.0f, 0.0f),
            b2Vec2(20.0f / PTM_RATIO, 0.0f),
            b2Vec2(20.0f / PTM_RATIO, 20.0f / PTM_RATIO),
            b2Vec2(0.0f / PTM_RATIO, 20.0f / PTM_RATIO)
        };
        polygon.Set(vertices, num);
        
        this->polygonFixture = this->polygonBody->CreateFixture(&polygon, 1.0f);
        
        this->polygonMouseJoint = NULL;
        
        return true;
    }
    
    return false;
}

CCScene* OzgBox2DEdgeTestScene::scene()
{
    CCScene *scene = CCScene::create();
    
    OzgBox2DEdgeTestScene *layer = new OzgBox2DEdgeTestScene();
    if(layer->init())
    {
        layer->autorelease();
        scene->addChild(layer);
    }
    return scene;
}

bool OzgBox2DEdgeTestScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{    
    CCPoint point = pTouch->getLocation();
    b2Vec2 vec = b2Vec2(point.x / PTM_RATIO, point.y / PTM_RATIO); //转换为box2d的坐标
    
    if(this->circleFixture->TestPoint(vec))
    {
        if(this->circleMouseJoint != NULL)
            return true;
        
        //设置MouseJoint
        b2MouseJointDef mouseJointDef;
        mouseJointDef.bodyA = this->groundBody;
        mouseJointDef.bodyB = this->circleBody;
        mouseJointDef.collideConnected = true;
        mouseJointDef.target = vec;
        mouseJointDef.maxForce = 1000.0f * this->circleBody->GetMass();
        
        this->circleMouseJoint = (b2MouseJoint*)this->world->CreateJoint(&mouseJointDef);
        
        this->circleBody->SetAwake(true);
    }
    else if(this->polygonFixture->TestPoint(vec))
    {
        //设置MouseJoint
        b2MouseJointDef mouseJointDef;
        mouseJointDef.bodyA = this->groundBody;
        mouseJointDef.bodyB = this->polygonBody;
        mouseJointDef.collideConnected = true;
        mouseJointDef.target = vec;
        mouseJointDef.maxForce = 1000.0f * this->polygonBody->GetMass();
        this->polygonMouseJoint = (b2MouseJoint*)this->world->CreateJoint(&mouseJointDef);
    }
    
    return true;
}

void OzgBox2DEdgeTestScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint point = pTouch->getLocation();
    b2Vec2 vec = b2Vec2(point.x / PTM_RATIO, point.y / PTM_RATIO); //转换为box2d的坐标
    
    if(this->circleMouseJoint != NULL)
    {
        this->circleMouseJoint->SetTarget(vec);
    }
    else if(this->polygonMouseJoint != NULL)
    {
        this->polygonMouseJoint->SetTarget(vec);
    }
    
}

void OzgBox2DEdgeTestScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(this->circleMouseJoint != NULL)
    {
        this->world->DestroyJoint(this->circleMouseJoint);
        this->circleMouseJoint = NULL;
    }
    else if(this->polygonMouseJoint != NULL)
    {
        this->world->DestroyJoint(this->polygonMouseJoint);
        this->polygonMouseJoint = NULL;
    }
    
}
