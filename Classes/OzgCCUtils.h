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

#define OZG_BASE64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="

USING_NS_CC;

static unsigned int OzgCCUtilsRandomSeed = 0;

class OzgCCUtils
{
    
    
public:
    
    //draw实心圆,参数为：中心点，半径，线段数（越大锯齿就越少），颜色
    static void ccDrawSolidCircle(const CCPoint& center, float radius, unsigned int segments, ccColor4F color);
    
    static void clearAnimate(const char *plist); //清空plist生成的帧动画
    static CCAnimate* createAnimate(const char *plist); //利用plist生成帧动画，plist结构在实现文件里面
    
    static void plistPosition(CCNode *node, const char *plist); //使用plist来定位
    
    static unsigned int rangeRand(unsigned int min, unsigned int max); //范围随机数
    //随机例子，第一次调用randomFloat的值都是一样的，所以第一次的值可以忽略
//    OzgCCUtils::randomSeed(0);
//    for (int i = 0; i < 10; i++)
//    {
//        CCLog("%f, %f", OzgCCUtils::randomFloat(0.0f, 3.0f), OzgCCUtils::randomFloat(0.0f, 3.0f));
//        sleep(1);
//    }
    static void randomSeed(int seed);
    static float randomFloat(float min, float max); //范围随机float
    
    static int atoi(const char *src); //atoi的加强版，字符转整数
    static char* itoa(int num, char *str); //整数转字符
    static char* formatTime(const char* format); //返回格式化的时间，参数1 demos:"%Y-%m-%d %H:%M:%S"
    static char* formatTime(const char* format, time_t utc_time);

    /*
     base64 demo
     
     const char *t = "this is ozg demo";
     int j = strlen(t);
     char *enc = OzgCCUtils::base64Encode(t, j);
     int len = strlen(enc);
     char *dec = OzgCCUtils::base64Decode(enc, len);
     printf("\noriginal: %s\n", t);
     printf("\nencoded : %s\n", enc);
     printf("\ndecoded : %s\n", dec);
     free(enc);
     free(dec);
     
     */
    static char *base64Encode(const char* data, int data_len);
    static char base64FindPos(char ch);
    static char *base64Decode(const char *data, int data_len);

};

#endif /* defined(__ozgccs__OzgCCUtils__) */
