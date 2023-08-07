/*
 * menu.h
 *
 * Created: 8/6/2023 12:09:38 AM
 *  Author: mohamed hatem
 */ 


#ifndef MENU_H_
#define MENU_H_
typedef enum {
ROOM1_MENU=1,
ROOM2_MENU,
ROOM3_MENU ,
MORE_MENU ,
ROOM4_MENU  ,
RGB_MENU,
AIRCONDITIONING_MENU,
All_menu
}en_menu;
en_menu menu_select(void);
void MenuOption(en_menu SelectedRoom);
#endif /* MENU_H_ */