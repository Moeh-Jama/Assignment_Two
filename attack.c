void attackMode(int playerNumber){
    //  printf("Player* number = %d\n", playerNumber);
    bool isEnemyBehindPlayer = false;
    bool isEnemyInFrontOfPlayer = false;

    printf("You have chosen to attack!\n");

    int i;
    for(i = 0; i < numberOfPlayers; i++){
        if(players[playerNumber].currentPosition -1 == players[i].currentPosition){
            printf("There is an enemy behind you. Players name is %s and his position is %d. Your position is %d\n", players[i].name, players[i].currentPosition, players[playerNumber].currentPosition);
            isEnemyBehindPlayer = true;
        } else if(players[playerNumber].currentPosition +1 == players[i].currentPosition){
            printf("There is an enemy in front of you. Players name is %s and his position is %d. Your position is %d\n", players[i].name, players[i].currentPosition, players[playerNumber].currentPosition);
            isEnemyInFrontOfPlayer = true;
        }
    }

    //Checks for players in front and behind you. User must choose which Player* to attack
    //The Player* that is not chosen gets set to false
    if(isEnemyBehindPlayer && isEnemyInFrontOfPlayer){
        printf("There is a Player in front and behind you. Do you want to attack the Player behind [b] or in front [f] of you?");
        char attackPlayerChoice;
        scanf("%s", &attackPlayerChoice);

        switch (attackPlayerChoice) {
        case 'b': isEnemyInFrontOfPlayer = false; break;
        case 'f': isEnemyBehindPlayer = false; break;
        default: printf("Wrong input selected, quitting game.\n");
        exit(0);
        }
    }


    if(isEnemyBehindPlayer){
        printf("You attack the player behind you.\n");
        alterStatsBasedOnPosition(&players[playerNumber], &players[playerNumber - 1]);
        attackPlayer(&players[playerNumber], &players[playerNumber - 1]);
    } else if (isEnemyInFrontOfPlayer){
        printf("You attack the player in front of you.\n");
        alterStatsBasedOnPosition(&players[playerNumber], &players[playerNumber + 1]);
        attackPlayer(&players[playerNumber], &players[playerNumber + 1]);
    } else {
        printf("There is no player to attack! Skipping turn.\n");
    }

}

//This is where the players stats are changed based on the terrain they currently are on
void alterStatsBasedOnPosition(struct Player * attacker, struct Player * attacked){

    if(slots[attacker->currentPosition] == HILL){
        if(attacker->dexterity < 50){
            attacker->strength -= 10;
            if(attacker->strength < 0){
                attacker->strength = 0;
            }
        } else {
            attacker->strength += 10;
        }
    } else if(slots[attacker->currentPosition] == CITY){
        if(attacker->smartness <= 50){
            attacker->dexterity -= 10;
            if(attacker->dexterity < 0){
                attacker->dexterity = 0;
            }
        } else {
            attacker->magicSkills += 10;
        }
    }

    if(slots[attacked->currentPosition] == HILL){
        if(attacked->dexterity < 50){
            attacked->strength -= 10;
            if(attacked->strength < 0){
                attacked->strength = 0;
            }
        } else {
            attacked->strength += 10;
        }
    } else if(slots[attacked->currentPosition] == CITY){
        if(attacked->smartness <= 50){
            attacked->dexterity -= 10;
        } else {
            attacked->magicSkills += 10;
        }
    }

}



//This is where the life points go down for the attacker/attacked based on strength
void attackPlayer(struct Player * attacker, struct Player * attacked){
    if(attacked->strength <= 70){
        printf("%f\n", (0.5 * attacker->strength));
        attacked->lifePoints -= (0.5 * attacker->strength);
    } else {
        printf("%f\n", (0.5 * attacker->strength));
        attacker->lifePoints -= (0.3 * attacked->strength);
    }
}

//Checks for empty slot to the right of the player, and will move it into that slot if it is free
void moveToNextSlot(struct Player * player){

    if (player->currentPosition +1 > numberOfSlots -1){
        printf("Cannot move player, you are at the end of the map. Skipping turn.\n");
    }else if(isNotUniquePosition(player->currentPosition +1)){
        printf("Cannot move player, enemy is in position %d. Skipping turn.\n", player->currentPosition +1);
    } else{
        printf("Moving player to position %d\n", player->currentPosition + 1);
        player->currentPosition += 1;
    }
}


//Checks that previous slot is free/valid, and moves player to that position
void moveToPreviousSlot(struct Player * player){
    if (player->currentPosition -1 < 0){
        printf("Cannot move Player*, you are at the end of the map. Skipping turn.\n");
    } else if(isNotUniquePosition(player->currentPosition -1)){
        printf("Cannot move Player*, enemy is in position %d. Skipping turn.\n", player->currentPosition -1);
    }else {
        printf("Moving Player* to position %d\n", player->currentPosition - 1);
        player->currentPosition -= 1;
    }
}