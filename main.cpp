#include "classification.hpp"
#include "FileOperation.h"
#include <ctime>
#include <cmath>
#include <thread>
string path = "E:\\deepLearningProject\\mini-caffe-example\\file_IMDB_WIKI\\";
string model_file = path + "age.prototxt";
string trained_file = path + "dex_chalearn_iccv2015.caffemodel";
string mean_file = "";
string label_file = path + "labels_age.txt";

int sum_error = 0;
using namespace std;
void calculate_MAE(vector<string> fileNames, Classifier classifier) {
	int n_fileNames = fileNames.size();
	for (int i = 0; i < n_fileNames; i++) {
		//打印图片名
		cout << fileNames[i] << "\t";

		//分割图片标签得到实际年龄for morph
		vector<string> strs = split2(fileNames[i], "A.");
		int realage = stoi(strs[1]);
		cout << "实际年龄:" << realage << "\t";
		
		////分割图片标签得到实际年龄for imdb
		//vector<string> strs = split2(fileNames[i], "_-.");
		//int realage = stoi(strs[7]) - stoi(strs[4]);
		//cout << "实际年龄:" << realage << "\t";

		//读取图片得到预测年龄
		cv::Mat img = cv::imread(fileNames[i], -1);
		if (img.empty()) continue;
		clock_t t;
		t = clock();
		std::vector<Prediction> predictions = classifier.Classify(img);
		t = clock() - t;
		Prediction p = predictions[0];
		cout << "预测年龄:" << p.first << "\t";


		//int error = abs(stoi(strs[1]) - stoi(p.first));
		int error = abs(realage - stoi(p.first));
		cout << "预测偏差:" << error << "\t runtime:" << (float)t / CLOCKS_PER_SEC << endl;
		sum_error += error;
	}
}
vector<vector<string>> divideVector(vector<string> fileNames, int n) {
	int num = fileNames.size();
	vector<vector<string>> result;
	for (int i = 0; i < n; i++) {
		vector<string> files;
		for (int j = 0; j * n + i < num ; j++) {
			files.push_back(fileNames[i + j * n ]);
		}
		result.push_back(files);
	}
	return result;
}
int main(int argc, char** argv) {

	Classifier classifier(model_file, trained_file, label_file);

	
	//选定测试数据文件夹，并将其中所有测试文件名获取
	string filePath = "E:\\dataset\\FG-net4";
	vector<string> fileNames;
	getFiles(filePath, fileNames);

	//输出总的测试数据量
	cout << "test nums :" << fileNames.size() << endl;
	//vector<vector<string>> files = divideVector(fileNames, 3);

	//测试本模型在FG-net数据集下的年龄准确率
	thread t1(calculate_MAE, fileNames, classifier);
	//thread t2(calculate_MAE, fileNames2, classifier);
	//thread t3(calculate_MAE, fileNames2, classifier);

	clock_t t;
	t = clock();
	t1.join();
	//t2.join();
	t = clock() - t;
	cout << "it takes " << (float)t / CLOCKS_PER_SEC << "s" << endl;
	float mae = (float) sum_error / fileNames.size();
	cout << "mae = " << mae << endl;
	system("pause");
	return 0;
}


