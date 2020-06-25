#pragma once

#include "Texture.h"

class GameObject {
    protected:
        int posx_;
        int posy_;
        int w_;
        int h_;
        Texture* texture_;
        bool enabled = true;

    public:
        GameObject(int posx, int posy, int w, int h, Texture* texture) {
            posx_ = posx;
            posy_ = posy;
            w_ = w;
            h_ = h;
            texture_ = texture;
        }

        void render() {
            if(enabled) {
                SDL_Rect r = { posx_, posy_, w_, h_ };
                texture_->render(r);
            }
        }

        void setEnabled(bool aux) {
            enabled = aux;
        }

}