//
//  OzgFileUtility.h
//  ozgcpp
//
//  Created by Tpwid on 13-4-27.
//  Copyright (c) 2013年 欧 志刚. All rights reserved.
//

/*
 
 demo
 
 vector<string> files = OzgFileUtility::getFoldersAndFile("/");
 vector<string>::iterator filesIterator = files.begin();
 while (filesIterator != files.end())
 {
    cout << *filesIterator << endl;
 
    filesIterator++;
 }
 
 */

#ifndef __ozgcpp__OzgFileUtility__
#define __ozgcpp__OzgFileUtility__

#include <iostream.h>
#include <fstream> 
#include <vector>
#include <cstring>
#include <ctime>
#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>
#include <dirent.h>

using namespace std;

const int MAX_DUR = 5 * 60;

class OzgFileUtility
{

public:
    
    //获取路径下的所有文件夹和文件
    static vector<string> getFoldersAndFile(const string &path, bool showAbsolutePath = true);
    
    //获取路径下的所有文件夹
    static vector<string> getFolders(const string &path, bool showAbsolutePath = true);
    
    //获取路径下的所有文件，可指定文件后缀名
    static vector<string> getFiles(const string &path, bool showAbsolutePath = true, const string &postfix = "");
    
    //检查文件或目录是否准备好，一定程度上防止数据正在拷贝的时候去读写。
    //方法是检查文件或目录的access time是否在5分钟以前
    static bool isPrepared(const string &path);
    
    //判断是否为文件夹
    static bool isFolder(const string &path);
    
    //判断是否为文件
    static bool isFile(const string &path);
    
    //判断文件或文件夹是否存在
    static bool fileExists(const string &path);
    
};


#endif /* defined(__ozgcpp__OzgFileUtility__) */
