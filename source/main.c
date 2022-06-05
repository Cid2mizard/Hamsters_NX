#include <stdio.h> //printf
#include <stdlib.h> //srand
#include <time.h> //time

#include <switch.h>

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

PadState pad;
u32 kDown;

void clean()
{
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
	printf("\x1b[46;1H                                               ");
}

void printGame()
{
	if (mode_intro)
	{
		printf("\x1b[1;30H\x1b[31m***** HAMSTERS NX *****\x1b[0m");

		if (langue == 2)
		{
			printf("\x1b[3;1HLe but du jeu est de gerer un elevage de hamsters");
			printf("\x1b[4;1Hpendant 12 mois en faisant des benefices.");
			printf("\x1b[5;1H* On peut vendre ou accoupler que des adultes.");
			printf("\x1b[6;1H* Les petits deviennent adultes en 1 mois.");
			printf("\x1b[7;1H* Chaque accouplement peut donner un maximum de 18 petits.");
			printf("\x1b[8;1H* Au dela de 20 hamsters par cage, les hamsters meurent etouffes.");
			printf("\x1b[10;1H** Appuyez sur A pour continuer...");
		}
		else
		{
			printf("\x1b[3;1HThe purpose of the game is to manage breeding");
			printf("\x1b[4;1Hhamsters 12 months by making profits.");
			printf("\x1b[5;1H* You can sell or couple only the adults.");
			printf("\x1b[6;1H* Youngs become adults after 1 month.");
			printf("\x1b[7;1H* Each coupling can give a maximum of 18 youngs.");
			printf("\x1b[8;1H* Beyond 20 hamsters per cage, hamsters die suffocated.");
			printf("\x1b[10;1H** Press A to continue...");
		}
	}
	else if ((mode_game > 0) && (mode_game <= 8))
	{
		if (langue == 2)
		{
			printf("\x1b[11;1H-------------------------------------------------");
			printf("\x1b[12;15HSITUATION DU MOIS No %d   ", Mois);
			printf("\x1b[14;10HMALES                 FEMELLES");
			printf("\x1b[16;10HADULTES : %d   ", MALES.ADULTES);
			printf("\x1b[16;32HADULTES : %d   ", FEMELLES.ADULTES);
			printf("\x1b[17;10HPETITS  : %d   ", MALES.PETITS);
			printf("\x1b[17;32HPETITS  : %d   ", FEMELLES.PETITS);
			printf("\x1b[18;10HCAGES   : %d   ", MALES.CAGES);
			printf("\x1b[18;32HCAGES   : %d   ", FEMELLES.CAGES);
			printf("\x1b[19;6Hnb par cage : %d   ", MALES.nb_par_cage);
			printf("\x1b[19;28Hnb par cage : %d   ", FEMELLES.nb_par_cage);
			printf("\x1b[21;1HNOURRITURE RESTANTE  %d KG   ", NOURRITURE);
			printf("\x1b[22;1HPRIX DU HAMSTER CE MOIS : %.2f $   ", PRIX_HAMSTER);
			printf("\x1b[23;1HEN CAISSE : %.2f $   ", CAISSE);
			printf("\x1b[25;1HMORTS DE FAIM  : %d   ", MORTS_FAIM);
			printf("\x1b[26;1HMORTS ETOUFFES : %d   ", MORTS_ETOUFFES);
			printf("\x1b[28;1H** Appuyez sur A pour continuer...");
			printf("\x1b[29;1H-------------------------------------------------");

			if (mode_game == 2)
			{
				printf("\x1b[30;1HMALES A VENDRE ? (%.2f$) x %d   ", PRIX_HAMSTER, males_a_vendre);
			}
			if (mode_game == 3)
			{
				printf("\x1b[31;1HFEMELLES A VENDRE ? (%.2f$) x %d   ", PRIX_HAMSTER, femelles_a_vendre);
			}
			if (mode_game == 4)
			{
				printf("\x1b[32;1HNOMBRE D'ACCOUPLEMENT ? %d   ", nombre_accouplement);
			}
			if (mode_game == 5)
			{
				printf("\x1b[33;1HNOURRITURE A ACHETER ? (0,10$) x %d   ", nourriture_a_acheter);
			}
			if (mode_game == 6)
			{
				printf("\x1b[34;1HACHAT DE CAGES POUR LES MALES ? (5$) x %d   ", achats_cages_males);
			}
			if (mode_game == 7)
			{
				printf("\x1b[35;1HACHAT DE CAGES POUR LES FEMELLES ? (5$) x %d   ", achats_cages_femelles);
			}
		}
		else
		{
			printf("\x1b[11;1H-------------------------------------------------");
			printf("\x1b[12;15HSITUATION OF THE MONTH No %d   ", Mois);
			printf("\x1b[14;10HMALES                 FEMALES");
			printf("\x1b[16;10HADULTS  : %d   ", MALES.ADULTES);
			printf("\x1b[16;32HADULTS  : %d   ", FEMELLES.ADULTES);
			printf("\x1b[17;10HYOUNGS  : %d   ", MALES.PETITS);
			printf("\x1b[17;32HYOUNGS  : %d   ", FEMELLES.PETITS);
			printf("\x1b[18;10HCAGES   : %d   ", MALES.CAGES);
			printf("\x1b[18;32HCAGES   : %d   ", FEMELLES.CAGES);
			printf("\x1b[19;6Hnb per cage : %d   ", MALES.nb_par_cage);
			printf("\x1b[19;28Hnb per cage : %d   ", FEMELLES.nb_par_cage);
			printf("\x1b[21;1HREMAINING FOOD  %d KG   ", NOURRITURE);
			printf("\x1b[22;1HPRICE OF HAMSTER THIS MONTH : %.2f $   ", PRIX_HAMSTER);
			printf("\x1b[23;1HCHECKOUT : %.2f $   ", CAISSE);
			printf("\x1b[25;1HDEAD HUNGRY     : %d   ", MORTS_FAIM);
			printf("\x1b[26;1HDEAD SUFFOCATED : %d   ", MORTS_ETOUFFES);
			printf("\x1b[28;1H** Press A to continue...");
			printf("\x1b[29;1H-------------------------------------------------");

			if (mode_game == 2)
			{
				printf("\x1b[30;1HMALES FOR SALE ? (%.2f$) x %d   ", PRIX_HAMSTER, males_a_vendre);
			}
			if (mode_game == 3)
			{
				printf("\x1b[31;1HFEMALES FOR SALE ? (%.2f$) x %d   ", PRIX_HAMSTER, femelles_a_vendre);
			}
			if (mode_game == 4)
			{
				printf("\x1b[32;1HNUMBER COUPLING ? %d   ", nombre_accouplement);
			}
			if (mode_game == 5)
			{
				printf("\x1b[33;1HFOOD TO BUY ? (0,10$) x %d   ", nourriture_a_acheter);
			}
			if (mode_game == 6)
			{
				printf("\x1b[34;1HPURCHASE CAGES FOR MALES ? (5$) x %d   ", achats_cages_males);
			}
			if (mode_game == 7)
			{
				printf("\x1b[35;1HPURCHASE CAGES FOR FEMALES ?  (5$) x %d   ", achats_cages_femelles);
			}
		}

		if (error)
			printf("\x1b[36;1HIMPOSSIBLE   ");
		else
			printf("\x1b[36;1H             ");
	}
	if (mode_game == 8)
	{
		if (langue == 2)
		{
			printf("\x1b[37;1H...........FIN DU JEU...........   ");

			if (SCORE <=300)
			{
				printf("\x1b[38;1HOOPS!, VOTRE METHODE D'ELEVAGE EST A REVOIR.   ");
			}
			else if ((SCORE > 300) && (SCORE <= 1000))
			{
				printf("\x1b[38;1HBRAVO, VOUS AVEZ CORRECTEMENT GERE L'ELEVAGE.   ");
			}
			else if (SCORE > 1000)
			{
				printf("\x1b[38;1HEXCELLENT, VOUS ETES UN CHAMPION DE L'ELEVAGE.   ");
			}

			printf("\x1b[39;1HVOUS AVEZ AU BOUT DE CES 12 MOIS :   ");
			printf("\x1b[40;1H%d ADULTES   ", MALES.ADULTES + FEMELLES.ADULTES);
			printf("\x1b[41;1H%d PETITS   ", MALES.PETITS + FEMELLES.PETITS);
			printf("\x1b[42;1H%d CAGES   ", MALES.CAGES + FEMELLES.CAGES);
			printf("\x1b[43;1H%d KG DE NOURRITURE   ", NOURRITURE);
			printf("\x1b[44;1HLA VALEUR DE VOTRE ELEVAGE EST DE %.2f $   ", SCORE);
			printf("\x1b[46;1H** APPUIES SUR A POUR RECOMMENCER...   ");
		}
		else
		{
			printf("\x1b[37;1H...........END OF GAME...........   ");

			if (SCORE <=300)
			{
				printf("\x1b[38;1HOOPS!, YOUR BREEDING METHOD IS FAILING.   ");
			}
			else if ((SCORE > 300) && (SCORE <= 1000))
			{
				printf("\x1b[38;1HWELL DONE, YOU PROPERLY MANAGE BREEDING.   ");
			}
			else if (SCORE > 1000)
			{
				printf("\x1b[38;1HGREAT JOB, YOU ARE A CHAMPION OF BREEDING.   ");
			}

			printf("\x1b[39;1HYOU HAVE AFTER THESE 12 MONTHS :   ");
			printf("\x1b[40;1H%d ADULTS   ", MALES.ADULTES + FEMELLES.ADULTES);
			printf("\x1b[41;1H%d YOUNGS   ", MALES.PETITS + FEMELLES.PETITS);
			printf("\x1b[42;1H%d CAGES   ", MALES.CAGES + FEMELLES.CAGES);
			printf("\x1b[43;1H%d KG OF FOOD   ", NOURRITURE);
			printf("\x1b[44;1HTHE VALUE OF YOUR BREEDING IS %.2f $   ", SCORE);
			printf("\x1b[46;1H** PRESS A TO PLAY AGAIN...   ");
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
	SCORE = 0;
}

void readInput()
{
	padUpdate(&pad);
	kDown = padGetButtonsDown(&pad);

	if ((kDown & HidNpadButton_A) && (mode_intro == true))
	{
		mode_intro = false;
		mode_game = 1;
	}
	else if ((kDown & HidNpadButton_A) && (mode_game == 1))
	{
		//ON demarre le mois
		selection = 0;
		mode_game = 2;
	}
	else if ((kDown & HidNpadButton_A) && (mode_game == 2))
	{
		if (males_a_vendre <= MALES.ADULTES)
		{
			selection = 0;
			mode_game = 3;
			MALES.ADULTES -= males_a_vendre;
			CAISSE += males_a_vendre*PRIX_HAMSTER;
			MALES.nb_par_cage = (MALES.ADULTES+MALES.PETITS)/MALES.CAGES;
			error = false;
		}
		else
		{
			//IMPOSSIBLE
			error = true;
		}
	}
	else if ((kDown & HidNpadButton_A) && (mode_game == 3))
	{
		if (femelles_a_vendre <= FEMELLES.ADULTES)
		{
			selection = 0;
			mode_game = 4;
			FEMELLES.ADULTES -= femelles_a_vendre;
			CAISSE += femelles_a_vendre*PRIX_HAMSTER;
			FEMELLES.nb_par_cage = (FEMELLES.ADULTES+FEMELLES.PETITS)/FEMELLES.CAGES;
			error = false;
		}
		else
		{
			//IMPOSSIBLE
			error = true;
		}
	}
	else if ((kDown & HidNpadButton_A) && (mode_game == 4))
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
	else if ((kDown & HidNpadButton_A) && (mode_game == 5))
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
	else if ((kDown & HidNpadButton_A) && (mode_game == 6))
	{
		if (achats_cages_males*5 <= CAISSE)
		{
			selection = 0;
			mode_game = 7;
			MALES.CAGES += achats_cages_males;
			CAISSE -= achats_cages_males*5;//5$ la cage
			MALES.nb_par_cage = (MALES.ADULTES+MALES.PETITS)/MALES.CAGES;
			error = false;
		}
		else
		{
			//IMPOSSIBLE
			error = true;
		}
	}
	else if ((kDown & HidNpadButton_A) && (mode_game == 7))
	{
		if (achats_cages_femelles*5 <= CAISSE)
		{
			selection = 0;
			FEMELLES.CAGES += achats_cages_femelles;
			CAISSE -= achats_cages_femelles*5;//5$ la cage
			FEMELLES.nb_par_cage = (FEMELLES.ADULTES + FEMELLES.PETITS)/FEMELLES.CAGES;
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

			//Les cages males
			MALES.nb_par_cage = (MALES.ADULTES + MALES.PETITS)/MALES.CAGES;

			//Reset du nombre de mort ettouffé
			MORTS_ETOUFFES = 0;

			//On calcule les morts
			while (MALES.nb_par_cage > 20)
			{
				//On tue les petits en premier
				if (MALES.PETITS > 0)
					MALES.PETITS--;
				//Sinon un adulte
				else
					MALES.ADULTES--;

				MORTS_ETOUFFES++;

				MALES.nb_par_cage = (MALES.ADULTES + MALES.PETITS)/MALES.CAGES;
			}

			//Les cages femelles
			FEMELLES.nb_par_cage = (FEMELLES.ADULTES + FEMELLES.PETITS)/FEMELLES.CAGES;

			while (FEMELLES.nb_par_cage > 20)
			{
				//On tue les petites en premier
				if (FEMELLES.PETITS > 0) FEMELLES.PETITS--;
				//Sinon une adulte
				else FEMELLES.ADULTES--;

				MORTS_ETOUFFES++;

				FEMELLES.nb_par_cage = (FEMELLES.ADULTES + FEMELLES.PETITS)/FEMELLES.CAGES;
			}

			//La nourriture
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
				SCORE = CAISSE + MALES.ADULTES + FEMELLES.ADULTES + MALES.PETITS + FEMELLES.PETITS + (MALES.CAGES + FEMELLES.CAGES)*5 + NOURRITURE*0.1;
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
	else if ((kDown & HidNpadButton_A) && (mode_game == 8))
	{
		SCORE = 0;
		mode_game = 1;
		clean();
		newGame();
	}

	//La selection au D-pad
	else if ((kDown & HidNpadButton_Right) && (mode_game >= 2) && (mode_game < 8))
	{
		selection++;
	}
	else if ((kDown & HidNpadButton_Left) && (selection >= 1) && (mode_game >= 2) && (mode_game < 8))
	{
		selection--;
	}
	else if ((kDown & HidNpadButton_Up) && (mode_game >= 2) && (mode_game < 8))
	{
		selection+=10;
	}
	else if ((kDown & HidNpadButton_Down) && (selection >= 10) && (mode_game >= 2) && (mode_game < 8))
	{
		selection-=10;
	}
	else if ((kDown & HidNpadButton_R) && (mode_game >= 2) && (mode_game < 8))
	{
		selection+=100;
	}
	else if ((kDown & HidNpadButton_L) && (selection >= 100) && (mode_game >= 2) && (mode_game < 8))
	{
		selection-=100;
	}
}

int main(int argc, char **argv)
{
	u64 LanguageCode=0;
	SetLanguage Language=SetLanguage_ENUS;

	consoleInit(NULL);
	srand(time(0));

	setInitialize();
	setGetSystemLanguage(&LanguageCode);
	setMakeLanguage(LanguageCode, &Language);
	langue = Language;

	padConfigureInput(1, HidNpadStyleSet_NpadStandard);
	padInitializeDefault(&pad);

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

		readInput();

		consoleUpdate(NULL);

		if (kDown & HidNpadButton_Plus)
			break;
	}

	setExit();
	consoleExit(NULL);
	return 0;
}

