			
											#define HAVE_OPENCV_FLANN
											#define HAVE_OPENCV_IMGPROC
											#define HAVE_OPENCV_VIDEO
											#define HAVE_OPENCV_OBJDETECT
											#define HAVE_OPENCV_CALIB3D
											#define HAVE_OPENCV_ML
											#define HAVE_OPENCV_HIGHGUI
											#define HAVE_OPENCV_CONTRIB
											#define HAVE_OPENCV_PHOTO
											#define HAVE_OPENCV_FEATURES2D


											#include<opencv2/opencv.hpp>
											#include<opencv2/core/core_c.h>
											#include<opencv2/core/core.hpp>


											#include<iostream>

											# include "opencv2/core/core.hpp"
											# include "opencv2/features2d/features2d.hpp"
											# include "opencv2/highgui/highgui.hpp"
											# include "opencv2/calib3d/calib3d.hpp"
											# include "opencv2/nonfree/features2d.hpp"


											#include "opencv2/opencv_modules.hpp"

											using namespace std;
											using namespace cv;






//#include "wqueue.h"
//#include "thread.h"
//#include "imgframe.h"
#include <iostream>
#include <fstream>
#include<string>
#include <iomanip>

#include <opencv2/core/core.hpp>


#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui//highgui.hpp>

#include "dmtx.h"   ////////////////////////////////////////////////dmtx 

#include <cstdio>
#include <ctime>



#include<stdio.h>
#include<string.h>

#include<stdio.h>
#include<sys/time.h>
#include<unistd.h>

									











	int test_data_matrix_encode(string& str, Mat& mat)  
													    {  
														
													      
														DmtxEncode* enc = dmtxEncodeCreate();  
														assert(enc != NULL);  
														int ret = dmtxEncodeDataMatrix(enc, strlen(str.c_str()), (unsigned char*)str.c_str());  
														assert(ret == 1);  
													      
														int width = dmtxImageGetProp(enc->image, DmtxPropWidth);  
														int height = dmtxImageGetProp(enc->image, DmtxPropHeight);  
														int bytesPerPixel = dmtxImageGetProp(enc->image, DmtxPropBytesPerPixel);  
														fprintf(stderr, "image width: %d, image height: %d, channels: %d\n", width, height, bytesPerPixel);  
														assert(bytesPerPixel == 1 || bytesPerPixel == 3 || bytesPerPixel == 4);  
													      
														//cv::Mat mat;  
														if (bytesPerPixel == 1)  
														    mat = cv::Mat(height, width, CV_8UC1);  
														else if (bytesPerPixel == 3)  
														    mat = cv::Mat(height, width, CV_8UC3);  
														else  
														    mat = cv::Mat(height, width, CV_8UC4);  
													      
														mat.data = enc->image->pxl;  
													      
														std::string image_name = "encode.jpg";  
														cv::imwrite(image_name, mat);  
													      
														dmtxEncodeDestroy(&enc);  
													      
														return 0;  
													    }  





													      
			 int test_data_matrix_decode(cv::Mat& mat)  
													    {  
														 
														if (!mat.data) {  
														    fprintf(stderr, "read image error\n");  
														    return -1;  
														}  
													      
														int width = mat.cols;  
														int height = mat.rows;  
														int channels = mat.channels();  
													      

//img = dmtxImageCreate(chBuf_CurCut, window_a, window_a, DmtxPack8bppK);
														DmtxImage* img = dmtxImageCreate(mat.data, width, height, DmtxPack8bppK);  
														if (!img) {  
														    fprintf(stderr, "dmtx image create fail\n");  
														    return -1;  
														}  
													      
														DmtxDecode* dec = dmtxDecodeCreate(img, 1);  
														if (!dec) {  
														    fprintf(stderr, "dmtx decode create fail\n");  
														    return -1;  
														}  
													      
													      







														DmtxRegion* reg = dmtxRegionFindNext(dec, NULL);  
														if (!reg) {  
														    fprintf(stderr, "dmtx region fail\n");  
														    return -1;  
														}  



						      
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

/*
   DmtxMessage *msg_xiu;
   DmtxVector2 topLeft, topRight, bottomLeft, bottomRight;
   DmtxPixelLoc pxTopLeft, pxTopRight, pxBottomLeft, pxBottomRight;

   msg_xiu = dmtxMessageCreate(reg->sizeIdx, DmtxFormatMatrix);
   if(msg_xiu == NULL)
      return 0;

   if(PopulateArrayFromMatrix(dec, reg, msg_xiu) != DmtxPass) {
      dmtxMessageDestroy(&msg_xiu);
      return 0;
   }

	cout<<"msg_xiu.arraySize="<<msg_xiu->arraySize<<endl;

	
*/
//=====================measure time =========
struct timeval start_whole, end_whole;
gettimeofday( &start_whole, NULL );
printf("start_findnext : %d s  and %d us \n", start_whole.tv_sec, start_whole.tv_usec);


//=====================end of measure time ======



														DmtxMessage* msg = dmtxDecodeMatrixRegion(dec, reg, DmtxUndefined);



//=====================measure time =========

gettimeofday( &end_whole, NULL );
printf("end_findnext : %d.%d \n", end_whole.tv_sec, end_whole.tv_usec);


double delta_time=end_whole.tv_sec-start_whole.tv_sec+  (end_whole.tv_usec - start_whole.tv_usec)*0.000001;

cout<<"delta_time_findnext="<<delta_time<<endl;

//=====================end of measure time ======
							



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////

														  
														if (!msg) {  
														    fprintf(stderr, "dmtx decode matrix region fail\n");  
														    return -1;  
														}  
													      
														std::string str(reinterpret_cast<char*>(msg->output));  
														fprintf(stderr, "decode result: %s\n", str.c_str());  
													      
														dmtxMessageDestroy(&msg);  
														dmtxRegionDestroy(&reg);  
														dmtxDecodeDestroy(&dec);  
														dmtxImageDestroy(&img);  
													      
														return 0;  
													    }  











//**********************************************************************************************************************************


//**********************************************************************************************************************************


//**********************************************************************************************************************************

Mat raw_01s=(Mat_<uchar>(10,10)<<
  1, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 1, 0, 1, 1, 0, 1, 1, 0, 1,
  0, 0, 0, 1, 1, 0, 0, 1, 1, 1,
  0, 1, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 1, 0, 0, 1, 1, 1, 1, 1,
  0, 1, 0, 1, 0, 1, 1, 0, 1, 1,
  1, 1, 1, 1, 1, 0, 0, 0, 1, 1,
  1, 0, 1, 1, 1, 1, 1, 0, 0, 0,
  1, 1, 1, 0, 1, 1, 0, 0, 1, 1,
  0, 1, 1, 0, 1, 1, 1, 1, 1, 0);


void reorder(Mat& raw, uchar* zo)
{
	Mat temp(raw_01s.rows,raw_01s.rows,CV_8UC1, Scalar(0) );

	for(int i=0;i<raw.rows;i++)
		for(int j=0;j<raw.cols;j++)
		{
			if(raw.at<uchar>(i,j)==1)
				temp.at<uchar>(10-1-i,j)=16;
			else
				temp.at<uchar>(10-1-i,j)=23;
		}
	cout<<"temp="<<endl<<temp<<endl;
}



uchar zeroones_after[100]=
 {0, 1, 1, 0, 1, 1, 1, 1, 1, 0,
  1, 1, 1, 0, 1, 1, 0, 0, 1, 1,
  1, 0, 1, 1, 1, 1, 1, 0, 0, 0,
  1, 1, 1, 1, 1, 0, 0, 0, 1, 1,
  0, 1, 0, 1, 0, 1, 1, 0, 1, 1,
  0, 0, 1, 0, 0, 1, 1, 1, 1, 1,
  0, 1, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 1, 1, 1,
  0, 1, 0, 1, 1, 0, 1, 1, 0, 1,
  1, 1, 1, 0, 1, 1, 0, 1, 1, 0
};


uchar zeroones_after_formsg[100]=
{23, 16, 16, 23, 16, 16, 16, 16, 16, 23,
  16, 16, 16, 23, 16, 16, 23, 23, 16, 16,
  16, 23, 16, 16, 16, 16, 16, 23, 23, 23,
  16, 16, 16, 16, 16, 23, 23, 23, 16, 16,
  23, 16, 23, 16, 23, 16, 16, 23, 16, 16,
  23, 23, 16, 23, 23, 16, 16, 16, 16, 16,
  23, 16, 23, 23, 23, 16, 16, 23, 23, 23,
  23, 23, 23, 16, 16, 23, 23, 16, 16, 16,
  23, 16, 23, 16, 16, 23, 16, 16, 23, 16,
  16, 16, 16, 23, 16, 16, 23, 16, 16, 23
};



void xiu_RS_decoding(uchar* zeroones, uchar* output)  // 100 0s and 1s as input, output the string
{

	DmtxMessage* msg = dmtxMessageCreate(1,DmtxFormatMatrix);  // sizeIdx=1;


	memcpy(msg->array,zeroones, 100*sizeof(uchar));

	int sizeIdx=1; 
	int fix=-1;
	dmtxDecodePopulatedArray(sizeIdx, msg, fix); // Key

							printf("outputSize=%d \n", msg->outputSize); //output 1

							for(int i=0;i<(int)(msg->outputSize);i++)

							printf("fuck msg_xiu.output(%d)=%c \n", i, msg->output[i]);

	memcpy(output,msg->output, msg->outputSize*sizeof(uchar));
}
























int main()
{
											uchar output[120]={0};	
										
										
											reorder(raw_01s, zeroones_after_formsg);

											xiu_RS_decoding(zeroones_after_formsg, output);







																	



					
											return 1;
	

		



}













































