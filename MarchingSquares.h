#pragma once
#ifndef MARCHINGSQUARES_H_INCLUDED
#define MARCHINGSQUARES_H_INCLUDED

#include "Vec2.h"
#include <list>

// Extract isolines from heightmaps

class MarchingSquares
{
public:

	MarchingSquares();
	~MarchingSquares();

	inline const float atDataIndex(const int i, const int j) const { return data_[i*width_ + j]; };
		
	inline const int getWidth() const { return width_; };
	inline const int getHeight() const { return height_; };
	inline float* getData() { return data_; };
	inline const float getThreshold() { return threshold_; };
	inline std::list< Vec2<float> >* getIsolineVertexList() { return &isolineVertexList_; };

	//inline void setWidth(const int width) { width_ = width; };
	//inline void setHeight(const int height) { height_ = height; };
	inline void setData(float* data) { data_ = data; };
	inline void setThreshold(const float threshold) { threshold_ = threshold; };
	void setHeightMap(const int width, const int height, float* data);

	void debugInfo() const;

	void lines(int num, int i,int j, float a, float b, float c, float d);
	int evaluateCell(const float a, const float b, const float c, const float d);

	void computeIsolines(const float threshold);

protected:

	void draw_one(const int num, const int i , const int j, const float a, const float b, const float c, const float d);
	void draw_adjacent(const int num, const int i,const int j, const float a, const float b, const float c, const float d);
	void draw_opposite(const int num, const int i,const int j, const float a, const float b, const float c, const float d);

	int width_;
	int height_;
	int xMax_;
	int xMin_;
	int yMax_;
	int yMin_;
	float threshold_;
	float* data_;

	std::list< Vec2<float> > isolineVertexList_;
};


#endif