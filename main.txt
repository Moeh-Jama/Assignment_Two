/*
 * main.c
 *
 *  Created on: Feb 27, 2017
 *      Author: Mohamed Jama & Eoin Leonard
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
//Here the struct is built where all the aspects of the character details and characteristics of what they would have included is laid out.

struct general_player_build{
	char name_one[20];
	char name_two[20];
	double health;
	int identifier;
	int type;
	int dexterity, luck, magic_skills, strength, smartness;
};
struct general_slot_build{
	int level;
	int position;
	int player_position;
};

void attackPlayer(struct general_player_build * attacker, struct general_player_build * attacked);
//function prototypes
//void alterStatsBasedOnPosition(struct Player * attacker, struct Player * attacked);
void player_type(int type_integer);
void player_type_function(int *t, int *d, int *l, int *m_s, int *st, int *sm, int *Index);	//function prototype!
void slot_sort();
void environment_print(int new_num);
void player_modification(int n, int k);
void movement(int player_index);
void attackMode(int playerNumber, int identity);
void moveToNextSlot(struct general_slot_build * location, struct general_player_build *player );
void moveToPreviousSlot(struct general_slot_build * location, struct general_player_build *player );
int isNotUniquePosition(int position);
void print_slots();
void print_players();
void final_print();
//the cases is used to store the specific number of levels
int player_number= 6;
int slot_number;
struct general_player_build cases[6];
struct general_slot_build levels[21];

int main(void)
{
	srand(time(NULL));
	setbuf(stdout,NULL);
	//Here the players the number of players will be initialized
		printf("Enter the number of Players in this game!\nNumber of Players: ");
		scanf("%d", &player_number);//number of levels in the game.
		while(player_number<=0 || player_number>=7){
			printf("\nThe number of levels is either too high or low, remember between 1-6 levels!\n");
			printf("Enter the number of levels in this game!\nNumber of levels: ");
			scanf("%d", &player_number);
		}
		//details for every detail will be given within this loop
		for(int i=1; i<=player_number; i++)
		{
			int t=0, d=0, sm=0, st=0, l=0, m_s=0;
			printf("PLEASE ENTER DETAILS FOR PLAYER %d", i);
			printf("\nEnter the first and second name of Player %d: ", i);
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
			//The function, player_type_function will give players their attributes according to their type.
			player_type_function(&t, &d, &l, &m_s, &st, &sm, &i);
			//Once those attributes have been given a value according to the specification, they will now be assigned to the actual struct array, per player specific
			cases[i].dexterity =d;
			cases[i].luck = l;
			cases[i].magic_skills =m_s;
			cases[i].strength = st;
			cases[i].smartness= sm;
			cases[i].health = 100;
			cases[i].identifier=i;
		}
		//Here we print the attributes and skills of the players.
		print_players();
		printf("Please enter the number of slots you would like to have!\nBetween 1-20\n Enter amount of slots: ");
		scanf("%d", &slot_number);
		//we have a probem if i make it 20
		while(slot_number<player_number || slot_number>20)
		{
			printf("\nThe the amount of slots that you inputed is incorrect\nRemember to have entered more slots than there are players!\n");
			printf("Please enter the number of slots you would like to have!\nBetween 1-20\n Enter amount of slots: ");
			scanf("%d", &slot_number);
		}
		printf("\n slot_number %d", slot_number);

		slot_sort();
		print_slots();
		for(int i=1; i<=player_number; i++)
		{
			printf("\nPlayer %s Would you like to move or attack?\n1. Move\n2. Attack\n.", cases[i].name_one);
			int move;
			scanf("%d", &move);
			if(move==1)
			{

					movement(cases[i].identifier);
			}
			if(move==2){

					int player_number;
					for(int k=1; k<=slot_number; k++)
					{
						if(levels[k].player_position == i)
						{
							player_number=k;
							k=slot_number;
						}
					}
					printf("YOUR POISITION IS: %d\n", levels[player_number].player_position);
					attackMode(player_number, i);
				}

			}

		print_slots();
		final_print();
	return 0;
}
void final_print()
{
	for(int i=1; i<=player_number; i++)
	{
		printf("%s (", cases[i].name_one);
		player_type(cases[i].type);
		printf(", %.0lf)\n", cases[i].health);
	}
}
void movement(int player_index)
{
	//Here the user chooses to either move back or forwards!.
	int position=1;
	//looking for when the slot contains the player.
	for(int k = 1; k<=slot_number; k++)
	{
		if(levels[k].player_position == player_index){
			position =k;
		}
	}
	print_players();
	print_slots();
	printf("\nWould you like to move to the previous slot, behind, or the next slot?\n1.next\n2.previous\nENTER: ");
	int choice;
	printf("\n***************\n");
	scanf("%d", &choice);

	switch(choice)
	{
	case 1:{
		moveToNextSlot(&levels[position], &cases[player_index]);
		break;
	}
	case 2:{
		moveToPreviousSlot(&levels[position], &cases[player_index]);
		break;
	}
	default:{
		printf("Invalid Data entry please try again!");
		movement(player_index);
		break;
	}
	}
}


void moveToNextSlot(struct general_slot_build * location, struct general_player_build *player ){
	//variables used for the checking of the next slot and moving them.
	 int k=1;
	 int player_number;
	 int level_number=0;
	 while(levels[k++].player_position != player->identifier);
	for(int j=0; j<=slot_number; j++)
	 {
		 if(player->identifier==levels[j].player_position){
			 level_number=j;
			 j=slot_number;
		 }
	 }

	 player_number=k;
	// k=slot_number;

	 	//variables to be used for the inspection and mvoing of the player.
	 	int player_located_at, i=1;
	     if (location->position +1 > slot_number){//if our location is zero then we cannot move.
	         printf("Cannot move %s, you are at the start of the map. \n", player->name_one);
	         int choice=0;
	         while(choice<=0 ||choice>=3){
	        	 printf("Would you like to 1.Move Back\n2.Attack?\n");
	        	 scanf("%d", &choice);
	         }
	         switch(choice)
	         {
	         case 1: moveToPreviousSlot(&levels[level_number], &cases[player->identifier]); break;
	         case 2: attackMode(level_number, player->identifier);
	         }
	     }
	     else if(levels[level_number+1].player_position!=9){	//if the slot is not empty, i.e. contains an element not being 9, then there is a player there.
	     	 printf("Cannot move player, enemy is in position %d.\n", location->position+1);
	     	 int choice=0;
	     		         while(choice<=0 ||choice>=3){
	     		        	 printf("Would you like to 1.Move Back\n2.Attack?\n");
	     		        	 scanf("%d", &choice);
	     		         }
	     		         switch(choice)
	     		         {
	     		         case 1: moveToPreviousSlot(&levels[level_number], &cases[player->identifier]); break;
	     		         case 2: attackMode(level_number, player->identifier);
	     		         }
	     }else {
	    	 i=0;
	         while(levels[++i].player_position!=player->identifier);				//looking for the
	         		player_located_at=i;
	         		printf("Moving %s to position %d a ", player->name_one, levels[i+1].position);
	 			    environment_print(levels[i+1].level);
	 			    printf("\n");
	         location->player_position = 9;
	         levels[level_number+1].player_position = player->identifier;
	     }


}

void print_slots(){
	//printing the slots
	printf("LEVEL | REGION  | AREA CONTAINS");
	for(int i=1; i<=slot_number; i++)
	{
		printf("\n%d\t", levels[i].position);
		environment_print(levels[i].level);
		if(levels[i].player_position==9)			//if the slot contains the value 9, we assume it is empty.
		{
			printf("\tEmpty");
		}
		else{
			for(int n=1; n<=player_number; n++)
			{
				if(levels[i].player_position==n)
				{
					printf("\t%s %s", cases[n].name_one, cases[n].name_two);
				}
			}
		}
	}
}

void moveToPreviousSlot(struct general_slot_build * location, struct general_player_build *player ){
	//variables to be used for the inspection and mvoing of the player.

	 int k=1;
		 int player_number, level_number=1;
		 while(levels[k++].player_position != player->identifier);
		 player_number=k;
		 for(int j=1; j<=slot_number; j++)
		 	 {
		 		 if(player->identifier==levels[j].player_position){
		 			 level_number=j;
		 			 j=slot_number;
		 		 }
		 	 }

	int player_located_at, i=1;
    if (location->position -1 <= 1){//if our location is zero then we cannot move.
        printf("Cannot move %s, you are at the start of the map. \n", player->name_one);
        int choice=0;
       while(choice<=0 ||choice>=3){
        	printf("Would you like to 1.Move Forward\n2.Attack?\n");
        	scanf("%d", &choice);
        }
        switch(choice)
        {
        case 1: moveToNextSlot(&levels[level_number], &cases[player->identifier]); break;
        case 2: attackMode(level_number, player->identifier); break;
        }
    }
    else if(levels[level_number-1].player_position!=9){	//if the slot is not empty, i.e. contains an element not being 9, then there is a player there.
    	 printf("Cannot move player, enemy is in position %d.\n", location->position-1);
    	 int choice=0;
    	 while(choice<=0 ||choice>=3){
    		 printf("Would you like to 1.Move Forward\n2.Attack?\n");
    		 scanf("%d", &choice);
    	 }
    	 switch(choice)
    	 {
    	 case 1: moveToNextSlot(&levels[level_number], &cases[player->identifier]); break;
    	 case 2: attackMode(level_number, player->identifier); break;
    	 }
    }else {
    	i=0;
        while(levels[++i].player_position!=player->identifier);				//looking for the
        		player_located_at=level_number;
        		printf("Moving %s to position %d a ", player->name_one, levels[i-1].position);
			    environment_print(levels[level_number-1].level);
			    printf("\n");
        location->player_position = 9;
        levels[level_number-1].player_position = player->identifier;
    }
}
int isNotUniquePosition(int position){
	if(position ==9){
        return 1;
    }
	else{
		return 0;
	}

}

void slot_sort(){
	//Here we create the slots and assign player into them.
	for(int i=1; i<=slot_number; i++)
	{
		levels[i].level = rand()%3;
		levels[i].player_position = 9;
		levels[i].position=i;
	}
	//we shuffle the slot, to randomise it further if there occured a "rand" error which came to notice to be a problem for some users.
	for(int i=1; i<=slot_number; i++)
	{
		int randomiser = 1+rand()%slot_number;
		int temp = levels[i].level;
		levels[i].level = levels[randomiser].level;
		levels[randomiser].level = temp;
	}
	// Here we will now assign a player to a random slot
	int random;
	for(int k=1; k<=player_number; k++)
	{
		//Create a random variable between 1 and the slotnumber. This is where the user will be going.
		do{
			random= 1+rand()%slot_number;
		}while(levels[random].player_position !=9);	//this loops helps us place the players into only empty slots.
			levels[random].player_position = cases[k].identifier;			//what we could do here is basically have levels[r].p_p = k, since k =identifier, same values.
			player_modification(random, k);
			printf("\n Player: %s %s is in Level %d\n", cases[k].name_one, cases[k].name_two, random );

	}
}

void environment_print(int n){
	//print the terraine according to the input integer as shown below.
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
	//Here we give the players their attributes according to their type, specified in the assignment details
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
		
		do{
			*sm = rand()%100;
		}while(*sm<90);
		*st = rand()%20;
		*d=rand()%100;
		do{
			*l = rand()%100;
		}while(*l<50);
		do{
			*m_s=rand()%100;
		}while(*m_s<80);
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
	for(int i=1; i<=player_number; i++)
	{
		int count = cases[i].type;				//int count is used for the player_type(int) function, that we use to print the player type.
		printf("Player Name: %s %s\n", cases[i].name_one, cases[i].name_two);
		printf("Player Type: ");
		player_type(count);
		printf("\nPlayer Health: %.0lf\n", cases[i].health);
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
	//print the player type, according from the integer of 0-3;
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
	//player modifications according to the terrain, or environment, they are in is implemented within this function.
	printf("\n %s is in the ", cases[i].name_one);
	environment_print(levels[n].level);
	printf("\n");
	if(levels[n].level==2)
	{
		//there will be no change as they are in the Ground terraine
	}
	else if(levels[n].level == 1)
	{
		//If the user has entered the City the their smartness will either increase their magic_skills, or reduce their dextrity.
		if(cases[i].smartness >60)
		{
			//since smartness is greater than 60, then their magic is increased. if their magic is passed the max, 100, we bring it back.
		  		cases[i].magic_skills += 10;
		  		if(cases[i].magic_skills>100)
		  		{
		  			cases[i].magic_skills=100;
		  		}

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
		//If the user has entered the Hill the their dexterity will either increase their strength, or reduce their strength.
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
		  	if(cases[i].strength>100)
		  	{
		  		cases[i].strength=100;
		  	}
		 }
	}
	else{
		printf("AN Error Has Occurred!\n");
	}
}

void attackMode(int playerNumber,int identity){
   //In this function the player will attack the closes player to them. first the variables that will be used are initialized
    bool isEnemyBehindPlayer = false;
    bool isEnemyInFrontOfPlayer = false;
    printf("%s have chosen to attack!\n", cases[identity].name_one);
    int victim_A, victim_B, index_A, index_B;
    int i;
    int count_forward=0, count_backward=0;
    //This loop is used to search for players in front of the attacking player.
    for(i = playerNumber+1; i <= slot_number; i++){
    	//in the even we find an element
    	count_forward++;
    	if(levels[i].player_position !=9){
    		printf("There is an enemy in front of you. players name is %s and his position is %d. Your position is %d\n", cases[levels[i].player_position].name_one, i, playerNumber);
            isEnemyInFrontOfPlayer = true;
            victim_A = levels[i].player_position;
            index_A=i;
            i=slot_number;	//terminates the loop
        }
    }
    for(int k=playerNumber-1; k>=1; k--)
    {
    	count_backward++;
    	 if(levels[k].player_position !=9)
    	 {
    		printf("There is an enemy behind you. players name is %s and his position is %d. Your position is %d\n", cases[levels[k].player_position].name_one,k, playerNumber);
    		 isEnemyBehindPlayer = true;
    		 victim_B = levels[k].player_position;
    		 index_B=k;
    		 k=0;	//terminates the loop
    	 }
    }
    if(isEnemyBehindPlayer==false)
    {
    	count_backward=9;
    }
    if(isEnemyInFrontOfPlayer==false)
    {
    	count_forward=9;
    }

    //Checks for levels in front and behind you. User must choose which Player* to attack
    //The Player* that is not chosen gets set to false
    if(count_forward == count_backward){
        printf("There is a Player in front and behind you. Do you want to attack the Player behind [b] or in front [f] of you?");
        char attackPlayerChoice;
        scanf("%s", &attackPlayerChoice);

        switch (attackPlayerChoice) {
        case 'b': isEnemyInFrontOfPlayer = false;count_forward=count_backward+1; break;
        case 'f': isEnemyBehindPlayer = false; count_backward=count_forward+1; break;
        default: printf("Wrong input selected, quitting game.\n");
        exit(0);
        }
    }



    if(isEnemyBehindPlayer || count_backward<count_forward)
    {
        printf("You attack the player behind you.\n");
        printf("ATTACKER STRENGTH %d\n", cases[identity].strength);
        attackPlayer(&cases[identity], &cases[victim_B]);
    }
    else if (isEnemyInFrontOfPlayer || count_forward<count_backward)
    {
        printf("You attack the player in front of you.\n");
        printf("ATTACKER STRENGTH %d\n", cases[identity].strength);
        attackPlayer(&cases[identity], &cases[victim_A]);
    }
    else {
        printf("There is no player to attack! Skipping turn.\n");
    }

}
//This is where the life points go down for the attacker/attacked based on strength
void attackPlayer(struct general_player_build * attacker, struct general_player_build * attacked){
    if(attacked->strength <= 70){
        printf(" %.0lf ATTACK points\n", (0.5 * attacker->strength));
        attacked->health -= (0.5 * attacker->strength);
    } else {
        printf(" %.0lf\n ATTACK points", (0.3 * attacked->strength));
        attacker->health -= (0.3 * attacked->strength);
    }
}
