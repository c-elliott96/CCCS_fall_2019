#ifndef FONTIMAGE_H
#define FONTIMAGE_H
#include "SDL_ttf.h"

class FontImage
{
public:
    FontImage(const char fontfamily[] = "fonts/FreeSans.ttf", int size = 12)
	{
		atexit( TTF_Quit );
		if ( TTF_Init() != 0 )
		{
			printf("Error in Font::Font: TTF_Init() != 0 with error %s\n", TTF_GetError());
			exit(1);
		}
		fontImage = TTF_OpenFont(fontfamily, size);
	}

	~FontImage()
	{
		TTF_CloseFont( fontImage );
	}

    Image render(const char s[], const Color & c)
	{
		return Image(TTF_RenderText_Solid(fontImage, s, c));
	}

	Image render(const char s[], int r, int g, int b)
	{
        Color c = {Uint8(r), Uint8(g), Uint8(b), 0};
		return render(s, c);
	}

    Rect rect;

private:   
    TTF_Font * fontImage;
};

#endif