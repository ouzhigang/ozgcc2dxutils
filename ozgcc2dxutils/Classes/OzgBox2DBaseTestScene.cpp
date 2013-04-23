//
//  OzgBox2DBaseTestScene.cpp
//  ozgccs
//
//  Created by Tpwid on 13-4-18.
//
//

#include "OzgBox2DBaseTestScene.h"

OzgBox2DBaseTestScene::OzgBox2DBaseTestScene()
{
    
}

OzgBox2DBaseTestScene::~OzgBox2DBaseTestScene()
{
    CC_SAFE_DELETE(this->debugDraw);
    CC_SAFE_DELETE(this->world);
    
}

bool OzgBox2DBaseTestScene::init()
{
    if(CCLayer::init())
    {
        b2Vec2 gravity;
        gravity.Set(0.0f, -10.0f);
        this->world = new b2World(gravity);
        
        this->scheduleUpdate();
        
        //debug
        this->debugDraw = new GLESDebugDraw(PTM_RATIO);
        this->world->SetDebugDraw(debugDraw);
        uint32 flags = 0;
        flags += b2Draw::e_shapeBit;
        this->debugDraw->SetFlags(flags);
        
        return true;
    }
    
    return false;
}

void OzgBox2DBaseTestScene::update(float dt)
{
    int velocityIterations = 8;
    int positionIterations = 1;
    
    this->world->Step(dt, velocityIterations, positionIterations);
    
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL)
        {
            
            CCSprite* sprite = (CCSprite*)b->GetUserData();
            sprite->setPosition(CCPointMake(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
            sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
        }
    }
    
}

void OzgBox2DBaseTestScene::draw()
{
    glDisable(GL_TEXTURE_2D);
    //glDisableClientState(GL_COLOR_ARRAY);
    //glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    
    this->world->DrawDebugData();
    
    glEnable(GL_TEXTURE_2D);
    //glEnableClientState(GL_COLOR_ARRAY);
    //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

CCScene* OzgBox2DBaseTestScene::scene()
{
    CCScene *scene = CCScene::create();
    
    OzgBox2DBaseTestScene *layer = new OzgBox2DBaseTestScene();
    if(layer->init())
    {
        layer->autorelease();
        scene->addChild(layer);
    }
    return scene;
}
