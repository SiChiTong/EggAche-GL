//
// Interface of EggAche Graphics Library
// By BOT Man, 2016
//

#ifndef EGGACHE_GL
#define EGGACHE_GL

#include <list>
#include "EggAche_impl.h"

namespace EggAche
{
	class Egg;

	//===================EggAche Window========================

	class Window
	{
	public:
		Window (
			size_t width = 1000, size_t height = 750,		// Size at least 240 * 120
			const char *cap_string = "Hello EggAche");		// Caption String
		// Remarks:
		// 1. Create a Window of Logic Size width * height with Caption cap_string;
		// 2. If you click or press a key on Window, back-end will call fnClick or fnPress;
		//    Calling fnClick with (int x, int y) means point (x, y) is Clicked;
		//    Calling fnPress with (char ch) means character ch is Inputed;
		// 3. When an error occurs, throw std::runtime_error

		~Window ();

		Egg *GetEgg ();										// Get Background Egg
		void Refresh ();									// Refresh the Window
		bool IsClosed () const;								// Is Window closed
		
		Window (const Window &) = delete;					// Not allow to copy
		void operator= (const Window &) = delete;			// Not allow to copy

	private:
		void DrawEgg (const Egg *);							// Helper Function of Refresh
		WindowImpl *windowImpl;								// Window Impl Bridge
		Egg *bgEgg;											// Background Egg
	};

	//===========================Egg===========================

	class Egg
	{
	public:
		Egg (unsigned int width, unsigned int height,		// Egg's size
			 int pos_x = 0, int pos_y = 0);					// Egg's initial postion
		// Remarks:
		// When an error occurs, throw std::runtime_error

		~Egg ();

		int GetX () const;									// Get Egg's coordinate x
		int GetY () const;									// Get Egg's coordinate y
		void MoveTo (int pos_x, int pos_y);					// Place Egg to (pos_x, pos_y)
		void Move (int scale_x, int scale_y);				// Move Egg
		// Remarks:
		// If scale_x > 0, Egg will be moved right scale_x units; else moved left -scale_x;
		// Similarly move scale_y;

		void AddEgg (const Egg &egg);								// Add Sub Eggs
		void RemoveEgg (const Egg &egg);							// Remove Sub Eggs

		bool SetPen (unsigned int width,					// Pen width
					 unsigned int r = 0,					// Pen color
					 unsigned int g = 0,
					 unsigned int b = 0);
		bool SetBrush (unsigned int r,						// Brush color
					   unsigned int g,
					   unsigned int b);
		// Remarks:
		// If one of r/g/b = -1, the Pen/Brush will be set Transparent;

		bool DrawLine (int xBeg, int yBeg, int xEnd, int yEnd);
		// Remarks:
		// Draw a Line from (xBeg, yBeg) to (xEnd, yEnd);

		bool DrawRect (int xBeg, int yBeg, int xEnd, int yEnd);
		// Remarks:
		// Draw a Rectangle
		//   (xBeg, yBeg)-----------------(xEnd, yBeg)
		//        |                            |
		//        |                            |
		//        |                            |
		//        |                            |
		//   (xBeg, yEnd)-----------------(xEnd, yEnd);

		bool DrawElps (int xBeg, int yBeg, int xEnd, int yEnd);
		// Remarks:
		// Draw the Ellipse in such an imaginary bounding box;

		bool DrawRdRt (int xBeg, int yBeg,
					   int xEnd, int yEnd, int wElps, int hElps);
		// Remarks:
		// Draw a round conner Rectangle;
		// wElps, hElps = the width/height of the rounded corners Ellipse;

		bool DrawArc (int xLeft, int yTop, int xRight, int yBottom,
					  int xBeg, int yBeg, int xEnd, int yEnd);
		// Remarks:
		// The points (xLeft, yTop) and (xRight, yBottom) specify the bounding box;
		// An Ellipse formed by the bounding box defines the curve of the Arc;
		// The Arc extends in the current drawing direction from the point
		// where it intersects the radial from the center to (xBeg, yBeg);
		// The Arc ends where it intersects the radial to (xEnd, yEnd);

		bool DrawChord (int xLeft, int yTop, int xRight, int yBottom,
						int xBeg, int yBeg, int xEnd, int yEnd);
		// Remarks:
		// The points (xLeft, yTop) and (xRight, yBottom) specify the bounding box;
		// An Ellipse formed by the bounding box defines the curve of the Chord;
		// The curve begins at the point where the Ellipse intersects the first radial
		// and extends counterclockwise to the point where the second radial intersects;
		// The Chord is closed by drawing a line from the intersection of the first radial
		// and the curve to the intersection of the second radial and the curve;

		bool DrawPie (int xLeft, int yTop, int xRight, int yBottom,
					  int xBeg, int yBeg, int xEnd, int yEnd);
		// Remarks:
		// The points (xLeft, yTop) and (xRight, yBottom) specify the bounding box;
		// An Ellipse formed by the bounding box defines the curve of the Pie;
		// The curve begins at the point where the Ellipse intersects the first radial
		// and extends counterclockwise to the point where the second radial intersects;

		bool DrawTxt (int xBeg, int yBeg, const char *szText);
		// Remarks:
		// Draw the szText with a upper left point (xBeg, yBeg)

		bool DrawBmp (const char *szPath);					// Source: "path/name.bmp"

		bool DrawBmp (const char *szPath,					// Source: "path/name.bmp"
					  int x = 0, int y = 0,					// Position to paste in Egg
					  int width = -1, int height = -1,		// Size to paste in Egg (-1 as default)
					  int r = -1,							// Red color of mask (-1 is not used)
					  int g = -1,							// Green color of mask
					  int b = -1);							// Blue color of mask
		// Remarks:
		// 1. The bmp file will be stretched into width * height in Egg;
		// 2. The color of colorMask will be set to Transparent;
		//    If one of r/g/b is -1, the Egg will be set Opaque;

		void Clear ();										// Clear the Egg
		// Remarks:
		// Erase all the content in Egg

		Egg (const Egg &) = delete;							// Not allow to copy
		void operator= (const Egg &) = delete;				// Not allow to copy
		friend class Window;
	private:
		int x, y;											// Postion
		std::list<const Egg *> subEggs;						// Sub Eggs
		GUIContext *context;								// GUI Impl Bridge
	};

	//======================Message Box========================

	void MsgBox (
		const char *szTxt,						// Text String
		const char *szCap = "Hello EggAche");	// Caption String
	// Remarks:
	// Pop up a Message Box;
}

#endif  //EGGACHE_GL
