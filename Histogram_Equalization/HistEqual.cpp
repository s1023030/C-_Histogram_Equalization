#include<opencv2\opencv.hpp>
#include<vector>
#include<cstring>
#include<string>
using namespace std;
using namespace cv;
int main(int argc, char *argv[]) {
	Mat src = imread(argv[1], 1);//讀檔
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
	cvtColor(src, ycrcb, CV_BGR2YCrCb);//從RGB轉換成YCrCb
	vector<Mat>channels;
	Mat Y;
	split(ycrcb, channels);//將ycrcb分成3個Mat
	equalizeHist(channels[0], Y);//對Y做直方圖等化
	vector<Mat> combined;
	combined.push_back(Y);
	combined.push_back(channels[1]);
	combined.push_back(channels[2]);
	merge(combined, ycrcb);//將channels合併成一個Mat
	Mat result;
	cvtColor(ycrcb, result, CV_YCrCb2BGR);//從YCrCb轉換成RGB

	string OutName = string(name);
	string OutNameExtension = string(nameExtension);
	OutName = OutName + "_out." + OutNameExtension;
	imwrite(OutName.c_str(), result);//寫檔
	return 0;
}