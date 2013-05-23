//
//  OzgCCAsyncImages.h
//  
//
//  Created by ouzhigang on 13-5-23.
//
//

/*
 
 demos:
 
 OzgCCAsyncImages *asyncImages = OzgCCAsyncImages::create("images", this, callfunc_selector(HelloWorld::start), callfunc_selector(HelloWorld::complete));
 asyncImages->start();
 
 void HelloWorld::start()
 {
    CCLog("start"); 
 }
 
 void HelloWorld::complete()
 {
    CCLog("complete"); 
 }
 
 */

#ifndef __kippo_drawing_animal__OzgCCAsyncImages__
#define __kippo_drawing_animal__OzgCCAsyncImages__

#include <vector.h>
#include "cocos2d.h"
#include "OzgFileUtility.h"

using namespace std;
using namespace cocos2d;

class OzgCCAsyncImages : public CCObject
{
    
private:
    const char* m_currImagesPath; //当前场景的图片目录
    vector<string> m_currImageFiles; //当前场景的图片目录里面的图片，绝对路径
    
    int m_imagesLoaded = 0; //已读取的图片数
    
    CCObject* m_pObj; //回调对象
    SEL_CallFunc m_startSelector; //开始前执行的回调
    SEL_CallFunc m_completeSelector; //完成后执行的回调
    
    const char* imagesGetPath(); //获取当前场景的图片目录，绝对路径
    
    void imagesAsyncProgress(CCObject* obj); //loading图片中的回调方法
    
public:
    
    OzgCCAsyncImages();
    virtual ~OzgCCAsyncImages();
    
    static OzgCCAsyncImages* create(const char* currImagesPath, CCObject* pObj, SEL_CallFunc startSelector, SEL_CallFunc completeSelector);
    
    void start();
    
};

#endif /* defined(__kippo_drawing_animal__OzgCCAsyncImages__) */
