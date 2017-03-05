/*
 * main.c
 *
 *  Created on: Feb 27, 2017
 *      Author: ja123
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Here the struct is built where all the aspects of the character details and characteristics of what they would have included is laid out.
struct general_player_build{
	char name_one[20];
	char name_two[20];
	int health;
	int type;
	int dexterity, luck, magic_skills, strength, smartness;
};
void player_type(int type_integer);
void player_type_function(int *t, int *d, int *l, int *m_s, int *st, int *sm, int *Index);	//function prototype!



//the cases is used to store the specific number of players
int player_number=6;
struct general_player_build cases[6];

int main(void)
{
	setbuf(stdout,NULL);
		printf("Enter the number of players in this game!\nNumber of Players: ");
		scanf("%d", &player_number);//number of players in the game.
		while(player_number<=0 || player_number>=7){
			printf("\nThe number of players is either too high or low, remember between 1-6 players!\n");
			printf("Enter the number of players in this game!\nNumber of Players: ");
			scanf("%d", &player_number);
		}

		for(int i=0; i<player_number; i++)
		{

			int t=0, d=0, sm=0, st=0, l=0, m_s=0;
			printf("PLEASE ENTER DETAILS FOR PLAYER %d", i+1);
			printf("\nEnter player[i] name: ");
			scanf("%s%s", cases[i].name_one, cases[i].name_two);
			printf("\nEnter player type\n");
			printf("choose \n1.Ogre\n2.Human\n3.Wizard\n4.Elf\n");
			int choice;
			scanf("%d", &choice);

			switch(choice)
			{
			case 1:{
				cases[i].type = 0;
				break;
			}
			case 2:{
				cases[i].type = 1;
				break;
			}
			case 3:{
				cases[i].type = 2;
				break;
			}
			case 4:{
				cases[i].type = 3;
				break;

			}
			default:{
				printf("ERROR!");
				exit(0);
			}
			}

			//Create a method so I can get the data out of the player_type_function.
			//Use pointers as in
			player_type_function(&t, &d, &l, &m_s, &st, &sm, &i); //do operation in order of variables shown type-smartness!
			cases[i].dexterity =d;
			cases[i].luck = l;
			cases[i].magic_skills =m_s;
			cases[i].strength = st;
			cases[i].smartness= sm;
			cases[i].health = 100;
		}
		print_players();
	return 0;
}
void player_type_function(int *t, int *d, int *l, int *m_s, int *st, int *sm, int *index){
	srand(time(NULL));
	if(cases[*index].type == 0)
	{
		//Limitations and requirements of the Ogre Type skills are adhered in this block.
		printf("\nOGRE\n");
		do{
			*sm = rand()%20;
			*l = rand()%100;
		}while((*sm+*l)>51);
		*m_s=0;
		do{*st = rand()%100;
		}while(*st<80);
		do{*d = rand()%100;
		}while(*d<80);
	}
	else if(cases[*index].type == 1)
	{
		//Limitations and requirements of the Human Type skills are adhered in this block.
		do{
			*m_s=1+rand()%100;
			*sm = 1+rand()%70;
			*st = 1+rand()%100;
			*l= 1+rand()%100;
			*d= 1+rand()%100;
		}while((*m_s+*sm+*st+*l+*d)>300);
	}
	else if(cases[*index].type == 2)
	{
		//Limitations and requirements of the Wizard Type skills are adhered in this block.
		*m_s=25;
		do{
			*sm = rand()%100;
		}while(*sm<90);
		*st = rand()%20;
		*d=rand()%100;
		do{
			*l = rand()%100;
		}while(*l<50);
	}
	else if(cases[*index].type == 3)
	{
		//Limitations and requirements of the Elf Type skills are adhered in this block.
		do{
			*m_s=rand()%80;
		}while(*m_s<50);
		do{
			*sm = rand()%100;
		}while(*sm<70);
		*st = rand()%50;
		*d=rand()%100;
		do{
			*l = rand()%100;
		}while(*l<50);
	}

	else{
		printf("ERROR CANNOT ASSIGN VALUE TO CHARACTER");
		exit(0);
	}

}
void print_players(){

	for(int i=0; i<player_number; i++)
	{
		int count = cases[i].type;
		printf("Player Name: %s %s\n", cases[i].name_one, cases[i].name_two);
		printf("Player Type: ");
		player_type(count);
		printf("\nPlayer Health: %d\n", cases[i].health);
		printf("Player Dexterity: %d\n", cases[i].dexterity);
		printf("Player Luck: %d\n", cases[i].luck);
		printf("Player Magic Skills: %d\n", cases[i].magic_skills);
		printf("Player Strength: %d\n", cases[i].strength);
		printf("Player Smartness: %d\n", cases[i].smartness);
		printf("\n*********************************************************\n");
	}

}
void player_type(int type_Integer)
{
	char type[6];
	if(type_Integer == 0)
	{
		printf( "Ogre");
	}
	else if(type_Integer ==1)
	{
		printf("Human");
	}
	else if(type_Integer ==2)
	{
		printf("Wizard");
	}
	else if(type_Integer ==3)
	{
		printf("Elf");
	}
	else{
		printf("ERROR");
	}


}
