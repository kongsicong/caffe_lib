#ifndef _FILEOPERATION_H_
#define _FILEOPERATION_H_
#pragma once
#include <string>
#include <vector>
#include <map>
#include "classification.hpp"
using namespace std;
//得到文件夹下所有文件的名称包含子文件夹下的文件
void getFiles(string filePath, vector<string>& fileNames);
//得到文件夹下所有第一级子文件夹的名称
void getFolders(string filePath, vector<string>& folderNames);
//分类文件并保存到相应的文件夹下
void classifyAndSaveFile(Classifier classifier, vector<string>& fileNames, string folderNames);
//测试在特定数据集下的分类精度
double classifyAndCalAccuracy(Classifier classifier, vector<string>& fileNames);
//字符串分割函数
vector< string> split(string str, string pattern);
vector<string> split2(string str, string pattern);
//从文件名字符串中提取出年龄
string getAgeGroup(string fileName);

#endif //_FILEOPERATION_H_