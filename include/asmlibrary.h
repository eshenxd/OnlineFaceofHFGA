/*
 * ASMLibrary(Active Shape Model Library) -- A compact SDK for face alignment
 *
 * Copyright (c) 2008-2010, Yao Wei <njustyw@gmail.com>,
 * http://visionopen.com/members/yaowei/, All rights reserved.
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */


/**@file 
Functions, structures, classes for implementing active shape model.

Copyright (c) 2008-2010 by Yao Wei <njustyw@gmail.com>, all rights reserved.

Please cite the following or equivalent reference in any publicly available 
text that uses asmlibrary: 

YAO Wei. Research on Facial Expression Recognition and Synthesis.
<EM> Master Thesis, Department of Computer Science and Technology, 
Nanjing University</EM>, Feb 2009. \url http://code.google.com/p/asmlibrary

@version 5.0-2010-5-20
*/

#ifndef _ASM_LIBRARY_H_
#define _ASM_LIBRARY_H_

#include <stdio.h>
//#include <cv.h>
//#include <highgui.h>
#include "../opencv/cv.h"
#include "../opencv/highgui.h"
typedef unsigned char uchar;

#ifdef WIN32
/** dllexport for win32 */
#define ASMLIB __declspec(dllexport)
#else
#define ASMLIB 
#endif

/**
 * Predefined local texture (profile) types.
 * <ul>
 * <li>PROFILE_1D: use only the pixels along the normal vector in the contour.</li>
 * <li>PROFILE_2D: use the pixels located at the recentage.</li>
 * <li>PROFILE_LBP: use the pixels processed with LBP-operator.</li>
 * </ul>
 **/
enum ASM_PROFILE_TYPE {PROFILE_1D, PROFILE_2D, PROFILE_LBP};

/**
 * Predefined mapping types.
 * <ul>
 * <li>MAP_UNIFORM: use only patterns that have at most two
 * 1-to-0 or 0-to-1 transitions. Junk the rest in one value.</li>
 * <li>MAP_ROTMIN: rotate patterns to their minimum values.</li>
 * <li>MAP_UNIFORM_ROTMIN: use only uniform patterns and rotate
 * them to their minimum values.</li>
 * <li>MAP_NONE: no mapping</li>
 * </ul>
 **/
enum LBP_MAPPING_TYPE { MAP_UNIFORM, MAP_ROTMIN, MAP_UNIFORM_ROTMIN, MAP_NONE };

class asm_shape;
class asm_profile;
class asm_model;
class asm_vjfacedetect;
class asm_cam_or_avi;
struct profile_Nd_model;
struct profile_lbp_model;


#ifdef __cplusplus
extern "C"{
#endif

/**
 @param x the coordinate in \f$x\f$-direction of source object.
 @param offset the length from the source object to the target object
 @param cos_alpha the value of cosine angle between the horizontal line and source-target line
 @return the coordinate in \f$x\f$-direction of target object
*/
ASMLIB inline double GetX(double x, int offset, double cos_alpha)
{	return x + (offset * cos_alpha); }

/**
 @param y the coordinate in \f$y\f$-direction of source object.
 @param offset the length from the source object to the target object
 @param sin_alpha the value of sine angle between the horizontal line and source-target line
 @return the coordinate in \f$y\f$-direction of target object
*/
ASMLIB inline double GetY(double y, int offset, double sin_alpha)
{	return y + (offset * sin_alpha); }

/**
 Write \a CvMat data to file stream.
 @param f the stream to write to.
 @param mat the \a CvMat that will be wrote.
*/
ASMLIB void WriteCvMat(FILE* f, const CvMat* mat);

/**
 Read \a CvMat data from file stream.
 @param f the stream to read from.
 @param mat the \a CvMat that will be read.
*/
ASMLIB void ReadCvMat(FILE* f, CvMat* mat);	

/**
 Image pixel at the location \f$(x,y)\f$ using bilinear interpolate.
  @param image the image resource
  @param x the grid value in \f$x\f$-direction
  @param y the grid value in \f$y\f$-direction
  @param width  the width of image
  @param height the height of image
  @return the pixel value at \f$(x,y)\f$
*/
ASMLIB uchar GetBilinearPixel(const IplImage *image, double x, double y, 
							  int width, int height);

/**
 Image pixel at the location \f$(x,y)\f$ using no interpolation.
  @param image Image resource
  @param x the grid value in \f$x\f$-direction
  @param y the grid value in \f$y\f$-direction
  @param width the width of image
  @param height the height of image
  @return the pixel value \f$(x,y)\f$
*/
ASMLIB uchar GetOriPixel(const IplImage *image, double x, double y, 
						 int width, int height);

/**
 Calculate Mahalanobis distance \f$d(x, M) = x' \times M \times x\f$.
 @param M the covariance matrix
 @param x the vector used to calculate the M-distance
 @return Mahalanobis distance
*/
ASMLIB double CalcMahalanobisDist(const CvMat* M, const double* x);

/**
 Calculate Chi square measure \f$d(H', H) = \sum {i=1,...,n} (H'(k)-H(k))^2 / (H'(k)+H(k)) \f$.
 @param h the testing point's histogram
 @param H the mean histogram
 @param nbins the dimension of histogram
 @return Chi square measure
*/
ASMLIB double CalcChiSquareDist(const double* h, const double* H, int nbins);


/**
 Initialize shape from the detected box.
 @param shape the returned initial shape
 @param det_shape the detected box calling by \a asm_vjfacedetect::\a Detect()
 @param ref_shape the average mean shape
 @param refwidth the width of average mean shape
*/
ASMLIB void InitShapeFromDetBox(asm_shape &shape, const asm_shape& det_shape, 
								const asm_shape &ref_shape, double refwidth);

/**
 Draw the fitting shape points onto the image.
 @param image the image resource
 @param shape the shape data
*/
ASMLIB void DrawPoints(IplImage* image, const asm_shape& shape);
	
/**
 Draw the fitting shape edge  onto the image.
 @param image the image resource
 @param shape the shape data
 @param edge_start the starting index of edges
 @param edge_end the ending index of edges
 @param n_edges the number of edges
*/
ASMLIB void DrawEdges(IplImage* image, const asm_shape& shape,
					  int* edge_start, int* edge_end, int n_edges);

/**
 Read the whole shape datas from the file lists
 @param shapes all shape datas
 @param n_shapes the number of shape data
 @param shape_lists the lists of shape point files
 @param image_lists the lists of image files
 @return false on failure, true otherwise
*/
ASMLIB bool ReadAllShapes(asm_shape* shapes, int n_shapes,
						  const char** shape_lists, const char** image_lists);

/**
 * Get the number of ones in a binary number.
 * @param c the number
 * @param bits the number of bits to consider
 **/
ASMLIB int LBP_onecount(unsigned int c, int bits = 8);

/**
 * Get the number of 0-to-1 or 1-to-0 transitions in a binary number.
 * @param c the number
 * @param bits the number of bits to consider
**/
ASMLIB int LBP_transitions(unsigned int c, int bits = 8);

/**
* Rotate a binary number to its minimum value.
* @param c the number
* @param bits the number of bits to consider
**/
ASMLIB unsigned int LBP_rotmin(unsigned int c, int bits = 8);

/**
 * Calculate a mapping look-up table for the given mapping type. The
 * returned value is a newly allocated array of integers in which
 * each item represents the index the particular LBP code should
 * be mapped to. The returned array will take up
 * 2<sup>samples</sup>*sizeof(int) bytes of memory.
 *
 * @param nsamples the number of neighborhood samples
 * @param type the type of mapping
 * @return a look-up table
 **/
ASMLIB int* LBP_InitMapping(int nsamples, LBP_MAPPING_TYPE type);

/**
 * Free memory of the mapping look-up table.
 * @param mapping the ptr of mapping look-up table
 **/
ASMLIB void LBP_FreeMapping(int* mapping);

/**
 * Get the number of distinct values (bins) the given mapping type can
 * produce. This is useful in determining the length of the
 * resulting feature vector when the mapping is in use.
 * @param nsamples the number of neighborhood samples
 * @param type the type of mapping
 * @return the maximum value of the mapping (alway plus one for 
     handling the case of outside or on the boundary )
 **/
ASMLIB int LBP_GetMapSize(int nsamples, LBP_MAPPING_TYPE type);


/**
 * "Circular neighborhood" is used to denote a situation where, instead of the
 * traditional rectangular one, neighborhood pixels are defined to
 * be the ones that lie at a certain distance from the center. The
 * distance is also called "predicate". The number of samples at
 * this distance and the predicate itself can be dynamically
 * changed. In digital images, all pixels in a circular neighborhood
 * do not necessarily match the pixel grid. Pixel values at these
 * positions are obtained with bilinear interpolation or, if the
 * interpolation flag is set to false, from the pixel nearest to the
 * exact position.
 **/
struct lbp_circle_table
{
	int			   nsamples;    /**< Number of neighborhood samples */
	CvPoint*	   points;		/**< A precalculated table of interpolation points. */
	CvPoint2D32f*  offsets;		/**< A precalculated table of interpolation offsets. */
	double *  multipliers;	/**< Precalculated values for interpolation multiplication. */
};

/**
 * Update the precalculated point value tables.
 * @param nsamples the number of neighborhood samples (e.g. 8u)
 * @param predicate the radius of the neighborhood (e.g. 1.5)
 * @return A new Circular Local Sampler instance
 **/
ASMLIB struct lbp_circle_table* LBP_InitTable(int nsamples, double predicate);

/**
 * Release the memory of the precalculated point value tables.
 * @param table the ptr of precalculated point value tables
 **/
ASMLIB void LBP_FreeTable(struct lbp_circle_table* table);

/**
 * Transform the source image using the LBP-operator .
 * @param grayimage the source image resource that must be 8-depth
 * @param table the precalculated circular local sampler instance
 * @param nsamples the number of neighborhood samples (e.g. 8u)
 * @param predicate the radius of the neighborhood (e.g. 1.5)
 * @param type the type of mapping
 * @param result the target image processed with LBP
 * @param rect the recentange for the masked image (if possible) 
 * @return -1 on failure, 0 otherwise
 **/
ASMLIB int LBP_CalcTransformedImage(const IplImage* grayimage, 
									const struct lbp_circle_table* table,
									int nsamples, int predicate,
									LBP_MAPPING_TYPE type, int* result,
									CvRect* rect = NULL);

/**
 * Calculate the feature vector from the image that has been transformed by LBP-operator.
 * @param result the transformed image with LBP
 * @param nrows the height of image 
 * @param ncols the width of image
 * @param mapping the mapping look-up table initialized by \a LBP_InitMapping()
 * @param hist the histogram of feature vector 
 * @param nbins the dimension of feature vector (identity to \a LBP_GetMapSize(\a nsamples, \a type))
 **/
ASMLIB void LBP_CalcFeatureVector(const int *result, int nrows, int ncols,
								  const int * mapping, int* hist, int nbins);

#ifdef __cplusplus
}
#endif

/** Class for 2d shape data. */
class ASMLIB asm_shape
{
public:
    /** Constructor */
	asm_shape();
    
	/** Copy Constructor */
	asm_shape(const asm_shape &v);
    
	/** Destructor */
    ~asm_shape();

	/**
     Access elements by \a CvPoint2D32f \a pt = \a shape[\a i] to get \a i-th point in the shape.
     @param i Index of points
     @return   Point at the certain index
	*/
	const CvPoint2D32f operator [](int i)const{ return m_vPoints[i];	}
	
	/**
     Access elements by \a CvPoint2D32f \a pt = \a shape[\a i] to get \a i-th point in the shape.
     @param i Index of points
     @return   Point at the certain index
	*/
	CvPoint2D32f& operator [](int i){ return m_vPoints[i];	}
	
	/**
     Get the number of points.
     @return   Number of points
	*/
	inline const int NPoints()const{ return	m_nPoints; }

    /**
     Override of operator =
    */
    asm_shape&			operator =(const asm_shape &s);
    
	/**
     Override of operator =.
    */
	asm_shape&			operator =(double value);
    
	/**
     Override of operator +
    */
    const asm_shape		operator +(const asm_shape &s)const;
    
	/**
     Override of operator +=
    */
    asm_shape&			operator +=(const asm_shape &s);
    
	/**
     Override of operator -
    */
    const asm_shape     operator -(const asm_shape &s)const;
    
	/**
     Override of operator -=
    */
    asm_shape&			operator -=(const asm_shape &s);
    
	/**
     Override of operator *
    */
    const asm_shape     operator *(double value)const;
    
	/**
     Override of operator *=
    */
    asm_shape&			operator *=(double value);
    
	/**
     Override of operator *
    */
    double				operator *(const asm_shape &s)const;
    
	/**
     Override of operator /
    */
    const asm_shape     operator /(double value)const;
    
	/**
     Override of operator /=
    */
    asm_shape&			operator /=(double value);

	/**
     Release memory.
    */
    void    Clear();
    
	/**
     Allocate memory.
	 @param length Number of of shape points
    */
    void    Resize(int length);
    
	/**
     Read points from file.
	 @param filename the filename the stored shape data
     @return   true on pts format, false on asf format, exit otherwise
    */
    bool	ReadAnnotations(const char* filename);
	
	/**
     Read points from asf format file.
	 @param filename the filename the stored shape data
    */
    void    ReadFromASF(const char*filename);
	
	/**
     Read points from pts format file.
	 @param filename the filename the stored shape data
    */
    void	ReadFromPTS(const char*filename);
	
	/**
     Write shape data into file stream.
	 @param f  stream to write to
    */
	void	Write(FILE* f);
	
	/**
     Read shape data from file stream.
	 @param f  stream to read from
    */
	void	Read(FILE* f);
	
	/**
     Calculate minimum \f$x\f$-direction value of shape.
    */
	const double  MinX()const;
    
	/**
     Calculate minimum \f$y\f$-direction value of shape.
    */
	const double  MinY()const;
    
	/**
     Calculate maximum \f$x\f$-direction value of shape.
    */
	const double  MaxX()const;
    
	/**
     Calculate maximum \f$y\f$-direction value of shape.
    */
	const double  MaxY()const;
	
	/**
     Calculate the left and right index for \f$x\f$-direction in the shape.
	 @param ileft the index of points in \f$x\f$-direction which has the minimum x
	 @param iright the index of points in \f$x\f$-direction which has the maximum x
    */
	void		  GetLeftRight(int& ileft, int& iright)const;
    
	/**
     Calculate width of shape.
	 @param ileft Index of points in \f$x\f$-direction which has the minimum x
	 @param iright Index of points in \f$x\f$-direction which has the maximum x
    */
	const double  GetWidth(int ileft = -1, int iright = -1)const;
	
	/**
     Calculate height of shape.
    */
	const double  GetHeight()const { return MaxY()-MinY();	}
	
    /**
     Calculate center of gravity for shape.
	 @param x Value of center in \f$x\f$-direction
	 @param y Value of center in \f$y\f$-direction
    */
	void    COG(double &x, double &y)const;
    
	/**
     Translate the shape to make its center locate at (0, 0).
	*/
	void    Centralize();
    
	/**
	 Translate the shape.
	 @param x Value of translation factor in \f$x\f$-direction
	 @param y Value of translation factor in \f$y\f$-direction
    */
	void    Translate(double x, double y);
    
	/**
     Scale shape by an uniform factor.
	 @param s Scaling factor
	*/
	void    Scale(double s);
    
	/**
     Rotate shape by anti clock-wise.
	 @param theta Angle to be rotated
	*/
	void    Rotate(double theta);
	
	/**
     Scale shape in x and y direction respectively.
	 @param sx Scaling factor in \f$x\f$-direction
	 @param sy Scaling factor in \f$y\f$-direction
	*/
	void    ScaleXY(double sx, double sy);
	
	/**
     Normalize shape (zero_mean_unit_length) so that its center locates at (0, 0) and its \f$L2\f$-norm is 1.
	 @return the \f$L2\f$-norm of original shape
	*/
	double	Normalize();
	
	
	enum{ LU, SVD, Direct };

	/**
	 Calculate the similarity transform between one shape and another reference shape. 
	 Where the similarity transform is: 
	 <BR>
	 \f$T(a,b,tx,ty) = [a \ -b \ Tx; b \ a \ Ty ; 0 \ 0 \ 1]\f$.
	 @param ref_shape the reference shape
	 @param a  will return \f$ s \times cos(theta) \f$ in form of similarity transform
	 @param b  will return \f$ s \times sin(theta) \f$ in form of similarity transform
	 @param tx will return \f$ Tx \f$ in form of similarity transform
	 @param ty will return \f$ Ty \f$ in form of similarity transform
	 @param method  Method of similarity transform
	*/
	void    AlignTransformation(const asm_shape &ref_shape, double &a, double &b, 
								double &tx, double &ty, int method = SVD)const;
    
	/**
	 Align the shape to the reference shape. 
	 @param ref_shape the reference shape
	 @param method  method of similarity transform
	*/
	void    AlignTo(const asm_shape &ref_shape, int method = SVD);
    
	/**
	 Transform Shape using the similarity transform \f$T(a,b,tx,ty)\f$. 
	*/
	void    TransformPose(double a, double b, double tx, double ty);

	/**
	 Calculate the angular bisector between two lines \f$Pi-Pj\f$ and \f$Pj-Pk\f$. 
	 @param i the index of point vertex
	 @param j the index of point vertex
	 @param k the index of point vertex
	 @return Angular bisector vector in form of \f$(cos(x), sin(x))^T\f$
	*/
	CvPoint2D32f CalcBisector(int i, int j, int k)const;

	/**
	 Calculate the Euclidean norm (\f$L2\f$-norm). 
	 @return Euclidean norm
	*/
	double  GetNorm2()const;

	/**
	 Calculate the normal vector at certain vertex around the shape contour. 
	 @param cos_alpha the normal vector in \f$x\f$-direction
	 @param sin_alpha the normal vector in \f$y\f$-direction
	 @param i the index of point vertex
	*/
	void	CalcNormalVector(double &cos_alpha, double &sin_alpha, int i)const;

	/**
	 Convert from OpenCV's \a CvMat to class asm_shape
	 @param mat \a CvMat that converted from
	*/
	void    CopyFrom(const CvMat* mat);
	
	/**
	 Convert from class asm_shape to OpenCV's CvMat.
	 @param mat CvMat that converted to
	*/
	void    CopyTo(CvMat* mat)const;

private:
	void    Transform(double c00, double c01, double c10, double c11);

private:
	CvPoint2D32f* m_vPoints;	/**< point data */
	int m_nPoints;				/**< number of points */
};

/** Class for profile. */
class ASMLIB asm_profile
{
public:
	/** Null Constructor */
	asm_profile();

	/** Constructor
	 @param length Width of profile
	*/
	asm_profile(int length);
	
	/** Copy Constructor */
    asm_profile(const asm_profile &v);
	
	/* and Destructor */
	~asm_profile();

	/**
     Access profile elements.
     @param i Index of profile
     @return  Value at the certain index
	*/
	inline const double operator [](int i)const{  return m_vProf[i]; }
	
	/**
     Access profile elements.
     @param i Index of profile
     @return  Value at the certain index
	*/
	inline double& operator [](int i){  return m_vProf[i]; }
	
	/**
     Access raw ptr of profile data.
     @return  Raw ptr of profile data
	*/
	const double* GetData()const { return m_vProf;	}
	
    /**
     Override of operator =
    */
	asm_profile&		operator =(const asm_profile &p);
	
	/**
     Override of operator =
    */
	asm_profile&		operator =(double value);
    
	/**
     Override of operator +
    */
	const asm_profile   operator +(const asm_profile &p)const;
    
	/**
     Override of operator +=
    */
	asm_profile&		operator +=(const asm_profile &p);
    
	/**
     Override of operator -
    */
	const asm_profile   operator -(const asm_profile &p)const;
    
	/**
     Override of operator -=
    */
	asm_profile&		operator -=(const asm_profile &p);
	
	/**
     Override of operator *
    */
	const asm_profile   operator *(double value)const;
    
	/**
     Override of operator *=
    */
	asm_profile&		operator *=(double value);
	
	/**
     Override of operator /
    */
	const asm_profile   operator /(double value)const;
    
	/**
     Override of operator /=
    */
	asm_profile&		operator /=(double value);

	/**
     Release memory.
    */
    void    Clear();

	/**
     Allocate memory.
	 @param length Width of profile
    */
    void    Resize(int length);
	
	/**
     Write profile data into file stream.
	 @param f  stream to write to
    */
	void	Write(FILE* f);
	
	/**
     Read profile data from file stream.
	 @param f  stream to read from
    */
	void	Read(FILE* f);

	/**
     Get the width of profile.
	*/
	inline const int  NLength()const{ return m_nWidth; }
	
	/**
     Pre-Calculate 1D-profiles of all possible locations at one certain point vertex.
	 Note: Use this before calling \a GetProfile().
	 @param image  the image resource
	 @param shape  the shape information
	 @param ipoint the index of point vertex
	 @param nwidth  the width of profile
	 @param binterpolate will sampling pixel by bilinear interpolate or not?
	 @param displace_offset how long will the profile be calculate?
	 @param whole_profile the buffer that store the entire profile (actually 
	 its length is \a width + 2 * \a displace_offset)
	 @param cos_alpha the normal vector in \f$x\f$-direction
	 @param sin_alpha the normal vector in \f$y\f$-direction
    */
	static void CalcProfile1D(const IplImage* image, const asm_shape& shape, 
		int ipoint, int nwidth, bool binterpolate, 
		int displace_offset, void* whole_profile, 
		double* cos_alpha = NULL, double* sin_alpha = NULL);

	/**
     Get the profile for one certain point vertex at the offset
	 @param image  the image resource
	 @param shape  the shape point information
	 @param ipoint the index of point vertex
	 @param whole_profile the buffer that store the entire profile (actually 
	 its length is \a width + 2 * \a displace_offset)
	 @param offset the offset bias from the point \a Shape[\a iPoint]
    */
	void GetProfile(const IplImage* image, const asm_shape &shape,
					int ipoint, void* whole_profile, int offset = 0);

	/**
     Calculate LBP-profiles of all possible locations at one certain point vertex.
	 Note: Use this before calling \a GetProfile().
	 @param shape  the shape information
	 @param ipoint the index of point vertex
	 @param lbp_img the target image processed with LBP
	 @param nrows the height of \a lbp_img
	 @param ncols the width of \a lbp_img
	 @param nblocklength  the width/height of recentage for sampling profile
	 @param xoffset the offset in \f$x\f$-direction away from the center \a shape[\a ipoint]
	 @param yoffset the offset in \f$y\f$-direction away from the center \a shape[\a ipoint]
	 @param mapping the mapping look-up table initialized by \a LBP_InitMapping()
	*/
	void CalcProfileLBP(const asm_shape& shape, int ipoint, 
		const int* lbp_img, int nrows, int ncols,
		int nblocklength, int xoffset, int yoffset, const int* mapping);

	/**
     Normalize the profile so that its \f$L1\f$-norm is 1. 
	*/
	void Normalize();

	/**
	 Convert from OpenCV's CvMat to class asm_profile.
	 @param mat CvMat that converted from
	*/
	void CopyFrom(const CvMat* mat);
	
	/**
	 Convert from LBP histogram to class asm_profile.
	 @param hist the histogram
	 @param nbins the dimension of histogram
	*/
	void CopyFrom(const int* hist, int nbins);

	/**
	 Convert from class asm_profile to OpenCV's CvMat.
	 @param mat CvMat that converted to
	*/
	void CopyTo(CvMat* mat)const;

private:
	double*		m_vProf;			/**< profile data */
	int			m_nWidth;			/**< profile width */
	static int	m_nDisplacement;	/**< displacement offset from the center */

};

/** Left and Right index in \f$x\f$-direction of shape */
typedef struct scale_param
{
	int left;	/**< Index of points in \f$x\f$-direction which has the minimum x */
	int right;	/**< Index of points in \f$x\f$-direction which has the maximum x */
}scale_param;

/** Profile distribution model for ASM_PROFILE_1D and ASM_PROFILE_2D */
struct profile_Nd_model
{
	CvMat*** m_P;						/**< mean of profile data*/
	asm_profile** m_asm_meanprofile;	/**< mean of profile data*/
	CvMat*** m_G; /**< inverted covariance matrix of profile data*/
	double*	m_buffer;	/**< pre-allocated buffer for calculate profile */
};

/** Profile distribution model for ASM_PROFILE_1D and ASM_PROFILE_2D */
struct profile_lbp_model
{
	asm_profile** m_asm_meanprofile;	/**< the mean histogram for all landmark */
	int nsamples;			/**< the number of neighborhood samples */
	int predicate;			/**< the radius of the neighborhood */
	int nblocklength;		/**< the width/height of block that for sampling profile */
	LBP_MAPPING_TYPE type;	/**< the type of LBP mapping */
	int* mapping;			/**< the look-up table */
	struct lbp_circle_table* table; /**< the precalculated circular local sampler instance */
	int nbins;				/**< the dimension of feature vector */
	int nlevels;			/**< the pyramid level */
};

/** Class for active shape model. */
class ASMLIB asm_model
{
public:
	/**
	 Constructor
	*/
	asm_model();
	
	/**
	 Destructor
	*/
	~asm_model();

	
	/**
	 Build active shape model.
	 @param image_lists the lists of image files
	 @param n_images the number of image files
	 @param shape_datas the lists of shape point data
	 @param n_shapes the number of shape data
	 @param binterpolate will sample pixel by bilinear interpolate or not?
	 @param halfwidth  the half-side width of profile
	 @param percentage the fraction of shape variation to retain during PCA
	 @param level_no the number of pyramid level
	 @param type the type of sampling profile
	 @return false on failure, true otherwise
	*/
	bool  Build(const char** image_lists,  int n_images,
		 const asm_shape* shape_datas, int n_shapes,
		 bool binterpolate, int halfwidth,  double percentage, 
		 int level_no, ASM_PROFILE_TYPE type);

	/**
	 Image alignment/fitting with an initial shape.
	 @param shape the point features that carries initial shape and also restores result after fitting
	 @param grayimage the gray image resource
	 @param max_iter the number of iteration
	 @param param the left and right index for \f$x\f$-direction in the shape (Always set \a NULL )
	 @return false on failure, true otherwise
	*/
	bool Fit(asm_shape& shape, const IplImage *grayimage, 
		int max_iter = 30, const scale_param* param = NULL);	
	
	/**
     Write model data to file stream.
	 @param f  stream to write to
    */
	void WriteModel(FILE* f);
	
	/**
     Read model data from file stream.
	 @param f  stream to read from
    */
	void ReadModel(FILE* f);

	/**
	 Get mean shape of model.
	*/
	const asm_shape& GetMeanShape()const { return m_asm_meanshape;	}
	
	/**
	 Get modes of shape distribution model (Will be calculated in shape's PCA)
	*/
	const int GetModesOfModel()const { return m_nModes;}
	
	/**
	 Get the width of mean shape [Identical to \a m_asm_meanshape.\a GetWidth()].
	*/
	const double GetReferenceWidthOfFace()const { return m_dReferenceFaceWidth; }

private:

	/**
     Get the optimal offset at one certain point vertex during the process of 
	 best profile matching (work for 1d/2d profile model).
	 @param image the image resource
	 @param ilev one certain pyramid level
	 @param shape the shape data
	 @param ipoint the index of point vertex
	 @param cos_alpha the normal vector in \f$x\f$-direction
	 @param sin_alpha the normal vector in \f$y\f$-direction
	 @return offset bias from \a Shape[\a iPoint]
	*/
	int FindBestOffsetForNd(const IplImage* image, int ilev,
							const asm_shape& shape, int ipoint,
							double& cos_alpha, double& sin_alpha);

	/**
     Get the optimal offset at one certain point vertex during the process of 
	 best profile matching (work for lbp profile model).
  	 @param lbp_img the target image processed with LBP
	 @param nrows the height of \a lbp_img
	 @param ncols the width of \a lbp_img
	 @param ilev one certain pyramid level
	 @param shape the shape data
	 @param ipoint the index of point vertex
	 @param xoffset the returned offset in \f$x\f$-direction away from \a Shape[\a iPoint]
	 @param yoffset the returned offset in \f$y\f$-direction away from \a Shape[\a iPoint]
	*/
	void FindBestOffsetForLBP(const int* lbp_img, int nrows, int ncols, int ilev,
				const asm_shape& shape, int ipoint, int& xoffset, int& yoffset);

	/**
     Update shape by matching the image profile to the model profile.
	 @param update_shape the updated shape
	 @param shape  the point feature that will be matched
	 @param ilev one certain pyramid level
	 @param image the image resource
	 @param lbp_img the LBP-operator image
	 @param norm the \f$L2\f$-norm of the difference between \a shape and \a update_shape
	 @return how many point vertex will be updated?
	*/
	int MatchToModel(asm_shape& update_shape, const asm_shape& shape, 
		int ilev, const IplImage* image, const int *lbp_img, double* norm = NULL);

	/**
     Calculate shape parameters (\a a, \a b, \a Tx, \a Ty) and pose parameters \a p.
	 @param p  Shape parameters
	 @param a  \f$ s \times cos(theta) \f$ in form of similarity transform
	 @param b  \f$ s \times sin(theta) \f$ in form of similarity transform
	 @param tx \f$ Tx \f$ in form of similarity transform
	 @param ty \f$ Ty \f$ in form of similarity transform
	 @param shape  the point features data
	 @param iter_no Number of iteration
	*/
	void CalcParams(CvMat* p, double& a, double& b,	double& tx, double& ty, 
		const asm_shape& shape, int iter_no = 2);
	
	/**
     Constrain the shape parameters.
	 @param p  Shape parameters
	*/
	void Clamp(CvMat* p);

	/**
     Generate shape instance according to shape parameters p and pose parameters.
	 @param shape the point feature data
	 @param p  the shape parameters
	 @param a  Return \f$ s \times cos(theta) \f$ in form of similarity transform
	 @param b  Return \f$ s \times sin(theta) \f$ in form of similarity transform
	 @param tx  Return \f$ Tx \f$ in form of similarity transform
	 @param ty  Return \f$ Ty \f$ in form of similarity transform
	*/
	void CalcGlobalShape(asm_shape& shape, const CvMat* p, 
							double a, double b, double tx, double ty);

	/**
     Pyramid fitting at one certain level.
	 @param shape the point feature data
	 @param image the image resource
	 @param ilev one certain pyramid level
	 @param iter_no the number of iteration
	*/
	void PyramidFit(asm_shape& shape, const IplImage* image, int ilev, int iter_no);

	/**
     Align all training shape datas.
	 @param shapes  All Shape datas
	 @param n_shapes Number of shape datas
	*/
	void AlignAllShapes(asm_shape* shapes, int n_shapes);
    
	/**
     Calculate mean shape of all shapes.
	 @param mean_shape the mean shape of all shapes
	 @param shapes  all of shape datas
	 @param n_shapes the number of shape data
	*/
	void  CalcMeanShape(asm_shape &mean_shape, const asm_shape* shapes, int n_shapes); 

	/**
     Do PCA on shape data.
	 @param shapes  all of shape datas
	 @param n_shapes the number of shape data
	 @param percentage the fraction of shape variation to retain during PCA
	*/
	void DoPCA(asm_shape* shapes, int n_shapes, double percentage);

	/**
     Calculate profiles for all landmarks, all samples and all pyramid levels.
	 @param profiles  all of profile datas
	 @param n_samples the number of samples
	 @param n_points the number of shape point
	 @param n_level the number of pyramid level
	 @param image_lists the lists of image files
	 @param shapes  all of shape datas
	 @param binterpolate will sample pixel by bilinear interpolate or not?
	*/
	void CalcProfiles(asm_profile***profiles, int n_samples, int n_points, int n_level,
		const char* image_lists[],  const asm_shape* shapes,
		bool binterpolate);

	/**
     Calculate the mean(1d/2d, lbp) and covariance(only for 1d/2d) matrix of profiles.
	 @param profiles  All profile datas
	 @param n_samples Number of samples
	 @param n_points Number of shape point
	 @param n_level Number of pyramid level
	*/
	void CalcStatProfiles(asm_profile***profiles, int n_samples, 
		int n_points, int n_level);

private:

	CvMat*  m_M;   /**< mean vector of shape data */
    CvMat*  m_B;   /**< eigenvetors of shape data */
    CvMat*  m_V;   /**< eigenvalues of shape data */

	CvMat* m_SM;   /**< mean of shapes projected space */	
	CvMat* m_SSD;  /**< standard deviation of shapes projected space	*/	


	ASM_PROFILE_TYPE m_type;	/**< the type of sampling profile */
	
	/**< the profile distribution model */
	union
	{
		struct profile_lbp_model* lbp_tdm;			/**< lbp profile model */
		struct profile_Nd_model* classical_tdm;	/**< 1d/2d profile model */
	}; 
	
	
	asm_shape m_asm_meanshape;			/**< mean shape of aligned shapes */
	
	int m_nPoints;					/**< number of shape points */
	int m_nWidth;					/**< width of each landmark's profile */
	int m_nLevels;					/**< pyramid level of multi-resolution */
	int m_nModes;					/**< number of truncated eigenvalues */
	double m_dReferenceFaceWidth;	/**< width of reference face  */
	bool m_bInterpolate;			/**< whether to using image interpolate or not*/
	double m_dMeanCost;		/**< the mean of fitting cost to determine whether fitting succeed or not*/
	double m_dVarCost;		/**< the variance of fitting cost determine whether fitting succeed or not*/

private:
	CvMat*		m_CBackproject; /**< Cached variables for speed up */
	CvMat*		m_CBs;			/**< Cached variables for speed up */
	double*		m_dist;			/**< Cached variables for speed up */
	asm_profile m_profile;		/**< Cached variables for speed up */
	asm_shape	m_search_shape;	/**< Cached variables for speed up */
	asm_shape	m_temp_shape;	/**< Cached variables for speed up */
};

/** You can define your own face detector function here
 @param shapes Returned face detected box which stores the Top-Left and Bottom-Right points, so its \a NPoints() = 2 here.
 @param image Image resource.
 @return false on no face exists in image, true otherwise.
*/
typedef	bool (*detect_func)(asm_shape& shape, const IplImage* image);


#endif  // _ASM_LIBRARY_H_

