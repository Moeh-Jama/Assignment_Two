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

enum environments{ Hill, City, Ground,};

struct general_player_build{
	char name_one[20];
	char name_two[20];
	int health;
	int identifier;
	int type;
	int dexterity, luck, magic_skills, strength, smartness;
};
struct general_slot_build{
	int level;
	int player_position;
};

//int slots[19][2];

//function prototypes
void player_type(int type_integer);
void player_type_function(int *t, int *d, int *l, int *m_s, int *st, int *sm, int *Index);	//function prototype!
void slot_sort();
void environment_print(int new_num);
void player_modification(int n, int k);
void movement(int player_index);

//the cases is used to store the specific number of players
int player_number= 6;
int slot_number;
struct general_slot_build levels[20];
struct general_player_build cases[6];

int main(void)
{
	srand(time(NULL));
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
			cases[i].identifier=i;
		}

		print_players();
		printf("Please enter the number of slots you would like to have!\nBetween 1-20\n Enter amount of slots: ");
		scanf("%d", &slot_number);
		//we have a probem if i make it 20
		while(slot_number<=0 && slot_number>20)
		{
			printf("\nThe the amount of slots that you inputed is incorrect\n");
			printf("Please enter the number of slots you would like to have!\nBetween 1-20\n Enter amount of slots: ");
			scanf("%d", &slot_number);
		}


		slot_sort();

		for(int i=0; i<player_number; i++)
		{
			printf("Player %d Would you like to move or attack?\n1. Move\n2. Attack\n.", i);
			int move;
			scanf("%d", &move);
			switch(move)
			{
				case 1:{
					movement(cases[i].identifier);
					break;
				}
				case 2:{
					//Her we should go to Attack menu;
					exit(0);
					break;
				}
				default:{
					printf("You have inputed an incorrect data value! Game has ended\n");
					exit(0);
				}
			}
		}
		print_players();
		//movement();

	return 0;
}

void movement(int player_index)
{
	//
	int position=0;
	for(int k = 0; k<slot_number; k++)
	{
		if(levels[k].player_position == player_index){
			position =k;
		}
	}
	printf("Would you like to move to the previous slot, behind, or the next slot?\n1.next\n2.previous\nENTER: ");
	int choice;
	printf("\n***************\n");
	scanf("%d", &choice);
	while(choice<1 || choice>2)
	{
		printf("Invalid Entry try again! \n1.next\n2.previous\nEnter: ");
		scanf("%d", &choice);
	}
	//IF CHOICE IS 1, then moving to the next operations is engaged.
	if(choice==1)
	{
		//checking if the player position is less than the array end!
		if(position<slot_number-1)
		{
			//if the player position is less than 9, it is player occupyng that area, therefore we cannot move there.
			if(levels[position+1].player_position==9){
				levels[position+1].player_position = cases[player_index].identifier;
				levels[position].player_position = 9;
				player_modification( (position+1), player_index);
				printf("\nYou Are Moving TO: ");
				environment_print(levels[position+1].level);
			}
			else{
				printf("You cannot go to this slot, it is already occupied!");
				movement(player_index);
			}
		}
		else{
			printf("There is no next slot to move back to, you are at the last slot!\nTry again");
			movement(player_index);
		}

	}
	else if(choice ==2){
		if(position>0){
			if(levels[position-1].player_position==9){
				levels[position-1].player_position = cases[player_index].identifier;
				levels[position].player_position = 9;
				player_modification( (position-1), player_index);
				printf("\nYou Are Moving TO: ");
				environment_print(levels[position-1].level);
			}
			else{
				printf("You cannot go to this slot, it is already occupied!");
				movement(player_index);

			}
		}
		else{
			printf("There is no previous slot to move next to, you are at the beginning slot!\nTry again");
			movement(player_index);
		}

	}

}


void slot_sort(){

	for(int i=0; i<slot_number; i++)
	{

		levels[i].level = rand()%3;
		levels[i].player_position = 9;
		printf("%d  ,", levels[i].level);
	}
	for(int i=0; i<slot_number; i++)
	{
		int randomiser = rand()%slot_number;
		int temp = levels[i].level;
		levels[i].level = levels[randomiser].level;
		levels[randomiser].level = temp;
	}
	// Maybe add a shuffling sort here later to truly randomize the set of slots
	for(int j; j<slot_number; j++)
	{
		printf("\n");
		environment_print(levels[j].player_position);
	}


	/// Here we will now assign a player to a random slot
	int random;
	for(int k=0; k<player_number; k++)
	{
		do{
			random= rand()%slot_number;
		}while(levels[random].player_position !=9);
			levels[random].player_position = cases[k].identifier;			//what we could do here is basically have levels[r].p_p = k, since k =identifier, same values.
			player_modification(random, k);
			printf("\n Player: %s %s, is in %d\n", cases[k].name_one, cases[k].name_two, random);
	}



}



void environment_print(int n){

	switch(n)
	{
	case 0:
	{
		printf("Hill");
		break;
	}
	case 1:
	{
		printf("City");
		break;
	}
	case 2:
	{
		printf("Ground");
		break;
	}
	}
}




void player_type_function(int *t, int *d, int *l, int *m_s, int *st, int *sm, int *index){

	if(cases[*index].type == 0)
	{
		//Limitations and requirements of the Ogre Type skills are adhered in this block.

		do{
			//here both smartness and luck are assigned values
			*sm = rand()%20;
			*l = rand()%100;
			//these values are then tested to whether they adhere to the limitations, if not it loops back and re-assigns both them a values.
		}while((*sm+*l)>51);
		*m_s=0;
		do{//Strength is assigned a value, if that value adheres to the limitations
			*st = rand()%100;
		}while(*st<80);
		do{
			*d = rand()%100;
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
//Only prints details and general_Build characteristics of the player.
	for(int i=0; i<player_number; i++)
	{
		int count = cases[i].type;				//int count is used for the player_type(int) function, that we use to print the player type.
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
void player_modification(int n, int i)
{
	//TODO finish this function then go onto completing the attack function
	printf("\nPlayer is %d\n", levels[n].level);
	//we can us this if they move positions.
	if(levels[n].level==2)
	{
		printf("NO changes as you are in Ground\n");
	}
	else if(levels[n].level == 1)
	{
		//City
		if(cases[i].smartness >60)
		{
		  		cases[i].magic_skills += 10;
		}
		else if(cases[i].smartness <=50)
		{
			cases[i].dexterity -= 10;
		  	//in the event that we get a negative number!
		  	if(cases[i].dexterity<0)
		  	{
		  		cases[i].dexterity=0;
		  	}
		 }
	}
	else if(levels[n].level == 0)
	{
		//Hill
		if(cases[i].dexterity <60)
		 {
		  	cases[i].strength -= 10;
		  	if(cases[i].strength<0)
		  	{
		  		cases[i].strength=0;
		  	}
		 }
		 else if(cases[i].dexterity >=50)
		 {
		  	cases[i].strength += 10;
		 }
	}
	else{
		printf("AN Error Has Occurred!\n");
	}
}
