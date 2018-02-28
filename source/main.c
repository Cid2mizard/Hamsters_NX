#include <string.h>
#include <stdio.h>
#include <stdlib.h>	

#include <switch.h>

u32 kDown;

bool mode_intro;
bool error;
int mode_game;

u8 Mois;

typedef struct 
{
	u16 ADULTES;
	u16 PETITS;
	u16 CAGES;
	int nb_par_cage;
} 
info;
info MALES, FEMELLES;

int NOURRITURE;
float PRIX_HAMSTER;
float CAISSE;
float SCORE;
int MORTS_FAIM;
int MORTS_ETOUFFES;

int males_a_vendre;
int femelles_a_vendre;
int nombre_accouplement;
int nourriture_a_acheter;
int achats_cages_males;
int achats_cages_femelles;
int selection;

u64 LanguageCode;
s32 Language;
Result langue;

//u8 langue = 2;

void clean()
{
	printf("\x1b[28;1H                                               ");
	printf("\x1b[29;1H                                               ");
	printf("\x1b[30;1H                                               ");
	printf("\x1b[31;1H                                               ");
	printf("\x1b[32;1H                                               ");
	printf("\x1b[33;1H                                               ");
	printf("\x1b[34;1H                                               ");
	printf("\x1b[35;1H                                               ");
	printf("\x1b[36;1H                                               ");
	printf("\x1b[37;1H                                               ");
	printf("\x1b[38;1H                                               ");
	printf("\x1b[39;1H                                               ");
	printf("\x1b[40;1H                                               ");
	printf("\x1b[41;1H                                               ");
	printf("\x1b[42;1H                                               ");
	printf("\x1b[43;1H                                               ");
	printf("\x1b[44;1H                                               ");
	printf("\x1b[45;1H                                               ");
}


void printGame()
{
	if (mode_intro)
	{
		printf("\x1b[2;30H\x1b[31m***** HAMSTERS NX *****\x1b[0m");

		if (langue == 2)
		{
			printf("\x1b[4;1HLe but du jeu est de gerer un elevage de hamsters");
			printf("\x1b[5;1Hpendant 12 mois en faisant des benefices.");
			printf("\x1b[6;1H* On ne peut vendre ou accoupler que des adultes.");
			printf("\x1b[7;1H* Les petits deviennent adultes en 1 mois.");
			printf("\x1b[8;1H* Chaque accouplement peut donner un maximum de 18 petits.");
			printf("\x1b[10;1H** Appuyez sur A pour continuer...");
		}
		else
		{
			printf("\x1b[4;1HThe purpose of the game is to manage breeding");
			printf("\x1b[5;1Hhamsters 12 months by making profits.");
			printf("\x1b[6;1H* You can sell or couple only the adults.");
			printf("\x1b[7;1H* Youngs become adults after 1 month.");
			printf("\x1b[8;1H* Each coupling can give a maximum of 18 youngs.");
			printf("\x1b[10;1H** Press A to continue...");
		}
	}
	else if ((mode_game > 0) && (mode_game < 8))
	{
		if (langue == 2)
		{
			printf("\x1b[12;1H-------------------------------------------------");
			printf("\x1b[13;15HSITUATION DU MOIS No %d   ", Mois);
			printf("\x1b[15;10HMALES                 FEMELLES");
			printf("\x1b[16;10HADULTES : %d   ", MALES.ADULTES);
			printf("\x1b[16;32HADULTES : %d   ", FEMELLES.ADULTES);
			printf("\x1b[17;10HPETITS  : %d   ", MALES.PETITS);
			printf("\x1b[17;32HPETITS  : %d   ", FEMELLES.PETITS);
			printf("\x1b[18;10HCAGES   : %d   ", MALES.CAGES);
			printf("\x1b[18;32HCAGES   : %d   ", FEMELLES.CAGES);
			printf("\x1b[19;6Hnb par cage : %d   ", MALES.nb_par_cage);
			printf("\x1b[19;28Hnb par cage : %d   ", FEMELLES.nb_par_cage);
			printf("\x1b[21;1HNOURRITURE RESTANTE     : %d KG   ", NOURRITURE);
			printf("\x1b[22;1HPRIX DU HAMSTER CE MOIS : %.2f $   ", PRIX_HAMSTER);
			printf("\x1b[23;1HEN CAISSE               : %.2f $   ", CAISSE);	
			printf("\x1b[24;1HMORTS DE FAIM           : %d   ", MORTS_FAIM);
			printf("\x1b[25;1HMORTS ETOUFFES          : %d   ", MORTS_ETOUFFES);	
			printf("\x1b[26;1H** Appuyez sur A pour continuer...");
			printf("\x1b[27;1H-------------------------------------------------");

			if (mode_game == 2)
			{
				printf("\x1b[28;1HMALES A VENDRE ? %d   ", males_a_vendre);
			}
			if (mode_game == 3)
			{
				printf("\x1b[29;1HFEMELLES A VENDRE ? %d   ", femelles_a_vendre);
			}
			if (mode_game == 4)
			{
				printf("\x1b[30;1HNOMBRE D'ACCOUPLEMENT ? %d   ", nombre_accouplement);
			}
			if (mode_game == 5)
			{
				printf("\x1b[31;1HNOURRITURE A ACHETER ? %d   ", nourriture_a_acheter);
			}
			if (mode_game == 6)
			{
				printf("\x1b[32;1HACHAT DE CAGES POUR LES MALES ? %d   ", achats_cages_males);
			}
			if (mode_game == 7)
			{
				printf("\x1b[33;1HACHAT DE CAGES POUR LES FEMELLES ? %d   ", achats_cages_femelles);
			}
		}
		else
		{
			printf("\x1b[12;1H-------------------------------------------------");
			printf("\x1b[13;15HSITUATION OF THE MONTH No %d   ", Mois);
			printf("\x1b[15;10HMALES                 FEMALES");
			printf("\x1b[16;10HADULTS  : %d   ", MALES.ADULTES);
			printf("\x1b[16;32HADULTS  : %d   ", FEMELLES.ADULTES);
			printf("\x1b[17;10HYOUNGS  : %d   ", MALES.PETITS);
			printf("\x1b[17;32HYOUNGS  : %d   ", FEMELLES.PETITS);
			printf("\x1b[18;10HCAGES   : %d   ", MALES.CAGES);
			printf("\x1b[18;32HCAGES   : %d   ", FEMELLES.CAGES);
			printf("\x1b[19;6Hnb per cage : %d   ", MALES.nb_par_cage);
			printf("\x1b[19;28Hnb per cage : %d   ", FEMELLES.nb_par_cage);
			printf("\x1b[21;1HREMAINING FOOD              : %d KG   ", NOURRITURE);
			printf("\x1b[22;1HPRICE OF HAMSTER THIS MONTH : %.2f $   ", PRIX_HAMSTER);
			printf("\x1b[23;1HCHECKOUT                    : %.2f $   ", CAISSE);	
			printf("\x1b[24;1HDEAD HUNGRY                 : %d   ", MORTS_FAIM);
			printf("\x1b[25;1HDEAD SUFFOCATED             : %d   ", MORTS_ETOUFFES);	
			printf("\x1b[26;1H** Press A to continue...");
			printf("\x1b[27;1H-------------------------------------------------");

			if (mode_game == 2)
			{
				printf("\x1b[28;1HMALES FOR SALE ? %d   ", males_a_vendre);
			}
			if (mode_game == 3)
			{
				printf("\x1b[29;1HFEMALES FOR SALE ? %d   ", femelles_a_vendre);
			}
			if (mode_game == 4)
			{
				printf("\x1b[30;1HNUMBER COUPLING ? %d   ", nombre_accouplement);
			}
			if (mode_game == 5)
			{
				printf("\x1b[31;1HFOOD TO BUY ? %d   ", nourriture_a_acheter);
			}
			if (mode_game == 6)
			{
				printf("\x1b[32;1HPURCHASE CAGES FOR MALES ? %d   ", achats_cages_males);
			}
			if (mode_game == 7)
			{
				printf("\x1b[33;1HPURCHASE CAGES FOR FEMALES ? %d   ", achats_cages_femelles);
			}
		}

		if (error)
			printf("\x1b[34;1HIMPOSSIBLE   ");
		else
			printf("\x1b[34;1H             ");
	}
	else if (mode_game == 8)
	{
		if (langue == 2)
		{
			printf("\x1b[35;1H...........FIN DU JEU...........   ");

			if (SCORE <=150)
			{
				printf("\x1b[37;1HOOPS!, VOTRE METHODE D'ELEVAGE EST A REVOIR.   ");
			}
			else if ((SCORE > 150) && (SCORE <= 500))
			{
				printf("\x1b[37;1HBRAVO, VOUS AVEZ CORRECTEMENT GERE L'ELEVAGE.   ");
			}
			else if (SCORE > 500)
			{
				printf("\x1b[37;1HEXCELLENT, VOUS ETES UN CHAMPION DE L'ELEVAGE.   ");
			}

			printf("\x1b[38;1HVOUS AVEZ AU BOUT DE CES 12 MOIS :   ");
			printf("\x1b[39;1H%d ADULTES   ", MALES.ADULTES + FEMELLES.ADULTES);
			printf("\x1b[40;1H%d PETITS   ", MALES.PETITS + FEMELLES.PETITS);
			printf("\x1b[41;1H%d CAGES   ", MALES.CAGES + FEMELLES.CAGES);
			printf("\x1b[42;1H%d KG DE NOURRITURE   ", NOURRITURE);
			printf("\x1b[43;1HLA VALEUR DE VOTRE ELEVAGE EST DE %.2f $   ", SCORE);
			printf("\x1b[45;1H** APPUIES SUR A POUR RECOMMENCER...   ");
		}
		else
		{
			printf("\x1b[35;1H...........END OF GAME...........   ");

			if (SCORE <=150)
			{
				printf("\x1b[37;1HOOPS!, YOUR BREEDING METHOD IS FAILING.   ");
			}
			else if ((SCORE > 150) && (SCORE <= 500))
			{
				printf("\x1b[37;1HWELL DONE, YOU PROPERLY MANAGE BREEDING.   ");
			}
			else if (SCORE > 500)
			{
				printf("\x1b[37;1HGREAT JOB, YOU ARE A CHAMPION OF BREEDING.   ");
			}

			printf("\x1b[38;1HYOU HAVE AFTER THESE 12 MONTHS :   ");
			printf("\x1b[39;1H%d ADULTS   ", MALES.ADULTES + FEMELLES.ADULTES);
			printf("\x1b[40;1H%d YOUNGS   ", MALES.PETITS + FEMELLES.PETITS);
			printf("\x1b[41;1H%d CAGES   ", MALES.CAGES + FEMELLES.CAGES);
			printf("\x1b[42;1H%d KG OF FOOD   ", NOURRITURE);
			printf("\x1b[43;1HTHE VALUE OF YOUR BREEDING IS %.2f $   ", SCORE);
			printf("\x1b[45;1H** PRESS A TO PLAY AGAIN...   ");
		}
	}
}

void newGame()
{
	Mois = 1;
	MALES.ADULTES = 1;
	FEMELLES.ADULTES = 1;
	MALES.PETITS = 0;
	FEMELLES.PETITS = 0;
	MALES.CAGES = 1;
	FEMELLES.CAGES = 1;
	MALES.nb_par_cage = 1;
	FEMELLES.nb_par_cage = 1;
	NOURRITURE = 5;
	PRIX_HAMSTER = 1 + (rand()%2)*0.10 ;//1.00 ou 1.10;
	CAISSE = 5.00;
	MORTS_ETOUFFES = 0;
	MORTS_FAIM = 0;
}

void readInput()
{
	if ((kDown & KEY_A) && (mode_intro == true))
	{
		mode_intro = false;
		mode_game = 1;
	}
	else if ((kDown & KEY_A) && (mode_game == 1))
	{
		//ON demarre le mois
		selection = 0;
		mode_game = 2;
	}
	else if ((kDown & KEY_A) && (mode_game == 2))
	{
		if (males_a_vendre <= MALES.ADULTES)
		{
			selection = 0;
			mode_game = 3;
			MALES.ADULTES -= males_a_vendre;
			CAISSE += males_a_vendre*PRIX_HAMSTER;
			error = false;
		}
		else
		{
			//IMPOSSIBLE
			error = true;
		}
	}
	else if ((kDown & KEY_A) && (mode_game == 3))
	{
		if (femelles_a_vendre <= FEMELLES.ADULTES)
		{
			selection = 0;
			mode_game = 4;
			FEMELLES.ADULTES -= femelles_a_vendre;
			CAISSE += femelles_a_vendre*PRIX_HAMSTER;
			error = false;
		}
		else
		{
			//IMPOSSIBLE
			error = true;
		}
	}
	else if ((kDown & KEY_A) && (mode_game == 4))
	{
		if ((nombre_accouplement <= MALES.ADULTES) && (nombre_accouplement <= FEMELLES.ADULTES))
		{
			selection = 0;
			mode_game = 5;
			error = false;
		}
		else
		{
			//IMPOSSIBLE
			error = true;
		}
	}
	else if ((kDown & KEY_A) && (mode_game == 5))
	{
		if (nourriture_a_acheter*0.10 <= CAISSE)
		{
			selection = 0;
			mode_game = 6;
			NOURRITURE += nourriture_a_acheter;
			CAISSE -= nourriture_a_acheter*0.10;
			error = false;
		}
		else
		{
			//IMPOSSIBLE
			error = true;
		}
	}
	else if ((kDown & KEY_A) && (mode_game == 6))
	{
		if (achats_cages_males*5 <= CAISSE)
		{
			selection = 0;
			mode_game = 7;
			MALES.CAGES += achats_cages_males;
			CAISSE -= achats_cages_males*5;//5$ la cage
			error = false;
		}
		else
		{
			//IMPOSSIBLE
			error = true;
		}
	}
	else if ((kDown & KEY_A) && (mode_game == 7))
	{
		if (achats_cages_femelles*5 <= CAISSE)
		{
			selection = 0;
			FEMELLES.CAGES += achats_cages_femelles;
			CAISSE -= achats_cages_femelles*5;//5$ la cage
			error = false;

			MORTS_ETOUFFES = 0;
			MORTS_FAIM = 0;

			//Les petits grandissent...
			MALES.ADULTES += MALES.PETITS;
			MALES.PETITS = 0;
			FEMELLES.ADULTES += FEMELLES.PETITS;
			FEMELLES.PETITS = 0;

			//Les accouplements
			if (nombre_accouplement >= 1)
			{
				int i, m, f;
				int quantity;

				for (i = 1; i <= nombre_accouplement;i++)
				{
					//Nombre aléatoire de petits maxi 18
					quantity = rand() % 18 + 1;

					//On divise males et femelles
					m = rand() % quantity + 1;
					f = quantity - m;

					//On ajoute les petits aux effectifs adultes
					MALES.PETITS += m;
					FEMELLES.PETITS += f;
				}
			}

			//Aide aux perdants, si plus d'hamsters, on rend un jeune couple en bonus
			if (MALES.ADULTES + FEMELLES.ADULTES + MALES.PETITS + FEMELLES.PETITS == 0)
			{
				MALES.PETITS = 1;
				FEMELLES.PETITS = 1;
			}

			//Les cages males
			MALES.nb_par_cage = (MALES.ADULTES + MALES.PETITS) / MALES.CAGES;

			//Reset du nombre de mort ettouffé
			MORTS_ETOUFFES = 0;

			//On calcule les morts
			while (MALES.nb_par_cage > 20)
			{
				//On tue les petits en premier
				if (MALES.PETITS > 0) MALES.PETITS--;
				//Sinon un adulte
				else MALES.ADULTES--;

				MORTS_ETOUFFES++;

				MALES.nb_par_cage = (MALES.ADULTES + MALES.PETITS) / MALES.CAGES;
			}

			//Les cages femelles
			FEMELLES.nb_par_cage = (FEMELLES.ADULTES + FEMELLES.PETITS) / FEMELLES.CAGES;

			while (FEMELLES.nb_par_cage > 20)
			{
				//On tue les petites en premier
				if (FEMELLES.PETITS > 0) FEMELLES.PETITS--;
				//Sinon une adulte
				else FEMELLES.ADULTES--;

				MORTS_ETOUFFES++;

				FEMELLES.nb_par_cage = (FEMELLES.ADULTES + FEMELLES.PETITS) / FEMELLES.CAGES;
			}

			//La bouffe
			int effectifs;
			effectifs = MALES.ADULTES + FEMELLES.ADULTES + MALES.PETITS + FEMELLES.PETITS;
			MORTS_FAIM = 0;

			if (NOURRITURE > effectifs) NOURRITURE -= effectifs;
			else
			{
				MORTS_FAIM = effectifs - NOURRITURE;

				while (	effectifs > NOURRITURE)
				{
					int choix;

					choix = rand() % 4 + 1;

					if ((choix == 1) && (MALES.ADULTES > 0)) 			MALES.ADULTES--;
					else if ((choix == 2) && (FEMELLES.ADULTES > 0)) 	FEMELLES.ADULTES--;
					else if ((choix == 3) && (MALES.PETITS > 0)) 		MALES.PETITS--;
					else if ((choix == 4) && (FEMELLES.PETITS > 0)) 	FEMELLES.PETITS--;

					effectifs = MALES.ADULTES + FEMELLES.ADULTES + MALES.PETITS + FEMELLES.PETITS;
				}

				NOURRITURE = 0;
			}

			//Passage au Mois suivant
			Mois++;

			//Variables à zéro
			males_a_vendre = 0;
			femelles_a_vendre = 0;
			nombre_accouplement = 0;
			nourriture_a_acheter = 0;
			achats_cages_males = 0;
			achats_cages_femelles = 0;

			//Nouveau prix du hamster
			PRIX_HAMSTER = 1 + (rand()%2)*0.10 ;//1.00 ou 1.10;

			if (Mois >= 13)
			{
				mode_game = 8;
				SCORE = CAISSE + MALES.ADULTES + FEMELLES.ADULTES + MALES.PETITS + FEMELLES.PETITS + MALES.CAGES + FEMELLES.CAGES;
			}
			else
			{
				mode_game = 1;
				clean();
			}
		}
		else
		{
			//IMPOSSIBLE
			error = true;
		}
	}
	else if ((kDown & KEY_A) && (mode_game == 8))
	{
		SCORE = 0;
		mode_game = 1;
		clean();
		newGame();
	}

	//La selection au D-pad
	else if ((kDown & KEY_RIGHT) && (mode_game >= 2) && (mode_game < 8))
	{
		selection++;
	}
	else if ((kDown & KEY_LEFT) && (selection >= 1) && (mode_game >= 2) && (mode_game < 8))
	{
		selection--;
	}
	else if ((kDown & KEY_UP) && (mode_game >= 2) && (mode_game < 8))
	{
		selection+=10;
	}
	else if ((kDown & KEY_DOWN) && (selection >= 10) && (mode_game >= 2) && (mode_game < 8))
	{
		selection-=10;
	}
	else if ((kDown & KEY_R) && (mode_game >= 2) && (mode_game < 8))
	{
		selection+=100;
	}
	else if ((kDown & KEY_L) && (selection >= 100) && (mode_game >= 2) && (mode_game < 8))
	{
		selection-=100;
	}
}


int main(int argc, char **argv)
{
	gfxInitDefault();
	consoleInit(NULL);

	setInitialize();
	setGetSystemLanguage(&LanguageCode);
	langue = setMakeLanguage(LanguageCode, &Language);


	mode_intro = true;
	newGame();

	while(appletMainLoop())
	{
		printGame();

		//Assignation du Input
		if (mode_game == 2) males_a_vendre = selection;
		else if (mode_game == 3) femelles_a_vendre = selection;
		else if (mode_game == 4) nombre_accouplement = selection;
		else if (mode_game == 5) nourriture_a_acheter = selection;
		else if (mode_game == 6) achats_cages_males = selection;
		else if (mode_game == 7) achats_cages_femelles = selection;

		hidScanInput();
		kDown = hidKeysDown(CONTROLLER_P1_AUTO);
		readInput();
		if (kDown & KEY_PLUS) break; // break in order to return to hbmenu

		gfxFlushBuffers();
		gfxSwapBuffers();
		gfxWaitForVsync();
	}

	setExit();
	gfxExit();
	return 0;
}

