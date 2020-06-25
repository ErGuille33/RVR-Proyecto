#pragma once

#include "Texture.h"
#include <iostream>

class ClientPlayer;

using CallBackOnClick = void(ClientPlayer*);


class Button {
    protected:
        CallBackOnClick* cb;
        ClientPlayer* cp_;
        int posx_;
        int posy_;
        int w_;
        int h_;
        Texture* texture_;

    public:
        Button(int posx, int posy, int w, int h, Texture* texture, ClientPlayer* cp, CallBackOnClick* callback);
        ~Button() {
            cb = nullptr;
        }
        void render();
        bool handleEvent(SDL_Event const& evt);
    
};