#include "MarchingSquares.h"

#include <cstddef>

MarchingSquares::MarchingSquares()
	:width_(0)
	,height_(0)
	,xMin_(0)
	,xMax_(0)
	,yMin_(0)
	,yMax_(0)
	,data_(NULL)
	,threshold_(0.0f)
{
}


//
MarchingSquares::~MarchingSquares()
{
	data_ = NULL; // do not delete data
}


//
void MarchingSquares::setHeightMap(const int width, const int height, float* data) 
{
	width_ = width; 
	height_ = height; 
	xMin_ = 0;  
	xMax_ = width_;  
	yMin_ = 0;  
	yMax_ = height_;

	/*
	xMin_ = -width_/2;  
	xMax_ = width_/2;  
	yMin_ = -height_/2;  
	yMax_ = height_/2;  
	*/
	data_ = data; 
};


//
int MarchingSquares::evaluateCell(const float a, const float b, const float c, const float d)
{
	int n = 0;
	
	if (a > threshold_) n+=1;
	if (b > threshold_) n+=8;
	if (c > threshold_) n+=4;
	if (d > threshold_) n+=2;
	
	return n ;
}


// draw line segments for each case
void MarchingSquares::lines(int num, int i,int j, float a, float b, float c, float d)
{
	switch(num) 
	{
		case 1 : case 2: case 4 : case 7: case 8: case 11: case 13: case 14:
			draw_one(num,i,j,a,b,c,d);
			break;
	
		case 3:  case 6:  case 9:  case 12:
			draw_adjacent(num,i,j,a,b,c,d);
			break;
	
		case 5:  case 10:
			draw_opposite(num,i,j,a,b,c,d);
			break;
	
		case 0:  case 15:
			break;
	}
}


//-----------------------------------------------------------------------------
void MarchingSquares::draw_one( const int num,
								const int i,
								const int j,
								const float a,
								const float b,
								const float c,
								const float d)
{

	const float dx=(xMax_-xMin_)/(width_-1.0f);
	const float dy=(yMax_-yMin_)/(height_-1.0f);
	const float ox=xMin_+i*(xMax_-xMin_)/(width_-1.0f);
	const float oy=yMin_+j*(yMax_-yMin_)/(height_-1.0f);

	float x1,y1,x2,y2;

	switch(num) 
	{
		case 1 : case 14:
			x1=ox;
			y1=oy+dy*(threshold_-a)/(d-a);
			x2=ox+dx*(threshold_-a)/(b-a);
			y2=oy;
			break;
		case 2: case 13:
			x1=ox;
			y1=oy+dy*(threshold_-a)/(d-a);
			x2=ox+dx*(threshold_-d)/(c-d);
			y2=oy+dy;
			break;
		case 4: case 11:
			x1=ox+dx*(threshold_-d)/(c-d);
			y1=oy+dy;
			x2=ox+dx;
			y2=oy+dy*(threshold_-b)/(c-b);
			break;
		case 7: case 8:
			x1=ox+dx*(threshold_-a)/(b-a);
			y1=oy;
			x2=ox+dx;
			y2=oy+dy*(threshold_-b)/(c-b);
			break;
	}


	isolineVertexList_.push_back(Vec2<float>(x1, y1));
	isolineVertexList_.push_back(Vec2<float>(x2, y2));
}


//-----------------------------------------------------------------------------
void MarchingSquares::draw_adjacent(const int num,
									const int i,
									const int j,
									const float a,
									const float b,
									const float c,
									const float d)
{
	const float dx=(xMax_-xMin_)/(width_-1.0f);
	const float dy=(yMax_-yMin_)/(height_-1.0f);
	const float ox=xMin_+i*(xMax_-xMin_)/(width_-1.0f);
	const float oy=yMin_+j*(yMax_-yMin_)/(height_-1.0f);
	
	float x1,y1,x2,y2;

	switch(num) 
	{
	case 3 : case 12:
		x1=ox+dx*(threshold_-a)/(b-a);
		y1=oy;
		x2=ox+dx*(threshold_-d)/(c-d);
		y2=oy+dy;
		break;
	case 6: case 9:
		x1=ox;
		y1=oy+dy*(threshold_-a)/(d-a);
		x2=ox+dx;
		y2=oy+dy*(threshold_-b)/(c-b);
		break;
	}

	isolineVertexList_.push_back(Vec2<float>(x1, y1));
	isolineVertexList_.push_back(Vec2<float>(x2, y2));

}


//-----------------------------------------------------------------------------
void MarchingSquares::draw_opposite(const int num,
									const int i,
									const int j,
									const float a,
									const float b,
									const float c,
									const float d)
{
	const float dx=(xMax_-xMin_)/(width_-1.0f);
	const float dy=(yMax_-yMin_)/(height_-1.0f);
	const float ox=xMin_+i*(xMax_-xMin_)/(width_-1.0f);
	const float oy=yMin_+j*(yMax_-yMin_)/(height_-1.0f);
	float x1,y1,x2,y2,x3,y3,x4,y4;

	switch(num) 
	{
		case 5 :
			x1=ox;
			y1=oy+dy*(threshold_-a)/(d-a);
			x2=ox+dx*(threshold_-a)/(b-a);
			y2=oy;
			x3=ox+dx*(threshold_-d)/(c-d);
			y3=oy+dy;
			x4=ox+dx;
			y4=oy+dy*(threshold_-b)/(c-b);
			break;
		case 10:
			x1=ox;
			y1=oy+dy*(threshold_-a)/(d-a);
			x2=ox+dx*(threshold_-d)/(c-d);
			y2=oy+dy;
			x3=ox+dx*(threshold_-d)/(c-d);
			y3=oy;
			x4=ox+dx;
			y4=oy+dy*(threshold_-b)/(c-b);		
			break;
	}

	isolineVertexList_.push_back(Vec2<float>(x1, y1));
	isolineVertexList_.push_back(Vec2<float>(x2, y2));
	isolineVertexList_.push_back(Vec2<float>(x3, y3));
	isolineVertexList_.push_back(Vec2<float>(x4, y4));
}


//-----------------------------------------------------------------------------
void MarchingSquares::computeIsolines(const float threshold)
{
	threshold_ = threshold;

	isolineVertexList_.clear();

	/* process each cell */
	for (int i = 0; i < width_; ++i)
	{
		for (int j = 0; j < height_; ++j)
		{
			const float a = data_[i*width_ + j];
			const float b = data_[(i+1)*width_ + j];
			const float c = data_[(i+1)*width_ + j+1];
			const float d = data_[i*width_ + j+1];

			lines(  evaluateCell(a, b, c, d), 
					i, j, 
					a, b, c, d );
		}
	}
}