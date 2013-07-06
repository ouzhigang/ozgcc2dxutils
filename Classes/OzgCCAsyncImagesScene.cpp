//
//  OzgCCAsyncImagesScene.cpp
//  
//
//  Created by ouzhigang on 13-5-23.
//
//

#include "OzgCCAsyncImagesScene.h"

OzgCCAsyncImagesScene::OzgCCAsyncImagesScene()
{
    
}

OzgCCAsyncImagesScene::~OzgCCAsyncImagesScene()
{
    
}

bool OzgCCAsyncImagesScene::init()
{
    if(CCLayer::init())
    {
        
        return true;
    }
    
    return false;
}

void OzgCCAsyncImagesScene::imagesClear()
{
    vector<string>::iterator fileIterator = this->m_currImageFiles.begin();
    while (fileIterator != this->m_currImageFiles.end())
    {
        string file = *fileIterator;
        file.erase(0, file.find(this->m_currImagesPath));
        
        CCTextureCache::sharedTextureCache()->removeTextureForKey(file.c_str());
        
        fileIterator++;
    }
}

void OzgCCAsyncImagesScene::imagesAsyncStart(const char *currImagesPath)
{
    this->m_currImageFiles = OzgFileUtility::getFiles(this->imagesGetPath(currImagesPath));
    
    //读取第1个图片
    CCTextureCache::sharedTextureCache()->addImageAsync(this->m_currImageFiles[0].c_str(), this, callfuncO_selector(OzgCCAsyncImagesScene::imagesAsyncProgress));
    
}

void OzgCCAsyncImagesScene::imagesAsyncProgress(cocos2d::CCObject *obj)
{
    this->m_imagesLoaded++;
    int loaded = (int)((float)this->m_imagesLoaded / (float)this->m_currImageFiles.capacity() * 100.0f);
    
    //CCLog("已完成:%i%%", loaded);
    
    if(loaded == 100)
    {
        //调试
        //this->imagesClear();
        //CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
        //CCLog("完成");
        
        this->imagesAsyncComplete();
    }
    else
    {
        //读取下一个图片
        CCTextureCache::sharedTextureCache()->addImageAsync(this->m_currImageFiles[this->m_imagesLoaded].c_str(), this, callfuncO_selector(OzgCCAsyncImagesScene::imagesAsyncProgress));
        
    }
    
}

void OzgCCAsyncImagesScene::imagesAsyncComplete()
{
    //CCLog("读取完成");
    
}

const char* OzgCCAsyncImagesScene::imagesGetPath(const char* currImagesPath)
{
    return CCFileUtils::sharedFileUtils()->fullPathForFilename(currImagesPath).c_str();
    
}
