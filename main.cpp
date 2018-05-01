/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Keyboard.h"
#include "Generique.h"

#ifdef __vita__
#include <psp2/power.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>
#include <vitaGL.h>
#include <imgui_vita.h>

int _newlib_heap_size_user = 192 * 1024 * 1024;
bool bilinear = true;
bool vflux_window = false;
bool credits_window = false;
bool vflux_enabled = false;
float vcolors[3];
uint16_t *vindices;
float *colors;
float *vertices;
uint64_t tick;
SDL_Shader shader = SDL_SHADER_NONE;
#endif

SDL_Surface* init() {             // initialise SDL
    if(SDL_Init(SDL_INIT_VIDEO) == -1) {
        printf("Could not load SDL : %s\n", SDL_GetError());
        exit(-1);
    }
    atexit(SDL_Quit);
    //if(SDL_InitSubSystem(SDL_INIT_AUDIO) == -1) *SOUND = false;

#ifndef __vita__
    SDL_WM_SetCaption("Return of the Hylian",NULL);
    SDL_Surface* icon = SDL_LoadBMP("data/images/logos/triforce.ico");
    SDL_SetColorKey(icon,SDL_SRCCOLORKEY,SDL_MapRGB(icon->format,0,0,0));
    SDL_WM_SetIcon(icon,NULL);
#endif

    SDL_ShowCursor(SDL_DISABLE);

#ifdef __vita__
    return SDL_SetVideoMode(320, 240, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
#else
    return SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
#endif
}

#ifdef __vita__
void ImGui_callback() {
    ImGui_ImplVitaGL_NewFrame();

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Graphics")) {
            if (ImGui::MenuItem("Bilinear Filter", nullptr, bilinear)) {
                bilinear = !bilinear;
                SDL_SetVideoModeBilinear(bilinear);
            }
            if (ImGui::MenuItem("vFlux Config", nullptr, vflux_window)) {
                vflux_window = !vflux_window;
            }
            if (ImGui::BeginMenu("Shaders")) {
                if (ImGui::MenuItem("None", nullptr, shader == SDL_SHADER_NONE)) {
                    shader = SDL_SHADER_NONE;
                    SDL_SetVideoShader(SDL_SHADER_NONE);
                }
                if (ImGui::MenuItem("Sharp Bilinear", nullptr, shader == SDL_SHADER_SHARP_BILINEAR_SIMPLE)) {
                    shader = SDL_SHADER_SHARP_BILINEAR_SIMPLE;
                    SDL_SetVideoShader(SDL_SHADER_SHARP_BILINEAR_SIMPLE);
                }
                if (ImGui::MenuItem("Sharp Bilinear (Scanlines)", nullptr, shader == SDL_SHADER_SHARP_BILINEAR)) {
                    shader = SDL_SHADER_SHARP_BILINEAR;
                    SDL_SetVideoShader(SDL_SHADER_SHARP_BILINEAR);
                }
                if (ImGui::MenuItem("LCD 3x", nullptr, shader == SDL_SHADER_LCD3X)) {
                    shader = SDL_SHADER_LCD3X;
                    SDL_SetVideoShader(SDL_SHADER_LCD3X);
                }
                if (ImGui::MenuItem("xBR x2", nullptr, shader == SDL_SHADER_XBR_2X_FAST)) {
                    shader = SDL_SHADER_XBR_2X_FAST;
                    SDL_SetVideoShader(SDL_SHADER_XBR_2X_FAST);
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Info")) {
            if (ImGui::MenuItem("Credits", nullptr, credits_window)) {
                credits_window = !credits_window;
            }
            ImGui::EndMenu();
        }

        if (vflux_window) {
            ImGui::Begin("vFlux Configuration", &vflux_window);
            ImGui::ColorPicker3("Filter Color", vcolors);
            ImGui::Checkbox("Enable vFlux", &vflux_enabled);
            ImGui::End();
        }

        if (credits_window) {
            ImGui::Begin("Credits", &credits_window);
            ImGui::TextColored(ImVec4(255, 255, 0, 255), "Zelda: Return of the Hylian v1.2");
            ImGui::Text("Game Creator: Vincent Jouillat");
            ImGui::Text("Port Author: usineur");
            ImGui::Separator();
            ImGui::TextColored(ImVec4(255, 255, 0, 255), "Special thanks to:");
            ImGui::Text("Rinnegatamante: SDL 1.2 and imgui Vita ports");
            ImGui::Text("littlebalup: several enhancements");
            ImGui::End();
        }

        ImGui::SameLine();
        ImGui::SetCursorPosX(870);

        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::EndMainMenuBar();
    }

    if (vflux_enabled) {
        memcpy(&colors[0], vcolors, sizeof(float) * 3);
        memcpy(&colors[4], vcolors, sizeof(float) * 3);
        memcpy(&colors[8], vcolors, sizeof(float) * 3);
        memcpy(&colors[12], vcolors, sizeof(float) * 3);

        float a;
        SceDateTime time;
        sceRtcGetCurrentClockLocalTime(&time);
        if (time.hour < 6)        // Night/Early Morning
            a = 0.25f;
        else if (time.hour < 10) // Morning/Early Day
            a = 0.1f;
        else if (time.hour < 15) // Mid day
            a = 0.05f;
        else if (time.hour < 19) // Late day
            a = 0.15f;
        else // Evening/Night
            a = 0.2f;
        colors[3] = colors[7] = colors[11] = colors[15] = a;
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        vglIndexPointerMapped(vindices);
        vglVertexPointerMapped(vertices);
        vglColorPointerMapped(GL_FLOAT, colors);
        vglDrawObjects(GL_TRIANGLE_FAN, 4, true);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }

    ImGui::Render();
    ImGui_ImplVitaGL_RenderDrawData(ImGui::GetDrawData());

    SceTouchData touch;
    sceTouchPeek(SCE_TOUCH_PORT_FRONT, &touch, 1);
    uint64_t delta_touch = sceKernelGetProcessTimeWide() - tick;
    if (touch.reportNum > 0) {
        ImGui::GetIO().MouseDrawCursor = true;
        tick = sceKernelGetProcessTimeWide();
    } else if (delta_touch > 3000000) {
        ImGui::GetIO().MouseDrawCursor = false;
    }
}
#endif

int main(int argc, char** argv) {
#ifdef __vita__
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG_WIDE);
    sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
    sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DISABLE_AUTO_SUSPEND);
    scePowerSetArmClockFrequency(444);

    sceIoMkdir("ux0:data/zroth", 0777);
    sceIoMkdir("ux0:data/zroth/save", 0777);
#endif

    if (argc && argv); //pour �viter un warning.....

    std::srand(std::time(NULL));

    SDL_Rect src;
    SDL_Rect dst;
    src.w=640; src.h=480; src.y=0;src.x=0;dst.x=0; dst.y=0;

    SDL_Surface* gpScreen = NULL;

    int mode = 2; //mode=0;

    gpScreen = init();
#ifdef __vita__
    int sh = 544;
    int sw = (float)gpScreen->w*((float)sh/(float)gpScreen->h);
    int x = (960 - sw)/2;
    SDL_SetVideoModeScaling(x, 0, sw, sh);
#endif
    SDL_Surface* gpScreen2 = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 240, 32, 0, 0, 0, 0);
    SDL_Surface* gpScreen3 = NULL;

#ifdef __vita__
    vindices = (uint16_t*)malloc(sizeof(uint16_t)*4);
    colors = (float*)malloc(sizeof(float)*4*4);
    vertices = (float*)malloc(sizeof(float)*3*4);
    vertices[0] =   0.0f;
    vertices[1] =   0.0f;
    vertices[2] =   0.0f;
    vertices[3] = 960.0f;
    vertices[4] =   0.0f;
    vertices[5] =   0.0f;
    vertices[6] = 960.0f;
    vertices[7] = 544.0f;
    vertices[8] =   0.0f;
    vertices[9] =   0.0f;
    vertices[10]= 544.0f;
    vertices[11]=   0.0f;
    vindices[0] = 0;
    vindices[1] = 1;
    vindices[2] = 2;
    vindices[3] = 3;

    ImGui::CreateContext();
    ImGui_ImplVitaGL_Init();
    ImGui_ImplVitaGL_TouchUsage(true);
    ImGui_ImplVitaGL_MouseStickUsage(false);
    ImGui_ImplVitaGL_UseIndirectFrontTouch(true);
    ImGui::StyleColorsDark();
    ImGui::GetIO().MouseDrawCursor = false;

    SDL_SetVideoCallback(ImGui_callback);
#endif

    Audio* gpAudio = new Audio();
    Jeu* gpJeu = new Jeu(gpAudio);
    Carte* gpCarte = new Carte(gpJeu);
    Encyclopedie* gpEncyclopedie = new Encyclopedie(gpJeu);
    Keyboard* gpKeyboard = new Keyboard(gpJeu, gpCarte, gpEncyclopedie, gpScreen, mode);
    gpJeu->setKeyboard(gpKeyboard);
    Generique* gpGenerique = new Generique(gpJeu);
    gpJeu->setGenerique(gpGenerique);
    //gpGenerique->initDisclamer();
    gpGenerique->initLogo();

    //gpJeu->init(5);

    bool gLoop = true;

    Uint32 lastAnimTime = SDL_GetTicks();

    while (gLoop) {

        if (gpKeyboard->gererClavier() == -1) {gLoop = false;}

        switch (gpKeyboard->getMode()) {
            case 0 : //jeu normal
                gpJeu->draw(gpScreen2); break;
            case 1 : //disclamer
            case 2 : //logo
            case 3 : //titre
            case 14 : //g�n�rique score
            case 17 : //menu d'aide 1
            case 18 : //menu d'aide 2
                gpGenerique->draw(gpScreen2); break;
            case 4 : //selection
                gpGenerique->drawSelection(gpScreen2, gpKeyboard->getLigne(),
                    gpKeyboard->getColonne()); break;
            case 6 : //options
                gpGenerique->drawOption(gpScreen2, gpKeyboard->getLigneOption(),
                gpKeyboard->getVolume()/8, gpKeyboard->getVolson()/8); break;
            case 7 : //charger partie
                gpGenerique->drawCharger(gpScreen2, gpKeyboard->getLigne(),
                    gpKeyboard->getLigneVal()); break;
            case 8 : //g�n�rique intro
                gpGenerique->drawIntro(gpScreen2, gpKeyboard->getIntro()); break;
            case 9 : //effacer partie
                gpGenerique->drawEffacerSave(gpScreen2, gpKeyboard->getLigne(),
                    gpKeyboard->getLigneVal()); break;
            case 10 : //g�n�rique d�but chez link
                gpGenerique->drawDebut(gpScreen2); break;
            case 11 : //g�n�rique fin
                gpGenerique->drawFin(gpScreen2); break;
            case 12 : //carte
                gpCarte->draw(gpScreen2); break;
            case 13 : //encyclop�die des monstres
                gpEncyclopedie->draw(gpScreen2); break;
            case 15 : //records
            case 19 : //rang 100%
            case 20 : //rang ultime
            case 21 : //rang de rapidit�
                gpGenerique->drawRecord(gpScreen2, gpKeyboard->getLigneRecord(),
                    gpKeyboard->getColonneRecord()); break;
            case 16 : //effacer record
                gpGenerique->drawEffacer(gpScreen2, gpKeyboard->getLigneVal()); break;
            default : break;
        }

#ifdef __vita__
        SDL_BlitSurface(gpScreen2, &src, gpScreen, &dst);
#else
        SDL_FreeSurface(gpScreen3);
        gpScreen3 = zoomSurface (gpScreen2, 2, 2, 0);

        SDL_BlitSurface(gpScreen3, &src, gpScreen, &dst);
#endif

        SDL_Flip(gpScreen);

        if (SDL_GetTicks() < lastAnimTime + 20) SDL_Delay(lastAnimTime+20-SDL_GetTicks());
        lastAnimTime = SDL_GetTicks();

    }

    SDL_FreeSurface(gpScreen2);
    SDL_FreeSurface(gpScreen3);

    delete gpEncyclopedie;
    delete gpGenerique;
    delete gpKeyboard;
    delete gpCarte;
    delete gpJeu;
    delete gpAudio;

    SDL_ShowCursor(SDL_ENABLE);
    SDL_Quit();
    exit(0);

    return 0;
}
