/*
 * option.h
 *
 * Created: 8/7/2023 10:36:41 AM
 *  Author: mohamed hatem
 */ 


#ifndef OPTION_H_
#define OPTION_H_

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



#endif /* OPTION_H_ */