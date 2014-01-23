#include <vector>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

class LandmarkLBP{
	public:
		LandmarkLBP(int cellSize, int patchSize);
		Mat norm(string img_path, vector<float> bbox, vector<float>& landmarks);
		float* encode(Mat normMat, vector<float> landmarks);

	private:
		int cellSize;
		int patchSize;
};