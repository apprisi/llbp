#include "llbp.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;
#define NUM_LANDMARKS 83
int main(){
	ifstream fin;
	fin.open("model/dev.txt");
	if (fin.fail()){
		cout<<"fail to open model file"<<endl;
	}
	
	char line[5000];
	//start with the forth line
	fin.getline(line,5000);
	fin.getline(line,5000);
	fin.getline(line,5000);
	fin.getline(line,5000);
	cout<<"before strtok"<<endl;
	char *tok;
	tok = strtok(line, "\t");
	string img_path(tok);
	cout<<"img: "<<img_path<<endl;
	vector<float> bbox;
	for (int i = 0; i < 4; i++){
		tok = strtok(NULL, "\t");
		cout<<"bbox "<<i<<" "<<tok<<endl;
		bbox.push_back(atof(tok));
	}
	vector<float> landmarks;
	for (int i = 0; i < NUM_LANDMARKS * 2; i++){
		tok = strtok(NULL, "\t");
		landmarks.push_back(atof(tok));
		cout<<"landmark "<<landmarks.size()<<" "<<tok<<endl;
	}
	
	cout<<"Bounding box: "<<bbox[0]<<" "<<bbox[1]<<" "<<bbox[2]<<" "<<bbox[3]<<endl;
	cout<<"Num landmarks: "<<landmarks.size()<<endl;
	LandmarkLBP detector(2,10);
	Mat face = detector.norm(img_path, bbox, landmarks);
	detector.encode(face, landmarks);
	return 0;
	
}