//
//  OzgCCAsyncImagesScene.h
//  
//
//  Created by ouzhigang on 13-5-23.
//
//

/*
 
 demos: 需要继承OzgCCAsyncImagesScene
 
 bool HelloWorld::init()
 {
    if ( !CCLayer::init() )
    {
        return false;
    }
 
    this->m_currImagesPath = "images";
    this->imagesAsyncStart(this->m_currImagesPath); //异步读取图片
 
    return true;
 }
 
 void HelloWorld::imagesAsyncComplete()
 {
    OzgCCAsyncImagesScene::imagesAsyncComplete();
 
    CCLog("complete"); 
 }
 
 */

#ifndef __ozgcc2dutils__OzgCCAsyncImagesScene__
#define __ozgcc2dutils__OzgCCAsyncImagesScene__

#include <vector.h>
#include "cocos2d.h"
#include "OzgFileUtility.h"

using namespace std;
USING_NS_CC;

class OzgCCAsyncImagesScene : public CCLayer
{
    
protected:
    
    const char* m_currImagesPath; //当前场景的图片目录名
    vector<string> m_currImageFiles; //当前场景的图片目录里面的图片，绝对路径
    int m_imagesLoaded = 0; //已读取的图片数
    
    //异步读取图片相关
    void imagesClear(); //执行清理整个场景的图片文件夹的资源
    virtual void imagesAsyncStart(const char* currImagesPath); //执行整个场景的图片文件夹异步读取
    virtual void imagesAsyncProgress(CCObject* obj); //loading图片中的回调方法
    virtual void imagesAsyncComplete(); //图片读取完成后执行
    const char* imagesGetPath(const char* currImagesPath); //获取当前场景的图片目录，绝对路径
    
public:
    OzgCCAsyncImagesScene();
    virtual ~OzgCCAsyncImagesScene();
    bool init();
    
    CREATE_FUNC(OzgCCAsyncImagesScene);
    
};

#endif /* defined(__ozgcc2dutils__OzgCCAsyncImagesScene__) */
