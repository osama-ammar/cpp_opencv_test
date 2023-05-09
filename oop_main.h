
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;  // to avoid using this cv::imread(...) every line we use
using namespace std; // to avoid using this std::cout  every line we use

// defining a function that open , process , make output image
void image_process(string image_path, string new_name, string processnig_type)

{
    // Read the image file
    // this image will bw a Mat object .. and will be accept Mat operations

    Mat image = imread(image_path);

    // Mat image(600, 800, CV_8UC3, Scalar(100, 250, 30)); // to make an image yourself

    // Check for failure
    if (image.empty())
    {
        cout << "Could not open or find the image" << endl;
        cin.get(); // wait for any key press
    }

    Mat output_image;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // processing activities

    if (processnig_type == "normal")
    {
        erode(image, output_image, getStructuringElement(MORPH_RECT, Size(5, 5)));

        // image.convertTo(output_image, -1, 1, 100); //increase the brightness by 50

        // image.convertTo(output_image, -1, 2, 0); //increase the contrast by *2

        // homogenius Blur the image with 3x3 kernel
        // blur(image, output_image, Size(5, 5));

        // gaussian  Blur the image with 3x3 kernel , The standard deviation in the X direction and the Y direction of the Gaussian distribution will be calculated based on the size of the kernel.
        // GaussianBlur(image, output_image, Size(5, 5),0);

        // Erode the image with 3x3 kernel (each pixel value of the resultant image is calculated as the minimum value of the neighborhood)
        // erode(image, output_image, getStructuringElement(MORPH_RECT, Size(5, 5)));

        // dilate the image with 3x3 kernel (each pixel value of the resultant image is calculated as the max value of the neighborhood)
        // dilate(image, output_image,0,2) ;

        /////////////////////////////////////////////////////////////////////////////////////////////////

        bool saved_processed = imwrite("D:/Code_store/cpp_opencv_test/image_function.png", output_image);
    };

    if (processnig_type == "hist_grey")
    {

        // equalizing  grey image histogram
        Mat output_image;
        cvtColor(image, output_image, COLOR_BGR2GRAY); // change the color image to grayscale image
        // equalize the histogram
        Mat hist_equalized_image;
        equalizeHist(output_image, hist_equalized_image);

        bool hist_bool = imwrite("D:/Code_store/cpp_opencv_test/modified_grey_histogram.png", hist_equalized_image); // write the image to a file as JPEG
    };

    if (processnig_type == "hist_color")
    {

        // eqalize color image
        // Convert the image from BGR to YCrCb color space
        // In this color space, Y channel only contains intensity information while Cr and Cb channels contain color information.
        // Therefore only the Y channel needs to be processed in order to equalize the histogram.

        cvtColor(image, output_image, COLOR_BGR2YCrCb);
        // Split the image into 3 channels; Y, Cr and Cb channels respectively and store it in a std::vector
        vector<Mat> vec_channels;
        split(output_image, vec_channels);

        // Equalize the histogram of only the Y channel
        equalizeHist(vec_channels[0], vec_channels[0]);

        // Merge 3 channels in the vector to form the color image in YCrCB color space.
        merge(vec_channels, output_image);

        // Convert the histogram equalized image from YCrCb to BGR color space again
        cvtColor(output_image, output_image, COLOR_YCrCb2BGR);

        bool color_equalized_image_bool = imwrite("D:/Code_store/cpp_opencv_test/modified_grey_histogram.png", output_image); // write the image to a file as JPEG
    };
};




//a function to rotate image
void  rotate_image(Mat image, int angle) 
{

    // get the center coordinates of the image to create the 2D rotation matrix
    Point2f center((image.cols - 1) / 2.0, (image.rows - 1) / 2.0);

    // using getRotationMatrix2D() to get the rotation matrix
    Mat rotation_matix = getRotationMatrix2D(center, angle, 1.0);

    Mat Rotaed_image;

    // rotate the image using warpAffine
    warpAffine(image, image, rotation_matix, image.size());

    //imshow("Rotated image", Rotaed_image);
    // wait indefinitely, press any key on keyboard to exit
    waitKey(0);




};

void detect_contour(Mat image){

    // convert the image to grayscale format
    Mat img_gray;
    cvtColor(image, image, COLOR_BGR2GRAY);

    // apply binary thresholding
    Mat thresh;
    threshold(image, thresh, 150, 255, THRESH_BINARY);
    imwrite("D:/Code_store/cpp_opencv_test/thresholded.jpg", thresh);


    // detect the contours on the binary image using cv2.CHAIN_APPROX_NONE
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(thresh, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    
    // draw contours on the original image
    Mat image_copy = image.clone();
    drawContours(image_copy, contours, -1, Scalar(0, 255, 0), 2);
    imwrite("D:/Code_store/cpp_opencv_test/contours_none_image1.jpg", image_copy);






}





