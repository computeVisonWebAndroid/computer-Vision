#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h> //algorithms
#include <iostream>

using namespace cv;
using namespace std;

Mat im;
Mat im2;
int x_count = 0;
int x_1 = 0;
int x_2 = 0;
int y_1 = 0;
int y_2 = 0;
int sum_x = 0, sum_y = 0, y_blk = 0, x_blk = 0;
int y_size = 0, x_size = 0, y_idex = 0, x_idex = 0;
int sum_x1 = 0, sum_y1 = 0;
int blur_dree = 5;
int sum_pxl_1 = 0, sum_pxl_2 = 0, sum_pxl_3 = 0, ave_sum_pxl_1 = 0, ave_sum_pxl_2 = 0, ave_sum_pxl_3 = 0;
int y_ret = 0, x_ret = 0;

void mousefunction(int event, int x, int y, int flags, void* userdata)
{
	//定义


	//定义



	if (event == EVENT_LBUTTONDOWN)
	{
		x_count = x_count + 1;
		printf("first Left click!\n");
		printf("x_cout=\n", x_count);
		printf("left click on (%d, %d)\n", x, y);
		if (x_count == 2)
		{

			x_2 = x;
			y_2 = y;

		}
		else
		{
			x_1 = x;
			y_1 = y;
		}

		//000000000000000000000000

		if (x_count == 2)
		{
			if (blur_dree > 0)
			{
				for (int y_blk = y_1; y_blk <= y_2; y_blk = y_blk + blur_dree)
				{
					for (int x_blk = x_1; x_blk <= x_2; x_blk = x_blk + blur_dree)
					{

						//ooooooo
						x_size = x_blk + (blur_dree - 1);
						y_size = y_blk + (blur_dree - 1);

						if (x_size <= x_2 && y_size <= y_2)
						{

							for (int y_idex = y_blk; y_idex <= y_size; y_idex++)
							{
								for (int x_idex = x_blk; x_idex <= x_size; x_idex++)
								{


									sum_pxl_1 += im.ptr<uchar>(y_idex)[3 * x_idex];
									sum_pxl_2 += im.ptr<uchar>(y_idex)[3 * x_idex + 1];
									sum_pxl_3 += im.ptr<uchar>(y_idex)[3 * x_idex + 2];
									if (x_idex == x_size && y_idex == y_size)
									{
										printf("sum_pt_123: %d, %d, %d\n", sum_pxl_1, sum_pxl_2, sum_pxl_3);
										ave_sum_pxl_1 = sum_pxl_1 / (blur_dree * blur_dree);
										ave_sum_pxl_2 = sum_pxl_2 / (blur_dree * blur_dree);
										ave_sum_pxl_3 = sum_pxl_3 / (blur_dree * blur_dree);
										printf("sum_pt_123: %d, %d, %d\n", ave_sum_pxl_1, ave_sum_pxl_2, ave_sum_pxl_3);

										for (int y_ret = y_blk; y_ret <= y_size; y_ret++)
										{
											for (int x_ret = x_blk; x_ret <= x_size; x_ret++)
											{
												im.ptr<uchar>(y_ret)[3 * (x_ret)] = ave_sum_pxl_1;
												im.ptr<uchar>(y_ret)[3 * (x_ret)+1] = ave_sum_pxl_2;
												im.ptr<uchar>(y_ret)[3 * (x_ret)+2] = ave_sum_pxl_3;

											}
										}
										sum_pxl_1 = 0, sum_pxl_2 = 0, sum_pxl_3 = 0, ave_sum_pxl_1 = 0, ave_sum_pxl_2 = 0, ave_sum_pxl_3 = 0;
									}

								}
							}
						}

					}

				}
			}
			x_count = 0;
		}

		printf("x_1=%d, y_1=%d\n", x_1, y_1);
		printf("x_2=%d, y_2=%d\n", x_2, y_2);

	}

}
//gggggggggggggg
int main(int argc, char** argv)
{
	im = imread("party.jpg");

	//cv::resize(im, im2, cv::Size(800, 600));
	namedWindow("Image", 1);
	setMouseCallback("Image", mousefunction);

	/* 按键功能 */
	for (;;)
	{

		imshow("Image", im);
		char c = cv::waitKey(1); //tells OpenCV refresh it every 1 millisecond
		if (c == 105 || c == 73)
		{

			if (blur_dree < 5)
			{
				blur_dree = blur_dree + 1;
				void mousefunction();
				if (blur_dree < 0)
				{
					blur_dree = 0;
				}
			}
			else
			{
				blur_dree = blur_dree + 5;
				void mousefunction();
				if (blur_dree < 0)
				{
					blur_dree = 0;
				}
			}
		}
		else if (c == 100 || c == 68)
		{

			if (blur_dree < 5)
			{
				blur_dree = blur_dree - 1;
				void mousefunction();
				if (blur_dree < 0)
				{
					blur_dree = 0;
				}
			}
			else
			{
				blur_dree = blur_dree - 5;
				void mousefunction();
				if (blur_dree < 0)
				{
					blur_dree = 0;
				}
			}
		}
		/* +++++++++++++++++++++++++++++ */
		else if (c == 83 || c == 115)
		{
			imwrite("C:/Project1.jpg", im);

		}

		/* ++++++++++++++++++++++++++++++ */
		/* “r” or “R” key  还原图像*/
		else if (c == 82 || c == 114)
		{
			im2 = imread("party.jpg");
			im2.copyTo(im);
		}

		/* “r” or “R” key  还原图像* */

		else if (c == 27)
		{
			break;
		}


	}

}