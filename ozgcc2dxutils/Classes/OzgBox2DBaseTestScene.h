//
//  OzgBox2DBaseTestScene.h
//  ozgccs
//
//  Created by Tpwid on 13-4-18.
//
//

#ifndef __ozgccs__OzgBox2DBaseTestScene__
#define __ozgccs__OzgBox2DBaseTestScene__

#include <vector.h>
#include "cocos2d.h"
#include "Box2D.h"
#include "GLES-Render.h"

#ifndef PTM_RATIO
#define PTM_RATIO 32
#endif

using namespace cocos2d;

class OzgBox2DBaseTestScene : public CCLayer
{
    
protected:
    b2World* world;
    GLESDebugDraw *debugDraw;
        
public:
    
    OzgBox2DBaseTestScene();
    virtual ~OzgBox2DBaseTestScene();
    bool init();
    
    void update(float dt);
    void draw();
    
    static CCScene* scene();
    
};

#endif /* defined(__ozgccs__OzgBox2DBaseTestScene__) */
