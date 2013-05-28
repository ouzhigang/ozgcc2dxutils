//
//  OzgCCUtils.cpp
//  ozgccs
//
//  Created by 欧 志刚 on 13-4-2.
//
//

#include "OzgCCUtils.h"

void OzgCCUtils::ccDrawSolidCircle(const CCPoint& center, float radius, unsigned int segments, ccColor4F color)
{
    const float coef = 2.0f * (float)M_PI / segments;
    CCPoint *vertices = (CCPoint*)calloc(segments + 1, sizeof(CCPoint));
    
    for(unsigned int i = 0;i <= segments; i++)
    {
        float rads = i * coef;
        GLfloat j = radius * cosf(rads)  + center.x;
        GLfloat k = radius * sinf(rads)  + center.y;
        vertices[i].x = j;
        vertices[i].y = k;
    }
    ccDrawSolidPoly(vertices, segments, color);
    free(vertices);
}

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

void OzgCCUtils::plistPosition(cocos2d::CCNode *node, const char *plist)
{
    CCDictionary *root = CCDictionary::createWithContentsOfFile(plist);
    float positionX = ((CCString*)root->objectForKey("position_x"))->floatValue();
    float positionY = ((CCString*)root->objectForKey("position_y"))->floatValue();
    node->setAnchorPoint(CCPointZero); //强制使用0锚点
    node->setPosition(ccp(positionX, positionY));
    
}

unsigned int OzgCCUtils::rangeRand(unsigned int min, unsigned int max)
{
    unsigned int x = abs((random() * time(NULL) % (max - min)));
    x += min;
    return x;
}

int OzgCCUtils::atoi(const char *src)
{
    char flag = 0;
    int sum = 0;
    int i = 0;
    int len = (int)strlen(src);
    
    /*参数的正确性*/
    if(NULL == src)
    {
        return 0;
    }
    
    /*是否存在符号问题*/
    if(src[i] == '-')
    {
        flag = '-';
        ++i;
    }
    
    for( ; i < len; ++i)
    {
        /*判断字符是否合法*/
        if(src[i] < 48 && src[i] > 57)
            return 0;
        
        /*数据求和，注意数值的转换问题src[i] - 48*/
        sum = sum * 10 + src[i] - 48;
    }
    
    /*根据标志位实现返回正确的正负数*/
    if(flag == '-')
        return -sum;
    else
        return sum;
}

char* OzgCCUtils::itoa(int num, char *str)
{
    //char flag = 0;
    int i = 0, count = 0, j = 0;
    
    /*参数检测*/
    if(NULL == str)
    {
        return NULL;
    }
    
    /*判断数值的正负,设置对应的符号*/
    if(num < 0)
    {
        str[i++] = '-';
        
        /************************
         同时要对数值取绝对值
         保证后面取余整除操作正常
         *************************/
        num = -num;
    }
    
    while(num / 10)
    {
        /***************************
         count用来保存实际的数字个数,
         便于后期的顺序调换
         ****************************/
        ++count;
        /*实际保存的顺序为反序列*/
        str[i++] = num % 10 + 48;
        num /= 10;
    }
    /*判断是*/
    if(num % 10)
    {
        str[i++] = num %10 + 48;
        ++count;
    }
    /*字符串结束符*/
    str[i] = 0;
    
    /*实现数据的较好操作*/
    i = 0;
    if(str[0] == '-')
    {
        i = 1;
    }
    /*实际交换的下标区间为i~j*/
    j = count + i - 1;
    
    for(; i < j ; ++i, --j)
    {
        /*数据的较好操作*/
        str[i] = str[i] + str[j];
        str[j] = str[i] - str[j];
        str[i] = str[i] - str[j];
    }
    
    /*返回实际的字符串*/
    return str;
}

char* OzgCCUtils::formatTime(const char *format)
{
    return OzgCCUtils::formatTime(format, time(NULL));
}

char* OzgCCUtils::formatTime(const char *format, time_t utc_time)
{
    static char str_time[128];
    struct tm *local_time = NULL;
    
    utc_time = time (NULL);
    local_time = localtime(&utc_time);
    strftime(str_time, sizeof(str_time), format, local_time);
    
    return str_time;
}
