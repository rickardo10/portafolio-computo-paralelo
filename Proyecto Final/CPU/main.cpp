#include <iostream>
#include <time.h> 
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "omp.h"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;


void harrisCorners( Mat mat, int window_size );

int main( int argc, char *argv[] ){
    // open the default camera
	VideoCapture cap(0); 

    // Checks if the camera is ready
	if( !cap.isOpened() ){
		cout << "The camera is not ready" << endl;
		return -1;
	}

    int h, w;
    Mat img_object;
    double t_time;
    double t_fps;
    // Checks if the WEIGHT and HEIGHT are set
    if( argc < 3 ){
        cout << "Warning: The frame size was not set. 1280x720 set by default." << endl;
        w = 640;
        h = 480;
        img_object = imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE );
    } else{
        w = atoi( argv[1] );
        h = atoi( argv[2] );
        img_object = imread( argv[3], CV_LOAD_IMAGE_GRAYSCALE );
        if( argc < 1 ){
            cout << "Error: Object is missing" << endl;
            cout << "Parameters: [weight] [height] [object image]" << endl;
        }
    }

    // Sets the video size
    cap.set(CV_CAP_PROP_FRAME_WIDTH, w);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, h);
    
    // Prints the frame size
    cout << "The Frame width is: " << cap.get(CV_CAP_PROP_FRAME_WIDTH) << endl;
    cout << "The Frame height is: " << cap.get(CV_CAP_PROP_FRAME_HEIGHT) << endl;

    // Creates a Window to display the mat
	namedWindow("Gray",1);

    // FPS counter variables 
    time_t start, end;
    int counter = 0;
    double sec;
    double fps;

    //-----------------------------------------------------
    //- Image Process
    //-----------------------------------------------------
    
    //-- Detect keypoints using SURF Detector
    int minHessian = 400;
    SurfFeatureDetector detector( minHessian );
    vector<KeyPoint> keypoints_object;
    detector.detect( img_object, keypoints_object );
    
    //-- Calculate descriptors
    SurfDescriptorExtractor extractor;
    Mat descriptors_object;
    extractor.compute( img_object, keypoints_object, descriptors_object );

    //-----------------------------------------------------
    //- Ends Image process
    //-----------------------------------------------------

    // Video Frames
	for(;;){
        // fps counter begin
        double s = omp_get_wtime();
        if (counter == 0){
            time(&start);
        }

        // Creates a frame
		Mat frame, gray;
		cap >> frame; 

        //-----------------------------------------------------
        //- Image Process
        //-----------------------------------------------------

        //-- Detect keypoints using SURF Detector
        cvtColor(frame, gray, CV_BGR2GRAY);
        vector<KeyPoint> keypoints_scene;
        detector.detect( gray, keypoints_scene ); 

        //-- Calculate descriptors
        Mat descriptors_scene;
        extractor.compute( gray, keypoints_scene, descriptors_scene );

        //-- Matching descriptor vectors using FLANN matcher
        FlannBasedMatcher matcher;
        vector<DMatch> matches;
        matcher.match( descriptors_object, descriptors_scene, matches );

        double min_dist = 100, max_dist = 0;

        //-- Delete outliers
        for( int i = 0; i < descriptors_object.rows; i++ ){
            double dist = matches[i].distance;
            if( dist < min_dist ) min_dist = dist;
            if( dist > max_dist ) max_dist = dist;
        }
    
        //-- Draw "good" matches
        vector<DMatch> good_matches;

        for( int i = 0; i < descriptors_object.rows; i++ ){
            if( matches[i].distance < 3 * min_dist ){
                good_matches.push_back( matches[i] );
            }
        }

        //-- Localize the object
        vector<Point2f> obj;
        vector<Point2f> scene;

        for( unsigned int i = 0; i < good_matches.size(); i++ ){
            obj.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );
            scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );
        }

        Mat H;
        try{
            H = findHomography( obj, scene, CV_RANSAC );
        } catch(Exception e){
            continue;
        }

        //-- Get the corners from the image_1 ( the object to be "detected" )
        vector<Point2f> obj_corners(4);
        obj_corners[0] = cvPoint(0,0); 
        obj_corners[1] = cvPoint( img_object.cols, 0 );
        obj_corners[2] = cvPoint( img_object.cols, img_object.rows ); 
        obj_corners[3] = cvPoint( 0,   img_object.rows );

        vector<Point2f> scene_corners(4);

        perspectiveTransform( obj_corners, scene_corners, H);

        //-- Draw lines between the corners (the mapped object in the scene - image_2 )
        line( frame, scene_corners[0], scene_corners[1], Scalar( 0, 255, 0), 4 );
        line( frame, scene_corners[1], scene_corners[2], Scalar( 0, 255, 0), 4 );
        line( frame, scene_corners[2], scene_corners[3], Scalar( 0, 255, 0), 4 );
        line( frame, scene_corners[3], scene_corners[0], Scalar( 0, 255, 0), 4 );

        //-----------------------------------------------------
        //- Ends Image process
        //-----------------------------------------------------
        

        // FPS counter calculation 
        time(&end);
        counter++;
        sec = difftime(end, start);
        fps = counter/sec;
        double diff = omp_get_wtime() - s;
        t_time += diff;
        if( fps < 50 )
            t_fps += fps;

        // Creates a string for FPS
        stringstream sstm;
        sstm << "FPS: " << round(fps);
        const string str_fps  = sstm.str();

        // Writes the FPS in the frame
        putText( frame, str_fps, Point(10,30), 
            CV_FONT_NORMAL, 1, Scalar(255,255,255), 1,1);

        // Shows the frame
		imshow("Characteristic points", frame );

        // overflow protection
        if (counter == (INT_MAX - 1000))
            counter = 0;

        // Wait for key for exit
		if(waitKey(30) >= 0){
            cap.release();
 			break;
		}
	} // Ends Video frames
    
    cout << "Mean time: " << t_time / counter << " ms" << endl;
    cout << "Mean FPS: " << t_fps / counter << endl;

	return 0;
}

void harrisCorners( Mat mat, int window_size ){
    // Checks if the window satisfies the restrictions
    if( window_size > 3 && ( window_size - 1 ) % 2 != 0 ){
        cout << "The window_size must be greater than 3 and impair" << endl;
        exit(EXIT_FAILURE);
    }
    
    Mat gray;
    //turns the image in gray scale
	cvtColor(mat, gray, CV_BGR2GRAY);
    // Creates a matrix with the harris values
    int harris[gray.cols][gray.rows];
    int I = 0, I_shifted = 0;
    int max = 0;
    // Iterates over the matrix
   
    // Loops over the matrx
    for( int i = window_size; i < gray.cols - window_size; i++ ){
        for( int j = window_size; j < gray.rows - window_size; j++ ){
            harris[i][j] = 0;
            I = gray.at<unsigned char>( Point(i,j) );

            // Loops over the submatrix
            for( int k = i - window_size / 2; k <= i + window_size / 2; k++ ){  
                for( int l = j - window_size / 2; l <= j + window_size / 2; l++ ){ 
                    I_shifted = gray.at<unsigned char>( Point(k,l) );
                    harris[i][j] += pow( I_shifted - I, 2 );
                } // next l
            } // next k
            
            if( harris[i][j] > max ){
                max = harris[i][j];
            }
        } //next j
    }
    
    for( int i = window_size; i < mat.cols - window_size; i++ ){
        for( int j = window_size; j < mat.rows - window_size; j++ ){
            if( harris[i][j] > 0.6 * max ){
                rectangle( mat, Point(i-2, j-2), Point(i+2, j+2), 
                           Scalar(0, 255, 0) ); 
            }
        }
    }

}


