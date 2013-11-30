#ifndef QSPLIT_H
#define QSPLIT_H

#include "Shape.h"
#include "BBox.h"

int qsplit(Shape** list, int size, float pivot_val, int axis)
{
	BBox bbox;
	double centroid;
	int ret_val = 0;

	for(int i=0; i <size; i ++)
	{
		/*bbox = list[j]->boundingBox(0.0f, 0.0f);*/
		bbox = BBox();
		centroid = ((bbox.min())[axis] + (bbox.max())[axis]) /2.0f;
		if(centroid < pivot_val)
		{
			Shape * temp = list[i];
			list[i] = list[ret_val];
			list[ret_val] = temp;
			ret_val++;
		}
	}
	if (ret_val==0 || ret_val == size) ret_val = size/2;
	return ret_val;
}
#endif