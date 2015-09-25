/*******************************************************************************
*
* File Name         : my_puts.c
* Created By        : Julien Lacombe
* Creation Date     : septembre  1th, 2015
* Last Change       : septembre 17th, 2015 at 20:10:23
* Last Changed By   : Julien Lacombe
* Purpose           :
*
*******************************************************************************/
#include<unistd.h>

/* ecrit un caractère ; la base du printf */
int my_putchar(char c) 
{
	write(1,&c,1);
	return 0;
}
/* sert à n'avoir que la partie absolu d'un nombre */
int my_abs(int val) 
{	
	if(val<0)
	{
		val=-val;
	}
	return val;
}

/* imprime les nombres avec la base voulu */
int my_putnbr(int nombre, int base) 
{
	int flag = 0;
	char base16[16]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'}; 	/* tableau utilisé avec les bases */
	char base_16[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};	/* tableau utilisé pour le spécifieur 'X'
												   appelé avec la base '-16'
	les utilisation de my_abs sont pour faire en sorte que la fonction marche même quand la base '-16' sera appelé */
	if (nombre>=my_abs(base))
	{

		my_putnbr(nombre /my_abs(base),base);
	}
	if (base<0)
	{
	

		my_putchar(base_16[nombre%my_abs(base)]);	

	}
	else
	{
		my_putchar(base16[nombre%my_abs(base)]);
	}
	

	


	return 0;
}

/* affiche une chaine de caractères */
int my_puts(char* s) 
{
	int i=0;

	while (s[i]!='\0')
	{
		my_putchar(s[i]);
		
		i++;
	}
	return 0;
}
/* affiche un chaine étendue. Par chaine étendu, j'ai compris chaine qui gère les '\0' */
int my_put_S(char* s)  
{

	int i=0;
	while (s[i]!='\0')
	{
		if (s[i]<31) /* si un caractère se trouve avant l'espace dans la table ASCII (comme le retour chariot) */
		{
			my_putchar(92); /* on affiche un slash */
			my_putchar(48); /* le 0 */
			my_putnbr(s[i],8); /* et l'octale correspondant au nombre */
		}
		else
		{
			my_putchar(s[i]); /* si le caractère est supérieur ou égal à 32 (l'espace), impression */
		}
		i++;
	}
	return 0;
}


int my_putnbr_u(unsigned int nombre, int base) /* même fonction que put_nbr sauf que l'argument 1 est un unsigned number */
{
	char base16[16]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};



	if (nombre>=base)
	{

		my_putnbr(nombre /base,base);
	}

	my_putchar(base16[nombre%my_abs(base)]);
}







