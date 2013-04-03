//
//  OzgCCUtils.cpp
//  ozgccs
//
//  Created by 欧 志刚 on 13-4-2.
//
//

#include "OzgCCUtils.h"

void OzgCCUtils::clearAnimate(const char *plist)
{
    CCDictionary *root = CCDictionary::createWithContentsOfFile(plist);
    CCArray *frames = (CCArray*)root->objectForKey("frames");
    CCObject *item = NULL;
    CCARRAY_FOREACH(frames, item)
    {
        CCString *itemStr = (CCString*)item;
        
        CCTextureCache::sharedTextureCache()->removeTextureForKey(itemStr->getCString());
    }
}

CCAnimate* OzgCCUtils::createAnimate(const char *plist)
{
    //plist的根节点为Root(CCDictionary)
    //plist的结构为frames(CCArray<CCString*>),loop(Number),delay(Number),rect(CCDictionary)里面有x(Number),y(Number),width(Number),height(Number)
    
    //loop为循环次数，-1为无限次
    //delay为每帧的时间间隔
    //rect帧的范围，一般为0, 0, 图片宽, 图片高
    //frames帧的路径
    
    CCArray *spriteFrames = CCArray::create();
    
    CCDictionary *root = CCDictionary::createWithContentsOfFile(plist);
    
    unsigned int loops = ((CCString*)root->objectForKey("loop"))->intValue();
    float delay = ((CCString*)root->objectForKey("delay"))->floatValue();
    CCArray *frames = (CCArray*)root->objectForKey("frames");
    CCDictionary *rectDict = (CCDictionary*)root->objectForKey("rect");
    float rectX = ((CCString*)rectDict->objectForKey("x"))->floatValue();
    float rectY = ((CCString*)rectDict->objectForKey("y"))->floatValue();
    float rectWidth = ((CCString*)rectDict->objectForKey("width"))->floatValue();
    float rectHeight = ((CCString*)rectDict->objectForKey("height"))->floatValue();
    CCRect rect = CCRectMake(rectX, rectY, rectWidth, rectHeight);
    
    CCObject *item = NULL;
    CCARRAY_FOREACH(frames, item)
    {
        CCString *itemStr = (CCString*)item;
        
        CCSpriteFrame *spriteFrame = CCSpriteFrame::create(itemStr->getCString(), rect);
        spriteFrames->addObject(spriteFrame);
    }
    
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(spriteFrames, delay);
    animation->setLoops(loops);
    CCAnimate *animate = CCAnimate::create(animation);
    
    return animate;
}
