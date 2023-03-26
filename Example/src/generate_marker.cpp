#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
  string dictionary = argv[1];   // ArUco dictionary name
  int id = stoi(argv[2]);        // ArUco marker id
  int size = stoi(argv[3]);      // ArUco marker size in pixels
  string filename = argv[4];     // Output filename

 // Get dictionary
Ptr<cv::aruco::Dictionary> dictionaryPtr = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_ARUCO_ORIGINAL);

// Generate marker image
Mat markerImage;
cv::aruco::drawMarker(dictionaryPtr, id, size, markerImage, 1);

  // Save marker image
  imwrite(filename, markerImage);

  return 0;
}
