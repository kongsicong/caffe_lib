#include "FileOperation.h"
#include <io.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdlib.h>
//得到文件夹下所有文件的名称包含子文件夹下的文件
void getFiles(string filePath, vector<string>& fileNames) {
	//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(filePath).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(filePath).append("\\").append(fileinfo.name), fileNames);
			}
			else
			{
				fileNames.push_back(p.assign(filePath).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}
//得到文件夹下所有第一级子文件夹的名称
void getFolders(string filePath, vector<string>& folderNames) {
	//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(filePath).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					folderNames.push_back(p.assign(filePath).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}
//字符串分割
vector<string> split2(string str, string pattern) {
	vector<string> ret;
	int n_str = str.size();
	int n_pattern = pattern.size();
	int pos = 0;
	for (int i = 0; i < n_str; i++) {
		for (int j = 0; j < n_pattern; j++) {
			if (str[i] == pattern[j]) {
				if (pos == i) {
					pos = i + 1;
					break;
				}
				else {
					ret.push_back(str.substr(pos, i - pos));
					pos = i + 1;
					break;
				}

			}
		}
	}
	if (pos != n_str) ret.push_back(str.substr(pos));
	return ret;
}
//分类文件并保存到相应的文件夹下
void classifyAndSaveFile(Classifier classifier, vector<string>& fileNames, string folderName) {
	vector<string> labels = classifier.getLabels();
	int n_labels = labels.size();
	int i = 0;
	for (i = 0; i < n_labels; i++) { 
		string newPath = "md " + folderName + "\\" + labels[i];
		system(newPath.c_str());
	}
	for (i = 0; i < fileNames.size(); i++) {
		cv::Mat img = cv::imread(fileNames[i], -1);
		if (img.empty()) continue;
		std::vector<Prediction> predictions = classifier.Classify(img);
		Prediction p = predictions[0];
		int pos = fileNames[i].find_last_of("\\");
		for (int j = 0; j < n_labels; j++) {
			if (!p.first.compare(labels[j])) {
				cv::imwrite(folderName + "\\" + labels[j] + "\\" + fileNames[i].substr(pos + 1), img);
			}
		}
	}
}
//测试在特定数据集下的分类精度
double classifyAndCalAccuracy(Classifier classifier, vector<string>& fileNames) {
	vector<string> labels = classifier.getLabels();
	int n_labels = labels.size();
	int n_files = fileNames.size();
	int count = 0;
	for (int i = 0; i < n_files; i++) {
		cv::Mat img = cv::imread(fileNames[i], -1);
		if (img.empty()) continue;
		std::vector<Prediction> predictions = classifier.Classify(img);
		Prediction p = predictions[0];
		vector<string> strs = split2(fileNames[i], "A.");
		string age = strs[1];
		if (!age.compare(p.first)) count++;
	
	}
	double accuracy = (double)count / n_files;
	return accuracy;
}

//字符串分割函数
vector<string> split(string str, string pattern)
{
	vector<string> ret;
	if (pattern.empty()) return ret;
	size_t start = 0, index = str.find_first_of(pattern, 0);
	while (index != str.npos)
	{
		if (start != index)
			ret.push_back(str.substr(start, index - start));
		start = index + 1;
		index = str.find_first_of(pattern, start);
	}
	if (!str.substr(start).empty())
		ret.push_back(str.substr(start));
	return ret;
}

//从文件名字符串中获取对象年龄
string getAgeGroup(string fileName) {
	vector<string> strs = split2(fileName, "A.");
	int age = stoi(strs[1]);
	string pos;
	if (age <= 3)  pos = "0-2";
	else if (age <= 7) pos = "4-6";
	else if (age <= 14) pos = "8-12";
	else if (age <= 24) pos = "15-20";
	else if (age <= 37) pos = "25-32";
	else if (age <= 47) pos = "38-43";
	else if (age <= 59) pos = "48-53";
	else pos = "60-100";
	return pos;
}