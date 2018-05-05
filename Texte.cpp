/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Texte.h"
#include "Menu.h"
#include "Joueur.h"
#include "Monde.h"
#include "Projectile.h"
#include "Jeu.h"

Texte::Texte(Jeu* jeu) : gpJeu(jeu), vitesse(40), av(0), x(0), y(0), w(0), h(0),
id(0), idsuiv(0), def(false), cadre(false), texte(""), buffer("") {
    lastAnimTime = SDL_GetTicks();
    imageFont = gpJeu->loadImg("data/images/texte/font.png");
    SDL_SetColorKey(imageFont,SDL_SRCCOLORKEY,SDL_MapRGB(imageFont->format,0,0,255));
    imageCoeur = gpJeu->loadImg("data/images/menu/coeur.png");
    SDL_SetColorKey(imageCoeur,SDL_SRCCOLORKEY,SDL_MapRGB(imageCoeur->format,0,0,255));
    getTextByLangFunc = &Texte::getTexteEN;
}

Texte::~Texte() {
    SDL_FreeSurface(imageFont);
    SDL_FreeSurface(imageCoeur);
}

void Texte::setTextLanguage(int id){
    switch(id){
        case 2:
            getTextByLangFunc = &Texte::getTexteFR;
            break;
        default:
            getTextByLangFunc = &Texte::getTexteEN;
    }
}

std::string Texte::getTexteEN(int id, std::string s){
    std::string texte = "";
    switch(id) {
        // 0 -> 99 : Carte
        case 0 : 
            texte = "Forest Temple"; 
            break;
        case 1 : 
            texte = "Water Temple"; 
            break;
        case 2 : 
            texte = "Mountain Temple";
            break;
        case 3 : 
            texte = "Desert Temple"; 
            break;
        case 4 : 
            texte = "Dark Temple"; 
            break;
        case 5 : 
            texte = "Fire Temple"; 
            break;
        case 6 : 
            texte = "Ice Temple"; 
            break;
        case 7 : 
            texte = "Hidden Temple"; 
            break;
        case 8 : 
            texte = "Hyrule Castle"; 
            break;

        // 100 -> 199 : Encyclopedie
        case 100 : 
            texte = "MONSTERS " + s;
            break;
            
        // 200 -> 299 : Generique
        case 200 :
            texte = "PLAYER SELECT";
            break;
        case 201 : 
            texte = "1.";
            break;
        case 202 :
            texte = "2.";
            break;
        case 203 : 
            texte = "3.";
            break;
        case 204 :
            texte = "OPTIONS";
            break;
        case 205 :
            texte = "RECORDS";
            break;
        case 206 :
            texte = "OPTIONS";
            break;
        case 207 :
            texte = "MUSIC";
            break;
        case 208 :
            texte = "SOUND";
            break;
        case 209 :
            texte = "RETURN";
            break;
        case 210 :
            texte = "RECORDS";
            break;
        case 211 :
            texte = "BEST TIME: " + s;
            break;
        case 212 :
            texte = "100% RANK";
            break;
        case 213 :
            texte = "ULTIMATE RANK";
            break;
        case 214 :
            texte = "SPEED RANK";
            break;
        case 215 :
            texte = "RETURN";
            break;
        case 216 :
            texte = "ERASE";
            break;
        case 217 :
            texte = "ERASE ?";
            break;
        case 218 :
            texte = "YES";
            break;
        case 219 :
            texte = "NO";
            break;
        case 220 :
            texte = "LOAD";
            break;
        case 221 :
            texte = "ERASE";
            break;
        case 222 :
            texte = "CANCEL";
            break;
        case 223 :
            texte = "HELP 1/2";
            break;
        case 224 :
#ifdef __vita__
            texte = "Return to the game: Cross - Next: <";
#else
            texte = "Return to the game: Enter - Next: Right";
#endif
            break;
        case 225 :
#ifdef __vita__
            texte = "Read / Open / Speak: Circle";
#else
            texte = "Read / Open / Speak: Space";
#endif
            break;
        case 226 :
#ifdef __vita__
            texte = "Confirm / Pass text: Cross";
#else
            texte = "Confirm / Pass text: Enter";
#endif
            break;
        case 227 :
#ifdef __vita__
            texte = "Move Link: Left stick";
#else
            texte = "Move Link: Direction Arrows";
#endif
            break;
        case 228 :
#ifdef __vita__
            texte = "Run : L (lock) / R";
#else
            texte = "Run : Shift hold or Caps lock";
#endif
            break;
        case 229 :
#ifdef __vita__
            texte = "Use sword: Square";
#else
            texte = "Use sword: Z or W";
#endif
            break;
        case 230 :
#ifdef __vita__
            texte = "Spin attack: Hold square then dropped";
#else
            texte = "Spin attack: Z or W hold then dropped";
#endif
            break;
        case 231 :
#ifdef __vita__
            texte = "Item selection: Right D-Pad";
#else
            texte = "Item selection: Enter";
#endif
            break;
        case 232 :
#ifdef __vita__
            texte = "Use selected object: Triangle";
#else
            texte = "Use selected object: X";
#endif
            break;
        case 233 :
#ifdef __vita__
            texte = "Carry without select gloves: Cross";
#else
            texte = "Carry without select gloves: C";
#endif
            break;
        case 234 :
#ifdef __vita__
            texte = "See the map: Left D-Pad (outside or dungeons)";
#else
            texte = "See the map: P (outside or dungeons)";
#endif
            break;
        case 235 :
#ifdef __vita__
            texte = "See the map: Left D-Pad (in dungeons)";
#else
            texte = "See the map: P (in dungeons)";
#endif
            break;
        case 236 :
#ifdef __vita__
            texte = "See defeated monsters: Up D-Pad";
#else
            texte = "See defeated monsters: M";
#endif
            break;
        case 237 :
#ifdef __vita__
            texte = "Look around: Right stick";
#else
            texte = "Look around: Ctrl and direction";
#endif
            break;
        case 238 :
#ifdef __vita__
            texte = "Save / Quit: Start";
#else
            texte = "Save / Quit: Esc";
#endif
            break;
        case 239 :
#ifdef __vita__
            texte = "";
#else
            texte = "Enlarge / Shrink: Ctrl and Enter";
#endif
            break;
        case 240 :
            texte = "HELP 2/2";
            break;
        case 241 :    
#ifdef __vita__
            texte = "Return to the game: Cross - Previous: >";
#else
            texte = "Return to the game: Enter - Previous: Left";
#endif
            break;
        case 242 :
#ifdef __vita__
            texte = "Use selected object: Triangle";
#else
            texte = "Use selected object: X";
#endif
            break;
        case 243 :
#ifdef __vita__
            texte = "Carry without select gloves: Cross"; 
#else
            texte = "Carry without select gloves: C"; 
#endif
            break;
        case 244 :
#ifdef __vita__
            texte = "See the map: Left D-Pad (outside or dungeons)";
#else
            texte = "See the map: P (outside or dungeons)";
#endif
            break;
        case 245 :
#ifdef __vita__
            texte = "See the map: Left D-Pad (in dungeons)";
#else
            texte = "See the map: P (in dungeons)";
#endif
            break;
        case 246 :
#ifdef __vita__
            texte = "See defeated monsters: Up D-Pad";
#else
            texte = "See defeated monsters: M";
#endif
            break;
        case 247 :
#ifdef __vita__
            texte = "Look around: Right stick";
#else
            texte = "Look around: Ctrl and direction";
#endif
            break;
        case 248 :
#ifdef __vita__
            texte = "Save / Quit: Start";
#else
            texte = "Save / Quit: Esc";
#endif
            break;
        case 249 :
#ifdef __vita__
            texte = "";
#else
            texte = "Enlarge / Shrink: Ctrl and Enter";
#endif
            break;

        case 250 :
            texte = "RANK: Hero of Hyrule";
            break;
        case 251 :
            texte = "RANK: UNKNOWN";
            break;
        case 252 :
            texte = "100% completion of the game";
            break;
        case 253 :
            texte = "RANK: Swanky";
            break;
        case 254 :
            texte = "RANK: UNKNOW";
            break;
        case 255 :
            texte = "Completed the game without dying,";
            break;
        case 256 :
            texte = "with 10 hearts at the very most,";
            break;
        case 257 :
            texte = "without talking to the Great Fairies,";
            break;
        case 258 :
            texte = "without buying bottles";
            break;
        case 259 :
            texte = "and without taking a shield.";
            break;
        case 260 :
            texte = "RANK: Hyrule Marathon Runner";
            break;
        case 261 :
            texte = "RANK: UNKNOW";
            break;
        case 262 :
            texte = "Complete the game in less than";
            break;
        case 263 :
            texte = "two hours";
            break;
        case 264 : 
            texte = "RESULTS:";
            break;
        case 265 :
            texte = "Game time: " + s;
            break;
        case 266 :
            texte = "Dead " + s + " time";
            break;
        case 267 :
            texte = "Dead " + s + " times";
            break;
        case 268 :
            texte = "Pieces of heart: " + s + " / 36";
            break;
        case 269 :
            texte = "Objects: " + s + " / 56";
            break;
        case 270 :
            texte = "Defeated all kinds of enemies: " + s + " / 46";
            break;
        case 271 :
            texte = "You completed the game with " + s + "%, congratulations!";
            break;
        case 272 :
            texte = "RANK: ";
            break;
        case 273 :
            texte = " - Swanky";
            break;
        case 274 :
            texte = " - Hero of Hyrule";
            break;
        case 275 :
            texte = " - Perfectionist";
            break;
        case 276 :
            texte = " - Zelda Fan";
            break;
        case 277 :
#ifdef __vita__
            texte = " - Pad professional";
#else
            texte = " - Keyboard professional";
#endif
            break;
        case 278 :
            texte = " - Experienced";
            break;
        case 279 :
            texte = " - Novice";
            break;
        case 280 :
            texte = " - Living dead";
            break;
        case 281 : 
            texte = " - Kamikaze";
            break;
        case 282 :
            texte = " - Hyrule Marathon Runner";
            break;
        case 283 :
            texte = "LANGUAGE";
            break;
        case 284 :
            texte = "English";
            break;

        // 300 -> 399 : Menu
        case 300 :
            texte = "X";
            break;
        case 301 :
            texte = "STATUS:";
            break;
        case 302 :
            texte = "LIFE      : " + s;
            break;
        case 303 :
            texte = "MAGIC     : " + s;
            break;
        case 304 :
            texte = "STRENGTH  : " + s;
            break;
        case 305 :
            texte = "DEFENSE   : " + s;
            break;
        case 306 :
            texte = "TIME      : " + s;
            break;
        case 307 :
            texte = "CRYSTALS:";
            break;

        // 500 -> ? : Texte
        case 501 : texte = "You find a shield!!!**Your defense rises by one point!"; break;
#ifdef __vita__
        case 502 : texte = "You find a sword!!!**You can now fight monsters with the key Square!!!*Hold Square to charge a spin attack!!!"; break;
#else
        case 502 : texte = "You find a sword!!!**You can now fight monsters with the key Z (or W)!!!*Hold Z to charge a spin attack!!!"; break;
#endif
        case 503 : texte = "You find a piece of heart!!!"; break;
        case 504 : texte = "Again "+s+" before having a new heart!!!"; break;
        case 505 : texte = "Your heart count just increases!!!"; break;
        case 511 : texte = "N: Link's Home*W: Hyrule Field*E: Forest Temple"; break;
        case 512 : texte = "Mountain Temple**Not for cardiacs, scaredy-cats, and generally faint of heart."; break;
        case 513 : texte = "W: Desert entrance*N: Mountain Temple"; break;
        case 514 : texte = "N: Mountain Temple*S: Hyrule Field"; break;
        case 515 : texte = "N: Death Mountain"; break;
        case 516 : texte = "E: Forest Entrance"; break;
        case 517 : texte = "S: Lake Hylia*E: Haunted Graveyard"; break;
        case 518 : texte = "S: To Kakariko Village"; break;
        case 519 : texte = "N: Kakariko Village"; break;
        case 520 : texte = "N: Hyrule Field"; break;
        case 521 : texte = "W: Fire Land"; break;
        case 522 : texte = "E: Shadow Village*- Not for the living -"; break;
        case 523 : texte = "Dark Temple**If you are a ghost, seeking a job, you'd better come here to hang out with us."; break;
        case 524 : texte = "N: Shadow Village*W: Lake Hylia"; break;
        case 525 : texte = "N: Haunted Graveyard**No entry"; break;
        case 526 : texte = "Shadow Village"; break;
        case 527 : texte = "I am selling a bottle for 100 rupees, are you interested?*              YES ?            no  "; break;
        case 528 : texte = "I am selling a bottle for 100 rupees, are you interested?*              yes             NO ?"; break;
        case 529 : texte = "Sorry, you don't have enough rupees"; break;
        case 530 : texte = "Thank you, here is your bottle."; break;
        case 531 : texte = "Come again if you change your mind."; break;
        case 532 : texte = "Sorry, that was my only bottle."; break;
        case 533 : texte = "You find an empty bottle!!!**It will help you to stock potions!!!"; break;
        case 535 : texte = "The inhabitants of that village have a dialect out of the ordinary, I don't understand anything..."; break;
        case 536 : texte = "@+@+@+@+@+@+@@@+*@=++=@=+@=+@=+=@*+@+@+@+=+="; break;
        case 537 : texte = "Wangle chief's permit if you really want to pass!!!"; break;
        case 538 : texte = "The chief allows you to pass??? Grrrr... So move along!!!"; break;
        case 539 : texte = "Get out of my way!!!"; break;
        case 540 : texte = "It's not common to have visitors around here."; break;
        case 541 : texte = "Local monsters don't fear a lot of things, fortunately they only attack humans."; break;
        case 542 : texte = "Really?*You understand what I say?"; break;
        case 543 : texte = "N: Desert and Gerudo Village"; break;
        case 544 : texte = "S: Lake Hylia*W: Hyrule Castle"; break;
        case 545 : texte = "Kakariko Village"; break;
        case 546 : texte = "W: Hyrule Castle"; break;
        case 547 : texte = "What a good day!!!"; break;
        case 548 : texte = "But why did I accept to take care of that rubbish???*I loathe hens!!!"; break;
        case 549 : texte = "You can find a lot of things in the shop of this village."; break;
        case 550 : texte = "S: Kakariko Village*W: Desert*E: Death Mountain"; break;
        case 551 : texte = "Gerudo Village"; break;
        case 552 : texte = "Lost in the desert?*You are here:*                        X"; break;
        case 554 : texte = "S: To Hyrule Castle"; break;
        case 555 : texte = "Desert Temple**Come to try our bath.*(water is not for drinking)"; break;
        case 556 : texte = "Forest Temple**Save the trees, eat beaver!!!"; break;
        case 557 : texte = "Lake Temple**Compulsory bathing cap."; break;
        case 558 : texte = "Ice Temple**The staff wishes to remind you that a dungeon is not a ice rink."; break;
        case 559 : texte = "Did you see the blacksmith of that village?*He is said to be very gifted to improve adventurers' equipment, a lot of people visit him."; break;
        case 560 : texte = "The Temple is in the deepest desert, in an ancient oasis."; break;
        case 561 : texte = "S: Fire Land*E: Kakariko Village"; break;
        case 562 : texte = "Hyrule Castle"; break;
        case 563 : texte = "E: Kakariko Village"; break;
        case 564 : texte = "W: Turtle Rock*E: Lake Hylia"; break;
        case 565 : texte = "Hidden Temple**Here rests the Sword of Evils Bane, the Master Sword."; break;
        case 566 : texte = "N: To the Haunted Graveyard"; break;
#ifdef __vita__
        case 567 : texte = "You find the Dungeon Map!!!*Press Left to see the map."; break;
#else
        case 567 : texte = "You find the Dungeon Map!!!*Press P to see the map."; break;
#endif
        case 568 : texte = "You find the Compass!!!*You can locate the boss and chests on the plan."; break;
        case 569 : texte = "You find the Boss Key!!!"; break;
        case 570 : texte = "You find a small key!!!*Go near a door to open it."; break;
#ifdef __vita__
        case 571 : texte = "You find the Gloves!!!*Use them to lift some object setting them up or pressing Cross."; break;
#else        
        case 571 : texte = "You find the Gloves!!!*Use them to lift some object setting them up or pressing C."; break;
#endif
        case 572 : texte = "You find a Magic Crystal!!!"; break;
        case 573 : texte = "For what may it be used...?"; break;
        case 574 : texte = "There are "+s+" left to find!!!"; break;
        case 575 : texte = "Only 2 left to find!!!"; break;
        case 576 : texte = "You lack only one!!!"; break;
        case 577 : texte = "You have all the crystals, run to the castle and save Zelda!!!"; break;
        case 580 : texte = "You find the Hookshot!!!*Use it to overcome obstacles."; break;
        case 581 : texte = "You find the Lantern!!!*Use it to shut up flames."; break;
        case 582 : texte = "You find the Flippers!!!*Set them up to go in the water."; break;
        case 583 : texte = "You find the Magic Hammer!!!*Use it to squash obstacles."; break;
        case 584 : texte = "You find the Fire Rod!!!*From now on you are able to shoot out powerful flames."; break;
        case 585 : texte = "You find the Ice Rod!!!*Use it to freeze anything from a distance."; break;
        case 586 : texte = "You find the Master Sword!!!*Even Ganon could not stand up to its power!!! (in theory)"; break;
        case 587 : texte = "Congratulation Link, you have succeeded in saving me!!!***Let's find Ganon quickly, we have to reclaim the Triforce!"; break;
        case 589 : texte = "The secret passage behind the throne room leads to Ganon. Hurry up!"; break;
        case 590 : texte = "We are very near, follow me!"; break;
        case 591 : texte = "I'm afraid you are not able to defeat Ganon with your present weapons...*Go and speak to the chief of the village Kakariko, I am sure he will find a solution."; break;
        case 592 : texte = "Ganon is just behind that door, I will cure your wounds."; break;
        case 593 : texte = "Ganon is still somewhere in the castle."; break;
        case 594 : texte = "You should wait princess Zelda!!!"; break;
        case 595 : texte = "Wouldn't you have the spooky feeling to forget someone by any chance???"; break;
        case 596 : texte = "Zelda is waiting for you!!!"; break;
        case 597 : texte = "You find the Triforce!!!"; break;
        case 598 : texte = "You find the book of Mudora!!!**From now on, you understand the ancient Hylian!!!"; break;
        case 599 : texte = "Congratulation Link, for finding me. As a reward, I give you the Din Pendent, it raises your defense by one point."; break;
        case 600 : texte = "Congratulation Link, for finding me. As a reward, I give you the Nayru Pendent, it rises your defense by two points!!!"; break;
        case 601 : texte = "..."; break;
        case 602 : texte = "You obtain a magic pendent!!!**Your defense just raised!!!"; break;
        case 603 : texte = "Congratulation Link, for finding me. As a reward, I will double the busload of your magic meter!!!"; break;
        case 604 : texte = "Your magic meter is twofold!!!"; break;
        case 605 : texte = "Come back when you have an empty bottle and I will sell you a red potion which restores energy."; break;
        case 606 : texte = "A red potion for 60 rupees, are you interested?*              YES ?            no  "; break;
        case 607 : texte = "A red potion for 60 rupees, are you interested?*              yes              NO ?"; break;
        case 608 : texte = "Thank you, here is your potion.";break;
        case 609 : texte = "You get a red potion!!!*Drink it to restore your energy!!!"; break;
        case 610 : texte = "You get a green potion!!!*Drink it to restore your magic!!!"; break;
        case 611 : texte = "You get a blue potion!!!*Drink it to restore your energy and your magic!!!"; break;
        case 612 : texte = "Hello, what would you like to drink?"; break;
        case 613 : texte = "-Hiccup!- A fairy is said to give enchanted objects... -Hiccup!- ...to the adventurers who would find her... -Hiccup!!!-"; break;
        case 614 : texte = "One heart for 10 rupees, ok?**              YES ?            no  "; break;
        case 615 : texte = "One heart for 10 rupees, ok?**              yes              NO ?"; break;
        case 616 : texte = "A little bit of magic for 20 rupees, ok?**              YES ?            no  "; break;
        case 617 : texte = "A little bit of magic for 20 rupees, ok?**              yes              NO ?"; break;
        case 618 : texte = "Some magic for 30 rupees, ok?**              YES ?            no  "; break;
        case 619 : texte = "Some magic for 30 rupees, ok?**              yes              NO ?"; break;
        case 620 : texte = "5 arrows for 30 rupees, ok?**              YES ?            no  "; break;
        case 621 : texte = "5 arrows for 30 rupees, ok?**              yes              NO ?"; break;
        case 622 : texte = "One bomb for 30 rupees, ok?**              YES ?            no  "; break;
        case 623 : texte = "One bomb for 30 rupees, ok?**              yes              NO ?"; break;
        case 624 : texte = "One bow for 1000 rupees, ok?**              YES ?            no  "; break;
        case 625 : texte = "One bow for 1000 rupees, ok?**              yes              NO ?"; break;
        case 626 : texte = "One bow for 50 rupees, ok?**              YES ?            no  "; break;
        case 627 : texte = "One bow for 50 rupees, ok?**              yes              NO ?"; break;
        case 628 : texte = "You don't need this right now."; break;
        case 629 : texte = "Thank you."; break;
        case 630 : texte = "You get the bow!!!*Use it to reach a distant target."; break;
        case 631 : texte = "Choose what you want."; break;
        case 632 : texte = "What???*You are in mission for the chief???*Okay, so I'm going to give you a discount for the bow"; break;
        case 633 : texte = "Hello Link, I am the chief of that village, I suspected you were coming."; break;
        case 634 : texte = "Since this morning, monsters stride along Hyrule, I tried to talk about that with Zelda, but as you perhaps already saw, a powerful spell blocks the access to the castle..."; break;
        case 636 : texte = "You say Ganon is responsible for all of that? He stole the Triforce and he holds the princess Zelda captive?"; break;
        case 637 : texte = "Mmmm... The situation is more serious than I thought..."; break;
        case 638 : texte = "We have to act very quickly, you must face Ganon again!"; break;
        case 639 : texte = "How to go in the castle? I may have an idea..."; break;
        case 640 : texte = "As you know, the power of the 7 wise men was locked in 7 crystals by wizard Aghanim when he was trying to open up the path to the Dark World, where Ganon was."; break;
        case 641 : texte = "Yet, even if you raised the descendants of the 7 wise men from death after you defeated Ganon and found the Triforce, these crystals have kept their power."; break;
        case 642 : texte = "They have been hidden deep in the 7 temples, gather them all, and you'll be able to get over Ganon's spell."; break;
        case 643 : texte = "However that won't be easy, Ganon will surely send his best units to protect these crystals..."; break;
        case 644 : texte = "A last thing, you won't go far with your present equipment. Go and see the arms dealer and tell him that you're coming on my behalf. He will probably make a gesture for you."; break;
        case 645 : texte = "Go and see the arms dealer and tell him that you're coming on my behalf. He will probably make a gesture for you."; break;
        case 646 : texte = "You have to gather the 7 crystals to have a chance to save Zelda and Hyrule..."; break;
        case 647 : texte = "You found the 7 crystals? So go right now to the castle, first you have to deliver the princess, she will know better than I how to save Hyrule."; break;
        case 648 : texte = "Your weapons are null and void against Ganon? Therefore, you have to find the Master Sword. It is said to have been concealed in a hidden temple.*Besides, the way leading to the Sword of Evils Bane is said to cross over a village populated by monsters...*I wonder if such a village exists..."; break;
        case 650 : texte = "However, I'm afraid that your present equipment is inadequate to reach this temple, you may go to see the blacksmith of Gerudo village..."; break;
        case 651 : texte = "It's about time to brave Ganon and take the Triforce back!"; break;
        case 652 : texte = "Hey! You have to pay to open one of my chests!!!"; break;
        case 653 : texte = "One of these chests contains a piece of heart, do you want to try for 10 rupees?*You will be allowed to open just one chest, ok?               YES ?            no  "; break;
        case 654 : texte = "One of these chests contains a piece of heart, do you want to try for 10 rupees?*You will be allowed to open just one chest, ok?               yes              NO ?"; break;
        case 655 : texte = "Choose a chest."; break;
        case 656 : texte = "I don't have anymore prizes to bring into play, sorry."; break;
        case 657 : texte = "You lose! This chest is empty. Try again!"; break;
        case 658 : texte = "Hello! If you are looking for the blacksmith, he lives a little farther."; break;
        case 659 : texte = "Hello Link, I am the chief of this village.*You should go to see the blacksmith and show him what you want him to temper in your equipment."; break;
        case 660 : texte = "I have been informed of your quest, so I have arranged it with him.*All will be free for you."; break;
        case 661 : texte = "You don't need to drink this potion now."; break;
        case 662 : texte = "A green potion for 40 rupees, are you interested?*              YES ?            no  "; break;
        case 663 : texte = "A green potion for 40 rupees, are you interested?*              yes              NO ?"; break;
        case 664 : texte = "Come back when you have an empty bottle and I will sell you a green potion which restores magic."; break;
        case 665 : texte = "Come back later, I am overbooked!"; break;
        case 666 : texte = "May I do something for you?"; break;
        case 667 : texte = "Do you want me to temper your sword?**              YES ?            no  "; break;
        case 668 : texte = "Do you want me to temper your sword?**              yes              NO ?"; break;
        case 669 : texte = "Your sword triples in power and you can now throw some magic attack, so good!!!*"; break;
        case 670 : texte = "Do you want me to upgrade your gloves?**              YES ?            no  "; break;
        case 671 : texte = "Do you want me to upgrade your gloves?**              yes              NO ?"; break;
        case 672 : texte = "The power of your gloves helps you to lift heavy rocks."; break;
        case 673 : texte = "Do you want me to upgrade your bow?**              YES ?            no  "; break;
        case 674 : texte = "Do you want me to upgrade your bow?**              yes              NO ?"; break;
        case 675 : texte = "Your bow now shoots silver arrows with a cataclysmic power!!!"; break;
        case 676 : texte = "Come back when you have an empty bottle and I will sell you a blue potion which restores energy and magic."; break;
        case 677 : texte = "A blue potion for 160 rupees, are you interested?*              YES ?            no  "; break;
        case 678 : texte = "A blue potion for 160 rupees, are you interested?*              yes              NO ?"; break;
        case 679 : texte = "Our village has been constituted in the aim to stop careless adventurers from reaching the temple, I don't allow just anyone to pass."; break;
        case 680 : texte = "Mmmm... You already found 4 crystals?*I have got to admit you impress me..."; break;
        case 681 : texte = "All right, you are allowed to cross over the graveyard, at your own risk."; break;
        case 682 : texte = "Talk to the guard at the north of the village, he will let you pass."; break;
        case 683 : texte = "I see you're still alive...*Surprising."; break;
        case 684 : texte = "The dark temple is the starting point of the way reaching a legendary object. This village just exists to dissuade adventurers from approaching."; break;
        case 685 : texte = "So you found the Sword?*But don't believe it is yours for all that."; break;
        case 686 : texte = "The Master Sword is among the most treasured heritage of Hyrule with the Triforce, you will have to bring it back in his sanctuary when your mission is completed."; break;
        case 687 : texte = "All the inhabitants of this village are spirits who responded to princess Zelda's call."; break;
        case 688 : texte = "When you returned peace to Hyrule and reunified the Light World with the Golden Land, Zelda secretly asked volunteer spirits to create this village to block"; break;
        case 689 : texte = "the access to a very high valued object."; break;
        case 690 : texte = "Welcome Link!*Let me explain to you what I am doing here."; break;
        case 691 : texte = "As you certainly have noticed, monsters appeared in Hyrule. It's the first time I can see monsters since your victory on Ganon."; break;
        case 692 : texte = "Well, I have decided to list all of them."; break;
        case 693 : texte = "Unfortunately, I'm really too fearful to meet them, so I need your help."; break;
        case 694 : texte = "You have to fight each kind of monster and come to give me your report."; break;
        case 695 : texte = "Each time you have defeated 7 new kinds of enemies, I will give you one piece of heart."; break;
#ifdef __vita__
        case 696 : texte = "If you want to see what enemies you've already defeated, press Up."; break;
#else
        case 696 : texte = "If you want to see what enemies you've already defeated, press M."; break;
#endif
        case 697 : texte = "Again "+s+" different enemies before the next reward."; break;
        case 698 : texte = "You just lack only one enemy before the next reward!!!"; break;
        case 699 : texte = "Take this gift for your contribution on my project:"; break;
        case 700 : texte = "I'm sorry, but I don't have a gift for you anymore..."; break;
        case 701 : texte = "I can't take it in, you succeeded in defeating all kinds of enemies!!!*Congratulation Link!!!"; break;
        case 702 : texte = "                    Level 1:**                  Forest Temple"; break;
        case 703 : texte = "                    Level 2:**                  Water Temple"; break;
        case 704 : texte = "                    Level 3:**                 Mountain Temple"; break;
        case 705 : texte = "                    Level 4:**                  Desert Temple"; break;
        case 706 : texte = "                    Level 5:**                   Dark Temple"; break;
        case 707 : texte = "                    Level 6:**                   Fire Temple"; break;
        case 708 : texte = "                    Level 7:**                   Ice Temple"; break;
        case 709 : texte = "                    Level ?:**                  Hidden Temple"; break;
        case 710 : texte = "                  Last Level:**                 Hyrule Castle"; break;
        case 711 :texte = "                 Already tired?                  ?                 CONTINUE                 ?                   Save and quit                               Quit without saving            "; break;
        case 712 :texte = "                 Already tired?                                    Continue                     ?               SAVE AND QUIT              ?                Quit without saving            "; break;
        case 713 :texte = "                 Already tired?                                    Continue                                     Save and quit                  ?            QUIT WITHOUT SAVING           ?"; break;
        case 714 : texte = "At the right time when Link touched the Triforce, monsters disappeared and peace recurred.**Then Princess Zelda made a great decision: she touched in turn the Triforce and made her wish.**Triforce had always been the origin of troubles in the Kingdom, sooner or later, another evil creature would find it.**Just when princess touched the relic, it disappeared from Hyrule forever."; break;
        case 715 : texte = "Since this day, Hyrule people have lived in peace, without fear of new disasters.**Thus the legend of Zelda, of the Triforce and of the Golden Land is achieved.**Master Sword is said to rest safely somewhere and to be the last heirloom of Link's quest..."; break;
        case 716 : texte = "Congratulation Link, for finding me. As a reward, I give you the Farore Pendent, it raises your defense by one point..."; break;
        case 717 : texte = "Do you want to save your game?**                    ? YES ?*                      no  "; break;
        case 718 : texte = "Do you want to save your game?**                      yes  *                    ? NO ?"; break;
        case 719 : texte = "Game saved."; break;
        case 720 : texte = "The Kingdom of Hyrule has been in peace since Link, the last knight of Hyrule, had defeated the malicious Ganon and reclaimed the precious Triforce to him."; break;
        case 721 : texte = "Nobody knows what Link's wish to the Triforce was, but it had the effect of reunifying the Light and Dark World, and upraising the 7 wise men's descendants."; break;
        case 722 : texte = "Next, Link handed Triforce and Master Sword over to Princess Zelda, and people started to believe that peace would last.*But the people were wrong..."; break;
        case 723 : texte = "Unfortunately, Link's wish also had negative effects. Ganon and his henchmen were resurrected and got ready to attack."; break;
        case 724 : texte = "Somewhere in Hyrule Forest, Link is sleeping without suspecting that Ganon has already moved into the attack, until a"; 
        case 725 : texte = "well-known voice talk to him during his sleep..."; break;
        case 726 : texte = "Help me!*Help me!*That's me! Zelda!*I'm talking to you by telepathy."; break;
        case 727 : texte = "I am a prisoner in the dungeon of the castle!*I need your help!*Ganon is back, and he surely has already found the Triforce..."; break;
        case 728 : texte = "Come quickly to the castle Link, you are my only hope..."; break;
        case 729 : texte = "HELP: Press Select to consult help."; break;
        default : 
            texte = "TEXT ERROR";
    }

    return texte;
}

std::string Texte::getTexteFR(int id, std::string s){
    std::string texte = "";
    switch(id) {
        // 0 -> 99 : Carte
        case 0 : 
            texte = "Temple de la for�t"; 
            break;
        case 1 : 
            texte = "Temple de l'eau"; 
            break;
        case 2 : 
            texte = "Temple de la montagne";
            break;
        case 3 : 
            texte = "Temple du d�sert"; 
            break;
        case 4 : 
            texte = "Temple de l'ombre"; 
            break;
        case 5 : 
            texte = "Temple du feu"; 
            break;
        case 6 : 
            texte = "Temple de la glace"; 
            break;
        case 7 : 
            texte = "Temple secret"; 
            break;
        case 8 : 
            texte = "Ch�teau d'Hyrule"; 
            break;

        // 100 -> 199 : Encyclopedie
        case 100 : 
            texte = "MONSTRES " + s;
            break;
            
        // 200 -> 299 : Generique
        case 200 :
            texte = "ECRAN DE SELECTION";
            break;
        case 201 : 
            texte = "1.";
            break;
        case 202 :
            texte = "2.";
            break;
        case 203 : 
            texte = "3.";
            break;
        case 204 :
            texte = "OPTIONS";
            break;
        case 205 :
            texte = "RECORDS";
            break;
        case 206 :
            texte = "OPTIONS";
            break;
        case 207 :
            texte = "MUSIQUE";
            break;
        case 208 :
            texte = "SON";
            break;
        case 209 :
            texte = "RETOUR";
            break;
        case 210 :
            texte = "RECORDS";
            break;
        case 211 :
            texte = "MEILLEUR TEMPS : " + s;
            break;
        case 212 :
            texte = "RANG DES 100%";
            break;
        case 213 :
            texte = "RANG ULTIME";
            break;
        case 214 :
            texte = "RANG DE RAPIDITE";
            break;
        case 215 :
            texte = "RETOUR";
            break;
        case 216 :
            texte = "EFFACER";
            break;
        case 217 :
            texte = "EFFACER ?";
            break;
        case 218 :
            texte = "OUI";
            break;
        case 219 :
            texte = "NON";
            break;
        case 220 :
            texte = "CHARGER";
            break;
        case 221 :
            texte = "EFFACER";
            break;
        case 222 :
            texte = "ANNULER";
            break;
        case 223 :
            texte = "AIDE 1/2";
            break;
        case 224 :
#ifdef __vita__
            texte = "Retour au jeu : Croix - Suite : >";
#else
            texte = "Retour au jeu : Entr�e - Suite : Droite";
#endif
            break;
        case 225 :
#ifdef __vita__
            texte = "Lire / Ouvrir / Parler : Rond";
#else
            texte = "Lire / Ouvrir / Parler : Espace";
#endif
            break;
        case 226 :
#ifdef __vita__
            texte = "Valider / Passer texte : Croix";
#else
            texte = "Valider / Passer texte : Entr�e";
#endif
            break;
        case 227 :
#ifdef __vita__
            texte = "D�placer Link : Stick Gauche";
#else
            texte = "D�placer Link : Fl�ches de direction";
#endif
            break;
        case 228 :
#ifdef __vita__
            texte = "Courir : L (maintenu) / R";
#else
            texte = "Courir : Shift maintenu ou Caps lock";
#endif
            break;
        case 229 :
#ifdef __vita__
            texte = "Coup d'�p�e : Carr�";
#else
            texte = "Coup d'�p�e : W ou Z";
#endif
            break;
        case 230 :
#ifdef __vita__
            texte = "Attaque Tornade : Carr� maintenu puis l�ch�";
#else
            texte = "Attaque Tornade : W ou Z maintenu puis l�ch�";
#endif
            break;
        case 231 :
#ifdef __vita__
            texte = "Menu de s�lection d'objet : D-Pad Droite";
#else
            texte = "Menu de s�lection d'objet : Entr�e";
#endif
            break;
        case 232 :
#ifdef __vita__
            texte = "Utiliser l'objet s�lectionn� : Triangle";
#else
            texte = "Utiliser l'objet s�lectionn� : X";
#endif
            break;
        case 233 :
#ifdef __vita__
            texte = "Porter sans �quiper les gants : Croix";
#else
            texte = "Porter sans �quiper les gants : C";
#endif
            break;
        case 234 :
#ifdef __vita__
            texte = "Afficher la carte : D-Pad Gauche (ext/donjons)";
#else
            texte = "Afficher la carte : D-Pad Gauche (dans les donjons)";
#endif
            break;
        case 235 :
#ifdef __vita__
            texte = "Afficher la carte : L (ext�rieur ou donjons)";
#else
            texte = "Afficher la carte : P (dans les donjons)";
#endif
            break;
        case 236 :
#ifdef __vita__
            texte = "Afficher les monstres vaincus : D-Pad Haut";
#else
            texte = "Afficher les monstres vaincus : M";
#endif
            break;
        case 237 :
#ifdef __vita__
            texte = "Regarder autour : Stick Droite";
#else
            texte = "Regarder autour : Ctrl et direction";
#endif
            break;
        case 238 :
#ifdef __vita__
            texte = "Sauvegarder / Quitter : Start";
#else
            texte = "Sauvegarder / Quitter : Echap";
#endif
            break;
        case 239 :
#ifdef __vita__
            texte = "";
#else
            texte = "Agrandir / R�tr�cir : Ctrl et Entr�e";
#endif
            break;
        case 240 :
            texte = "AIDE 2/2";
            break;
        case 241 :    
#ifdef __vita__
            texte = "Retour au jeu : Croix - Pr�c�dent : <";
#else
            texte = "Retour au jeu : Entr�e - Pr�c�dent : Gauche";
#endif
            break;
        case 242 :
#ifdef __vita__
            texte = "Utilise objet s�lectionn�: Triangle";
#else
            texte = "Utilise objet s�lectionn�: X";
#endif
            break;
        case 243 :
#ifdef __vita__
            texte = "Porter sans �quiper les gants : Croix"; 
#else
            texte = "Porter sans �quiper les gants : C"; 
#endif
            break;
        case 244 :
#ifdef __vita__
            texte = "Afficher la carte : D-Pad Gauche (ext/donjon)";
#else
            texte = "Afficher la carte : P (ext�rieur ou donjons)";
#endif
            break;
        case 245 :
#ifdef __vita__
            texte = "Afficher la carte : D-Pad Gauche (dans les donjons)";
#else
            texte = "Afficher la carte : P (dans les donjons)";
#endif
            break;
        case 246 :
#ifdef __vita__
            texte = "Afficher les monstres vaincus : D-Pad Haut";
#else
            texte = "Afficher les monstres vaincus : M";
#endif
            break;
        case 247 :
#ifdef __vita__
            texte = "Regarder autour : Stick Droite";
#else
            texte = "Regarder autour : Ctrl et direction";
#endif
            break;
        case 248 :
#ifdef __vita__
            texte = "Sauvegarder / Quitter : Start";
#else
            texte = "Sauvegarder / Quitter : Echap";
#endif
            break;
        case 249 :
#ifdef __vita__
            texte = "";
#else
            texte = "Agrandir / R�tr�cir : Ctrl et Entr�e";
#endif
            break;

        case 250 :
            texte = "RANG : H�ros d'Hyrule";
            break;
        case 251 :
            texte = "RANG : INCONNU";
            break;
        case 252 :
            texte = "Finir le jeu � 100%";
            break;
        case 253 :
            texte = "RANG : Frimeur";
            break;
        case 254 :
            texte = "RANG : INCONNU";
            break;
        case 255 :
            texte = "Finir le jeu sans mourir,";
            break;
        case 256 :
            texte = "avec 10 coeurs au maximum,";
            break;
        case 257 :
            texte = "sans parler aux Grandes F�es,";
            break;
        case 258 :
            texte = "sans acheter de flacons";
            break;
        case 259 :
            texte = "et sans prendre le bouclier.";
            break;
        case 260 :
            texte = "RANG : Marathonien d'Hyrule";
            break;
        case 261 :
            texte = "RANG : INCONNU";
            break;
        case 262 :
            texte = "Finir le jeu en moins de";
            break;
        case 263 :
            texte = "deux heures";
            break;
        case 264 : 
            texte = "SCORES :";
            break;
        case 265 :
            texte = "Temps de jeu : " + s;
            break;
        case 266 :
            texte = "Mort " + s + " fois";
            break;
        case 267 :
            texte = "Mort " + s + " fois";
            break;
        case 268 :
            texte = "Quarts de coeurs : " + s + " / 36";
            break;
        case 269 :
            texte = "Objets : " + s + " / 56";
            break;
        case 270 :
            texte = "Types d'ennemis vaincus : " + s + " / 46";
            break;
        case 271 :
            texte = "Tu as fini ce jeu � " + s + "%, f�licitation !";
            break;
        case 272 :
            texte = "RANG : ";
            break;
        case 273 :
            texte = " - Frimeur";
            break;
        case 274 :
            texte = " - H�ros d'Hyrule";
            break;
        case 275 :
            texte = " - Perfectionniste";
            break;
        case 276 :
            texte = " - Fan de Zelda";
            break;
        case 277 :
#ifdef __vita__
            texte = " - Pro du pad";
#else
            texte = " - Pro du clavier";
#endif
            break;
        case 278 :
            texte = " - Confirm�";
            break;
        case 279 :
            texte = " - D�butant";
            break;
        case 280 :
            texte = " - Mort-vivant";
            break;
        case 281 : 
            texte = " - Kamikaze";
            break;
        case 282 :
            texte = " - Marathonien d'Hyrule";
            break;
        case 283 :
            texte = "LANGUE";
            break;
        case 284 :
            texte = "Fran�aise";
            break;

        // 300 -> 399 : Menu
        case 300 :
            texte = "X";
            break;
        case 301 :
            texte = "STATUT :";
            break;
        case 302 :
            texte = "VIE       : " + s;
            break;
        case 303 :
            texte = "MAGIE     : " + s;
            break;
        case 304 :
            texte = "FORCE     : " + s;
            break;
        case 305 :
            texte = "DEFENSE   : " + s;
            break;
        case 306 :
            texte = "TEMPS     : " + s;
            break;
        case 307 :
            texte = "CRISTAUX :";
            break;

        // 500 -> ?? : Texte
        case 501 : texte = "Tu as trouv� un bouclier !!!**Ta d�fense augmente d'un point !"; break;
#ifdef __vita__
        case 502 : texte = "Tu as trouv� une �p�e !!!**Tu vas pouvoir te d�fendre face aux monstres avec la touche Carr� !!!*Maintiens Carr� enfonc� pour charger une attaque cyclone !!!"; break;
#else
        case 502 : texte = "Tu as trouv� une �p�e !!!**Tu vas pouvoir te d�fendre face aux monstres avec la touche W (ou Z) !!!*Maintiens W enfonc� pour charger une attaque cyclone !!!"; break;
#endif
        case 503 : texte = "Tu as trouv� un quart de coeur !!!"; break;
        case 504 : texte = "Encore "+s+" et tu gagneras un coeur suppl�mentaire !!!"; break;
        case 505 : texte = "Ton nombre de coeurs vient d'augmenter !!!"; break;
        case 511 : texte = "N : Maison de Link*O : Plaine d'Hyrule*E : Temple de la For�t"; break;
        case 512 : texte = "Temple de la Montagne**D�conseill� aux cardiaques, peureux, et aux �mes sensibles en g�n�ral."; break;
        case 513 : texte = "O : Entr�e du D�sert*N : Temple de la Montagne"; break;
        case 514 : texte = "N : Temple de la Montagne*S : Plaine d'Hyrule"; break;
        case 515 : texte = "N : Mont du P�ril"; break;
        case 516 : texte = "E : Entr�e de la For�t"; break;
        case 517 : texte = "S : Lac Hylia*E : Cimeti�re Hant�"; break;
        case 518 : texte = "S : Vers le Village Cocorico"; break;
        case 519 : texte = "N : Village Cocorico"; break;
        case 520 : texte = "N : Plaine d'Hyrule"; break;
        case 521 : texte = "O : Terres de Feu"; break;
        case 522 : texte = "E : Village de l'Ombre*- D�conseill� aux vivants -"; break;
        case 523 : texte = "Temple des T�n�bres**Si vous �tes un fant�me et que vous cherchez un job, venez plut�t ch�mer ici."; break;
        case 524 : texte = "N : Village de l'Ombre*O : Lac Hylia"; break;
        case 525 : texte = "N : Cimeti�re Hant�**Entr�e interdite"; break;
        case 526 : texte = "Village de l'Ombre"; break;
        case 527 : texte = "Je vends un flacon pour 100 rubis, �a t'int�resse ?*              OUI ?            non  "; break;
        case 528 : texte = "Je vends un flacon pour 100 rubis, �a t'int�resse ?*              oui              NON ?"; break;
        case 529 : texte = "D�sol�, mais tu n'as pas assez de rubis."; break;
        case 530 : texte = "Merci beaucoup, voil� ton flacon."; break;
        case 531 : texte = "Reviens me voir si tu changes d'avis."; break;
        case 532 : texte = "D�sol�, c'�tait mon seul flacon."; break;
        case 533 : texte = "Tu as trouv� un flacon vide !!!**Tu vas pouvoir t'en servir pour stocker des potions !!!"; break;
        case 535 : texte = "Les habitants de ce village ont un dialecte tr�s particulier, je n'y comprends rien..."; break;
        case 536 : texte = "@+@+@+@+@+@+@@@+*@=++=@=+@=+@=+=@*+@+@+@+=+="; break;
        case 537 : texte = "Obtiens une autorisation du chef si tu veux vraiment passer!!!"; break;
        case 538 : texte = "Le chef t'as autoris� � passer ??? Grrrr... Alors �carte toi!!!"; break;
        case 539 : texte = "Ne tra�ne pas dans mes pattes !!!"; break;
        case 540 : texte = "On n'a pas l'habitude de voir des visiteurs par ici..."; break;
        case 541 : texte = "Les monstres du coin ne craignent pas grand chose, heureusement qu'ils n'attaquent que les humains."; break;
        case 542 : texte = "C'est vrai ?*Tu comprends ce que je dis ?"; break;
        case 543 : texte = "N : D�sert et Village Gerudo"; break;
        case 544 : texte = "S : Lac Hylia*O : Ch�teau d'Hyrule"; break;
        case 545 : texte = "Village Cocorico"; break;
        case 546 : texte = "O : Ch�teau d'Hyrule"; break;
        case 547 : texte = "Quelle belle journ�e !!!"; break;
        case 548 : texte = "Pourquoi ai-je accept� de m'occuper de ces salet�s ???*J'ai horreur des poules !!!"; break;
        case 549 : texte = "On trouve des tas de choses dans les boutiques du village."; break;
        case 550 : texte = "S : Village Cocorico*O : D�sert*E : Mont du P�ril"; break;
        case 551 : texte = "Village Gerudo"; break;
        case 552 : texte = "Perdu dans le d�sert ?*Vous �tes ici :*                        X"; break;
        case 554 : texte = "S : Vers le Ch�teau d'Hyrule"; break;
        case 555 : texte = "Temple du D�sert**Venez essayer nos bains.*(eau non-potable)"; break;
        case 556 : texte = "Temple de la For�t**Sauvez les arbres, mangez du castor!!!"; break;
        case 557 : texte = "Temple du Lac**Bonnet de bain obligatoire."; break;
        case 558 : texte = "Temple de Glace**Le personnel tient � rappeler qu'un donjon n'est pas une patinoire."; break;
        case 559 : texte = "As-tu �t� voir le forgeron de ce village ?*On dit qu'il est tr�s dou� pour am�liorer l'�quipement des aventuriers, beaucoup de monde lui rend visite."; break;
        case 560 : texte = "Le temple se trouve au fin fond du d�sert, � la place d'une ancienne oasis."; break;
        case 561 : texte = "S : Terres de Feu*E : Village Cocorico"; break;
        case 562 : texte = "Ch�teau d'Hyrule"; break;
        case 563 : texte = "E : Village Cocorico"; break;
        case 564 : texte = "O : Roc de la Tortue*E : Lac Hylia"; break;
        case 565 : texte = "Temple Cach�**Ici repose la lame purificatrice, Excalibur."; break;
        case 566 : texte = "N : Vers le cimeti�re hant�"; break;
#ifdef __vita__
        case 567 : texte = "Tu as trouv� la carte du donjon !!!*Appuie sur D-Pad Gauche pour voir le plan."; break;
#else
        case 567 : texte = "Tu as trouv� la carte du donjon !!!*Appuie sur P pour voir le plan."; break;
#endif
        case 568 : texte = "Tu as trouv� la boussole !!!*Tu peux localiser le boss et les coffres sur le plan."; break;
        case 569 : texte = "Tu as trouv� la cl� du boss !!!"; break;
        case 570 : texte = "Tu as trouv� une petite cl� !!!*Approche une porte pour l'ouvrir."; break;
#ifdef __vita__
        case 571 : texte = "Tu as trouv� les gants !!!*Utilise-les pour soulever des objets en les �quipant ou en appuyant sur Croix."; break;
#else        
        case 571 : texte = "Tu as trouv� les gants !!!*Utilise-les pour soulever des objets en les �quipant ou en appuyant sur C."; break;
#endif        
        case 572 : texte = "Tu as trouv� un cristal magique !!!"; break;
        case 573 : texte = "A quoi pourra-t-il bien servir ?"; break;
        case 574 : texte = "Il en reste encore "+s+" � trouver !!!"; break;
        case 575 : texte = "Plus que 2 � trouver !!!"; break;
        case 576 : texte = "Il ne t'en manque plus qu'un seul !!!"; break;
        case 577 : texte = "Tu as tous les cristaux, cours au ch�teau sauver Zelda !!!"; break;
        case 580 : texte = "Tu as trouv� le grappin !!!*Utilise-le pour franchir des obstacles."; break;
        case 581 : texte = "Tu as trouv� la lanterne !!!*Utilise-la pour faire jaillir des flammes."; break;
        case 582 : texte = "Tu as trouv� les palmes !!!*Equipe-les pour aller dans l'eau."; break;
        case 583 : texte = "Tu as trouv� le marteau magique !!!*Utilise-le pour �craser les obstacles."; break;
        case 584 : texte = "Tu as trouv� le baton de feu !!!*Tu peux d�sormais lancer de puissantes flammes � distance."; break;
        case 585 : texte = "Tu as trouv� le baton de glace !!!*Utilise-le pour tout congeler � distance."; break;
        case 586 : texte = "Tu as trouv� Excalibur !!!*M�me Ganon ne devrait pas pouvoir r�sister � sa puissance !!! (en th�orie)"; break;
        case 587 : texte = "F�licitation Link, tu as r�ussi � venir me d�livrer!!!***Allons vite trouver Ganon, il faut imp�rativement lui reprendre la Triforce !"; break;
        case 589 : texte = "Le passage secret derri�re la salle du tr�ne m�ne � Ganon. D�p�chons-nous !"; break;
        case 590 : texte = "Nous y sommes presque, suis-moi !"; break;
        case 591 : texte = "J'ai bien peur que tu ne puisses jamais vaincre Ganon avec tes armes actuelles...*Va parler au chef du village Cocorico, je suis s�re qu'il trouvera une solution."; break;
        case 592 : texte = "Ganon est juste derri�re cette porte, je vais soigner tes blessures."; break;
        case 593 : texte = "Ganon est toujours quelque part dans le ch�teau."; break;
        case 594 : texte = "Tu devrais attendre la princesse Zelda !!!"; break;
        case 595 : texte = "Tu n'aurais pas l'�trange sentiment d'oublier quelqu'un par hasard ???"; break;
        case 596 : texte = "Zelda t'attend!!!"; break;
        case 597 : texte = "Tu as trouv� la Triforce!!!"; break;
        case 598 : texte = "Tu as trouv� le livre de Mudora!!!**Tu comprends d�sormais le Hylien ancien!!!"; break;
        case 599 : texte = "F�licitation Link, tu as r�ussi � me trouver. En r�compense, je t'offre le m�daillon de Din, il augmente ta d�fense d'un point."; break;
        case 600 : texte = "F�licitation Link, tu as r�ussi � me trouver. En r�compense, je t'offre le m�daillon de Nayru, il augmente ta d�fense de deux points!!!"; break;
        case 601 : texte = "..."; break;
        case 602 : texte = "Tu as obtenu un m�daillon magique !!!**Ta d�fense vient d'augmenter!!!"; break;
        case 603 : texte = "F�licitation Link, tu as r�ussi � me trouver. Pour te r�compenser, je vais doubler la capacit� de ta r�serve de magie!!!"; break;
        case 604 : texte = "Ta r�serve de magie a doubl�!!!"; break;
        case 605 : texte = "Reviens me voir quand tu auras un flacon vide  et je te vendrai une potion rouge qui restaure l'�nergie."; break;
        case 606 : texte = "Une potion rouge pour 60 rubis, �a t'int�resse?*              OUI ?            non  "; break;
        case 607 : texte = "Une potion rouge pour 60 rubis, �a t'int�resse?*              oui              NON ?"; break;
        case 608 : texte = "Merci, voil� ta potion.";break;
        case 609 : texte = "Tu as obtenu une potion rouge !!!*Bois-la pour restaurer ton �nergie!!!"; break;
        case 610 : texte = "Tu as obtenu une potion verte !!!*Bois-la pour restaurer ta magie!!!"; break;
        case 611 : texte = "Tu as obtenu une potion bleue !!!*Bois-la pour restaurer ton �nergie et ta magie!!!"; break;
        case 612 : texte = "Bonjour, je vous sers quelque chose ?"; break;
        case 613 : texte = "Hic! On raconte qu'une f�e donnerait des objets enchant�s... Hic! ...aux aventuriers qui la  trouveraient... Hic!!!"; break;
        case 614 : texte = "Un coeur pour 10 rubis, ok ?**              OUI ?            non  "; break;
        case 615 : texte = "Un coeur pour 10 rubis, ok ?**              oui              NON ?"; break;
        case 616 : texte = "Un peu de magie pour 20 rubis, ok ?**              OUI ?            non  "; break;
        case 617 : texte = "Un peu de magie pour 20 rubis, ok ?**              oui              NON ?"; break;
        case 618 : texte = "Beaucoup de magie pour 30 rubis, ok ?**              OUI ?            non  "; break;
        case 619 : texte = "Beaucoup de magie pour 30 rubis, ok ?**              oui              NON ?"; break;
        case 620 : texte = "5 fl�ches pour 30 rubis, ok ?**              OUI ?            non  "; break;
        case 621 : texte = "5 fl�ches pour 30 rubis, ok ?**              oui              NON ?"; break;
        case 622 : texte = "Une bombe pour 30 rubis, ok ?**              OUI ?            non  "; break;
        case 623 : texte = "Une bombe pour 30 rubis, ok ?**              oui              NON ?"; break;
        case 624 : texte = "Un arc pour 1000 rubis, ok ?**              OUI ?            non  "; break;
        case 625 : texte = "Un arc pour 1000 rubis, ok ?**              oui              NON ?"; break;
        case 626 : texte = "Un arc pour 50 rubis, ok ?**              OUI ?            non  "; break;
        case 627 : texte = "Un arc pour 50 rubis, ok ?**              oui              NON ?"; break;
        case 628 : texte = "Tu n'as pas besoin de �a maintenant."; break;
        case 629 : texte = "Merci."; break;
        case 630 : texte = "Tu as obtenu l'arc !!!*Utilise-le pour atteindre des cibles �loign�es."; break;
        case 631 : texte = "Choisis ce que tu veux."; break;
        case 632 : texte = "Hein ???*Tu es en mission pour le chef ???*Bon alors je vais te faire une r�duction sur l'arc..."; break;
        case 633 : texte = "Bonjour Link, je suis le chef de ce village, je me doutais que tu passerais."; break;
        case 634 : texte = "Depuis ce matin des monstres sont apparus un peu partout � Hyrule, j'ai voulu aller en parler � la princesse Zelda, mais comme tu l'as peut-�tre d�j� vu, un puissant sortil�ge bloque l'acc�s au ch�teau..."; break;
        case 636 : texte = "Tu dis que Ganon est responsable de tout �a ? Qu'il a vol� la Triforce et qu'il d�tient la princesse Zelda prisonni�re ?"; break;
        case 637 : texte = "Mmmm... la situation est plus grave que je le croyais..."; break;
        case 638 : texte = "Il faut agir au plus vite, tu dois affronter Ganon � nouveau!"; break;
        case 639 : texte = "Comment entrer dans le ch�teau ? J'ai peut-�tre une id�e..."; break;
        case 640 : texte = "Comme tu le sais, le pouvoir des 7 sages a �t� enferm� dans 7 cristaux par le sorcier Aghanim alors qu'il tentait de lever le sceau qui confinait Ganon au monde des t�n�bres."; break;
        case 641 : texte = "Or, bien que tu aies ressuscit� les descendants des sages apr�s avoir vaincu Ganon et trouv� la Triforce, ces cristaux ont conserv� leur puissance."; break;
        case 642 : texte = "Ils ont �t� cach�s au fin fond des 7 temples, r�unis-les tous et tu pourras passer outre le sortil�ge de Ganon."; break;
        case 643 : texte = "Ce ne sera toutefois pas chose ais�, Ganon a certainement d� envoyer ses meilleurs �l�ments prot�ger ces cristaux..."; break;
        case 644 : texte = "Une derni�re chose, tu n'iras pas loin avec ton �quipement actuel. Va voir le marchand d'armes et dis-lui que tu viens de ma part. Il fera s�rement un geste pour toi."; break;
        case 645 : texte = "Va voir le marchand d'armes et dis-lui que tu viens de ma part, il fera certainement un geste pour toi."; break;
        case 646 : texte = "Il te faut rassembler les 7 cristaux pour avoir une chance de sauver Zelda et Hyrule..."; break;
        case 647 : texte = "Tu as trouv� les 7 cristaux ? Alors rends-toi au ch�teau, tu dois avant tout d�livrer la princesse, elle saura mieux que moi comment sauver Hyrule."; break;
        case 648 : texte = "Tes armes sont sans effet sur Ganon ? Dans ce cas tu dois trouver Excalibur. On raconte qu'elle a �t� dissimul�e dans un temple cach�.*On dit aussi que le chemin menant � la lame purificatrice passe par un village peupl� de monstres...*Je me demande si un tel village existe..."; break;
        case 650 : texte = "Toutefois j'ai bien peur que ton �quipement actuel soit insuffisant pour acc�der � ce temple, tu devrais peut-�tre passer voir le forgeron du village Gerudo..."; break;
        case 651 : texte = "Il est temps d'affronter Ganon et de lui reprendre la Triforce!"; break;
        case 652 : texte = "Hey! Il faut payer pour ouvrir un de mes coffres!!!"; break;
        case 653 : texte = "Un de ces coffres contient un quart de coeur, tu veux tenter ta chance pour 10 rubis ?*Tu ne pourras ouvrir qu'un seul coffre, ok ?*              OUI ?            non  "; break;
        case 654 : texte = "Un de ces coffres contient un quart de coeur, tu veux tenter ta chance pour 10 rubis ?*Tu ne pourras ouvrir qu'un seul coffre, ok ?*              oui              NON ?"; break;
        case 655 : texte = "Choisis un coffre."; break;
        case 656 : texte = "Je n'ai plus de prix � mettre en jeu, d�sol�."; break;
        case 657 : texte = "Perdu! Ce coffre est vide."; break;
        case 658 : texte = "Bonjour! Si vous �tes venu voir le forgeron, il habite un peu plus loin."; break;
        case 659 : texte = "Bonjour Link, je suis le chef de ce village.*Tu devrais aller voir le forgeron et lui pr�senter ce que tu veux qu'il reforge dans ton �quipement."; break;
        case 660 : texte = "J'ai �t� inform� de ta qu�te, alors je me suis arrang� avec lui.*Tout sera gratuit pour toi."; break;
        case 661 : texte = "Tu n'as pas besoin de boire cette potion maintenant."; break;
        case 662 : texte = "Une potion verte pour 40 rubis, �a t'int�resse?*              OUI ?            non  "; break;
        case 663 : texte = "Une potion verte pour 40 rubis, �a t'int�resse?*              oui              NON ?"; break;
        case 664 : texte = "Reviens me voir quand tu auras un flacon vide et je te vendrai une potion verte qui restaure la magie."; break;
        case 665 : texte = "Reviens plus tard, je suis d�bord�!"; break;
        case 666 : texte = "Puis-je faire quelque chose pour toi ?"; break;
        case 667 : texte = "Veux-tu que je reforge ton �p�e ?**              OUI ?            non  "; break;
        case 668 : texte = "Veux-tu que je reforge ton �p�e ?**              oui              NON ?"; break;
        case 669 : texte = "Ton �p�e a tripl� de puissance et peut d�sormais renvoyer certaines attaques magiques, trop bien !!!*"; break;
        case 670 : texte = "Veux-tu que j'am�liore tes gants ?**              OUI ?            non  "; break;
        case 671 : texte = "Veux-tu que j'am�liore tes gants ?**              oui              NON ?"; break;
        case 672 : texte = "La puissance de tes gants va te permettre de soulever de lourds rochers."; break;
        case 673 : texte = "Veux-tu que j'am�liore ton arc ?**              OUI ?            non  "; break;
        case 674 : texte = "Veux-tu que j'am�liore ton arc ?**              oui              NON ?"; break;
        case 675 : texte = "Ton arc tire d�sormais des fl�ches d'argent d'une puissance d�vastatrice!!!"; break;
        case 676 : texte = "Reviens me voir quand tu auras un flacon vide et je te vendrai une potion bleue qui restaure l'�nergie et la magie."; break;
        case 677 : texte = "Une potion bleue pour 160 rubis, �a t'int�resse?*              OUI ?            non  "; break;
        case 678 : texte = "Une potion bleue pour 160 rubis, �a t'int�resse?*              oui              NON ?"; break;
        case 679 : texte = "Notre village a �t� fond� pour emp�cher les aventuriers imprudents d'acc�der au temple, je ne donne pas l'autorisation de passer � n'importe qui."; break;
        case 680 : texte = "Mmmm... Tu as d�j� trouv� 4 cristaux ?*Je dois avouer que tu m'impressionnes..."; break;
        case 681 : texte = "Bon c'est entendu, tu as l'autorisation de passer par le cimeti�re, � tes risques et p�rils."; break;
        case 682 : texte = "Va parler au garde au nord du village, il te laissera passer."; break;
        case 683 : texte = "Je vois que tu es toujours vivant...*Etonnant."; break;
        case 684 : texte = "Le temple de l'ombre constitue le point de d�part du chemin menant � un objet de l�gende. Ce village ne sert qu'� dissuader les aventuriers de trop s'en approcher."; break;
        case 685 : texte = "Ainsi tu as trouv� l'Ep�e ?*Mais ne crois pas qu'elle soit � toi pour autant."; break;
        case 686 : texte = "Excalibur fait partie du patrimoine le plus pr�cieux d'Hyrule avec la Triforce, tu devras la ramener dans son sanctuaire une fois ta mission achev�e."; break;
        case 687 : texte = "Les habitants de ce village sont tous des esprits ayant r�pondu � l'appel de la princesse Zelda."; break;
        case 688 : texte = "Lorsque tu as ramen� la paix sur Hyrule et r�unifi� le monde de la lumi�re avec la Terre d'Or, Zelda a secr�tement demand� aux esprits volontaires de cr�er ce village pour bloquer"; break;
        case 689 : texte = "l'acc�s � un objet de tr�s grande valeur."; break;        
        case 690 : texte = "Bienvenue Link!*Laisse-moi t'expliquer ce que je fais ici."; break;
        case 691 : texte = "Comme tu l'as certainement remarqu�, des monstres sont apparus partout dans Hyrule. C'est la premi�re fois que je vois des monstres depuis que tu as vaincu Ganon."; break;
        case 692 : texte = "Et bien j'ai d�cid� de tous les r�pertorier."; break;
        case 693 : texte = "L'ennui c'est que je suis bien trop peureux pour aller � leur rencontre, alors j'ai besoin de ton aide."; break;
        case 694 : texte = "Il faut que tu battes chaque type de monstre et que tu viennes me faire ton rapport."; break;
        case 695 : texte = "Je te r�compenserai tous les 7 nouveaux types d'ennemis vaincus."; break;
        case 696 : texte = "Si tu veux savoir quels ennemis tu as d�j� vaincu, appuye sur M."; break;
        case 697 : texte = "Encore "+s+" ennemis diff�rents avant la prochaine r�compense."; break;
        case 698 : texte = "Plus qu'un nouvel ennemi avant la prochaine r�compense!!!"; break;
        case 699 : texte = "Accepte ce cadeau pour ta contribution � mon projet :"; break;
        case 700 : texte = "Je suis d�sol� mais je n'ai plus rien � t'offrir..."; break;
        case 701 : texte = "Je n'en crois pas mes yeux, tu as r�ussi � vaincre chaque type d'ennemis !!!*F�licitation Link!!!"; break;        
        case 702 : texte = "                   Niveau 1 :**               Temple de la for�t"; break;
        case 703 : texte = "                   Niveau 2 :**                 Temple de l'eau"; break;
        case 704 : texte = "                   Niveau 3 :**              Temple de la montagne"; break;
        case 705 : texte = "                   Niveau 4 :**                Temple du d�sert"; break;
        case 706 : texte = "                   Niveau 5 :**                Temple de l'ombre"; break;
        case 707 : texte = "                   Niveau 6 :**                  Temple du feu"; break;
        case 708 : texte = "                   Niveau 7 :**                Temple de la glace"; break;
        case 709 : texte = "                   Niveau ? :**                   Temple secret"; break;
        case 710 : texte = "                 Niveau Final :**                Ch�teau d'Hyrule"; break;        
        case 711 :texte = "                D�j� fatigu� ?                  ?                CONTINUER                  ?             Sauvegarder et quitter                        Quitter sans sauvegarder           "; break;
        case 712 :texte = "                D�j� fatigu� ?                                   Continuer                     ?          SAUVEGARDER ET QUITTER           ?            Quitter sans sauvegarder           "; break;
        case 713 :texte = "                D�j� fatigu� ?                                   Continuer                                Sauvegarder et quitter              ?         QUITTER SANS SAUVEGARDER          ?"; break;
        case 714 : texte = "A l'instant o� Link toucha la Triforce, les monstres disparurent et la paix revint.**La princesse Zelda prit alors une grande d�cision: elle toucha � son tour la Triforce pour exaucer son voeu...**La Triforce fut depuis toujours � l'origine des probl�mes survenus au Royaume, t�t ou tard un autre �tre malfaisant aurait fini par la trouver.**A la seconde o� la princesse toucha la relique, elle disparue � jamais d'Hyrule.";
        case 715 : texte = "Depuis ce jour, le peuple d'Hyrule v�cut en paix, sans craindre de nouveaux d�sastres.**Ainsi s'ach�ve la l�gende de Zelda, celle de la  Triforce et de la Terre d'Or.**On dit que l'�p�e Excalibur repose en s�ret� quelque part, et qu'elle constitue le dernier souvenir de la qu�te de Link..."; break;
        case 716 : texte = "F�licitation Link, tu as r�ussi � me trouver. En r�compense, je t'offre le m�daillon de Farore, il augmente ta d�fense d'un point."; break;
        case 717 : texte = "Souhaites-tu sauvegarder ta partie ?**                    ? OUI ?*                      non  "; break;
        case 718 : texte = "Souhaites-tu sauvegarder ta partie ?**                      oui  *                    ? NON ?"; break;
        case 719 : texte = "Partie sauvegard�e."; break;
        case 720 : texte = "Le Royaume d'Hyrule �tait en paix depuis que Link, dernier chevalier hylien, avait vaincu le mal�fique Ganon et lui avait repris la pr�cieuse Triforce."; break;
        case 721 : texte = "Nul ne sait quel voeu fit Link en touchant la Triforce, mais il eut comme effet de r�unifier le monde de la lumi�re et celui des t�n�bres, et ramena � la vie les descendants des 7 sages."; break;
        case 722 : texte = "Link remit ensuite � la princesse Zelda la Triforce et l'�p�e Excalibur, et le peuple se mit � croire que la paix durerait.*Mais le peuple se trompait..."; break;
        case 723 : texte = "Le souhait de Link � la Triforce eu h�las de f�cheux effets. Ganon et ses sbires furent ainsi ressuscit�s et s'appr�t�rent � attaquer."; break;
        case 724 : texte = "Quelque part dans la for�t d'Hyrule, Link dort sans se douter que Ganon est pass� � l'attaque, jusqu'� ce qu'"; break;
        case 725 : texte ="une voix famili�re lui parle dans son sommeil..."; break;
        case 726 : texte = "A l'aide!*A l'aide!*C'est moi! C'est Zelda!*Je te parle par t�l�pathie."; break;
        case 727 : texte = "Je suis retenue prisonni�re dans le donjon du ch�teau! J'ai besoin de ton aide!*Ganon est de retour, et il a certainement d� trouver la Triforce � l'heure qu'il est..."; break;
        case 728 : texte = "Viens vite au ch�teau Link, tu es mon seul espoir..."; break;
#ifdef __vita__
        case 729 : texte = "AIDE : Appuie sur Select pour consulter l'aide."; break;
#else
        case 729 : texte = "AIDE : Appuie sur F1 pour consulter l'aide."; break;
#endif
        default : 
            texte = "[ERREUR TEXTE]";
    }

    return texte;
}

void Texte::chercheText() {
    ostringstream os;
    int tmp;
    switch (id) {
        case 1  : texte = (this->*getTextByLangFunc)(501, os.str()); break;
        case 2  : texte = (this->*getTextByLangFunc)(502, os.str()); break;
        case 3  : 
            tmp = 4-(gpJeu->getJoueur()->nbQuarts()%4);
            os << tmp;
            texte = (this->*getTextByLangFunc)(503, os.str());
            if (tmp<4) buffer = (this->*getTextByLangFunc)(504, os.str());
            else buffer = (this->*getTextByLangFunc)(505, os.str());
            break;
        case 11 : texte = (this->*getTextByLangFunc)(511, os.str()); break;
        case 12 : texte = (this->*getTextByLangFunc)(512, os.str()); break;
        case 13 : texte = (this->*getTextByLangFunc)(513, os.str()); break;
        case 14 : texte = (this->*getTextByLangFunc)(514, os.str()); break;
        case 15 : texte = (this->*getTextByLangFunc)(515, os.str()); break;
        case 16 : texte = (this->*getTextByLangFunc)(516, os.str()); break;
        case 17 : texte = (this->*getTextByLangFunc)(517, os.str()); break;
        case 18 : texte = (this->*getTextByLangFunc)(518, os.str()); break;
        case 19 : texte = (this->*getTextByLangFunc)(519, os.str()); break;
        case 20 : texte = (this->*getTextByLangFunc)(520, os.str()); break;
        case 21 : texte = (this->*getTextByLangFunc)(521, os.str()); break;
        case 22 : texte = (this->*getTextByLangFunc)(522, os.str()); break;
        case 23 : texte = (this->*getTextByLangFunc)(523, os.str()); break;
        case 24 : texte = (this->*getTextByLangFunc)(524, os.str()); break;
        case 25 : texte = (this->*getTextByLangFunc)(525, os.str()); break;
        case 26 : texte = (this->*getTextByLangFunc)(526, os.str()); break;
        case 27 : texte = (this->*getTextByLangFunc)(527, os.str()); 
            if ((gpJeu->getJoueur()->hasBouteille(0) && gpJeu->getZone()==8)
            || (gpJeu->getJoueur()->hasBouteille(1) && gpJeu->getZone()==5)
            || (gpJeu->getJoueur()->hasBouteille(2) && gpJeu->getZone()==6)) {id=32; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<100) idsuiv=29;
            else idsuiv=30;
            break;
        case 28 : texte = (this->*getTextByLangFunc)(528, os.str()); idsuiv=31; break;
        case 29 : texte = (this->*getTextByLangFunc)(529, os.str()); break;
        case 30 : texte = (this->*getTextByLangFunc)(530, os.str()); break;
        case 31 : texte = (this->*getTextByLangFunc)(531, os.str()); break;
        case 32 : texte = (this->*getTextByLangFunc)(532, os.str()); break;
        case 33 : texte = (this->*getTextByLangFunc)(533, os.str()); break;
        case 35 : texte = (this->*getTextByLangFunc)(535, os.str()); break;
        case 36 : texte = (this->*getTextByLangFunc)(536, os.str()); break;
        case 37 : texte = (this->*getTextByLangFunc)(537, os.str()); break;
        case 38 : texte = (this->*getTextByLangFunc)(538, os.str()); break;
        case 39 : texte = (this->*getTextByLangFunc)(539, os.str()); break;
        case 40 : texte = (this->*getTextByLangFunc)(540, os.str()); break;
        case 41 : texte = (this->*getTextByLangFunc)(541, os.str()); break;
        case 42 : texte = (this->*getTextByLangFunc)(542, os.str()); break;
        case 43 : texte = (this->*getTextByLangFunc)(543, os.str()); break;
        case 44 : texte = (this->*getTextByLangFunc)(544, os.str()); break;
        case 45 : texte = (this->*getTextByLangFunc)(545, os.str()); break;
        case 46 : texte = (this->*getTextByLangFunc)(546, os.str()); break;
        case 47 : texte = (this->*getTextByLangFunc)(547, os.str()); break;
        case 48 : texte = (this->*getTextByLangFunc)(548, os.str()); break;
        case 49 : texte = (this->*getTextByLangFunc)(549, os.str()); break;
        case 50 : texte = (this->*getTextByLangFunc)(550, os.str()); break;
        case 51 : texte = (this->*getTextByLangFunc)(551, os.str()); break;
        case 52 : texte = (this->*getTextByLangFunc)(552, os.str()); break;
        case 54 : texte = (this->*getTextByLangFunc)(554, os.str()); break;
        case 55 : texte = (this->*getTextByLangFunc)(555, os.str()); break;
        case 56 : texte = (this->*getTextByLangFunc)(556, os.str()); break;
        case 57 : texte = (this->*getTextByLangFunc)(557, os.str()); break;
        case 58 : texte = (this->*getTextByLangFunc)(558, os.str()); break;
        case 59 : texte = (this->*getTextByLangFunc)(559, os.str()); break;
        case 60 : texte = (this->*getTextByLangFunc)(560, os.str()); break;
        case 61 : texte = (this->*getTextByLangFunc)(561, os.str()); break;
        case 62 : texte = (this->*getTextByLangFunc)(562, os.str()); break;
        case 63 : texte = (this->*getTextByLangFunc)(563, os.str()); break;
        case 64 : texte = (this->*getTextByLangFunc)(564, os.str()); break;
        case 65 : texte = (this->*getTextByLangFunc)(565, os.str()); break;
        case 66 : texte = (this->*getTextByLangFunc)(566, os.str()); break;
        case 67 : texte = (this->*getTextByLangFunc)(567, os.str()); break;
        case 68 : texte = (this->*getTextByLangFunc)(568, os.str()); break;
        case 69 : texte = (this->*getTextByLangFunc)(569, os.str()); break;
        case 70 : texte = (this->*getTextByLangFunc)(570, os.str()); break;
        case 71 : texte = (this->*getTextByLangFunc)(571, os.str()); break;
        case 72 : 
            texte = (this->*getTextByLangFunc)(572, os.str());; 
            tmp = 7-gpJeu->getJoueur()->nbCristaux();
            os << tmp;
            if (tmp==6 && !gpJeu->getJoueur()->getAvancement()) buffer = (this->*getTextByLangFunc)(573, os.str());
            else if (tmp>2) buffer = (this->*getTextByLangFunc)(574, os.str());
            else if (tmp==2) buffer = (this->*getTextByLangFunc)(575, os.str());
            else if (tmp==1) buffer = (this->*getTextByLangFunc)(576, os.str());
            else if (tmp==0) buffer = (this->*getTextByLangFunc)(577, os.str());
            break;
        case 80 : texte = (this->*getTextByLangFunc)(580, os.str());; break;
        case 81 : texte = (this->*getTextByLangFunc)(581, os.str()); break;
        case 82 : texte = (this->*getTextByLangFunc)(582, os.str()); break;
        case 83 : texte = (this->*getTextByLangFunc)(583, os.str()); break;
        case 84 : texte = (this->*getTextByLangFunc)(584, os.str()); break;
        case 85 : texte = (this->*getTextByLangFunc)(585, os.str()); break;
        case 86 : texte = (this->*getTextByLangFunc)(586, os.str()); break;
        case 87 : texte = (this->*getTextByLangFunc)(587, os.str()); break;
        case 89 : texte = (this->*getTextByLangFunc)(589, os.str()); break;
        case 90 : texte = (this->*getTextByLangFunc)(590, os.str()); break;
        case 91 : texte = (this->*getTextByLangFunc)(591, os.str()); break;
        case 92 : texte = (this->*getTextByLangFunc)(592, os.str()); break;
        case 93 : texte = (this->*getTextByLangFunc)(593, os.str()); break;
        case 94 : texte = (this->*getTextByLangFunc)(594, os.str()); break;
        case 95 : texte = (this->*getTextByLangFunc)(595, os.str()); break;
        case 96 : texte = (this->*getTextByLangFunc)(596, os.str()); break;
        case 97 : texte = (this->*getTextByLangFunc)(597, os.str()); break;
        case 98 : texte = (this->*getTextByLangFunc)(598, os.str()); break;
        case 99 : texte = (this->*getTextByLangFunc)(599, os.str()); break;
        case 100 : texte = (this->*getTextByLangFunc)(600, os.str()); break;
        case 101 : texte = (this->*getTextByLangFunc)(601, os.str());; break;
        case 102 : texte = (this->*getTextByLangFunc)(602, os.str()); break;
        case 103 : texte = (this->*getTextByLangFunc)(603, os.str()); break;
        case 104 : texte = (this->*getTextByLangFunc)(604, os.str()); break;
        case 105 : texte = (this->*getTextByLangFunc)(605, os.str()); break;
        case 106 : texte = (this->*getTextByLangFunc)(606, os.str());
            if (gpJeu->getJoueur()->hasBouteille(0)!=1
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1) {id=105; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<60) idsuiv=29;
            else idsuiv=108; break;
        case 107 : texte = (this->*getTextByLangFunc)(607, os.str()); break;
        case 108 : texte = (this->*getTextByLangFunc)(608, os.str());break;
        case 109 : texte = (this->*getTextByLangFunc)(609, os.str()); break;
        case 110 : texte = (this->*getTextByLangFunc)(610, os.str()); break;
        case 111 : texte = (this->*getTextByLangFunc)(611, os.str()); break;
        case 112 : texte = (this->*getTextByLangFunc)(612, os.str()); break;
        case 113 : texte = (this->*getTextByLangFunc)(613, os.str()); break;
        case 114 : texte = (this->*getTextByLangFunc)(614, os.str()); 
            if (gpJeu->getJoueur()->getVie()+gpJeu->getJoueur()->getBoostVie()
            == gpJeu->getJoueur()->getVieMax()) {id=128; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=29;
            else idsuiv=129; break;
        case 115 : texte = (this->*getTextByLangFunc)(615, os.str()); break;
        case 116 : texte = (this->*getTextByLangFunc)(616, os.str());
            if (gpJeu->getJoueur()->getMagie()+gpJeu->getJoueur()->getBoostMagie()
            == gpJeu->getJoueur()->getMagieMax() || !gpJeu->getJoueur()->hasObjet(O_LANTERNE)) {
                id=128; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<20) idsuiv=29;
            else idsuiv=129; break;
        case 117 : texte = (this->*getTextByLangFunc)(617, os.str()); break;
        case 118 : texte = (this->*getTextByLangFunc)(618, os.str());
            if (gpJeu->getJoueur()->getMagie()+gpJeu->getJoueur()->getBoostMagie()
            == gpJeu->getJoueur()->getMagieMax() || !gpJeu->getJoueur()->hasObjet(O_LANTERNE)) {
                id=128; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<30) idsuiv=29;
            else idsuiv=129; break;
        case 119 : texte = (this->*getTextByLangFunc)(619, os.str()); break;
        case 120 : texte = (this->*getTextByLangFunc)(620, os.str());
            if (gpJeu->getJoueur()->getFleche() == gpJeu->getJoueur()->getFlecheMax() 
            || !gpJeu->getJoueur()->hasObjet(O_ARC)) {id=128; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<30) idsuiv=29;
            else idsuiv=129; break;
        case 121 : texte = (this->*getTextByLangFunc)(621, os.str()); break;
        case 122 : texte = (this->*getTextByLangFunc)(622, os.str()); 
            if (gpJeu->getJoueur()->getBombe() == gpJeu->getJoueur()->getBombeMax() 
            || !gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=128; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<30) idsuiv=29;
            else idsuiv=129; break;
        case 123 : texte = (this->*getTextByLangFunc)(623, os.str()); break;
        case 124 : texte = (this->*getTextByLangFunc)(624, os.str()); 
            idsuiv=29; break;
        case 125 : texte = (this->*getTextByLangFunc)(625, os.str()); break;
        case 126 : texte = (this->*getTextByLangFunc)(626, os.str()); 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<50) idsuiv=29;
            else idsuiv=129; break;
        case 127 : texte = (this->*getTextByLangFunc)(627, os.str()); break;
        case 128 : texte = (this->*getTextByLangFunc)(628, os.str()); break;
        case 129 : texte = (this->*getTextByLangFunc)(629, os.str()); break;
        case 130 : texte = (this->*getTextByLangFunc)(630, os.str()); break;
        case 131 : texte = (this->*getTextByLangFunc)(631, os.str()); break;
        case 132 : texte = (this->*getTextByLangFunc)(632, os.str()); break;
        case 133 : texte = (this->*getTextByLangFunc)(633, os.str()); idsuiv=134; break;
        case 134 : texte = (this->*getTextByLangFunc)(634, os.str()); idsuiv=136; break;
        case 136 : texte = (this->*getTextByLangFunc)(636, os.str()); idsuiv=137; break;
        case 137 : texte = (this->*getTextByLangFunc)(637, os.str()); idsuiv=138; break;
        case 138 : texte = (this->*getTextByLangFunc)(638, os.str()); idsuiv=139; break;
        case 139 : texte = (this->*getTextByLangFunc)(639, os.str()); idsuiv=140; break;
        case 140 : texte = (this->*getTextByLangFunc)(640, os.str()); idsuiv=141; break;
        case 141 : texte = (this->*getTextByLangFunc)(641, os.str()); idsuiv=142; break;
        case 142 : texte = (this->*getTextByLangFunc)(642, os.str()); idsuiv=143; break;
        case 143 : texte = (this->*getTextByLangFunc)(643, os.str()); idsuiv=144; break;
        case 144 : texte = (this->*getTextByLangFunc)(644, os.str());; break;
        case 145 : texte = (this->*getTextByLangFunc)(645, os.str()); break;
        case 146 : texte = (this->*getTextByLangFunc)(646, os.str()); break;
        case 147 : texte = (this->*getTextByLangFunc)(647, os.str()); break;
        case 148 : texte = (this->*getTextByLangFunc)(648, os.str()); break;
        case 150 : texte = (this->*getTextByLangFunc)(650, os.str()); break;
        case 151 : texte = (this->*getTextByLangFunc)(651, os.str()); break;
        case 152 : texte = (this->*getTextByLangFunc)(652, os.str()); break;
        case 153 : texte = (this->*getTextByLangFunc)(653, os.str()); 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=29; break;
        case 154 : texte = (this->*getTextByLangFunc)(654, os.str()); break;
        case 155 : texte = (this->*getTextByLangFunc)(655, os.str()); break;
        case 156 : texte = (this->*getTextByLangFunc)(656, os.str()); break;
        case 157 : texte = (this->*getTextByLangFunc)(657, os.str()); break;
        case 158 : texte = (this->*getTextByLangFunc)(658, os.str()); break;
        case 159 : texte = (this->*getTextByLangFunc)(659, os.str());
            buffer = (this->*getTextByLangFunc)(660, os.str()); break;
        case 160 : texte = (this->*getTextByLangFunc)(661, os.str()); break;
        case 161 : texte = (this->*getTextByLangFunc)(662, os.str());
            if (gpJeu->getJoueur()->hasBouteille(0)!=1
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1) {id=163; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<40) idsuiv=29;
            else idsuiv=108; break;
        case 162 : texte = (this->*getTextByLangFunc)(663, os.str()); break;
        case 163 : texte = (this->*getTextByLangFunc)(664, os.str()); break;
        case 164 : texte = (this->*getTextByLangFunc)(665, os.str()); break;
        case 165 : texte = (this->*getTextByLangFunc)(666, os.str());
            if (gpJeu->getJoueur()->getEpee()==1) {id=166; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_GANTS)==1 && gpJeu->getJoueur()->getObjet()==8) {
                id=169; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_ARC)==2 && gpJeu->getJoueur()->getObjet()==0 
            && gpJeu->getJoueur()->nbCristaux()==7) {
                id=172; chercheText();break;}
            break;
        case 166 : texte = (this->*getTextByLangFunc)(667, os.str()); break;
        case 167 : texte = (this->*getTextByLangFunc)(668, os.str()); break;
        case 168 : texte = (this->*getTextByLangFunc)(669, os.str()); break;
        case 169 : texte = (this->*getTextByLangFunc)(670, os.str()); break;
        case 170 : texte = (this->*getTextByLangFunc)(671, os.str()); break;
        case 171 : texte = (this->*getTextByLangFunc)(672, os.str()); break;
        case 172 : texte = (this->*getTextByLangFunc)(673, os.str()); break;
        case 173 : texte = (this->*getTextByLangFunc)(674, os.str()); break;
        case 174 : texte = (this->*getTextByLangFunc)(675, os.str()); break;
        case 175 : texte = (this->*getTextByLangFunc)(676, os.str()); break;
        case 176 : texte = (this->*getTextByLangFunc)(677, os.str());
            if (gpJeu->getJoueur()->hasBouteille(0)!=1
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1) {id=175; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<160) idsuiv=29;
            else idsuiv=108; break;
        case 177 : texte = (this->*getTextByLangFunc)(678, os.str()); break;
        case 178 : texte = (this->*getTextByLangFunc)(679, os.str()); break;
        case 179 : texte = (this->*getTextByLangFunc)(680, os.str());
            buffer = (this->*getTextByLangFunc)(681, os.str()); break;
        case 181 : texte = (this->*getTextByLangFunc)(682, os.str()); break;
        case 182 : texte = (this->*getTextByLangFunc)(683, os.str()); break;
        case 183 : texte = (this->*getTextByLangFunc)(684, os.str()); break;
        case 184 : texte = (this->*getTextByLangFunc)(685, os.str());
            buffer = (this->*getTextByLangFunc)(686, os.str()); break;
        case 186 : texte = (this->*getTextByLangFunc)(687, os.str()); break;
        case 187 : texte = (this->*getTextByLangFunc)(688, os.str());
            buffer = (this->*getTextByLangFunc)(689, os.str()); break;
        
        case 189 : texte = (this->*getTextByLangFunc)(690, os.str()); idsuiv=190; break;
        case 190 : texte = (this->*getTextByLangFunc)(691, os.str()); idsuiv=191; break;
        case 191 : texte = (this->*getTextByLangFunc)(692, os.str()); idsuiv=192; break;
        case 192 : texte = (this->*getTextByLangFunc)(693, os.str()); idsuiv=193; break;
        case 193 : texte = (this->*getTextByLangFunc)(694, os.str()); idsuiv=194; break;
        case 194 : texte = (this->*getTextByLangFunc)(695, os.str()); idsuiv=195; break;
        case 195 : texte = (this->*getTextByLangFunc)(696, os.str()); break;
        
        
        case 196 : 
            if (gpJeu->getJoueur()->getCoeur(43)) {
                if (gpJeu->getJoueur()->nbEnnemis() >= 46) {id=205; chercheText();return;}
                else {id=204; chercheText();return;}
            }
            for (int i = 38; i < 44; i++) 
                if (!gpJeu->getJoueur()->getCoeur(i) 
                && (gpJeu->getJoueur()->nbEnnemis()/7)+37>=i) {
                    id=203; chercheText();return;
                }
            tmp = 7-(gpJeu->getJoueur()->nbEnnemis()%7);
            os << tmp;
            if (tmp>1) texte = (this->*getTextByLangFunc)(697, os.str());
            else texte = (this->*getTextByLangFunc)(698, os.str());
            break;
        case 203 : texte = (this->*getTextByLangFunc)(699, os.str()); break;
        case 204 : texte = (this->*getTextByLangFunc)(700, os.str()); break;
        case 205 : texte = (this->*getTextByLangFunc)(701, os.str()); break;
        
        case 206 : texte = (this->*getTextByLangFunc)(702, os.str()); break;
        case 207 : texte = (this->*getTextByLangFunc)(703, os.str()); break;
        case 208 : texte = (this->*getTextByLangFunc)(704, os.str()); break;
        case 209 : texte = (this->*getTextByLangFunc)(705, os.str()); break;
        case 210 : texte = (this->*getTextByLangFunc)(706, os.str()); break;
        case 211 : texte = (this->*getTextByLangFunc)(707, os.str()); break;
        case 212 : texte = (this->*getTextByLangFunc)(708, os.str()); break;
        case 213 : texte = (this->*getTextByLangFunc)(709, os.str()); break;
        case 214 : texte = (this->*getTextByLangFunc)(710, os.str()); break;
        
        case 215 :texte = (this->*getTextByLangFunc)(711, os.str()); break;
        case 216 :texte = (this->*getTextByLangFunc)(712, os.str()); break;
        case 217 :texte = (this->*getTextByLangFunc)(713, os.str()); break;
        
        case 223 : texte = (this->*getTextByLangFunc)(714, os.str());
            buffer = (this->*getTextByLangFunc)(715, os.str()); break;
        case 224 : texte = (this->*getTextByLangFunc)(716, os.str()); break;
        case 225 : texte = (this->*getTextByLangFunc)(717, os.str()); break;
        case 226 : texte = (this->*getTextByLangFunc)(718, os.str()); break;
        case 227 : texte = (this->*getTextByLangFunc)(719, os.str()); break;
        
        case 228 : texte = (this->*getTextByLangFunc)(720, os.str()); idsuiv = 229; break;
        case 229 : texte = (this->*getTextByLangFunc)(721, os.str()); idsuiv = 230; break;
        case 230 : texte = (this->*getTextByLangFunc)(722, os.str()); idsuiv=231; break;
        case 231 : texte = (this->*getTextByLangFunc)(723, os.str()); idsuiv=232; break;
        case 232 : texte = (this->*getTextByLangFunc)(724, os.str()); 
            buffer=(this->*getTextByLangFunc)(725, os.str()); break;
        case 233 : texte = (this->*getTextByLangFunc)(726, os.str()); idsuiv = 234; break;
        case 234 : texte = (this->*getTextByLangFunc)(727, os.str()); idsuiv=235; break;
        case 235 : texte = (this->*getTextByLangFunc)(728, os.str()); break;
        case 236 : texte = (this->*getTextByLangFunc)(729, os.str()); break;
    }
    
    
}

void Texte::affiche(SDL_Surface* gpScreen, std::string s, int a, int b) {
    for (int i = 0; i < (int)s.length(); i++) {
        afficheLettre(gpScreen, s.at(i),a,b);
        a+=6;
    }
}

void Texte::afficheTexteAvecId(SDL_Surface* gpScreen, int id, std::string s, int a, int b) {
    std::string texte = (this->*getTextByLangFunc)(id, s);
    affiche(gpScreen, texte, a, b);
}

void Texte::draw(SDL_Surface* gpScreen) {
    
    if (cadre) drawCadre(gpScreen);
    
    if (id==3 && texte == "Tu as trouv� un quart de coeur !!!") {
        SDL_Rect src; SDL_Rect dst;
        src.x=16*(gpJeu->getJoueur()->nbQuarts()%4);
        if(src.x==0)src.x=16*4;
        src.y=0; src.w=16; src.h=16; dst.x=160-8; dst.y=120-8+16*5;
        SDL_BlitSurface(imageCoeur, &src, gpScreen, &dst);
    }
    
    int a = x+8; int b = y+8;
    for (int i = 0; i < av; i++) {
        afficheLettre(gpScreen, texte.at(i),a,b);
        a+=6;
        if (a > x+w-16) {a=x+8; b+=16;}
    }
    
    if(SDL_GetTicks() > lastAnimTime + vitesse && def && av < (int)texte.length()) {
        lastAnimTime = SDL_GetTicks();
        do av++;
        while (av < (int)texte.length() && texte.at(av-1) == ' ');
        if (texte.at(av-1) != ' ') gpJeu->getAudio()->playSound(0,1);
    }
}

bool Texte::isFinished() {return (av==(int)texte.length());}

int Texte::getId() {return id;}

void Texte::changeId(int i) {
    id=i; idsuiv=0; buffer="";
    chercheText();
    decoupeText();
    if (av>(int)texte.length()) av=(int)texte.length();
}

void Texte::drawCadre(SDL_Surface* gpScreen) {
    SDL_Rect src;
    SDL_Rect dst;
    
    src.w=8; src.h=8; src.x = 103; src.y = 100; dst.x = x; dst.y = y;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.x = 112;
    for (int i = 8; i < w-8; i+=16) {
        dst.x = x+i; src.w=16;
        while (dst.x + src.w > x+w && src.w>0) src.w--;
        if (src.w>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.w=8; src.x = 129; dst.x = x+w-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.y = 109; src.w=8;
    for (int j = 8; j < h-8; j+=16) {
        dst.y = y + j;
        src.x = 103; dst.x = x; src.h=16;
        while (dst.y + src.h > y+h && src.h>0) src.h--;
        if (src.h>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
        src.x = 129; dst.x = x+w-8;
        if (src.h>0)SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.h=8; src.x = 103; src.y = 126; dst.x = x; dst.y = y+h-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.x = 112;
    for (int i = 8; i < w-8; i+=16) {
        dst.x = x+i; src.w=16;
        while (dst.x + src.w > x+w && src.w>0) src.w--;
        if (src.w>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.w=8; src.x = 129; dst.x = x+w-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
}

void Texte::setTexte(int idTxt, int vx, int vy, int vw, int vh, bool cadr, bool defil, int vit) {
    if (idTxt == 0) return;
    id = idTxt; 
    idsuiv = 0;
    buffer = "";
    chercheText();
    
    x = vx; y = vy; w = vw; h = vh;
    decoupeText();
        
    def=defil;
    if (def) av = 0;
    else av = texte.length();
    
    cadre = cadr;
    
    vitesse = vit;
}

void Texte::decoupeText() {
    //compte le nombre de caract�res possibles et largeur et en hauteur
    int nbcol = (w-16)/6 -1;
    int nblig = (h-16)/16;
    int tailleMax = nbcol * nblig;
    int taille;
    
    //parcours du texte � afficher; � chaque d�but de mot, 
    //v�rifie que le mot peut tenir sur la ligne
    for (int i = 0; i < (int)texte.length(); i++) {
        
        //supprime les espaces isol�s en d�but de ligne
        if (texte.at(i)==' ' && texte.at(i+1)!=' ' && i%nbcol == 0) texte.erase(i,1);
        //recherche du d�but du prochain mot
        while(texte.at(i)==' ' && i < (int)texte.length()-1) i++;
        
        //saute une ligne si trouve une �toile
        if (texte.at(i)=='*') {
            texte.erase(i,1);//replace(i, 1, " ");
            int nb = (nbcol)-(i%(nbcol));
            for (int j = 0; j < nb; j++) texte.insert(i," ");
            continue;
        }
        
        //si le mot d�passe
        taille = tailleMot(i);
        if ((i%nbcol)+taille>nbcol) {
            if  (i < tailleMax) {
                //si le mot ne tient pas sur une ligne, on le coupe avec des tirets
                if (taille>nbcol) {
                    texte.insert(((i/nbcol)+1)*nbcol-1,"--");
                    i = 1+((i/nbcol)+1)*nbcol;
                }
                //sinon, on ajoute des espaces pour faire commencer le mot � la ligne
                else while((i%nbcol) != 0) {texte.insert(i," "); i++;}
            }
        }
        
    }
    
    // si le texte est trop grand, on le coupe en deux
    if ((int)texte.length() > tailleMax) {
        buffer = texte.substr(tailleMax);
        texte = texte.substr(0, tailleMax);
    }
}

int Texte::tailleMot(int deb) {
    int i = deb;
    int total = 0;
    while (texte.at(i)!=' ') {total++; i++; if (i >= (int)texte.length()) return total;}
    return total;
}

void Texte::afficheLettre(SDL_Surface* gpScreen, char c, int vx, int vy) {
    SDL_Rect src;
    SDL_Rect dst;
    
    int val = (int)c;
    
    dst.x=vx; dst.y=vy;
    src.h=16;src.w=8;
    
    if(val==32) return;
    
    //minuscules a-z
    if(val>=97 && val<=122) {
		src.x=4+16*((val-97)%10); 
		src.y=52+16*((val-97)/10);
	}
	//majuscules A-Z
	else if(val>=65 && val<=90) {src.x=6+16*((val-65)%10); src.y=2+16*((val-65)/10);}
	//chiffres
    else if(val>=48 && val<=57) {src.x=3+16*((val-48)%5); src.y=103+16*((val-48)/5);}
	else {
		switch(val){
			// Caract�res sp�ciaux
			// /
			case 47: src.x=52;src.y=151;break;
			// @ hylien
			case 64: src.x=4;src.y=151;break;
            // + hylien
			case 43: src.x=20;src.y=151;break;
            // = hylien
			case 61: src.x=36;src.y=151;break;
			// �
			case -25:
			case 231: src.x=148;src.y=34;break;
			// �
			case -23: 
			case 233: src.x=100;src.y=84;break;
			// �
			case -22:
			case 234: src.x=116;src.y=84;break;
			// �
			case -24:
			case 232: src.x=132;src.y=84;break;
			// �
			case -21:
			case 235: src.x=132;src.y=151;break;
			// �
			case -32:
			case 224: src.x=148;src.y=84;break;
			// �
			case -30:
			case 226: src.x=148;src.y=103;break;
			// �
			case -28:
			case 228: src.x=148;src.y=135;break;
			// �
			case -18:
			case 238: src.x=84;src.y=119;break;
			// �
			case -17:
			case 239: src.x=116;src.y=151;break;
			// �
			case -5:
			case 251: src.x=84;src.y=103;break;
			// �
			case -7:
			case 249: src.x=148;src.y=151;break;
			// �
			case -4:
			case 252: src.x=116;src.y=135;break;
			// �
			case -10:
			case 246: src.x=132;src.y=135;break;
			// �
			case -12:
			case 244: src.x=148;src.y=119;break;
			
			// Ponctuation
			//ponctuation
			// -
			case 45: src.x=102;src.y=34;break;
			// .
			case 46: src.x=118;src.y=34;break;
			// ,
			case 44: src.x=134;src.y=34;break;
			// !
			case 33: src.x=3;src.y=135;break;
			// ?
			case 63: src.x=19;src.y=135;break;
			// (
			case 40: src.x=35;src.y=135;break;
			// )
			case 41: src.x=51;src.y=135;break;            
			// ' ( avec @ )
			case 39: src.x=67;src.y=135;break;
			// :
			case 58: src.x=83;src.y=135;break;
			// ... ( avec % )
			case 37: src.x=101;src.y=135;break;
			// >
			case 62: src.x=100;src.y=151;break;
			// <
			case 60: src.x=84;src.y=151;break;
		}
	}
    
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
}

bool Texte::hasNext() {
    return (buffer != "" || idsuiv > 0);
}

bool Texte::suite() {
    if (av < (int)texte.length()) {
        av = texte.length();
        return true;
    }
    if (!hasNext()) {
        gpJeu->getAudio()->playSound(18);
        return gpJeu->finTexte(id);
    }
    if (buffer != "") {
        texte = buffer;
        buffer = "";
    }
    else {
        id = idsuiv;
        idsuiv = 0;
        chercheText();
    }
    decoupeText();
    if (def) av = 0;
    else av = texte.length();
    gpJeu->getAudio()->playSound(17);
    return true;
}
