/**
 * @file yams_finalversion.c
 * @author Jouffe Samuel J2
 * @brief Ce programme permet de jouer à 2 au jeu de Yams
 * 
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>
#define CARAC_TAB 4
#define NB_JOUEUR 2
#define TAILLE_MAX_NOM 7 // taille max = -1
#define TAILLE_TAB  17
const int NB_TOUR = 13;
#define NB_DES 5
const int MIN_VAL_DE = 1;
const int MAX_VAL_DE = 6;
const int VAL_PAS_PRIS_EN_COMPTE = -1;

void mise_a_zero(int [NB_JOUEUR][TAILLE_TAB]);
void demande_nom(char [NB_JOUEUR][TAILLE_MAX_NOM]);
void change_tab(int [NB_JOUEUR][TAILLE_TAB], int, int, char *);
void affiche_tab_score(int [NB_JOUEUR][TAILLE_TAB], char [NB_JOUEUR][TAILLE_MAX_NOM]);
void premier_lance(int [NB_DES]);
void lancer_de_de (int , int [NB_DES]);
void choix_combinaison(int [NB_DES],int [NB_JOUEUR][TAILLE_TAB], int);
void relancer(int [NB_DES]);
void echange(int [NB_DES], int , int );
void trie(int [NB_DES]);
void suite_chiffre(int [NB_DES], int [NB_DES][TAILLE_TAB], int, int);
void brelan(int [NB_DES], int[NB_DES][TAILLE_TAB], int);
void carre(int [NB_DES], int[NB_DES][TAILLE_TAB], int);
void fullhouse(int [NB_DES],int [NB_DES][TAILLE_TAB], int );
void petite_suite(int [NB_DES],int [NB_DES][TAILLE_TAB], int );
void grande_suite(int [NB_DES],int [NB_DES][TAILLE_TAB], int );
void yams(int [NB_DES],int [NB_DES][TAILLE_TAB], int );
void chance(int [NB_DES],int [NB_DES][TAILLE_TAB], int );
void calcul_bonus_totaux(int [NB_JOUEUR][TAILLE_TAB], int);

/*********************************************************************************/
/*******************************PROGRAMME PRINCIPAL*******************************/
/*********************************************************************************/




int main(){
    srand(time(NULL));
    int tab_scores[NB_JOUEUR][TAILLE_TAB]; /** Tableau des scores des joueurs*/
    char tab_nom_j[NB_JOUEUR][TAILLE_MAX_NOM]; /**Tableau du nom des joueurs*/
    int tab_des[NB_DES]; /**Tableau des dés*/
    int tour_compteur, tour_joueur_compteur, compteur_zero;
    int reponse;
    bool bool_rep;
    mise_a_zero(tab_scores);
    printf("      www.regledujeu.fr      \n __     __      __  __  _____ \n \\ \\   / //\\   |  \\/  |/ ____|\n  \\ \\_/ //  \\  | \\  / | (___  \n   \\   // /\\ \\ | |\\/| |\\___ \\ \n    | |/ ____ \\| |  | |____) |\n    |_/_/    \\_\\_|  |_|_____/ \n");
    sleep(2);
    system("clear");
    printf("Vous allez lancer une nouvelle partie de Yams, le meilleur jeu de dés au monde.[Tapez sur internet www.regledujeu.fr pour avoir les règles]\n\n\n");
    demande_nom(tab_nom_j);
    for ( tour_compteur = 0; tour_compteur < NB_TOUR; tour_compteur++)
    {
        for (tour_joueur_compteur = 0; tour_joueur_compteur < NB_JOUEUR; tour_joueur_compteur++)
        {
            bool_rep = true;
            system("clear");
            affiche_tab_score(tab_scores, tab_nom_j);
             printf("%s c'est votre tour\n", tab_nom_j[tour_joueur_compteur]);
            while (bool_rep)
            {
                reponse = 0;
                printf("Voulez vous lancer les dés ? 0 pour oui et 1 pour non.\n");
                scanf("%d", &reponse);
                if (reponse == 0)
                {
                    premier_lance(tab_des);
                    while (bool_rep)
                    {
                        printf("Voulez vous relancer? 0 pour oui et 1 pour non.\n");
                        scanf("%d", &reponse);
                        if (reponse == 0)
                        {
                            relancer(tab_des);
                            printf("Voulez vous relancer? C'est votre dernier lancé. 0 pour oui et 1 pour non.\n");
                            scanf("%d", &reponse);
                            if (reponse == 0)
                            {
                                relancer(tab_des);
                                choix_combinaison(tab_des, tab_scores, tour_joueur_compteur);
                                bool_rep = false;
                            }
                            else if (reponse == 1){
                                choix_combinaison(tab_des, tab_scores, tour_joueur_compteur);
                                bool_rep = false;
                            }
                            else{
                                printf("Erreur, 0 pour oui et 1 pour non.\n");
                            }
                        }
                        else if (reponse == 1)
                        {
                            choix_combinaison(tab_des, tab_scores, tour_joueur_compteur);
                            bool_rep = false;
                        }
                        else{
                            printf("Erreur, 0 pour oui et 1 pour non.\n");
                        }
                    } 
                }
                else if(reponse == 1){
                    printf("Vous devez choisir la combisaison à sacrifier\n");
                    for (compteur_zero = 0; compteur_zero < NB_DES; compteur_zero++)
                    {
                        tab_des[compteur_zero] = 0;
                    }
                    choix_combinaison(tab_des, tab_scores, tour_joueur_compteur);
                    bool_rep = false;
                }
                else{
                    printf("Erreur, 0 pour oui et 1 pour non.\n");
                }
            }
            printf("Fin du tour de %s.\n", tab_nom_j[tour_joueur_compteur]);
        }
        if(tab_scores[0][16] < tab_scores[1][16]){
            printf("Bien joué %s vous avez gagnez !!!!!!!!! avec %d points\n", tab_nom_j[1], tab_scores[1][16]);
        }
        else{
            printf("Bien joué %s vous avez gagnez !!!!!!!!! avec %d points\n", tab_nom_j[0], tab_scores[0][16]);
        }
        printf("MERCI D'AVOIR JOUE\n");
    }
    return EXIT_SUCCESS;
}

/**
 * @brief Procédure permettant  de mettre à zéro le tableau des scores.
 * 
 * @param tab_scores permet de mettre le tableau des scores à zero.
 */
void mise_a_zero(int tab_scores[NB_JOUEUR][TAILLE_TAB]) {
    for (int joueur = 0; joueur < NB_JOUEUR; joueur++) {
        for (int Case = 0; Case < 17; Case++) {
            tab_scores[joueur][Case] = VAL_PAS_PRIS_EN_COMPTE;
		}	
    }
}

/**
 * @brief Procédure permettant de rentrer le nom des joueurs.
 * 
 * @param tab_nom_j c'est le tableau pour le nom des joueurs.
 */
void demande_nom(char tab_nom_j[NB_JOUEUR][TAILLE_MAX_NOM]){
    char nom[50];
    int compteur_j;
    bool boucle_condi;
    boucle_condi = true;
    for (compteur_j = 0; compteur_j < NB_JOUEUR; compteur_j++)
    {
        while (boucle_condi)
        {
            printf("Joueur %d, donnez votre nom. (%d Max caractères)\n", compteur_j+1, TAILLE_MAX_NOM-1);
            scanf("%s", nom);
            if(strlen(nom) < TAILLE_MAX_NOM){
                strcpy(tab_nom_j[compteur_j], nom);
                boucle_condi = false;
            }
            else{
                printf("Utilisez %d caractères max.\n", TAILLE_MAX_NOM-1);
            }
        }
        boucle_condi = true;
    }
}
/**
 * @brief Cettre procédure permet de placer un nombre du tableau des scores dans une chaîne de caractères.
 * 
 * @param tab_scores Donnes l'accès au tableau des scores.
 * @param x_tab gère l'indice des joueurs.
 * @param y_tab gère l'indice de la ligne.
 * @param chaine permet de renvoyer une chaîne de caractères pour l'affichage.
 */
void change_tab(int tab_scores[NB_JOUEUR][TAILLE_TAB],int x_tab,int y_tab,char chaine[5]){
    int val = 0;
    if(tab_scores[x_tab][y_tab] == -1){
        strcpy(chaine,"\t");
    }
    else{
        val = tab_scores[x_tab][y_tab];
        sprintf(chaine,"%d\t", val);
    }
}
/**
 * @brief Permet d'afficher la feuille de marque.
 * 
 * @param tab_scores permet d'avoir accès au tableau 
 * @param tab_nom_j 
 */
void affiche_tab_score(int tab_scores[NB_JOUEUR][TAILLE_TAB], char tab_nom_j[NB_JOUEUR][TAILLE_MAX_NOM]){
    char chaine1[CARAC_TAB];
    char chaine2[CARAC_TAB];
    printf("┏━━━━━━━━━━━━━━━━━━━━━━┫%s\t┃%s\t┃\n", tab_nom_j[0], tab_nom_j[1]);
    change_tab(tab_scores, 0, 0, chaine1);
    change_tab(tab_scores, 1, 0, chaine2);
    printf("┃ 1 [total de 1]       ┃%s┃%s┃\n", chaine1, chaine2);
    change_tab(tab_scores, 0, 1, chaine1);
    change_tab(tab_scores, 1, 1, chaine2);
    printf("┃ 2 [total de 2]       ┃%s┃%s┃\n", chaine1, chaine2);
    change_tab(tab_scores, 0, 2, chaine1);
    change_tab(tab_scores, 1, 2, chaine2);
    printf("┃ 3 [total de 3]       ┃%s┃%s┃\n", chaine1, chaine2);
    change_tab(tab_scores, 0, 3, chaine1);
    change_tab(tab_scores, 1, 3, chaine2);
    printf("┃ 4 [total de 4]       ┃%s┃%s┃\n", chaine1, chaine2);
    change_tab(tab_scores, 0, 4, chaine1);
    change_tab(tab_scores, 1, 4, chaine2);
    printf("┃ 5 [total de 5]       ┃%s┃%s┃\n", chaine1, chaine2);
    change_tab(tab_scores, 0, 5, chaine1);
    change_tab(tab_scores, 1, 5, chaine2);
    printf("┃ 6 [total de 6]       ┃%s┃%s┃\n", chaine1, chaine2);
    printf("┣━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━╋━━━━━━━┫\n");
    change_tab(tab_scores, 0, 6, chaine1);
    change_tab(tab_scores, 1, 6, chaine2);
    printf("┃ Bonus si > à 62 [35] ┃%s┃%s┃\n", chaine1, chaine2);
    printf("┣━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━╋━━━━━━━┫\n");
    change_tab(tab_scores, 0, 7, chaine1);
    change_tab(tab_scores, 1, 7, chaine2);
    printf("┃ Total supérieur      ┃%s┃%s┃\n", chaine1, chaine2);
    printf("┣━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━╋━━━━━━━┫\n");
    change_tab(tab_scores, 0, 8, chaine1);
    change_tab(tab_scores, 1, 8, chaine2);
    printf("┃ Brelan               ┃%s┃%s┃\n", chaine1, chaine2);
    change_tab(tab_scores, 0, 9, chaine1);
    change_tab(tab_scores, 1, 9, chaine2);
    printf("┃ Carré                ┃%s┃%s┃\n", chaine1, chaine2);
    change_tab(tab_scores, 0, 10, chaine1);
    change_tab(tab_scores, 1, 10, chaine2);
    printf("┃ Full House           ┃%s┃%s┃\n", chaine1, chaine2);
    change_tab(tab_scores, 0, 11, chaine1);
    change_tab(tab_scores, 1, 11, chaine2);
    printf("┃ Petite suite         ┃%s┃%s┃\n", chaine1, chaine2);
    change_tab(tab_scores, 0, 12, chaine1);
    change_tab(tab_scores, 1, 12, chaine2);
    printf("┃ Grande suite         ┃%s┃%s┃\n", chaine1, chaine2);
    change_tab(tab_scores, 0, 13, chaine1);
    change_tab(tab_scores, 1, 13, chaine2);
    printf("┃ Yams                 ┃%s┃%s┃\n", chaine1, chaine2);
    change_tab(tab_scores, 0, 14, chaine1);
    change_tab(tab_scores, 1, 14, chaine2);
    printf("┃ Chance               ┃%s┃%s┃\n", chaine1, chaine2);
    printf("┣━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━╋━━━━━━━┫\n");
    change_tab(tab_scores, 0, 15, chaine1);
    change_tab(tab_scores, 1, 15, chaine2);
    printf("┃ Total inférieur      ┃%s┃%s┃\n", chaine1, chaine2);
    printf("┣━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━╋━━━━━━━┫\n");
    change_tab(tab_scores, 0, 16, chaine1);
    change_tab(tab_scores, 1, 16, chaine2);
    printf("┃ Total inférieur      ┃%s┃%s┃\n", chaine1, chaine2);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━┻━━━━━━━┛\n");
}
/**
 * @brief Permet de faire 5 lancés aléatoires.
 * 
 * @param tab_des permet mettre les valeurs aléatoires dans le tableau des dés
 */
void premier_lance(int tab_des[NB_DES]){
    int compteur;
    for (compteur = 0; compteur < 5; compteur++){
        lancer_de_de(compteur, tab_des);
        printf("%d  ", tab_des[compteur]);
    }
    printf("\n");
}
/**
 * @brief Permet de faire un lancé aléatoire et choisir dans case du tableau on place le résultat.
 * 
 * @param indice_de permet de choisir quel case du tableau on veut modifier
 * @param tab_des permet d'avoir accès au tableau des dés
 */
void lancer_de_de (int indice_de, int tab_des[NB_DES]){
    int De = rand() % MAX_VAL_DE + 1;
    tab_des[indice_de] = De;
}
/**
 * @brief Procédure qui permet de gérer quel dé on veut relancer et de savoir si le dé à déjà été relancé.
 * 
 * @param tab_des permet d'avoir accès aux dés
 */
void relancer(int tab_des[NB_DES]){
    int nb_des_rel, compteur_nb_lance, rep_num_de, compteur_aff, compteur_zero;
    bool bool_boucle = true;
    bool tab_bool[NB_DES];
    for (compteur_zero = 0; compteur_zero < NB_DES; compteur_zero++)
    {
        tab_bool[compteur_zero] = true;
    }
    
    while(bool_boucle){
        printf("Choisissez combien de dés vous voulez relancer, entre 1 et 5, 0 si vous ne voulez pas relancer de dés.\n");
        scanf("%d", &nb_des_rel);
        if (nb_des_rel == 0)
        {
            bool_boucle = false;
        }
        else if((nb_des_rel >= 1)&&(nb_des_rel <= 5)){
            for (compteur_nb_lance = 1; compteur_nb_lance <= nb_des_rel; compteur_nb_lance++)
            {
                while (bool_boucle)
                {
                    printf("Quel dé voulez vous relancer ? Entrez un chiffre entre 1 et 5, 0 si vous ne voulez pas relancer de dés.\n");
                    scanf("%d", &rep_num_de);
                    if (rep_num_de == 0)
                    {
                        bool_boucle = false;
                    }
                    else if ((rep_num_de >= 1)&&(rep_num_de <= 5))
                    {
                        sleep(1);
                        if((rep_num_de == 1)&&(tab_bool[0])){
                            lancer_de_de(rep_num_de-1, tab_des);
                            tab_bool[0] = false;
                            bool_boucle = false;
                        }
                        else if((rep_num_de == 2)&&(tab_bool[1])){
                            lancer_de_de(rep_num_de-1, tab_des);
                            tab_bool[1] = false;
                            bool_boucle = false;
                        }
                        else if((rep_num_de == 3)&&(tab_bool[2])){
                            lancer_de_de(rep_num_de-1, tab_des);
                            tab_bool[2] = false;
                            bool_boucle = false;
                        }
                        else if((rep_num_de == 4)&&(tab_bool[3])){
                            lancer_de_de(rep_num_de-1, tab_des);
                            tab_bool[3] = false;
                            bool_boucle = false;
                        }
                        else if((rep_num_de == 5)&&(tab_bool[4])){
                            lancer_de_de(rep_num_de-1, tab_des);
                            tab_bool[4] = false;
                            bool_boucle = false;
                        }
                        else{
                            printf("Vous avez déjà utilisé ce dés\n");
                        }
                    }
                    else{
                        printf("Entre 1 et 5, 0 si vous ne voulez pas relancer de dés.\n");
                    }
                }
                bool_boucle = true;
            }
        }
        else{
            printf("Entre 1 et 5, 0 si vous ne voulez pas relancer de dés.\n");
        }
        printf("Voilà vos nouveaux dés:");
        for (compteur_aff = 0; compteur_aff < 5; compteur_aff++){
            printf("%d  ", tab_des[compteur_aff]);
        }
        printf("\n");
        bool_boucle = false;
    }
}
/**
 * @brief Procédure qui permet de choisir quelle combinaison on veut et de vérifier si elle est déjà prise
 * 
 * @param tab_des permet d'avoir accès aux dés
 * @param tab_scores 
 * @param tour_joueur_compteur 
 */
void choix_combinaison(int tab_des[NB_DES],int tab_scores[NB_JOUEUR][TAILLE_TAB], int tour_joueur_compteur){
    bool boucle = true;
    int reponse;
    trie(tab_des);
    while (boucle)
    {
        printf("Quelle combinaison voulez vous choisir ? Entrez un nombre entre 1 et 13, les nombres correspondent aux différentes combinaison.\n");
        scanf("%d", &reponse);
        if ((reponse >= 1)&&(reponse <= 13))
        {
            if (tab_scores[tour_joueur_compteur][reponse-1] != -1)
            {
                printf("Cette combinaison est déjà prise.\n");
            }
            else if (tab_scores[tour_joueur_compteur][reponse-1] == -1) 
            {
                if ((reponse >= MIN_VAL_DE)&&(reponse <= MAX_VAL_DE))
                {
                    suite_chiffre(tab_des,tab_scores, reponse-1, tour_joueur_compteur);
                }
                else if(reponse == 7){
                    brelan(tab_des, tab_scores, tour_joueur_compteur);
                }
                else if(reponse == 8){
                    carre(tab_des, tab_scores, tour_joueur_compteur);
                }
                else if(reponse == 9){
                    fullhouse(tab_des, tab_scores, tour_joueur_compteur);
                }
                else if(reponse == 10){
                    petite_suite(tab_des, tab_scores, tour_joueur_compteur);
                }
                else if(reponse == 11){
                    grande_suite(tab_des, tab_scores, tour_joueur_compteur);
                }
                else if(reponse == 12){
                    yams(tab_des, tab_scores, tour_joueur_compteur);
                }
                else if(reponse == 13){
                    chance(tab_des, tab_scores, tour_joueur_compteur);
                }
                boucle = false;
            }
        }
        else{
            printf("Erreur, entrez un nombre entre 1 et 13.\n");
        }
    }
    calcul_bonus_totaux(tab_scores, tour_joueur_compteur);
}
/**
 * @brief Permet d'échanger des valeurs pour le trie.
 * 
 * @param tab_des permet d'avoir accès aux dés
 * @param val1 1ère valeur a remplacer
 * @param val2 2ème valeur a remplacer
 */
void echange(int tab_des[NB_DES], int val1, int val2){
    int tmp;
    tmp=tab_des[val1];
    tab_des[val1]=tab_des[val2];
    tab_des[val2]=tmp;   
}
/**
 * @brief Procédure de trie
 * 
 * @param tab_des permet d'avoir accès aux dés
 */
void trie(int tab_des[NB_DES]){
    int val1,val2,min,indmin;
    for(val1=0;val1<NB_DES-1;val1++){
        min=tab_des[val1];
        indmin=val1;
        for(val2=val1+1;val2<NB_DES;val2++){
            if (tab_des[val2]<min){
                min=tab_des[val2];
                indmin=val2;
            }
        }
        echange(tab_des,val1,indmin);
    }
}
/**
 * @brief Permet de calculer les points pour les scores pour les suites de 1 à 6.
 * 
 * @param tab_des permet d'avoir accès aux dés
 * @param tab_scores permet d'avoir accès aux scores
 * @param val_chiffre permet de savoir quelle suite on test pour les points
 * @param tour_joueur_compteur permet de à qui on va donner les points.
 */
void suite_chiffre(int tab_des[NB_DES],int tab_scores[NB_JOUEUR][TAILLE_TAB],int val_chiffre, int tour_joueur_compteur){
    int compteur_boucle, resultat;
    resultat = 0;
    tab_scores[tour_joueur_compteur][val_chiffre-1] = 0;
    for (compteur_boucle = 0; compteur_boucle < NB_DES; compteur_boucle++)
    {
        if(tab_des[compteur_boucle] == val_chiffre + 1){
            resultat = resultat + 1;
        }
    }
    tab_scores[tour_joueur_compteur][val_chiffre] =(val_chiffre + 1) * resultat;
}
/**
 * @brief Permet de calculer les points pour les scores pour le brelan
 * 
 * @param tab_des permet d'avoir accès aux dés
 * @param tab_scores permet d'avoir accès aux scores
 * @param tour_joueur_compteur permet de à qui on va donner les points.
 */
void brelan(int tab_des[NB_DES],int tab_scores[NB_JOUEUR][TAILLE_TAB], int tour_joueur_compteur){
    int compteur_brelan, compteur_val, somme;
    compteur_val = 1;
    somme = 0;
    tab_scores[tour_joueur_compteur][8] = 0;
    for (compteur_brelan = 0; compteur_brelan < NB_DES; compteur_brelan++)
    {
        if(tab_des[compteur_brelan] == tab_des[compteur_brelan + 1]){
            compteur_val = compteur_val +1;
            
        }
        else if (compteur_val == 3)
        {
            compteur_val = NB_DES;
            if(compteur_val == 4){
                for (compteur_brelan = 0; compteur_brelan < NB_DES; compteur_brelan++)
                {
                    somme = somme + tab_des[compteur_brelan];
                }
                tab_scores[tour_joueur_compteur][9] = tab_scores[tour_joueur_compteur][9] + somme;
            }
        }
        else{
            compteur_val = 0;
        }
    }
    if(compteur_val == 3){
        for (compteur_brelan = 0; compteur_brelan < NB_DES; compteur_brelan++)
        {
            somme = somme + tab_des[compteur_brelan];
        }
        tab_scores[tour_joueur_compteur][8] = tab_scores[tour_joueur_compteur][8] + somme;
    }
}
/**
 * @brief Permet de calculer les points pour les scores pour le carre
 * 
 * @param tab_des permet d'avoir accès aux dés
 * @param tab_scores permet d'avoir accès aux scores
 * @param tour_joueur_compteur permet de à qui on va donner les points.
 */
void carre(int tab_des[NB_DES],int tab_scores[NB_JOUEUR][TAILLE_TAB], int tour_joueur_compteur){
    int compteur_carre, compteur_val, somme;
    compteur_val = 1;
    somme = 0;
    tab_scores[tour_joueur_compteur][9] = 0;
    for (compteur_carre = 0; compteur_carre < NB_DES; compteur_carre++)
    {
        if(tab_des[compteur_carre] == tab_des[compteur_carre + 1]){
            compteur_val = compteur_val +1;
            
        }
        else if (compteur_val == 4)
        {
            compteur_val = NB_DES;
            if(compteur_val == 4){
                for (compteur_carre = 0; compteur_carre < NB_DES; compteur_carre++)
                {
                    somme = somme + tab_des[compteur_carre];
                }
                tab_scores[tour_joueur_compteur][9] = tab_scores[tour_joueur_compteur][9] + somme;
            }
        }
        else{
            compteur_val = 0;
        }
    }
    if(compteur_val == 4){
        for (compteur_carre = 0; compteur_carre < NB_DES; compteur_carre++)
        {
            somme = somme + tab_des[compteur_carre];
        }
        tab_scores[tour_joueur_compteur][9] = tab_scores[tour_joueur_compteur][9] + somme;
    }
}
/**
 * @brief Permet de calculer les points pour les scores pour le fullhouse
 * 
 * @param tab_des permet d'avoir accès aux dés
 * @param tab_scores permet d'avoir accès aux scores
 * @param tour_joueur_compteur permet de à qui on va donner les points.
 */
void fullhouse(int tab_des[NB_DES],int tab_scores[NB_JOUEUR][TAILLE_TAB], int tour_joueur_compteur){
    int compteur_full, compteur_val;
    compteur_val = 1;
    tab_scores[tour_joueur_compteur][10] = 0;
    for (compteur_full = 0; compteur_full < NB_DES; compteur_full++)
    {
        if(tab_des[compteur_full] == tab_des[compteur_full + 1]){
            compteur_val = compteur_val + 1;
        }
        else if (compteur_val == 3)
        {
            compteur_val = NB_DES;
            if ( (tab_des[0] == tab_des[1]) || (tab_des[3] == tab_des[4]) )  {
                tab_scores[tour_joueur_compteur][10] = 25;
            }
        else{
            compteur_val = 0;
            }
        }
    }
}
/**
 * @brief Permet de calculer les points pour les scores pour la petite suite
 * 
 * @param tab_des permet d'avoir accès aux dés
 * @param tab_scores permet d'avoir accès aux scores
 * @param tour_joueur_compteur permet de à qui on va donner les points.
 */
void petite_suite(int tab_des[NB_DES],int tab_scores[NB_JOUEUR][TAILLE_TAB], int tour_joueur_compteur){
    int compteur, val_compteur;
    val_compteur = 1;
    tab_scores[tour_joueur_compteur][11] = 0;
    for ( compteur = 0; compteur < NB_DES; compteur++)
    {        
        if (tab_des[compteur] == tab_des[compteur + 1] - 1) {
            val_compteur = val_compteur + 1;
        }
    }
    if (val_compteur >= 4) {
        tab_scores[tour_joueur_compteur][11] = 30;
    }
}
/**
 * @brief Permet de calculer les points pour les scores pour la grande suite
 * 
 * @param tab_des permet d'avoir accès aux dés
 * @param tab_scores permet d'avoir accès aux scores
 * @param tour_joueur_compteur permet de à qui on va donner les points.
 */
void grande_suite(int tab_des[NB_DES],int tab_scores[NB_JOUEUR][TAILLE_TAB], int tour_joueur_compteur){
    int compteur, val_compteur;
    val_compteur = 1;
    tab_scores[tour_joueur_compteur][12] = 0;
    for ( compteur = 0; compteur < NB_DES; compteur++)
    {        
        if (tab_des[compteur] == tab_des[compteur + 1] - 1) {
            val_compteur = val_compteur + 1;
        }
        else{
            compteur = NB_DES;
        }
    }
    if (val_compteur == 5) {
        tab_scores[tour_joueur_compteur][12] = 40;
    }
}
/**
 * @brief Permet de calculer les points pour les scores pour le yams
 * 
 * @param tab_des 
 * @param tab_scores 
 * @param tour_joueur_compteur 
 */
void yams(int tab_des[NB_DES],int tab_scores[NB_JOUEUR][TAILLE_TAB], int tour_joueur_compteur){
    int compteur_boucle, resultat;
    resultat = 0;
    for (compteur_boucle = 0; compteur_boucle < NB_DES; compteur_boucle++)
    {
        if(tab_des[compteur_boucle] == tab_des[compteur_boucle + 1]){
            resultat = resultat + 1;
        }
        else{
            compteur_boucle = NB_DES;
        }
    }
    if (resultat == 5) {
        tab_scores[tour_joueur_compteur][13] = 50;
    }
}
/**
 * @brief permet de 
 * 
 * @param tab_des 
 * @param tab_scores 
 * @param tour_joueur_compteur 
 */
void chance(int tab_des[NB_DES],int tab_scores[NB_JOUEUR][TAILLE_TAB], int tour_joueur_compteur){
    int somme;
    for (int compteur = 0; compteur < NB_DES; compteur++)
    {
        somme = somme + tab_des[compteur];
    }
    tab_scores[tour_joueur_compteur][14] = somme;
}

void calcul_bonus_totaux(int tab_scores[NB_JOUEUR][TAILLE_TAB], int tour_joueur_compteur){
    int somme, compteur;
    somme = 0;
    
    for (int compteur = 0; compteur < MAX_VAL_DE; compteur++)
    {
        if (tab_scores[tour_joueur_compteur][compteur] != -1)
        {
            somme = somme + tab_scores[tour_joueur_compteur][compteur];
        }
    }
    if(somme > 62){
        tab_scores[tour_joueur_compteur][6] = 35;
    }
    else if(somme < 62){
        tab_scores[tour_joueur_compteur][6] = 0;
    }
    tab_scores[tour_joueur_compteur][7] = somme + tab_scores[tour_joueur_compteur][6];
    somme = 0;
    for (compteur = 8; compteur <= 14; compteur++)
    {
        if (tab_scores[tour_joueur_compteur][compteur] != -1)
        {
            somme = somme + tab_scores[tour_joueur_compteur][compteur];
        }
    }
    tab_scores[tour_joueur_compteur][15] = somme;
    tab_scores[tour_joueur_compteur][16] = tab_scores[tour_joueur_compteur][7] + tab_scores[tour_joueur_compteur][15];
}