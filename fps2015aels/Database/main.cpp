#include "Database.h"
#include "Player.h"
#include "Weapon.h"
#include "Charger.h"
#include <stdio.h>
#include <unistd.h>

int	main()
{
	Database*	database;
	Player*		player1;

	database = Database::GetInstance();
	database->Init();
//	player1 = new Player("test",0);
//	printf("dans player = %d\n", player1->__list_charger[1]);
/*	while (player1->Get_Weapon()->Get_Charger1() >= 0)
	{
//		printf("avant fire(chargeur) = %d\n", player1->Get_Weapon()->Get_Nb_Charger1());
		printf("avant fire(ammo2) = %d\n", player1->Get_Weapon()->Get_Charger1()->Get_Nb_Ammo());
		printf("avant fire(chargeur2) = %d\n", player1->Get_Weapon()->Get_Charger2()->Get_Nb_Ammo());
		player1->Fire(0);
		player1->Fire(1);
		printf("apres fire(ammo2) = %d\n", player1->Get_Weapon()->Get_Charger1()->Get_Nb_Ammo());
		printf("apres fire(chargeur2) = %d\n", player1->Get_Weapon()->Get_Charger2()->Get_Nb_Ammo());
		if (player1->Get_Weapon()->Get_Charger1()->Get_Nb_Ammo() == 0)
			player1->Reload(0);
		if (player1->Get_Weapon()->Get_Charger2()->Get_Nb_Ammo() == 0)
			player1->Reload(1);
//		printf("dans player = %d\n", player1->__list_charger[1]);
		printf("apres reload(ammo2) = %d\n", player1->Get_Weapon()->Get_Charger1()->Get_Nb_Ammo());
		printf("apres reload(chargeur2) = %d\n", player1->Get_Weapon()->Get_Charger2()->Get_Nb_Ammo());
		sleep(1);
	}*/
}
