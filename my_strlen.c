/*******************************************************************************
*
* File Name         : my_strlen.c
* Created By        : Julien Lacombe
* Creation Date     : septembre  1th, 2015
* Last Change       : septembre 17th, 2015 at 20:21:35
* Last Changed By   : Julien Lacombe
* Purpose           :
*
*******************************************************************************/
/* calcul de la longueur d'une chaine de caractère */
int my_strlen(char *arg){
        int len =0; 
        while (arg[len]!='\0')
	{
		len++;
	}
	return len;
}


