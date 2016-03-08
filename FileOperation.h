#ifndef _FILEOPERATION_H_
#define _FILEOPERATION_H_
#pragma once
#include <string>
#include <vector>
#include <map>
#include "classification.hpp"
using namespace std;
//�õ��ļ����������ļ������ư������ļ����µ��ļ�
void getFiles(string filePath, vector<string>& fileNames);
//�õ��ļ��������е�һ�����ļ��е�����
void getFolders(string filePath, vector<string>& folderNames);
//�����ļ������浽��Ӧ���ļ�����
void classifyAndSaveFile(Classifier classifier, vector<string>& fileNames, string folderNames);
//�������ض����ݼ��µķ��ྫ��
double classifyAndCalAccuracy(Classifier classifier, vector<string>& fileNames);
//�ַ����ָ��
vector< string> split(string str, string pattern);
vector<string> split2(string str, string pattern);
//���ļ����ַ�������ȡ������
string getAgeGroup(string fileName);

#endif //_FILEOPERATION_H_