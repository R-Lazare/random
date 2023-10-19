/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Projet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/10/18 22:54:41 by rluiz             #+#    #+#             */
/*   Updated: 2023/10/18 22:54:41 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Fonction pour afficher le plateau de jeu
void afficherPlateau(char **plateau) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", plateau[i][j]);
            if (j < 2)
                printf("|");
        }
        printf("\n");
        if (i < 2)
            printf("-----------\n");
    }
    printf("\n");
}

// Fonction pour vérifier s'il y a un gagnant
int	verifierGagnant(char **plateau, char symbole)
{
	for (int i = 0; i < 3; i++)
	{
		if (plateau[i][0] == symbole && plateau[i][1] == symbole
			&& plateau[i][2] == symbole)
		{
			return (1);
		}
		if (plateau[0][i] == symbole && plateau[1][i] == symbole
			&& plateau[2][i] == symbole)
		{
			return (1);
		}
	}
	if (plateau[0][0] == symbole && plateau[1][1] == symbole
		&& plateau[2][2] == symbole)
	{
		return (1);
	}
	if (plateau[0][2] == symbole && plateau[1][1] == symbole
		&& plateau[2][0] == symbole)
	{
		return (1);
	}
	return (0);
}

// Fonction pour vérifier s'il y a un match nul
int	verifierMatchNul(char **plateau)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (plateau[i][j] == ' ')
			{
				return (0);
			}
		}
	}
	return (1);
}

// Fonction pour que l'ordinateur fasse un mouvement aléatoire
void	tourOrdinateur(char **plateau)
{
	while (1)
	{
		int ligne = rand() % 3;
		int colonne = rand() % 3;
		if (plateau[ligne][colonne] == ' ')
		{
			plateau[ligne][colonne] = 'O';
			break ;
		}
	}
}

int	main(void)
{
	char **plateau = (char **)malloc(3 * sizeof(char *));
    for (int i = 0; i < 3; i++) {
        plateau[i] = (char *)malloc(3 * sizeof(char));
        for (int j = 0; j < 3; j++) {
            plateau[i][j] = ' ';
        }
    }
	int tour = 1; // Le tour du joueur 1
	int choix;
	int continu = 1;

	srand(time(NULL)); // Initialisation du générateur de nombres aléatoires
	printf("Bienvenue dans le jeu Tic-Tac-Toe !\nChoisissez le mode de jeu :\n1. Joueur contre Joueur\n2. Joueur contre Ordinateur\nEntrez 1 ou 2 : ");
	scanf("%d", &choix);

	while (choix != 1 && choix != 2)
	{
		printf("Choix invalide. Entrez 1 ou 2 : ");
		scanf("%d", &choix);
	}

	while (continu)
	{
		afficherPlateau(plateau);

		if (tour == 1)
		{
			int ligne, colonne;
			printf("Joueur 1 (X), veuillez entrer la ligne et la colonne (ex. 1 2) : ");
			scanf("%d %d", &ligne, &colonne);

			if (ligne < 1 || ligne > 3 || colonne < 1 || colonne > 3
				|| plateau[ligne - 1][colonne - 1] != ' ')
			{
				printf("Coup invalide. Reessayez.\n");
				continu--;
			}

			plateau[ligne - 1][colonne - 1] = 'X';
			if (verifierGagnant(plateau, 'X'))
			{
				printf("Joueur 1 (X) a gagne !\n");
				continu--;
			}
		}
		else
		{
			if (choix == 1)
			{
				int ligne, colonne;
				printf("Joueur 2 (O), veuillez entrer la ligne et la colonne (ex. 1 2) : ");
				scanf("%d %d", &ligne, &colonne);

				if (ligne < 1 || ligne > 3 || colonne < 1 || colonne > 3
					|| plateau[ligne - 1][colonne - 1] != ' ')
				{
					printf("Coup invalide. Reessayez.\n");
					continu--;
				}

				plateau[ligne - 1][colonne - 1] = 'O';

				if (verifierGagnant(plateau, 'O'))
				{
					printf("Joueur 2 (O) a gagne !\n");
					continu--;
				}
			}
			else
			{
				printf("Tour de l'ordinateur (O) :\n");
				tourOrdinateur(plateau);

				if (verifierGagnant(plateau, 'O'))
				{
					printf("L'ordinateur a gagne !\n");
					continu--;
				}
			}
		}

		if (verifierMatchNul(plateau))
		{
			printf("Match nul !\n");
			continu--;
		}
		afficherPlateau(plateau);
		tour = 3 - tour;
		// Alterner entre les joueurs 1 et 2 ou entre le joueur et l'ordinateur
	}
	free(plateau);
	return (0);
}
