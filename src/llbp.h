#include <vector>
#include <string>
class LandmarkLBP{
	public:
		LandmarkLBP(int cellSize, int patchSize);
		float* detect(string img, vector<double> landmarks);
	private:
		int cellSize;
		int patchSize;
	};