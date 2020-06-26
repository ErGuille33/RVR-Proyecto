#include "Button.h"

Button::Button(int posx, int posy, int w, int h, Texture *texture, ClientPlayer *cp, CallBackOnClick *callback)
{
	posx_ = posx;
	posy_ = posy;
	w_ = w;
	h_ = h;
	cb = callback;
	texture_ = texture;
	cp_ = cp;
}

bool Button::handleEvent(SDL_Event const &evt)
{
	if (enabled)
	{

		if (evt.type == SDL_MOUSEBUTTONUP && evt.button.button == SDL_BUTTON_LEFT)
		{
			SDL_Point p = {evt.button.x, evt.button.y};
			SDL_Rect r = {posx_, posy_, w_, h_};

			if (SDL_PointInRect(&p, &r))
			{
				cb(cp_);
				return true;
			}
		}
	}
	return false;
}

void Button::render()
{

	if (enabled)
	{
		SDL_Rect r = {posx_, posy_, w_, h_};
		texture_->render(r);
	}
}