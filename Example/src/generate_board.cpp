#include <opencv2/aruco.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;

int main(int argc, char *argv[])
{
    // parse command line arguments
    int num_rows = atoi(argv[1]);
    int num_cols = atoi(argv[2]);
    std::string dict_name = argv[3];
    int marker_size = atoi(argv[4]);
    int marker_sep = atoi(argv[5]);
    std::string file_name = argv[6];

    // create ArUco dictionary
    cv::Ptr<cv::aruco::Dictionary> dict = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);


    // create board
    Ptr<aruco::GridBoard> board = aruco::GridBoard::create(num_cols, num_rows, float(marker_size), float(marker_sep), dict);

    // draw board and save to file
    Mat img;
    board->draw(Size(1920, 1080), img, 0, 1);
    imwrite(file_name, img);

    return 0;
}
