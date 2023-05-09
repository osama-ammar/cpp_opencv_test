#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "oop_main.h"


using namespace cv;  // to avoid using this cv::imread(...) every line we use
using namespace std; // to avoid using this std::cout  every line we use


/////////////////////////////////////////////////////////////////////////////////////////////////
// Mat image = imread("D:/cpp_opencv_test/opencv_training/xray.jpg");

static void onMouse(int event, int x, int y, int, void *imgptr)
{

    Point pt1 = Point(x, y);
    Mat &img = (*(Mat *)imgptr);

    if (event == EVENT_LBUTTONDOWN)
    {
        circle(img, pt1, 0, Scalar(244, 00, 0), 10, 8, 0);
        cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;

        // imshow ("The man", img);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////
// a callback function used to viwe mouse position of a window

void CallBackFunc(int event, int x, int y, int flags, void *userdata)
{

    if (event == EVENT_LBUTTONDOWN)
    {
        cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;

        // cv::drawMarker	( image , Point (x,y) ,Scalar(255, 100, 49) );
    }

    else if (event == EVENT_RBUTTONDOWN)
    {
        cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    }

    else if (event == EVENT_MBUTTONDOWN)
    {
        cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    }

    else if (event == EVENT_MOUSEMOVE)
    {
        cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
    }
}

//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{

    image_process("D:/Code_store/cpp_opencv_test/xray.jpg", "generated_image", "normal");

    /////////////////////////////////////////////////////////////////////////////////////////////////
    Mat image = imread("D:/Code_store/cpp_opencv_test/xray.jpg");

    detect_contour(image);


    // Create a window
    namedWindow("The man", WINDOW_NORMAL); // Create a window
                                           // Resize the Window
    resizeWindow("The man", 500, 700);

    // cv::drawMarker	( image , Point (100,100) ,Scalar(255, 100, 49),markerType=cv2.MARKER_CROSS );

    // set the callback function for any mouse event
    setMouseCallback("The man", onMouse, &image);

    // showingthe image in the defined window
    // imshow("The man", image); // Show our image inside the created window.

    ////////////////////////////////////////////////////////////////////////////////////////////////

    // Create track bar to rotate
    int iSliderRotate = 0;
    createTrackbar("Rotation", "The man", &iSliderRotate, 100);


    // Create track bar to change brightness
    int iSliderValue1 = 50;
    createTrackbar("Brightness", "The man", &iSliderValue1, 100);

    // Create track bar to change contrast
    int iSliderValue2 = 50;
    createTrackbar("Contrast", "The man", &iSliderValue2, 100);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    while (1 == 1)
    {
        // Change the brightness and contrast of the image

        Mat output;
        int iBrightness = iSliderValue1 - 50;
        double dContrast = iSliderValue2 / 50.0;
        int rotation=iSliderRotate;


        //rotate_image(image,iSliderRotate);
        image.convertTo(output, -1, dContrast, iBrightness);





        // show the brightness and contrast adjusted image
        imshow("The man", output);

        // Wait until user press some key for 50ms
        int iKey = waitKey(50);

        // if user press 'ESC' key
        if (iKey == 27)
        {
            break;
        }
    }

    ////////////////////////////////////////
    waitKey(0);          // Wait for any keystroke in the window
    destroyAllWindows(); // Destroy all opened windows

    return 0;
}
