/*
* Auteur: Patrick Lainesse
* Cours: IFT1166 - A19 - Mardi 16h30
*
* client.h
* Fichier d'en-tête des classes et methodes qui representent les clients de la banque. Fidele a mon habitude, j'ai complique les choses inutilement
* et j'ai decide qu'un meme client pourrait avoir plusieurs comptes cheque et plusieurs compte epargne pour tester
* davantage le concept de listes et vecteurs.
*/

#include <iostream>
#include <iomanip>			// pour utiliser setprecision()
#include <string>
#include <list>
#include <vector>
#include "compte.h"

using namespace std;

class client
{
private:
	int numero;
	string nom;
	string prenom;

public:
	list<comptBanq*> portefeuille;
	client(string nom, string prenom);
	client(string nom, string prenom, comptCheq* cheque, comptEpargn* epargne);
	client(const client& copie);
	~client();
	client& operator = (const client&);
	int getNumero();
	client(string nom, string prenom, list<double> cheque, vector<double> epargne);
	void afficher();
};

/* EXECUTION
Cher client, votre compte #1001 contient moins que le solde minimum prevu a votre contrat. Des frais de 50 sous ont ete debites a votre compte pour cette transaction. Veuillez agreer de nos sentiments les plus distingues.
Affichage des comptes a l'initialisation:
======================================================
Bienvenue chez Despotagers.
Bunton, Emma    Client #162018
Voici la liste de vos comptes dans notre institution:
------------------------------------------------------
Compte cheque #1001:
Solde: 99.50$
Solde minimum a respecter: 1000.00$
Frais mensuels: 2.25$
Frais de service: 0.50$
------------------------------------------------------
Compte epargne #1002:
Solde: 0.00$
Taux d'interet: 1.50%
A la fin du mois, vous recolterez 0.00$
------------------------------------------------------
======================================================
======================================================
Bienvenue chez Despotagers.
B, Mel  Client #162019
Voici la liste de vos comptes dans notre institution:
------------------------------------------------------
Compte cheque #1003:
Solde: 5.00$
Solde minimum a respecter: 1000.00$
Frais mensuels: 2.49$
Frais de service: 0.50$
------------------------------------------------------
======================================================
======================================================
Bienvenue chez Despotagers.
Chisholm, Melanie       Client #162020
Voici la liste de vos comptes dans notre institution:
------------------------------------------------------
Compte cheque #1004:
Solde: 2500.00$
Solde minimum a respecter: 1000.00$
Frais mensuels: 0.00$
Frais de service: 0.50$
------------------------------------------------------
Compte epargne #1005:
Solde: 4000.00$
Taux d'interet: 2.20%
A la fin du mois, vous recolterez 7.33$
------------------------------------------------------
======================================================
======================================================
Bienvenue chez Despotagers.
Halliwell, Geri Client #162021
Voici la liste de vos comptes dans notre institution:
------------------------------------------------------
Compte cheque #1006:
Solde: 300000.00$
Solde minimum a respecter: 12000.00$
Frais mensuels: 0.00$
Frais de service: 0.50$
------------------------------------------------------
Compte epargne #1007:
Solde: 700000.00$
Taux d'interet: 0.20%
A la fin du mois, vous recolterez 116.67$
------------------------------------------------------
======================================================
======================================================
Bienvenue chez Despotagers.
Beckham, Victoria       Client #162022
Voici la liste de vos comptes dans notre institution:
------------------------------------------------------
Compte cheque #1008:
Solde: 1000000.00$
Solde minimum a respecter: 1000.00$
Frais mensuels: 0.00$
Frais de service: 0.50$
------------------------------------------------------
Compte cheque #1009:
Solde: 500000.00$
Solde minimum a respecter: 1000.00$
Frais mensuels: 0.00$
Frais de service: 0.50$
------------------------------------------------------
Compte cheque #1010:
Solde: 6400000.00$
Solde minimum a respecter: 1000.00$
Frais mensuels: 0.00$
Frais de service: 0.50$
------------------------------------------------------
Compte epargne #1011:
Solde: 48000000.00$
Taux d'interet: 1.50%
A la fin du mois, vous recolterez 60000.00$
------------------------------------------------------
Compte epargne #1012:
Solde: 34000000.00$
Taux d'interet: 1.50%
A la fin du mois, vous recolterez 42500.00$
------------------------------------------------------
======================================================


Emma garde les enfants de Victoria et se fait payer 20$ pour la soiree.
Cher client, votre compte #1001 contient moins que le solde minimum prevu a votre contrat. Des frais de 50 sous ont ete debites a votre compte pour cette transaction. Veuillez agreer de nos sentiments les plus distingues.


Victoria est recompensee pour ce genereux salaire et se voit offrir un taux avantageux de notre banque pour son compte epargne.


Affichage des comptes apres ces operations:
======================================================
Bienvenue chez Despotagers.
Bunton, Emma    Client #162018
Voici la liste de vos comptes dans notre institution:
------------------------------------------------------
Compte cheque #1001:
Solde: 119.00$
Solde minimum a respecter: 1000.00$
Frais mensuels: 2.20$
Frais de service: 0.50$
------------------------------------------------------
Compte epargne #1002:
Solde: 0.00$
Taux d'interet: 1.50%
A la fin du mois, vous recolterez 0.00$
------------------------------------------------------
======================================================
======================================================
Bienvenue chez Despotagers.
Beckham, Victoria       Client #162022
Voici la liste de vos comptes dans notre institution:
------------------------------------------------------
Compte cheque #1008:
Solde: 999980.00$
Solde minimum a respecter: 1000.00$
Frais mensuels: 0.00$
Frais de service: 0.50$
------------------------------------------------------
Compte cheque #1009:
Solde: 500000.00$
Solde minimum a respecter: 1000.00$
Frais mensuels: 0.00$
Frais de service: 0.50$
------------------------------------------------------
Compte cheque #1010:
Solde: 6400000.00$
Solde minimum a respecter: 1000.00$
Frais mensuels: 0.00$
Frais de service: 0.50$
------------------------------------------------------
Compte epargne #1011:
Solde: 48000000.00$
Taux d'interet: 1.50%
A la fin du mois, vous recolterez 60000.00$
------------------------------------------------------
Compte epargne #1012:
Solde: 34000000.00$
Taux d'interet: 3.00%
A la fin du mois, vous recolterez 85000.00$
------------------------------------------------------
======================================================


Sous forte pression financiere, Mel B tente de retirer plus que ce qu'elle a dans son compte.

Cher client, votre compte #1003 contient moins que le solde minimum prevu a votre contrat. Des frais de 50 sous ont ete debites a votre compte pour cette transaction. Veuillez agreer de nos sentiments les plus distingues.

Cher client, votre compte #1003 n'a pas suffisamment de fonds. Impossible d'effectuer un retrait. Allez directement en prison et si vous passez Go, NE RECLAMEZ PAS 200$.
Compte cheque #1003:
Solde: 4.50$
Solde minimum a respecter: 1000.00$
Frais mensuels: 2.49$
Frais de service: 0.50$


Mel B est punie pour sa tentative et notre banque lui impose un solde minimum plus eleve dans son compte:
Cher client, votre compte #1003 contient moins que le solde minimum prevu a votre contrat. Des frais de 50 sous ont ete debites a votre compte pour cette transaction. Veuillez agreer de nos sentiments les plus distingues.
Compte cheque #1003:
Solde: 4.00$
Solde minimum a respecter: 10000.00$
Frais mensuels: 24.99$
Frais de service: 0.50$



I'll tell you what I want, what I really, really want
So tell me what you want, what you really, really want
I wanna, (ha)I wanna, (ha)I wanna, (ha)I wanna, (ha)
I wanna really, really, really wanna zigazig ah


C:\Users\admin\Desktop\1166\tp3\191213\lafin\Debug\lafin.exe (process 2140) exited with code 0.
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .

*/
