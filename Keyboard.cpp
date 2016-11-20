/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <iostream>

#include <SDL/SDL.h>

/*#include "Menu.h"
#include "Texte.h"
#include "Joueur.h"
#include "Monde.h"
#include "Projectile.h"
#include "Jeu.h"*/
#include "Keyboard.h"

#define BTN_TRIANGLE 0
#define BTN_CIRCLE 1
#define BTN_CROSS 2
#define BTN_SQUARE 3
#define BTN_LTRIGGER 4
#define BTN_RTRIGGER 5
#define BTN_DOWN 6
#define BTN_LEFT 7
#define BTN_UP 8
#define BTN_RIGHT 9
#define BTN_SELECT 10
#define BTN_START 11

Keyboard::Keyboard(Jeu* jeu, Carte* carte, Encyclopedie* encycl, SDL_Surface* screen, int m) : 
    gpJeu(jeu), gpCarte(carte), gpEncyclopedie(encycl), mode(m), gFullScreen(1), 
    gpScreen(screen), tmp(0), tmpx(0), tmpc(0), tmpw(0), tmpt(0), tmpp(0), tmpm(0),
#ifdef __PSP2__
    ligne(0), colonne(0), ligneOption(2), volume(MIX_MAX_VOLUME), volson(32), ligneRecord(3), 
#else
    ligne(0), colonne(0), ligneOption(2), volume(32), volson(32), ligneRecord(3), 
#endif
    colonneRecord(0), temps(0), ligneVal(0), intro(0) {
    for (int i = 0; i < 3; i++) save[i]=0;
    for (int i = 0; i < 3; i++) rang[i]=0;
    loadP();
    gpJeu->getAudio()->setVolume(volume);
    gpJeu->getAudio()->setVolson(volson);
#ifdef __PSP2__
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    joystick = SDL_JoystickOpen(0);
#endif
}

void Keyboard::saveP() {
#ifdef __PSP2__
    ofstream f("ux0:data/zroth/save/system.dat",ios::out | ios::binary);
#else
    ofstream f("data/save/system.dat",ios::out | ios::binary);
#endif
    f.write((char *)&volume,sizeof(int));
    f.write((char *)&volson,sizeof(int));
    f.write((char *)&temps,sizeof(int));
    for (int i = 0; i < 3; i++) f.write((char *)&rang[i],sizeof(int));
    f.close();
}

void Keyboard::loadP() {
#ifdef __PSP2__
    ifstream f("ux0:data/zroth/save/system.dat",ios::in | ios::binary);
#else
    ifstream f("data/save/system.dat",ios::in | ios::binary);
#endif
    if(!f.is_open()) return;
    f.read((char *)&volume,sizeof(int));
    f.read((char *)&volson,sizeof(int));
    f.read((char *)&temps,sizeof(int));
    for (int i = 0; i < 3; i++) f.read((char *)&rang[i],sizeof(int));
    f.close();
}

int Keyboard::getLigne() {return ligne;}
int Keyboard::getColonne() {return colonne;}
int Keyboard::getSave(int i) {return save[i];}
void Keyboard::setSave(int i, int val) {save[i]=val;}
int Keyboard::getLigneOption() {return ligneOption;}
int Keyboard::getVolume() {return volume;}
int Keyboard::getVolson() {return volson;}
int Keyboard::getLigneRecord() {return ligneRecord;}
int Keyboard::getColonneRecord() {return colonneRecord;}
int Keyboard::getTemps() {return temps;}
void Keyboard::setTemps(int t) {temps=t;}
int Keyboard::getRang(int i) {return rang[i];}
void Keyboard::setRang(int i) {rang[i]=1;}
int Keyboard::getLigneVal() {return ligneVal;}
int Keyboard::getIntro() {return intro;}
int Keyboard::getMode() {return mode;}
void Keyboard::setMode(int i) {mode=i;}

int Keyboard::gererClavier() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
#ifdef __PSP2__
            case SDL_JOYBUTTONDOWN:
            case SDL_JOYBUTTONUP:
                if (joystick && pollKey(event) == -1) return -1;
                break;
#endif
            case SDL_QUIT : return -1;
            case SDL_KEYDOWN :
                if (pollKey(event) == -1) return -1;
                break;
        }
    }
    keys = SDL_GetKeyState(NULL);
    pollKeys(keys);

    return 0;
}

void Keyboard::toggleFullScreen() {
    gFullScreen = (gFullScreen ? 0 : SDL_FULLSCREEN);
    gFullScreen ? SDL_ShowCursor(SDL_DISABLE) : SDL_ShowCursor(SDL_ENABLE);
    gpScreen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE
                                |SDL_DOUBLEBUF|gFullScreen);   
}

int Keyboard::pollKey(SDL_Event event) {
#ifdef __PSP2__
    switch (event.jbutton.button) {
        case BTN_START :
#else
    switch (event.key.keysym.sym) {
        case SDLK_ESCAPE :
#endif
            if (mode==0) { if (!gpJeu->getStop() && !gpJeu->getJoueur()->getImmo() 
            && gpJeu->getJoueur()->getVie()>0) 
                gpJeu->ecrit(215);
            } else if (mode<8 || mode==9 || mode==15 || mode==16 || mode >18) return -1;
            break;
#ifdef __PSP2__
        case BTN_SELECT :
#else
        case SDLK_F1 :
#endif
            if (mode == 0) {mode = 17; gpJeu->getGenerique()->initAide1(); 
                gpJeu->getAudio()->playSound(1);}
            break;
#ifndef __PSP2__
        case SDLK_F4 :
            if (event.key.keysym.mod & KMOD_ALT) return -1;
            break;
        case SDLK_RETURN :
            if (event.key.keysym.mod & KMOD_CTRL) toggleFullScreen();
            break;
#endif
        default : break;
    }
    return 0;
}

void Keyboard::pollKeys(Uint8* keys) {
    Joueur* gpJoueur;
    int vit;
    int avance;
    int nbdir;
    switch (mode) {
        case 0 :
            gpJoueur = gpJeu->getJoueur();
            
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                if (gpJoueur->getTypeAnim() == MORT) gpJoueur->revie();
                else if (!gpJeu->getStop() && !gpJeu->getMenu()) gpJeu->setMenu(true);
                else if (gpJeu->getMenu()) gpJeu->setMenu(false);
                else if (gpJeu->getText()) gpJeu->setText(gpJeu->getTexte()->suite());
                tmp = 1;
            }
            if ((!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !gpJeu->getMenu()) || (gpJeu->getMenu() 
            && !(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !(keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) 
            && !(keys[SDLK_UP] || buttonPressed(BTN_UP)) && !(keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)))) tmp=0;
            
            if (gpJeu->getText() && gpJeu->getTexte()->isFinished()) {
                if(tmpt==0){
                    tmpt=1;
                    switch (gpJeu->getTexte()->getId()) {
                        case 27 : case 106 : case 114 : case 116 : case 118 : case 120 :
                        case 122 : case 124 : case 126 : case 153 : case 161 : case 166 :
                        case 169 : case 172 : case 176 :
                            if ((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) || (keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT))) {
                                gpJeu->getAudio()->playSound(3);
                                gpJeu->getTexte()->changeId(gpJeu->getTexte()->getId()+1);
                            }
                            break;
                        case 28 : case 107 : case 115 : case 117 : case 119 : case 121 :
                        case 123 : case 125 : case 127 : case 154 : case 162 : case 167 :
                        case 170 : case 173 : case 177 :
                            if ((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) || (keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT))) {
                                gpJeu->getAudio()->playSound(3);
                                gpJeu->getTexte()->changeId(gpJeu->getTexte()->getId()-1);
                            }
                            break;
                        case 215 : case 216 : case 217 : case 225 : case 226 :
                            if ((keys[SDLK_UP] || buttonPressed(BTN_UP)) && gpJeu->getTexte()->getId()!=215
                            && gpJeu->getTexte()->getId()!=225) {
                                gpJeu->getAudio()->playSound(3);
                                gpJeu->getTexte()->changeId(gpJeu->getTexte()->getId()-1);
                            }
                            if ((keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) && gpJeu->getTexte()->getId()!=217
                            && gpJeu->getTexte()->getId()!=226) {
                                gpJeu->getAudio()->playSound(3);
                                gpJeu->getTexte()->changeId(gpJeu->getTexte()->getId()+1);
                            }
                            break;
                    }
                }
                if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) 
                && !(keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && !(keys[SDLK_UP] || buttonPressed(BTN_UP)) && !(keys[SDLK_DOWN] || buttonPressed(BTN_DOWN))) tmpt=0;
            }
            
            nbdir=0;
            if ((keys[SDLK_UP] || buttonPressed(BTN_UP))) nbdir++;
            if ((keys[SDLK_DOWN] || buttonPressed(BTN_DOWN))) nbdir++;
            if ((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT))) nbdir++;
            if ((keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT))) nbdir++;
            
            int vitesse;
            if ((keys[SDLK_CAPSLOCK] || (keys[SDLK_LSHIFT] || buttonPressed(BTN_LTRIGGER))) && !gpJeu->getStop() 
            && gpJoueur->hasObjet(O_BOTTES)) vitesse=4; 
            else vitesse=2;
    
            avance=0;
            
            //marche
            if (!keys[SDLK_LCTRL] && (
            gpJoueur->getTypeAnim()==AUCUNE || gpJoueur->getTypeAnim()==MARCHE 
            || gpJoueur->getTypeAnim()==PORTE || gpJoueur->getTypeAnim()==EMMENE
            || gpJoueur->getTypeAnim()==NAGE || gpJoueur->getTypeAnim()==FLOTTE) 
            && !gpJeu->getStop() && !gpJeu->getTransition() && !gpJoueur->getImmo()) {
                gpJoueur->savePrec();
                if ((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT))) {
                    if(!gpJoueur->getCharge() 
                    && (!(keys[SDLK_UP] || buttonPressed(BTN_UP)) || gpJoueur->getDirection()!=N) 
                    && (!(keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) || gpJoueur->getDirection()!=S))
                        gpJoueur->setDirection(O);
                    if (gpJoueur->getX()%4==2) vit=2; else vit = vitesse;
                    //gpJeu->moveJoueurX(-vit, nbdir);
                    gpJoueur->moveX(-vit, nbdir);
                    avance = 1;
                }
                if ((keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT))) {
                    if(!gpJoueur->getCharge() 
                    && (!(keys[SDLK_UP] || buttonPressed(BTN_UP)) || gpJoueur->getDirection()!=N) 
                    && (!(keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) || gpJoueur->getDirection()!=S))
                        gpJoueur->setDirection(E);
                    if (gpJoueur->getX()%4==2) vit=2; else vit = vitesse;
                    //gpJeu->moveJoueurX(vit, nbdir);
                    gpJoueur->moveX(vit, nbdir);
                    avance=1;
                }
                if ((keys[SDLK_UP] || buttonPressed(BTN_UP))) {
                    if(!gpJoueur->getCharge()
                    && (!(keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) || gpJoueur->getDirection()!=O) 
                    && (!(keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) || gpJoueur->getDirection()!=E))
                        gpJoueur->setDirection(N);
                    if (gpJoueur->getY()%4!=0) vit=2; else vit = vitesse;
                    //gpJeu->moveJoueurY(-vit, nbdir);
                    gpJoueur->moveY(-vit, nbdir);
                    avance=1;
                }
                if ((keys[SDLK_DOWN] || buttonPressed(BTN_DOWN))) {
                    if(!gpJoueur->getCharge()
                    && (!(keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) || gpJoueur->getDirection()!=O) 
                    && (!(keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) || gpJoueur->getDirection()!=E))
                        gpJoueur->setDirection(S);
                    if (gpJoueur->getY()%4!=0) vit=2; else vit = vitesse;
                    //gpJeu->moveJoueurY(vit, nbdir);
                    gpJoueur->moveY(vit, nbdir);
                    avance=1;
                }
                if (gpJeu->getVueHorz()>0) {
                    if (gpJeu->getVueHorz()>=4) gpJeu->setVueHorz(gpJeu->getVueHorz()-4);
                    else gpJeu->setVueHorz(0);
                }
                if (gpJeu->getVueHorz()<0) {
                    if (gpJeu->getVueHorz()<=-4) gpJeu->setVueHorz(gpJeu->getVueHorz()+4);
                    else gpJeu->setVueHorz(0);
                }
                if (gpJeu->getVueVert()>0) {
                    if (gpJeu->getVueVert()>=4) gpJeu->setVueVert(gpJeu->getVueVert()-4);
                    else gpJeu->setVueVert(0);
                }
                if (gpJeu->getVueVert()<0) {
                    if (gpJeu->getVueVert()<=-4) gpJeu->setVueVert(gpJeu->getVueVert()+4);
                    else gpJeu->setVueVert(0);
                }
            }
            if (keys[SDLK_LCTRL] && !gpJoueur->getImmo()) {
                if ((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && gpJeu->getVueHorz()>-64)
                    gpJeu->setVueHorz(gpJeu->getVueHorz()-2);
                if ((keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && gpJeu->getVueHorz()<64)
                    gpJeu->setVueHorz(gpJeu->getVueHorz()+2);
                if ((keys[SDLK_UP] || buttonPressed(BTN_UP)) && gpJeu->getVueVert()>-64)
                    gpJeu->setVueVert(gpJeu->getVueVert()-2);
                if ((keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) && gpJeu->getVueVert()<64)
                    gpJeu->setVueVert(gpJeu->getVueVert()+2);
            }
            
            if (avance == 1) {
                if (gpJoueur->getTypeAnim()==AUCUNE) gpJoueur->setTypeAnim(MARCHE);
                if (gpJoueur->getTypeAnim()==FLOTTE) gpJoueur->setTypeAnim(NAGE);
                if (gpJoueur->getTypeAnim()==PORTE) gpJoueur->setTypeAnim(EMMENE);
                gpJeu->testFin();
            }
            else {
                if (gpJoueur->getTypeAnim()==MARCHE && !gpJeu->getStop()) 
                    gpJoueur->setTypeAnim(AUCUNE);
                if (gpJoueur->getTypeAnim()==NAGE && !gpJeu->getStop()) 
                    gpJoueur->setTypeAnim(FLOTTE);
                if (gpJoueur->getTypeAnim()==EMMENE && !gpJeu->getStop()) 
                    gpJoueur->setTypeAnim(PORTE);
            }
            
            
            //�p�e
            if ((gpJoueur->getTypeAnim()==AUCUNE || gpJoueur->getTypeAnim()==MARCHE) 
            && !gpJoueur->getCharge() && gpJoueur->getEpee() && !gpJeu->getStop()
            && !gpJoueur->isLapin() && !gpJoueur->getImmo()) {
                if (((keys[SDLK_z] || buttonPressed(BTN_SQUARE)) || keys[SDLK_w]) && !tmpw) {
                    gpJoueur->setTypeAnim(EPEE);
                    gpJoueur->chargeSpin();
                    tmpw=1;
                }
                if (!(keys[SDLK_z] || buttonPressed(BTN_SQUARE)) && !keys[SDLK_w] && tmpw) tmpw=0;
            }
            if (!(keys[SDLK_z] || buttonPressed(BTN_SQUARE)) && !keys[SDLK_w] && gpJoueur->getCharge() && !gpJeu->getStop() 
            && !gpJoueur->isLapin()) {
                if (gpJoueur->getCharge() >= 20) gpJoueur->setTypeAnim(SPIN);
                gpJoueur->dechargeSpin();
            }
            
            
            //curseur menu
            if (gpJeu->getMenu() && 
            (gpJoueur->getTypeAnim()<4 || gpJoueur->getTypeAnim()>20) && tmp==0) {
                if ((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT))) {
                    int obj = gpJoueur->getObjet();
                    if (obj%3 == 0) gpJoueur->setObjet(obj+2);
                    else gpJoueur->setObjet(obj-1);
                    gpJeu->getAudio()->playSound(3);
                    tmp=1;
                }
                if ((keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT))) {
                    int obj = gpJoueur->getObjet();
                    if (obj%3 == 2) gpJoueur->setObjet(obj-2);
                    else gpJoueur->setObjet(obj+1);
                    gpJeu->getAudio()->playSound(3);
                    tmp=1;
                }
                if ((keys[SDLK_UP] || buttonPressed(BTN_UP))) {
                    int obj = gpJoueur->getObjet();
                    if (obj/3 == 0) gpJoueur->setObjet(obj+9);
                    else gpJoueur->setObjet(obj-3);
                    gpJeu->getAudio()->playSound(3);
                    tmp=1;
                }
                if ((keys[SDLK_DOWN] || buttonPressed(BTN_DOWN))) {
                    int obj = gpJoueur->getObjet();
                    if (obj/3 == 3) gpJoueur->setObjet(obj-9);
                    else gpJoueur->setObjet(obj+3);
                    gpJeu->getAudio()->playSound(3);
                    tmp=1;
                }
            }
            
            
            
            if ((keys[SDLK_x] || buttonPressed(BTN_TRIANGLE)) && (
            gpJoueur->getTypeAnim()==AUCUNE || gpJoueur->getTypeAnim()==MARCHE || 
            (gpJoueur->getObjet()==8 && 
            (gpJoueur->getTypeAnim()==PORTE || gpJoueur->getTypeAnim()==EMMENE))) 
            && !gpJeu->getStop() && !gpJoueur->getImmo()
            && gpJoueur->getVie()>0 && !gpJoueur->getCharge() && !gpJoueur->isLapin() 
            && !tmpx) {
                tmpx=1;
                switch(gpJoueur->getObjet()) {
                    case 0 : //arc
                        if (gpJoueur->hasObjet(O_ARC)) gpJoueur->setTypeAnim(ARC);
                        break;
                    case 1 : //grappin
                        if (gpJoueur->hasObjet(O_GRAPPIN)) gpJoueur->setTypeAnim(GRAPPIN);
                        break;
                    case 2 : //bombe
                        if (gpJoueur->hasObjet(O_SAC_BOMBES) && gpJoueur->getBombe()) 
                            gpJoueur->setTypeAnim(BOMBE);
                        break;
                    case 3 : //baguette de feu
                        if (gpJoueur->hasObjet(O_BFEU)) gpJoueur->setTypeAnim(BFEU);
                        break;
                    case 4 : //baguette de glace
                        if (gpJoueur->hasObjet(O_BGLACE)) gpJoueur->setTypeAnim(BGLACE);
                        break;
                    case 5 : //lanterne
                        if (gpJoueur->hasObjet(O_LANTERNE) && gpJoueur->getMagie()) 
                            gpJoueur->setTypeAnim(LANTERNE);
                        break;
                    case 6 : //marteau
                        if (gpJoueur->hasObjet(O_MARTEAU)) gpJoueur->setTypeAnim(MARTEAU);
                        break;
                    case 8 : //gants
                        if (gpJoueur->hasObjet(O_GANTS)) {
                            if (gpJoueur->getTypeAnim()==AUCUNE 
                            || gpJoueur->getTypeAnim()==MARCHE) gpJeu->ramasse();
                            else if (gpJoueur->getTypeAnim()==PORTE 
                            || gpJoueur->getTypeAnim()==EMMENE) gpJoueur->setTypeAnim(LANCE);
                        }
                        break;
                    case 9 : // flacon
                    case 10 :
                    case 11 :
                        if (gpJoueur->hasBouteille(gpJoueur->getObjet()-9)) 
                            gpJoueur->setTypeAnim(BOIRE);
                        break;
                }    
            }
            
            if (!(keys[SDLK_x] || buttonPressed(BTN_TRIANGLE)) && tmpx) tmpx=0;
            
            if (keys[SDLK_c] && !tmpc && !gpJoueur->getCharge() && gpJoueur->getVie()>0
            && !gpJoueur->isLapin() && !gpJeu->getStop() && !gpJoueur->getImmo()) {
                if (gpJoueur->getTypeAnim()==AUCUNE || gpJoueur->getTypeAnim()==MARCHE)
                    gpJeu->ramasse();
                else if (gpJoueur->getTypeAnim()==PORTE || gpJoueur->getTypeAnim()==EMMENE)
                    gpJoueur->setTypeAnim(LANCE);
            }
            
            if (!keys[SDLK_c] && tmpc) tmpc=0;
            
            if ((keys[SDLK_SPACE] || buttonPressed(BTN_CIRCLE)) && !gpJeu->getStop() && gpJoueur->getVie() && 
            (gpJoueur->getTypeAnim()==AUCUNE || gpJoueur->getTypeAnim()==MARCHE) 
             && !gpJoueur->getImmo()) {
                gpJeu->lire();
            }
            
            if ((keys[SDLK_p] || buttonPressed(BTN_RTRIGGER)) && gpJoueur->hasObjet(O_CARTE) && 
            (gpJeu->isDehors() || gpJeu->isDonjon())
            && !gpJeu->getStop() && gpJoueur->getVie()>0 && !tmpp) {
                mode = 12;
                gpJeu->getAudio()->playSound(1);
                gpCarte->init();
                tmpp=1;
            }
            
            if (!(keys[SDLK_p] || buttonPressed(BTN_RTRIGGER)) && tmpp) tmpp=0;
            
            if ((keys[SDLK_m] || keys[SDLK_SEMICOLON]) && gpJoueur->hasObjet(O_ENCYCL)
            && !gpJeu->getStop() && gpJoueur->getVie()>0 && !tmpm) {
                mode = 13;
                gpJeu->getAudio()->playSound(1);
                gpEncyclopedie->setPage(0);
                gpEncyclopedie->init();
                tmpm=1;
            }
            
            if (!(keys[SDLK_m] || keys[SDLK_SEMICOLON]) && tmpm) tmpm=0;
            break;
        case 1 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                mode = 2;
                gpJeu->getGenerique()->initLogo();
                gpJeu->getAudio()->playSound(1);
                tmp = 1;
            }
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS))) tmp=0;
            break;
        case 2 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                mode = 3;
                gpJeu->getGenerique()->initTitre();
                gpJeu->getAudio()->playSound(1);
                gpJeu->getAudio()->playMusic(45);
                tmp = 1;
            }
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS))) tmp=0;
            break;
        case 3 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                mode = 4; colonne=0;
                gpJeu->getGenerique()->initSelection();
                gpJeu->getAudio()->playSound(1);
                gpJeu->getAudio()->playMusic(46);
                tmp = 1;
            }
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS))) tmp=0;
            break;
        case 4 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                if (ligne < 3) {
                    if (save[ligne]) {
                        mode = 7; ligneVal=0;
                        gpJeu->getGenerique()->initCharger();
                    }
                    else {
                        mode = 8; intro = 0; gpJeu->getGenerique()->initIntro();
                        gpJeu->getAudio()->playMusic(47);
                    }
                }
                if (ligne == 3 && colonne == 0) {
                    mode = 6; ligneOption=2;
                    gpJeu->getGenerique()->initOption();
                }
                if (ligne == 3 && colonne == 1) {
                    mode = 15; ligneRecord=3; colonneRecord=0;
                    gpJeu->getGenerique()->initRecord();
                }
                tmp=1; gpJeu->getAudio()->playSound(1);
            }
            
            if ((keys[SDLK_UP] || buttonPressed(BTN_UP)) && !tmp) {
                ligne--; if (ligne<0) ligne=3; tmp=1; 
                if (ligne!=3) colonne=0;
                gpJeu->getAudio()->playSound(3);}
            if ((keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) && !tmp) {
                ligne++; if (ligne>3) ligne=0; tmp=1;
                if (ligne!=3) colonne=0;
                gpJeu->getAudio()->playSound(3);}
            if ((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !tmp && ligne==3) {
                colonne--; if (colonne<0) colonne=1; tmp=1;
                gpJeu->getAudio()->playSound(3);}
            if ((keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && !tmp && ligne==3) {
                colonne++; if (colonne>1) colonne=0; tmp=1;
                gpJeu->getAudio()->playSound(3);}
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_UP] || buttonPressed(BTN_UP)) && !(keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) 
                && !(keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !(keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && tmp) tmp=0;
            break;
        case 6 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0 && ligneOption == 2) {
                mode = 4;
                gpJeu->getGenerique()->initSelection();
                gpJeu->getAudio()->playSound(2);
                tmp = 1;
                saveP();
            }
            
            if ((keys[SDLK_UP] || buttonPressed(BTN_UP)) && !tmp) {
                ligneOption--; if (ligneOption<0) ligneOption=2; tmp=1; 
                gpJeu->getAudio()->playSound(3);}
            if ((keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) && !tmp) {
                ligneOption++; if (ligneOption>2) ligneOption=0; tmp=1;
                gpJeu->getAudio()->playSound(3);}
            if ((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !tmp) {
                if (ligneOption == 0) {
                    volume-=8; if (volume < 0) volume = 0; tmp=1;
                    gpJeu->getAudio()->setVolume(volume); gpJeu->getAudio()->playSound(3);}
                if (ligneOption == 1) {
                    volson-=8; if (volson < 0) volson = 0; tmp=1;
                    gpJeu->getAudio()->setVolson(volson); gpJeu->getAudio()->playSound(3);}}
            if ((keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && !tmp) {
                if (ligneOption == 0) {
                    volume+=8; if (volume > 64) volume = 64; tmp=1;
                    gpJeu->getAudio()->setVolume(volume);gpJeu->getAudio()->playSound(3);}
                if (ligneOption == 1) {
                    volson+=8; if (volson > 64) volson = 64; tmp=1;
                    gpJeu->getAudio()->setVolson(volson);gpJeu->getAudio()->playSound(3);}}
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_UP] || buttonPressed(BTN_UP)) && !(keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) 
                && !(keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !(keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && tmp) tmp=0;
            break;
        case 7 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                if (ligneVal==0) {
                    mode = 0;
                    gpJeu->init(ligne+1);
                }
                if (ligneVal==1) {
                    mode = 9; ligneVal=1;
                    gpJeu->getGenerique()->initEffacer();
                    gpJeu->getAudio()->playSound(1);
                }
                if (ligneVal==2) {
                    mode = 4; gpJeu->getGenerique()->initSelection();
                    gpJeu->getAudio()->playSound(2);
                }    
                tmp = 1;
            }
            
            if ((keys[SDLK_UP] || buttonPressed(BTN_UP)) && !tmp) {
                if (--ligneVal<0) ligneVal=2; tmp=1; 
                gpJeu->getAudio()->playSound(3);}
            if ((keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) && !tmp) {
                if (++ligneVal>2) ligneVal=0; tmp=1;
                gpJeu->getAudio()->playSound(3);}
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_UP] || buttonPressed(BTN_UP)) && !(keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) && tmp) tmp=0;
            break;
        case 8 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                int old;
                old = gpJeu->getTexte()->getId();
                if (!gpJeu->getTexte()->suite()) {
                    mode = 10; gpJeu->getGenerique()->initNuit();
                    gpJeu->getAudio()->stopMusic();
                }
                else if (old != gpJeu->getTexte()->getId()) intro++;
                tmp = 1;
            }
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp) tmp=0;
            break;
        case 9 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                if (ligneVal==0) {
                    ostringstream oss; oss << (ligne+1);
#ifdef __PSP2__
                    remove(("ux0:data/zroth/save/roth" + oss.str() + ".dat").c_str());
#else
                    remove(("data/save/roth" + oss.str() + ".dat").c_str());
#endif
                    mode = 4; gpJeu->getGenerique()->initSelection();
                    gpJeu->getAudio()->playSound(2);
                }
                else {
                    mode = 7; gpJeu->getGenerique()->initCharger();
                    gpJeu->getAudio()->playSound(1);
                }
                tmp = 1;
            }
            
            if (((keys[SDLK_UP] || buttonPressed(BTN_UP)) || (keys[SDLK_DOWN] || buttonPressed(BTN_DOWN))) && !tmp) {
                ligneVal ? ligneVal=0 : ligneVal = 1; tmp=1;
                gpJeu->getAudio()->playSound(3);}
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_UP] || buttonPressed(BTN_UP)) && !(keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) && tmp) tmp=0;
            break;
        case 10 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                if (gpJeu->getText()) gpJeu->setText(gpJeu->getTexte()->suite());
                if (!gpJeu->getText()) {
                    mode = 0; gpJeu->init(ligne+1);
                    gpJeu->ecrit(236);
                }
                tmp = 1;
            }
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp) tmp=0;
            break;
        case 11 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                gpJeu->setText(gpJeu->getTexte()->suite());
                tmp = 1;
            }
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS))) tmp=0;
            break;
        case 12 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !tmp) {
                mode = 0;
                gpJeu->getAudio()->playSound(2);
                tmp=1;
            }
            
            if ((keys[SDLK_UP] || buttonPressed(BTN_UP)) && !tmp) {
                gpCarte->moveLevel(N);
                tmp=1;
            }
            if ((keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) && !tmp) {
                gpCarte->moveLevel(S);
                tmp=1;
            }
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_UP] || buttonPressed(BTN_UP)) && !(keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) && tmp) tmp=0;
            break;
        case 13 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !tmp) {
                mode = 0;
                gpJeu->getAudio()->playSound(2);
                tmp=1;
            }
            
            if ((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !tmp) {
                gpJeu->getAudio()->playSound(3);
                gpEncyclopedie->moveL();
                tmp=1;
            }
            if ((keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && !tmp) {
                gpJeu->getAudio()->playSound(3);
                gpEncyclopedie->moveR();
                tmp=1;
            }
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !(keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && tmp) tmp=0;
            break;
        case 14 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                mode = 2; gpJeu->getAudio()->playSound(1);
                gpJeu->getGenerique()->initLogo();
                tmp = 1;
            }
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp) tmp=0;
            break;
        case 15 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                if (ligneRecord==3) {
                    if (colonneRecord == 0) {
                        mode = 4;
                        gpJeu->getGenerique()->initSelection();
                        gpJeu->getAudio()->playSound(2);
                    }
                    else {
                        mode = 16; ligneVal=1;
                        gpJeu->getGenerique()->initEffacer();
                        gpJeu->getAudio()->playSound(1);
                    }
                }
                else {
                    mode = 19 + ligneRecord;
                    gpJeu->getGenerique()->initRang(ligneRecord);
                    gpJeu->getAudio()->playSound(1);
                }
                tmp = 1;
            }
            
            if ((keys[SDLK_UP] || buttonPressed(BTN_UP)) && !tmp) {
                ligneRecord--; if (ligneRecord<0) ligneRecord=3; tmp=1; 
                colonneRecord=0; gpJeu->getAudio()->playSound(3);}
            if ((keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) && !tmp) {
                ligneRecord++; if (ligneRecord>3) ligneRecord=0; tmp=1;
                colonneRecord=0; gpJeu->getAudio()->playSound(3);}
            
            if (((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) || (keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT))) && ligneRecord==3 && !tmp) {
                if (colonneRecord == 0) colonneRecord=1;
                else colonneRecord=0; tmp=1;
                gpJeu->getAudio()->playSound(3);}
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_UP] || buttonPressed(BTN_UP)) && !(keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) 
                && !(keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !(keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && tmp) tmp=0;
            break;
        case 16 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp == 0) {
                mode = 15;
                if (ligneVal==0) {
                    gpJeu->getAudio()->playSound(2);
                    temps=0; for (int i = 0; i < 3; i++) rang[i]=0; saveP();
                }
                else gpJeu->getAudio()->playSound(1);
                gpJeu->getGenerique()->initRecord();
                tmp = 1;
            }
            
            if (((keys[SDLK_UP] || buttonPressed(BTN_UP)) || (keys[SDLK_DOWN] || buttonPressed(BTN_DOWN))) && !tmp) {
                ligneVal ? ligneVal=0 : ligneVal = 1; tmp=1;
                gpJeu->getAudio()->playSound(3);}
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_UP] || buttonPressed(BTN_UP)) && !(keys[SDLK_DOWN] || buttonPressed(BTN_DOWN)) && tmp) tmp=0;
            break;
        case 17 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !tmp) {
                mode = 0;
                gpJeu->getAudio()->playSound(2);
                tmp=1;
            }
            if ((keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && !tmp) {
                mode = 18; gpJeu->getGenerique()->initAide2();
                gpJeu->getAudio()->playSound(3); tmp=1;}
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_RIGHT] || buttonPressed(BTN_RIGHT)) && tmp) tmp=0;
            break;
        case 18 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !tmp) {
                mode = 0;
                gpJeu->getAudio()->playSound(2);
                tmp=1;
            }
            if ((keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && !tmp) {
                mode = 17; gpJeu->getGenerique()->initAide1();
                gpJeu->getAudio()->playSound(3); tmp=1;}
            
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !(keys[SDLK_LEFT] || buttonPressed(BTN_LEFT)) && tmp) tmp=0;
            break;
        case 19 :
        case 20 :
        case 21 :
            if ((keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && !tmp) {
                mode = 15; gpJeu->getGenerique()->initRecord();
                gpJeu->getAudio()->playSound(2);
                tmp=1;
            }
            if (!(keys[SDLK_RETURN] || buttonPressed(BTN_CROSS)) && tmp) tmp=0;
            break;
    }
}

int Keyboard::buttonPressed(int i) {
#ifdef __PSP2__
    return SDL_JoystickGetButton(joystick, i);
#else
    return 0;
#endif
}