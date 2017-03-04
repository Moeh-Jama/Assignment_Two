/*
 * main.c
 *
 *  Created on: Feb 27, 2017
 *      Author: Eoin Leonard & Mohamed Jama.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*struct general_player_build {

	char name_one[20];
//	char name_two[20];
	int health = 0;
	char type = " ";
	int dexterity=0, luck=0, magic_skills=0, strength=0, smartness=0;
};*/


struct general_player_build{
	char name_one[20];
	char name_two[20];
	int health;
	int type;
	int dexterity, luck, magic_skills, strength, smartness;
};

void player_type_function(int *t, int *d, int *l, int *m_s, int *st, int *sm, int Index);	//function prototype!

//static global
struct general_player_build cases[6];

int main(void)
{
	setbuf(stdout,NULL);
	int player_number;	//change to unsigned int i.e. >=0
		printf("Enter the number of players in this game!\nNumber of Players: ");
		scanf("%d", &player_number);//number of players in the game.


		for(int i=0; i<player_number-1; i++)
		{

			int t=0, d=0, sm=0, st=0, l=0, m_s=0;
			printf("PLEASE ENTER DETAILS FOR PLAYER %d", i+1);
			printf("\nEnter player[i] name: ");
			scanf("%s%s", cases[i].name_one, cases[i].name_two);
			printf("\nEnter player type");
			printf("choose 1.Ogre\n2.Human\n3.Wizard\n4.Elf");
			int choice;
			scanf("%d", &choice);

			switch(choice)
			{
			case 1:{
				printf("you have chosen Ogre!");
				cases[i].type = 0;
				printf("\nT\n");
				//printf("\n %s", cases[i].type);
				break;
			}
			case 2:{
				printf("you have chosen Human!");
				cases[i].type = 1;
				printf("\nT\n");
				//printf("\n %s", cases[i].type);
				break;
			}
			case 3:{
				printf("you have chosen Wizard!");
				cases[i].type = 2;
				printf("\nT\n");
				//printf("\n %s", cases[i].type);
				break;
			}
			case 4:{
				printf("you have chosen Elf!");
				cases[i].type = 3;
				printf("\nT\n");
				//printf("\n %s\n", cases[i].type);
				break;

			}
			default:{
				printf("ERROR!");
				//exit(0);
			}
			}

			//Create a method so I can get the data out of the player_type_function.
			//Use pointers as in
			player_type_function(&t, &d, &l, &m_s, &st, &sm, i); //do operation in order of variables shown type-smartness!
			printf("\nTESTING\n");
			cases[i].type = t;
			cases[i].dexterity =d;
			cases[i].luck = l;
			cases[i].magic_skills =m_s;
			cases[i].strength = st;
			cases[i].smartness= sm;

					printf("\n\nPlayer Name: %s\nPlayer Type %d\nPlayer dexterity\ %d\nPlayer Luck %d\n Player MagicSkills %d\nPlayer Strength %d\nPlayer Smartness %d\n", cases[i].name_one, cases[i].type, cases[i].dexterity, cases[i].luck, cases[i].magic_skills, cases[i].strength, cases[i].smartness);
					printf("\n*********************************************************\n");

		}
		print_players();
	return 0;
}
void player_type_function(int *t, int *d, int *l, int *m_s, int *st, int *sm, int index){
	srand(time(NULL));
	int rand_t, rand_d, rand_l, rand_m_s, rand_st, rand_sm;
	if(cases[index].type == 0)
	{
		//OGRE
		*m_s=0;
		*sm = rand()%20;
		do{*st = rand()%100;
		}while(*st<80);
		do{*d = rand()%100;
		}while(*d<80);
		*l =  rand()%10;
	}
	else if(cases[index].type == 1)
		{
		//HUMAN
			*m_s=25;
			*sm = rand()%70;
			do{*st = rand()%70;
			}while(*st>80);

			*d=rand()%70;
		}
	else if(cases[index].type == 2){
			//
				*m_s=25;
				do{
					*sm = rand()%100;
				}while(*sm<90);
				*st = rand()%20;
				*d=0;
				do{
					*l = rand()%100;
				}while(*l<50);
			}
	else if(cases[index].type == 3){
				//printf("choose 1.Ogre\n2.Human\n3.Wizard\n4.Elf");
					do{*m_s=rand()%80;}while(*m_s<50);
					do{
						*sm = rand()%100;
					}while(*sm<70);
					*st = rand()%50;
					*d=0;
					do{*l = rand()%100;}while(*l<50);
				}

	else{
		printf("ERROR CANNOT ASSIGN VALUE TO CHARACTER");
		exit(0);
	}

}
void print_players(){

	for(int i=0; i<6; i++)
	{
		printf("Player Name: %s\nPlayer Type %d\nPlayer dexterity\ %d\nPlayer Luck %d\n Player MagicSkills %d\nPlayer Strength %d\nPlayer Smartness %d\n", cases[i].name_one, cases[i].type, cases[i].dexterity, cases[i].luck, cases[i].magic_skills, cases[i].strength, cases[i].smartness);
		printf("\n*********************************************************\n");
	}

}
