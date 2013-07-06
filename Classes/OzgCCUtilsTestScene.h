#ifndef __OzgCCUtilsTestScene_H__
#define __OzgCCUtilsTestScene_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "OzgCCUtils.h"

USING_NS_CC;
using namespace CocosDenshion;

class OzgCCUtilsTestScene : public CCLayerColor
{
public:
    virtual bool init();

    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(OzgCCUtilsTestScene);
    
    void clearCache();
};

#endif
