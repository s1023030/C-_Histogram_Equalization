#include<opencv2\opencv.hpp>
#include<vector>
#include<cstring>
#include<string>
using namespace std;
using namespace cv;
int main(int argc, char *argv[]) {
	Mat src = imread(argv[1], 1);//Ū��
	const char *delim = ".";
	char *out = "_out";
	char *pch;
	char *name;
	char *nameExtension;
	char *p;
	pch = strtok_s(argv[1],delim, &p);
	name = pch;
	pch = strtok_s(NULL, delim, &p);
	nameExtension = pch;
	Mat ycrcb;
	cvtColor(src, ycrcb, CV_BGR2YCrCb);//�qRGB�ഫ��YCrCb
	vector<Mat>channels;
	Mat Y;
	split(ycrcb, channels);//�Nycrcb����3��Mat
	equalizeHist(channels[0], Y);//��Y������ϵ���
	vector<Mat> combined;
	combined.push_back(Y);
	combined.push_back(channels[1]);
	combined.push_back(channels[2]);
	merge(combined, ycrcb);//�Nchannels�X�֦��@��Mat
	Mat result;
	cvtColor(ycrcb, result, CV_YCrCb2BGR);//�qYCrCb�ഫ��RGB

	string OutName = string(name);
	string OutNameExtension = string(nameExtension);
	OutName = OutName + "_out." + OutNameExtension;
	imwrite(OutName.c_str(), result);//�g��
	return 0;
}