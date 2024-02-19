// HiGuiDemo.cpp : Defines the entry point for the application.
//

#include "HiGuiDemo.h"
//#include <opencv2/opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iostream>

cv::Mat3b canvas;
cv::Mat3b img;
std::string buttonText("Click me!");
std::string aboutButtonText("About");
std::string winName = "OpenCV HiGUI Demo";
cv::Rect button;
cv::Rect aboutButton;
int sliderValue = 0;


void draw()
{
    button = cv::Rect(0, 0, img.cols, 50);
    aboutButton = cv::Rect(0, 50, img.cols, 50);

    canvas = cv::Mat3b(img.rows + button.height + aboutButton.height + 40, img.cols, cv::Vec3b(0, 0, 0));

    canvas(button) = cv::Vec3b(200, 200, 200);
    cv::putText(canvas(button), buttonText, cv::Point(button.width * 0.35, button.height * 0.7),
        cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 0, 0));

    canvas(aboutButton) = cv::Vec3b(200, 200, 200);
    cv::putText(canvas(aboutButton), aboutButtonText, cv::Point(aboutButton.width * 0.35, aboutButton.height * 0.7),
        cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 0, 0));

    img.copyTo(canvas(cv::Rect(0, button.height + aboutButton.height, img.cols, img.rows)));
}

void aboutPopup() {
    cv::Mat aboutWindow(200, 400, CV_8UC3, cv::Scalar(255, 255, 255));
    cv::putText(aboutWindow, "HiGUI Demo", cv::Point(20, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 0), 2);
    cv::putText(aboutWindow, "Created using OpenCV HighGui", cv::Point(20, 100), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 0, 0), 1);
    cv::putText(aboutWindow, "Author: Roy Burgess", cv::Point(20, 150), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 0, 0), 1);
    cv::imshow("About", aboutWindow);
}

void buttonCallback(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        if (button.contains(cv::Point(x, y))) {
            std::cout << "Button Clicked!" << std::endl;
            cv::rectangle(canvas(button), button, cv::Scalar(0, 0, 255), 2);
        }
        else if (aboutButton.contains(cv::Point(x, y)))
        {
            aboutPopup();
        }
    }
    if (event == cv::EVENT_LBUTTONUP) {
        cv::rectangle(canvas, button, cv::Scalar(200, 200, 200), 2);
    }
    cv::imshow(winName, canvas);
}

void sliderCallback(int value, void* userdata) {
    sliderValue = value;

    // Redraw the canvast to prevent text being garbled.
    draw();
    cv::putText(canvas(cv::Rect(0, button.height + aboutButton.height + 10, canvas.cols, 30)), "Slider Value: " + std::to_string(sliderValue),
        cv::Point(10, 30), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255));
    imshow(winName, canvas);
}

int main() {
    img = cv::Mat3b(600, 800, cv::Vec3b(255, 0, 0));

    draw();

    cv::namedWindow(winName);
    cv::setMouseCallback(winName, buttonCallback);

    cv::createTrackbar("Slider", winName, &sliderValue, 100, sliderCallback);

    cv::imshow(winName, canvas);
    cv::waitKey();

    cv::destroyAllWindows();

    return 0;
}
