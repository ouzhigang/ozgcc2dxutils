//
//  OzgFileUtility.cpp
//  ozgcpp
//
//  Created by Tpwid on 13-4-27.
//  Copyright (c) 2013年 欧 志刚. All rights reserved.
//

#include "OzgFileUtility.h"

//私有方法
bool OzgFileUtility::isSpecialDir(const char *path)
{
    return strcmp(path, ".") == 0 || strcmp(path, "..") == 0;
}

void OzgFileUtility::getFilePath(const char *path, const char *fileName,  char *filePath)
{
    strcpy(filePath, path);
    if(filePath[strlen(path) - 1] != '/')
        strcat(filePath, "/");
    strcat(filePath, fileName);
}

//获取路径下的所有文件夹和文件
vector<string> OzgFileUtility::getFoldersAndFile(const string &path, bool showAbsolutePath)
{
    vector<string> items;
    struct dirent* ent = NULL;
    DIR* pDir;
    pDir = opendir(path.c_str());
    while(NULL != (ent = readdir(pDir)))
    {
        string fullpath = path + "/" + ent->d_name;
        if(strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
        {
            string filePath;
            
            //绝对路径
            if(showAbsolutePath)
                filePath.append(path);
            
            //所在目录的结尾是否有/
            if (path.c_str()[path.size() - 1] != '/')
                filePath.append("/");
                            
            filePath.append(ent->d_name);
            items.push_back(filePath);                
        }
    }
    closedir(pDir);
    return items;
}

//获取路径下的所有文件夹
vector<string> OzgFileUtility::getFolders(const string &path, bool showAbsolutePath)
{
    vector<string> folders;
    struct dirent* ent = NULL;
    DIR* pDir;
    pDir = opendir(path.c_str());
    while(NULL != (ent = readdir(pDir)))
    {
        string fullpath = path + "/" + ent->d_name;
        //if(4 == ent->d_type)  //在nfs或xfs下，有的目录d_type也是0
        if(OzgFileUtility::isFolder(fullpath))
        {
            if(strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
            {
                string filePath;
                
                //绝对路径
                if(showAbsolutePath)
                    filePath.append(path);
                
                //所在目录的结尾是否有/
                if (path.c_str()[path.size() - 1] != '/')
                    filePath.append("/");
                
                filePath.append(ent->d_name);
                folders.push_back(filePath);
            }
        }
    }
    closedir(pDir);
    return folders;
}

//获取路径下的所有文件，可指定文件后缀名
vector<string> OzgFileUtility::getFiles(const string &path, bool showAbsolutePath, const string &postfix)
{
    vector<string> files;
    struct dirent* ent = NULL;
    DIR* pDir;
    pDir = opendir(path.c_str());
    while(NULL != (ent = readdir(pDir)))
    {
        string fullpath = path + "/" + ent->d_name;
        //if(8 == ent->d_type)  //在nfs或xfs下，有的文件d_type也是0
        if(OzgFileUtility::isFile(fullpath))
        {
            if(postfix == "" || strstr(ent->d_name, postfix.c_str())!=NULL)
            {
                string filePath;
                
                //绝对路径
                if(showAbsolutePath)
                    filePath.append(path);
                
                //所在目录的结尾是否有/
                if (path.c_str()[path.size() - 1] != '/')
                    filePath.append("/");
                
                filePath.append(ent->d_name);
                files.push_back(filePath);
            }
        }
    }
    closedir(pDir);
    return files;
}

//检查文件或目录是否准备好，一定程度上防止数据正在拷贝的时候去读写。
//方法是检查文件或目录的access time是否在5分钟以前
bool OzgFileUtility::isPrepared(const string &path)
{
    struct stat st;
    stat(path.c_str(), &st);
    return time(0) - st.st_ctime >= MAX_DUR;
}

//判断是否为文件夹，用stat的标志来判断
bool OzgFileUtility::isFolder(const string &path)
{
    struct stat st;
    int ret = stat(path.c_str(), &st);
    return ret >= 0 && S_ISDIR(st.st_mode);
}

//判断是否为文件，用stat的标志来判断
bool OzgFileUtility::isFile(const string &path)
{
    struct stat st;
    int ret = stat(path.c_str(), &st);
    return ret >= 0 && S_ISREG(st.st_mode);
}

//判断文件或文件夹是否存在
bool OzgFileUtility::fileExists(const string &path)
{
    fstream fs;
    fs.open(path.c_str(), ios::in);
    if(!fs)
        return false;
    else
        return true;
    
}

void OzgFileUtility::deleteFile(const string &path)
{
    DIR *dir;
    dirent *dirInfo;
    char filePath[PATH_MAX];
    if(OzgFileUtility::isFile(path))
    {
        remove(path.c_str());
        return;
    }
    
    if(OzgFileUtility::isFolder(path))
    {
        if((dir = opendir(path.c_str())) == NULL)
            return;
        while((dirInfo = readdir(dir)) != NULL)
        {
            OzgFileUtility::getFilePath(path.c_str(), dirInfo->d_name, filePath);
            if(OzgFileUtility::isSpecialDir(dirInfo->d_name))
                continue;
            OzgFileUtility::deleteFile(filePath);
            rmdir(filePath);
        }
        
        rmdir(path.c_str());
    }
}

bool OzgFileUtility::copyFile(const char *src, const char *des)
{
    FILE * fSrc = fopen(src, "rb");
    if(!fSrc)
    {
        printf("打开文件`%s`失败", src);
        return false;
    }
    FILE * fDes = fopen(des, "wb");
    if(!fDes)
    {
        printf("创建文件`%s`失败", des);
        return false;
    }
    
    unsigned char * buf;
    unsigned int length;
    fseek(fSrc, 0, SEEK_END);
    length = ftell(fSrc);
    buf = new unsigned char[length+1];
    memset(buf, 0, length+1);
    fseek(fSrc, 0, SEEK_SET);
    fread(buf, length, 1, fSrc);
    
    fwrite(buf, length, 1, fDes);
    
    fclose(fSrc);
    fclose(fDes);
    delete [] buf;
    return true;
}
