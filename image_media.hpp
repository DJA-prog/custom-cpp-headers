#include <string>
#include <opencv2/opencv.hpp>

bool isImageComplete(const std::string &imagePath)
{
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_UNCHANGED);

    if (image.empty())
    {
        // Failed to load the image
        return false;
    }

    // Check if the image has any blank (white) pixels
    cv::Mat whitePixels;
    cv::inRange(image, cv::Scalar(255, 255, 255), cv::Scalar(255, 255, 255), whitePixels);
    double totalWhitePixels = cv::countNonZero(whitePixels);

    // Calculate the percentage of white pixels in the image
    double imageCompleteness = (totalWhitePixels / (image.rows * image.cols)) * 100.0;

    // Set a threshold value to determine if the image is complete or not
    double completenessThreshold = 10.0; // Adjust this value as per your requirement

    return imageCompleteness < completenessThreshold;
}

/*
int main()
{
    std::string imagePath = "path_to_your_image.jpg"; // Replace with your image path

    if (isImageComplete(imagePath))
    {
        std::cout << "Image is complete." << std::endl;
    }
    else
    {
        std::cout << "Image is not complete." << std::endl;
    }

    return 0;
}
*/