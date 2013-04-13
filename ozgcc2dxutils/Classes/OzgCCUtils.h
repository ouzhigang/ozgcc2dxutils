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
    
    //draw实心圆,参数为：中心点，半径，线段数（越大锯齿就越少），颜色
    static void ccDrawSolidCircle(const CCPoint& center, float radius, unsigned int segments, ccColor4F color);
    
    static void clearAnimate(const char *plist); //清空plist生成的帧动画
    static CCAnimate* createAnimate(const char *plist); //利用plist生成帧动画，plist结构在实现文件里面
    
    static void plistPosition(CCNode *node, const char *plist); //使用plist来定位
    
};

#endif /* defined(__ozgccs__OzgCCUtils__) */
