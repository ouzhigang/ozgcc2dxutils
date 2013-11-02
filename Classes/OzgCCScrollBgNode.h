//
//  OzgCCScrollBgNode.h
//  OzgGameDuskFantasy
//
//  Created by 欧 志刚 on 13-10-22.
//
//

//滚动背景
//目前之支持左右滚动

#ifndef __OzgGameDuskFantasy__OzgCCScrollBgNode__
#define __OzgGameDuskFantasy__OzgCCScrollBgNode__

#include "cocos2d.h"
#include <iostream>

USING_NS_CC;
using namespace std;

class OzgCCScrollBgNode : public CCNode
{
private:
    CCSprite* m_bgSprite1;
    CCSprite* m_bgSprite2;
    string m_bg;
    
public:
    virtual ~OzgCCScrollBgNode();
    bool init(const char* bg);
    static OzgCCScrollBgNode* create(const char* bg);
    void update(float delta);
    
};

#endif /* defined(__OzgGameDuskFantasy__OzgCCScrollBgNode__) */
