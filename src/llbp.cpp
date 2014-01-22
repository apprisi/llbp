#include "llbp.h"
#include <iostream>
#include <vl/lbp.h>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;

LandmarkLBP::LandmarkLBP(int cellSize, int patchSize){
		this->cellSize = cellSize;
		this->patchSize = patchSize;
}

float* LandmarkLBP::detect(string img_path, vector<double> landmarks){
	Mat img = imread(img_path, CV_LOAD_IMAGE_COLOR);
	VlLbp * lbp = vl_lbp_new (VlLbpUniform, VL_TRUE) ;
	int dimensionx = patchSize / cellSize;
	int dimensiony = patchSize / cellSize;
	int dimensionc = vl_lbp_get_dimension(lbp) ;
	
	for (int i = 0; i < landmarks.size()/2; i++){
		Mat roi(img, Rect(landmarks[i] - patchSize/2, landmarks[i+1]-patchSize/2, patchSize, patchSize));
		/* get LBP object */
		
		if (lbp == NULL) {
		  vlmxError(vlmxErrAlloc, NULL) ;
		}
		float* features = new float[dimensionx * dimensiony * dimensionc];
		vl_lbp_process(lbp, features, roi, patchSize, patchSize, cellSize);
		cout<<"feature "<<i<<" size: "<<dimensionx * dimensiony * dimensionc<<endl;
	}
	vl_lbp_delete(lbp);
}