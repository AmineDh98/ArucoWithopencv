#include "opencv2/core/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
  if (argc < 2){
    std::cerr << "Usage: " << argv[0] << " <video source no.>" << std::endl;
    return -1;
  }

  cv::VideoCapture webCam(std::atoi(argv[1]));       // VideoCapture object declaration. Usually 0 is the integrated, 2 is the first external USB one

  if (webCam.isOpened() == false){   // Check if the VideoCapture object has been correctly associated to the webcam
    std::cerr << "error: Webcam could not be connected." << std::endl;
    return -1;
  }

  cv::Mat imgOriginal;    // input image
  cv::Mat imgGrayScale;   // grayscale image
  cv::Mat imgBlurred;     // blurred image
  cv::Mat imgCanny;       // edge image
  cv::Mat imgBinarized;   // binary image using simple thresholding
  cv::Mat imgAdaptiveBinarized; //binary image using adaptive thresholding




  char charCheckForESCKey{0};
  int lowTh{45};
  int highTh{90};
  int thresholdValue{128}; //initialthreshold value for simple thresholding
  int adaptiveBlockSize{11}; //initial block size for adaptive thresholding
  int adaptiveConstant{2}; //initial constant for adaptive thresholding

  while (charCheckForESCKey != 27 && webCam.isOpened()){    // loop until ESC key is pressed or webcam is lost
    bool frameSuccess = webCam.read(imgOriginal);           // get next frame from input stream

    if (!frameSuccess || imgOriginal.empty()){              // if the frame was not read or read wrongly
      std::cerr << "error: Frame could not be read." << std::endl;
      break;
    }

    cv::cvtColor(imgOriginal, imgGrayScale, cv::COLOR_BGR2GRAY);  // original video is converted to grayscale into imgGrayScale
    cv::GaussianBlur(imgGrayScale, imgBlurred, cv::Size(5, 5), 1.8);  // blurrs the grayscale video. Check OpenCV docs for explanation of parameters
    cv::Canny(imgBlurred, imgCanny, lowTh, highTh);   // Canny edge detection. Check OpenCV docs for explanation of parameters

    // Simple thresholding using all available thresholding types in OpenCV
    //cv::threshold(imgGrayScale, imgBinarized, thresholdValue, 255, cv::THRESH_BINARY);
    //cv::threshold(imgGrayScale, imgBinarized, thresholdValue, 255, cv::THRESH_BINARY_INV);
    //cv::threshold(imgGrayScale, imgBinarized, thresholdValue, 255, cv::THRESH_TRUNC);
    //cv::threshold(imgGrayScale, imgBinarized, thresholdValue, 255, cv::THRESH_TOZERO);
    cv::threshold(imgGrayScale, imgBinarized, thresholdValue, 255, cv::THRESH_TOZERO_INV);

    // Adaptive thresholding
    cv::adaptiveThreshold(imgGrayScale, imgAdaptiveBinarized, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, adaptiveBlockSize, adaptiveConstant);

    // Declaration of windows for output video results. Check OpenCV docs for explanation of parameters
    cv::namedWindow("imgOriginal", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("imgCanny", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("imgBinarized", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("imgAdaptiveThreshold", cv::WINDOW_AUTOSIZE);

    // Declaration of trackbars to change thresholds. Check OpenCV docs for explanation of parameters
    cv::createTrackbar("LowTh", "imgCanny", &lowTh, 100);
    cv::createTrackbar("HighTh", "imgCanny", &highTh, 100);

    // Show output video results windows
    cv::imshow("imgOriginal", imgOriginal);
    cv::imshow("imgCanny", imgCanny);
    cv::imshow("imgBinarized", imgBinarized);
    cv::imshow("imgAdaptiveThreshold", imgAdaptiveBinarized);

    charCheckForESCKey = cv::waitKey(1);  // gets the key pressed
  }
  return 0;
}
