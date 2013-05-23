//
//  OzgCCAsyncImages.cpp
//  
//
//  Created by ouzhigang on 13-5-23.
//
//

#include "OzgCCAsyncImages.h"

OzgCCAsyncImages::OzgCCAsyncImages()
{

}

OzgCCAsyncImages::~OzgCCAsyncImages()
{

}

OzgCCAsyncImages* OzgCCAsyncImages::create(const char* currImagesPath, cocos2d::CCObject *pObj, SEL_CallFunc startSelector, SEL_CallFunc completeSelector)
{
    OzgCCAsyncImages *obj = new OzgCCAsyncImages();
    if(obj)
    {
        obj->autorelease();
        
        obj->m_currImagesPath = currImagesPath;
        obj->m_pObj = pObj;
        obj->m_startSelector = startSelector;
        obj->m_completeSelector = completeSelector;
        
        return obj;
    }
    
    CC_SAFE_DELETE(obj);
    return NULL;
}

void OzgCCAsyncImages::start()
{
    (this->m_pObj->*this->m_startSelector)();
    
    this->m_currImageFiles = OzgFileUtility::getFiles(this->imagesGetPath());    
    
    //读取第1个图片
    CCTextureCache::sharedTextureCache()->addImageAsync(this->m_currImageFiles[0].c_str(), this, callfuncO_selector(OzgCCAsyncImages::imagesAsyncProgress));
}

const char* OzgCCAsyncImages::imagesGetPath()
{
    return CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(this->m_currImagesPath);
    
}

void OzgCCAsyncImages::imagesAsyncProgress(CCObject* obj)
{
    this->m_imagesLoaded++;
    int loaded = (int)((float)this->m_imagesLoaded / (float)this->m_currImageFiles.capacity() * 100.0f);
    
    //CCLog("已完成:%i%%", loaded);
    
    if(loaded == 100)
    {
        (this->m_pObj->*this->m_completeSelector)();
        
    }
    else
    {
        //读取下一个图片
        CCTextureCache::sharedTextureCache()->addImageAsync(this->m_currImageFiles[this->m_imagesLoaded].c_str(), this, callfuncO_selector(OzgCCAsyncImages::imagesAsyncProgress));
    }
    
}
