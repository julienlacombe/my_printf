/*******************************************************************************
*
* File Name         : my_printf.c
* Created By        : Julien Lacombe
* Creation Date     : septembre  9th, 2015
* Last Change       : septembre 17th, 2015 at 18:46:22
* Last Changed By   : Julien Lacombe
* Purpose           :
*
*******************************************************************************/
#include "my_puts.h"
#include<stdarg.h>
#include "my_strlen.h"


/* existInTab va chercher dans le tableau mis en argument 1, l'élément mis en argument 2. Si l'élément
 * est présent dans le tableau, la fonction retourne trouver qui sera à 1, sinon 0.*/

int existInTab(char * tableau, char element)
{
	int longueur_tableau=my_strlen(&tableau[0]);
	int trouver = 0;
	int i = 0;
	for (i=0 ; i<longueur_tableau ; i++)
	{
		if (tableau[i] == element)
		{
			trouver = 1;
		}
	}
	return trouver;
}

/* ecrit_pourcent est la fonction qui va prendre en compte les specifieurs, les flags, la largeur etc et va
 * imprimer en console la demande. C'est cette fonction qui appelle les différentes fonctions d'impression
 * console et qui formatte l'affichage */
void ecrit_pourcent(va_list arglist, char c, int width, int precision, int flag_plus, int flag_moins)
{
	int valeur; /* variable qui sera utilisée pour formatter l'affichage des nombres */
	int valeur_temp; /* même fonction que valeur */
	int valeur_size=0; /* Cette variable va stocké la longueur de la variable à afficher */
	unsigned int u; /* Sera utilisé pour le spécifieur 'u'*/

	if 	(c == 115) /* Ici, 115 correspond à 's' en ASCII*/
	{
		my_puts(va_arg(arglist, char*));
		flag_moins=0; /* sert à désactiver le flag consernant l'alignement à droite */
	}
	else if (c == 'o')
	{
		my_putnbr(va_arg(arglist, int), 8);
	}
	else if (c == 'c')
	{
		my_putchar((char) va_arg(arglist, int));
	}
	else if (c == 'i' || c == 'd')
	{
		valeur = va_arg(arglist, int); /* stocke la valeur de va_arg pour ne pas l'appeler
					        * plusieurs fois et incrémenter le pointeur*/
		valeur_temp=valeur;	       /* Sert à avoir une version "modifiable" de valeur */
		
		/* le if et le while ci-dessous servent à calculer la taille du nombre pour gérer
		 * la largeur */
		if (valeur_temp<0) /* traitement pour un négatif */
		{
			valeur_temp=valeur_temp*-1; /* passe en positif la variable et ajout de */
			valeur_size++;		    /* 1 pour prendre en compte la taille du '-' */ 
		}				    /*   car il est ajouté "manuellement" plus tard */
		while (valeur_temp>9)		    /* à cause du cas 'alignement à droite'*/
		{
			valeur_size++;
			valeur_temp = valeur_temp/10;
		}
		valeur_size++;
		
		/* ce if sert à gérer l'alignement à droite */
		if (flag_moins==0)
		{
			valeur_temp=width-valeur_size; /* stock dans valeur_temp le nombre d'espaces */
			while (valeur_temp>0)          /* a ajouter avant d'ecrire le nombre pour */
			{			       /* respecter un alignement à droite. */
				my_putchar(32);
				valeur_temp--;
			}
		}
		
		if (valeur < 0)
		{
			valeur=-valeur;  /* passage de la valeur en positif */
			my_putchar('-'); /* impression le '-' si le nombre est négatif */
		}
		else if (valeur>0 && flag_plus ==1)  
		{
			my_putchar('+'); /* impression du '+' si flag + est détecter et le nombre positif */
		}
		my_putnbr(valeur, 10); /* impression du nombre en base 10 */
	}
	else if (c == '%') /* cas du '%%' */
	{
		my_putchar('%');
	}
	else if (c== 'x')
	{
		my_putnbr(va_arg(arglist, int), 16); /* impression du nombre en hexa en minuscule */
	}
	else if (c == 'X')
	{
		my_putnbr(va_arg(arglist, int), -16); /* impression du nombre en hexa en majuscule */
	}
	else if (c == 'b')
	{
		my_putnbr(va_arg(arglist, int), 2); /* impression du nombre en binaire */
	}
	else if (c == 'p')
	{
		int ptr = (va_arg(arglist, int));
		my_puts("0x");
		my_putnbr(ptr, 16); /* impression du pointeur */
	}
	else if (c == 'u')
	{
		u =va_arg(arglist, int); /* conversion de l'int en unsigned */
		my_putnbr_u(u, 10); 
	}
	else if (c =='S')
	{
		my_put_S(va_arg(arglist, char *)); /* cas des chaines de caractères spéciales */
		flag_moins=0;
	}

	if (flag_moins==1 && width>0) /* alignement à gauche */
	{
		while (width-valeur_size-1>0)
		{
			my_putchar(32);
			width--;
		}
	}	
}

/* fonction appeler par la moulinette. Elle utilise toutes les autres fonctions du fichier  */
int my_printf(char * argument, ... )
{
	va_list argliste; /* récupère l'argument '...' qui est une suite d'argument. A chaque appel,
			   * la liste s'incrémentera automatiquement */
	char type;		/* le spécifieur */
	int inc = 0;		/* une incrémentation pour les boucles */
	int width=0;		/* largeur de l'affichage */
	int precision=0;	/* precision relevée mais non utilisée */
	char flag=1;	 	/* contiendra le flag ( + # 0 ...) */
	int flag_plus=0;  	/* flag de l'impression du signe */
	int flag_moins=0; 	/* flag de l'alignement à gauche (ici, initié à droite) */
	/* Différents tableaux où sont stokés les caractéristiques connus du my_printf */
	char liste_Flags[4] = 
	{ 
		'+',' ','#','0'
	};
	char liste_Width[12] = 
	{
		'-','*','0','1','2','3','4','5','6','7','8','9'	/* note : '-' est un flag mais il se trouve ici */
	};							/* pour le cas du '+-' */
 	char liste_Specifieur[18] = 
	{
		'c','d','i','e','E','f','g','G','o','s','u','x','X','p','n','%','b','S'
	};
/*	char liste_Lenght[3] =   // ne sera pas utilisé par manque de temps
	{
		'h','L','l'
	};*/
	va_start(argliste,argument); /* initialisation de la liste de variables */
	/* la boucle va parcourir tout l'argument à la recherche de '%' */
	while (argument[inc] != '\0')
	{
		if (argument[inc] == '%')
		{
			inc++; /* avance d'un caractère, celui après le % */
			if (existInTab(liste_Flags, argument[inc]))
			{
				if(argument[inc]=='+')
				{
					flag_plus=1; /* activation de la demande de signe */
				}
				flag=argument[inc];
				if(flag==32 && existInTab(liste_Specifieur, argument[inc+1]))
				{
					my_putchar(32); /* si espace avec spécifieur à venir, impression d'un espace */
				}
				if(flag=='#') /* flag d'ajout de 0, 0x pour les spécifieur 'x' et 'o' */
				{
					if(argument[inc+1]=='x')
					{
						my_putchar('0');
						my_putchar(argument[inc+1]); /* on ecrit '0' et 'x' (inc+1 est 'x') */
					}
					else if (argument[inc+1]=='o')
					{
						my_putchar('0');
					}
				}
				inc++; /* on avance dans l'argument si un flag a été découvert */
				}
			if (existInTab(liste_Width, argument[inc]))
			{
				if (argument[inc]=='-') 	/* alignement à gauche */
				{
					flag_moins=1;
					inc ++;
				}
				while (argument[inc]-48>=0 && argument[inc]-48<=9) 	/* tant que l'on trouve un chiffre */
				{							/* on le prend pour créer width */
					width = width *10 + argument[inc]-48; 		/* création de width */
					inc++;
				}
			}	
			if (argument[inc]=='.') /* présence d'une précision */
			{
				inc++;
				while (argument[inc]-48>=0 && argument[inc]-48<=9) 	/* tant que argument[inc]==chiffre */
				{
					precision = precision *10 + argument[inc]-48;	/* calcul de la précision */
					inc++;
				}
			}		
			if (existInTab(liste_Specifieur, argument[inc])) /* test si présence d'un spécifieur */
			{
			
				type = argument[inc];
				ecrit_pourcent(argliste, type, width, precision, flag_plus, flag_moins);	
			}
			else
			{
				my_putchar('%'); 		/* si spécifieur non trouver, on imprimer un % plus le */
				my_putchar(argument[inc]);	/* spécifieur inconnu comme le %k dans la moulinette */
				while (width>0)
				{
					my_putchar(32); /* si la largeur n'est pas nulle, on imprime les espaces demandés */
					width--;
				}
				
			}		
		}
		else
		{
			my_putchar(argument[inc]); /* si il n'y a pas de %, on imprime les caractères demandés */
		}		
		inc++;	
	}
	return 0;
}
