#include "OzgCCUtilsTestScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* OzgCCUtilsTestScene::scene()
{
    CCScene *scene = CCScene::create();
    
    OzgCCUtilsTestScene *layer = OzgCCUtilsTestScene::create();

    scene->addChild(layer);

    return scene;
}

bool OzgCCUtilsTestScene::init()
{
    if (!CCLayerColor::initWithColor(ccc4(100, 100, 100, 255)))
    {
        return false;
    }
    
    //test1
    CCSprite *obj = CCSprite::create("CloseSelected.png");
    obj->setTag(99);
    obj->setPosition(ccp(100, 100));
    this->addChild(obj);
    
    CCAnimate *objAnim = OzgCCUtils::createAnimate("anim.plist");
    obj->runAction(objAnim);
    
    this->scheduleOnce(schedule_selector(OzgCCUtilsTestScene::clearCache), 3.0f);
    
    return true;
}

void OzgCCUtilsTestScene::clearCache()
{
    CCSprite *obj = (CCSprite*)this->getChildByTag(99);
    obj->stopAllActions();
    obj->removeFromParentAndCleanup(true);
    
    OzgCCUtils::clearAnimate("anim.plist");
    
    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
}
