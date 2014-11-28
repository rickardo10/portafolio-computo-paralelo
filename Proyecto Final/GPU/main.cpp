#include <iostream>
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/gpu/gpu.hpp"
#include "opencv2/nonfree/gpu.hpp"

using namespace std;
using namespace cv;

int main( int argc, char** argv )
{
    Mat img_template_cpu = imread( argv[1],IMREAD_GRAYSCALE);
    gpu::GpuMat img_template;
    img_template.upload(img_template_cpu);

    //Detect keypoints and compute descriptors of the template
    gpu::SURF_GPU surf;
    gpu::GpuMat keypoints_template, descriptors_template;

    surf(img_template,gpu::GpuMat(),keypoints_template,       descriptors_template);

    //Matcher variables
    gpu::BFMatcher_GPU matcher(NORM_L2);   

    //VideoCapture from the webcam
    gpu::GpuMat img_frame;
    gpu::GpuMat img_frame_gray;
    Mat img_frame_aux;
    VideoCapture cap;
    cap.open(0);
    if (!cap.isOpened()){
        cerr << "cannot open camera" << endl;
        return -1;
    }
    int nFrames = 0;
    uint64 totalTime = 0;
    //main loop
    for(;;){
        int64 start = getTickCount();
        cap >> img_frame_aux;
        if (img_frame_aux.empty())
            break;
        img_frame.upload(img_frame_aux);
        cvtColor(img_frame,img_frame_gray, CV_BGR2GRAY);

        //Step 1: Detect keypoints and compute descriptors
        gpu::GpuMat keypoints_frame, descriptors_frame;
        surf(img_frame_gray,gpu::GpuMat(),keypoints_frame, descriptors_frame);

        //Step 2: Match descriptors
        vector< vector<DMatch> >matches;
        matcher.knnMatch(descriptors_template,descriptors_frame,matches,2);

        //Step 3: Filter results
        vector<DMatch> good_matches;
        float ratioT = 0.7;
        for(int i = 0; i < (int) matches.size(); i++)
        {
            if((matches[i][0].distance < ratioT*(matches[i][1].distance)) && ((int) matches[i].size()<=2 && (int) matches[i].size()>0))
            {
                good_matches.push_back(matches[i][0]);
            }
        }
        // Step 4: Download results
        vector<KeyPoint> keypoints1, keypoints2;
        vector<float> descriptors1, descriptors2;
        surf.downloadKeypoints(keypoints_template, keypoints1);
        surf.downloadKeypoints(keypoints_frame, keypoints2);
        surf.downloadDescriptors(descriptors_template, descriptors1);
        surf.downloadDescriptors(descriptors_frame, descriptors2);

        //-- Localize the object
        vector<Point2f> obj;
        vector<Point2f> scene;

        for( unsigned int i = 0; i < good_matches.size(); i++ ){
            obj.push_back( keypoints1[ good_matches[i].queryIdx ].pt );
            scene.push_back( keypoints2[ good_matches[i].trainIdx ].pt );
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
        obj_corners[1] = cvPoint( img_template_cpu.cols, 0 );
        obj_corners[2] = cvPoint( img_template_cpu.cols, img_template_cpu.rows ); 
        obj_corners[3] = cvPoint( 0,   img_template_cpu.rows );

        vector<Point2f> scene_corners(4);

        perspectiveTransform( obj_corners, scene_corners, H);

        //-- Draw lines between the corners (the mapped object in the scene - image_2 )
        line( img_frame_aux, scene_corners[0], scene_corners[1], Scalar( 0, 255, 0), 4 );
        line( img_frame_aux, scene_corners[1], scene_corners[2], Scalar( 0, 255, 0), 4 );
        line( img_frame_aux, scene_corners[2], scene_corners[3], Scalar( 0, 255, 0), 4 );
        line( img_frame_aux, scene_corners[3], scene_corners[0], Scalar( 0, 255, 0), 4 );



        //Draw the results
		/*
        Mat img_result_matches;
        drawMatches(img_template_cpu, keypoints1, img_frame_aux, keypoints2, good_matches, img_result_matches);
		*/

        int64 time_elapsed = getTickCount() - start;
        double fps = getTickFrequency() / time_elapsed;
        totalTime += time_elapsed;
        nFrames++;

        // Creates a string for FPS
        stringstream sstm;
        sstm << "FPS: " << round(fps);
        const string str_fps  = sstm.str();

        // Writes the FPS in the frame
        putText( img_frame_aux, str_fps, Point(10,30), 
            CV_FONT_NORMAL, 1, Scalar(255,255,255), 1,1);

        imshow("Matching a template", img_frame_aux);

        if( waitKey(30) >= 0 ){
			cap.release();
			break;
		}
   
    }
    double meanFps = getTickFrequency() / (totalTime / nFrames);
    cout << "Mean FPS: " << meanFps << endl;

    return 0;
}
