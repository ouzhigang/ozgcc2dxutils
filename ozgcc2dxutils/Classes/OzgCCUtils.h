//
//  OzgCCUtils.h
//
//  大部分为常用的静态方法
//
//  Created by 欧 志刚 on 13-4-2.
//
//

#ifndef __ozgccs__OzgCCUtils__
#define __ozgccs__OzgCCUtils__

#include "cocos2d.h"

USING_NS_CC;

using namespace cocos2d;

class OzgCCUtils
{
    
    
public:
    
    static void clearAnimate(const char *plist); //清空plist生成的帧动画
    static CCAnimate* createAnimate(const char *plist); //利用plist生成帧动画，plist结构在实现文件里面
    
};

#endif /* defined(__ozgccs__OzgCCUtils__) */
