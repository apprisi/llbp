#include "llbp.h"
#include <iostream>
#include <vl/lbp.h>
#define PI 3.14159265

Mat rotateImage(const Mat& source, double angle)
{
    Point2f src_center(source.cols/2.0F, source.rows/2.0F);
    Mat rot_mat = getRotationMatrix2D(src_center, angle, 1.0);
    Mat dst;
    warpAffine(source, dst, rot_mat, source.size());
    return dst;
}

LandmarkLBP::LandmarkLBP(int cellSize, int patchSize){
	this->cellSize = cellSize;
	this->patchSize = patchSize;
}

Mat LandmarkLBP::norm(string img_path, vector<float> bbox, vector<float>& landmarks){
	//calculate bounding box
	Mat img = imread(img_path, CV_LOAD_IMAGE_COLOR);
	for (int i = 0; i < landmarks.size(); i++){
		if (landmarks[i]/100*img.cols - patchSize/2 - 1< bbox[0]){
			cout<<"landmark x: "<<landmarks[i]/100*img.cols<<endl;
			bbox[2] = bbox[2] + (bbox[0] - landmarks[i]/100*img.cols) + patchSize/2 + 1;
			bbox[0] = landmarks[i]/100*img.cols - patchSize/2 - 1;
			cout<<"x: "<<bbox[0]<<" "<<" width: "<<bbox[2]<<endl;
		}	
		if (landmarks[i]/100*img.cols + patchSize/2 + 1 > bbox[0] + bbox[2]){
			cout<<"landmark x: "<<landmarks[i]/100*img.cols<<endl;
			bbox[2] = landmarks[i]/100*img.cols + patchSize/2 + 1 - bbox[0];
			cout<<"x: "<<bbox[0]<<" "<<" width: "<<bbox[2]<<endl;
		}
		if (landmarks[i+1]/100*img.rows - patchSize/2 - 1 < bbox[1]){
			bbox[3] = bbox[3] + (bbox[1] - landmarks[i+1]/100*img.rows) + patchSize/2 + 1;
			bbox[1] = landmarks[i+1]/100*img.rows - patchSize/2 - 1;
			
		}
		if (landmarks[i+1]/100*img.rows + patchSize/2 + 1> bbox[1] + bbox[3]){
			cout<<"landmark y: "<<landmarks[i+1]/100*img.rows<<endl;
			bbox[3] = landmarks[i+1]/100*img.rows - bbox[1] + patchSize/2 + 1;
			cout<<"y: "<<bbox[1]<<" "<<" height: "<<bbox[3]<<endl;
		}
		i++;
	}
	cout<<"bounding box: "<<bbox[0]<<" "<<bbox[1]<<" "<<bbox[2]<<" "<<bbox[3]<<endl;

	
	Mat resized;
	Mat roi(img, Rect(bbox[0],bbox[1],bbox[2],bbox[3]));
	resize(roi, resized, Size(100, 100));
	for (unsigned int i = 0; i < landmarks.size(); i++){
		landmarks[i] = (landmarks[i]/100*img.cols - bbox[0])/bbox[2]*100;
		landmarks[i+1] = (landmarks[i+1]/100*img.rows - bbox[1])/bbox[3]*100;
		circle(resized, Point(landmarks[i], landmarks[i+1]), 2, Scalar(255,0,0));
		i++;
	}
	
	Mat rotated = rotateImage(resized, -7.2842);
	imwrite( "./tmp/face.jpg" , rotated );
	return resized;
}

float* LandmarkLBP::encode(	Mat img, vector<float> landmarks){
	//Mat img = imread(img_path, CV_LOAD_IMAGE_COLOR);
	VlLbp * lbp = vl_lbp_new (VlLbpUniform, VL_TRUE) ;
	int dimensionx = patchSize / cellSize;
	int dimensiony = patchSize / cellSize;
	int dimensionc = vl_lbp_get_dimension(lbp) ;
	
	//i = 48
	for (unsigned int i = 0; i < landmarks.size(); i++){
		if (landmarks[i] > patchSize/2 && landmarks[i+1] > patchSize/2 && landmarks[i] + patchSize/2 < 100 && landmarks[i+1] + patchSize/2 < 100){
			Mat roi(img, Rect(landmarks[i] - patchSize/2, landmarks[i+1]-patchSize/2, patchSize, patchSize));
			i++;
			vector<float> data;
			for (int j = 0; j < roi.cols; j++){
				for (int k = 0; k < roi.rows; k++){
						//printf("%f ", (float)resized.at<unsigned char>(i, j)/255);
						data.push_back((float)roi.at<unsigned char>(k, j)/255);
				}
			//cout<<endl;
			}
			if (lbp == NULL) {
			  cout<<"fail to init LBP detector"<<endl;
			  return NULL;
			}
			float* features = new float[dimensionx * dimensiony * dimensionc];
			vl_lbp_process(lbp, features, &data[0], patchSize, patchSize, cellSize);
			cout<<"feature "<<i/2<<" size: "<<dimensionx * dimensiony * dimensionc<<endl;
		}
		else{
			cout<<"Patch out of bound: "<<landmarks[i]<<" "<<landmarks[i+1]<<endl;
			i++;
		}
	}
	vl_lbp_delete(lbp);
	return NULL;
}