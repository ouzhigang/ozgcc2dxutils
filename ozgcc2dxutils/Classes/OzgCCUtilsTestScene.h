#ifndef __OzgCCUtilsTestScene_H__
#define __OzgCCUtilsTestScene_H__

#include "cocos2d.h"
#include "OzgCCUtils.h"

class OzgCCUtilsTestScene : public cocos2d::CCLayerColor
{
public:
    virtual bool init();

    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(OzgCCUtilsTestScene);
    
    void clearCache();
};

#endif
