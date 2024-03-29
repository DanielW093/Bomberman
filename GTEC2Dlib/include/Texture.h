#pragma once

#include "GTEC.h"

using namespace std;

class CTexture
{
public:
	
	// ----- Constructors & Destructor -----
	
	CTexture() { Width=Height=0; TextureID=0; Frames=frame=1; Zoom=100;}
	
	~CTexture() { glDeleteTextures( 1, &TextureID); }

	// ----- Attributes ------

private:
	
	// Position & Size
	int Width, Height;		// width and height of texture in pixels
    GLuint TextureID;		// OpenGL texture ID
	int frame, Frames;
	double Zoom;

	
public:
	

	// Size of the Texture
	int GetWidth()			    	    { return Width; }
	int GetHeight()			    		{ return Height; }
	void SetSize(int w, int h)         { Width=w; Height=h; }
	
	void SetZoom(double zoom);
	double GetZoom()					{ return Zoom; }
	
	
	int GetFrames()						{ return Frames; }
	void SetFrame (int f) 				{ frame=f; }
	void NextFrame()					{ frame++; if (frame > Frames) frame=1; }

	GLuint GetTextureID()				{ return TextureID; }
	
    bool LoadTextureFromBitmap( string filename, int frames=1);
	void Draw(int x, int y);

private:

	unsigned char* LoadFromBMP(const char* filename);
    int readWord(FILE* in, int len);

        

	
};



