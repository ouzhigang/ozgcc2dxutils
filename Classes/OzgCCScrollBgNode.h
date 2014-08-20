
//滚动背景
//目前只支持左右滚动

#ifndef __ozgcc2dxutils__OzgCCScrollBgNode__
#define __ozgcc2dxutils__OzgCCScrollBgNode__

#include <iostream>
#include "cocos2d.h"

class OzgCCScrollBgNode : public cocos2d::CCParallaxNode
{
private:
    
	std::vector<std::string> m_bgList;
    
public:
    
	float m_scrollSpeed;
    
    virtual ~OzgCCScrollBgNode();
    
	bool init(std::vector<std::string> bgList);
	static OzgCCScrollBgNode* create(std::vector<std::string> bgList);
    
    void update(float delta);
    
};

#endif /* defined(__ozgcc2dxutils__OzgCCScrollBgNode__) */
