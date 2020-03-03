/*
* Auteur: Patrick Lainesse
* Cours: IFT1166 - A19 - Mardi 16h30
*
* client.cpp
* Classe qui represente les clients de la banque. Fidele a mon habitude, j'ai complique les choses inutilement
* et j'ai decide qu'un meme client pourrait avoir plusieurs comptes cheque et plusieurs compte epargne pour tester
* davantage le concept de listes et vecteurs.
*/

#include "client.h"

int no_client = 162008;	// initialise a n'importe quoi pour faire plus serieux

client::client(string nom, string prenom)		// constructeur par defaut
{
	numero = no_client++;
	this->nom = nom;
	this->prenom = prenom;
	portefeuille.push_back(new comptCheq());	// par defaut, on cree seulement un compte cheque pour le client
}

client::client(string nom, string prenom, comptCheq* cheque, comptEpargn* epargne)		// la star des constructeurs chez Despotagers, pour les gens aises
{
	numero = no_client++;
	this->nom = nom;
	this->prenom = prenom;
	portefeuille.push_back(cheque);
	portefeuille.push_back(epargne);
}

client::client(string nom, string prenom, list<double> cheque, vector<double> epargne) : nom(nom), prenom(prenom)	// si je garde ca, je devrais mettre les frais a zero et mettre le taux au max
{
	numero = no_client++;
	
	list<double>::iterator test;				// on initie un iterateur pour acceder aux membres de la liste de comptes

	for (test = cheque.begin(); test != cheque.end(); test++)
		portefeuille.push_back(new comptCheq(*test));

	for (int i = 0; i < epargne.size(); i++)
		portefeuille.push_back(new comptEpargn(epargne[i]));
}

client::client(const client& copie)
{
	numero = no_client++;		// on evite d'avoir deux clients avec le meme numero (on n'est pas Desjardins, quand meme)
	nom = copie.nom;
	prenom = copie.prenom;
	portefeuille = copie.portefeuille;
}

client::~client()
{
	portefeuille.clear();
}

client& client::operator=(const client& copie)
{
	numero = copie.numero;
	nom = copie.nom;
	prenom = copie.prenom;
	portefeuille = copie.portefeuille;

	return *this;
}

int client::getNumero(){ return numero; }

void client::afficher()
{
	cout << "======================================================\n"
		<< "Bienvenue chez Despotagers.\n" << nom << ", " << prenom << "\tClient #" << numero << endl
		<< "Voici la liste de vos comptes dans notre institution:\n"
		<< "------------------------------------------------------\n";

	list<comptBanq*>::iterator test = portefeuille.begin();				// on initie un iterateur pour acceder aux membres de la liste de comptes
	
	for (test = portefeuille.begin(); test != portefeuille.end(); test++)
	{
		(*test)->afficher();		// on accede aux fonctions afficher des differents comptes bancaires
		cout << "------------------------------------------------------\n";
	}

	cout << "======================================================\n";
}

int main()
{
	cout << fixed << setprecision(2);		// montants s'affichent avec format usuel pour l'argent

	comptCheq* courant;		// on cree des comptes pour transmettre aux constructeurs de clients
	comptEpargn* economies;

	courant = new comptCheq(100);
	economies = new comptEpargn(0);
	
	// Emma s'inscrit a notre banque et y depose les economies qu'elle a accumulees en gardant des enfants
	client baby("Bunton", "Emma", courant, economies);

	// Mel B s'inscrit a notre banque suite a sa faillite personnelle
	client scary("B", "Mel");

	// on cree de nouveaux comptes pour deux autres membres
	courant = new comptCheq(2500, 1000);
	economies = new comptEpargn(4000, 0.022);
	client sporty("Chisholm", "Melanie", courant, economies);

	courant = new comptCheq(300000, 12000);
	economies = new comptEpargn(700000, 0.002);
	client ginger("Halliwell", "Geri", courant, economies);
	

	// Victoria a du succes dans ses affaires et possede plus d'un compte,
	// on cree donc une liste et un vecteur pour transmettre tous ces comptes
	// au constructeur pour gens tres, tres aises.
	list<double> courant_riche = { 1000000, 500000, 6400000 };
	vector<double> economies_riche = { 48000000, 34000000 };
	client posh("Beckham", "Victoria", courant_riche, economies_riche);		// appel du constructeur VIP


	list<client> spice = { baby, scary, sporty, ginger, posh };
	list<client>::iterator it_spice;

	cout << "Affichage des comptes a l'initialisation:\n";
	for (it_spice = spice.begin(); it_spice != spice.end(); it_spice++)
	{
		it_spice->afficher();
	}
	
	// Pour comptBanq, l'attribution d'un numero, l'affichage du numero et du solde et
	// l'affichage des informations du compte ont deja ete testes par les initialisations.
	// Pour comptCheq, la determination des frais mensuels a deja ete teste par la meme occasion.
	
	// Test du retrait pour comptCheq (qui fait aussi appel au retrait de comptBanq et fraisService()).

	cout << "\n\nEmma garde les enfants de Victoria et se fait payer 20$ pour la soiree.\n";
	list<comptBanq*>::iterator transaction = posh.portefeuille.begin();
	(*transaction)->retrait(20);
	
	transaction = baby.portefeuille.begin();
	(*transaction)->depot(20);

	// Test de la determination du taux d'interet pour le comptEpargn
	cout << "\n\nVictoria est recompensee pour ce genereux salaire et se voit offrir un taux avantageux de notre banque "
		<< "pour son compte epargne.\n\n";
	transaction = posh.portefeuille.end();
	transaction--;

	// On doit faire un cast pour acceder aux fonctions de comptEpargn. Ce n'etait pas necessaires pour les autres operations, car
	// elles etaient declarees virtuelles dans comptBanq, tandis que setTaux n'existe pas dans la classe mere
	static_cast<comptEpargn*>(*transaction)->setTaux(0.03);

	cout << "\nAffichage des comptes apres ces operations:\n";
	spice.begin()->afficher();
	spice.back().afficher();

	// Test de retrait pour un solde a decouvert
	cout << "\n\nSous forte pression financiere, Mel B tente de retirer plus que ce qu'elle a dans son compte.\n\n";

	transaction = scary.portefeuille.begin();
	(*transaction)->retrait(300);
	(*transaction)->afficher();

	// Test de determination et affichage du solde minimum pour compteCheq (on utilise encore un cast)
	cout << "\n\nMel B est punie pour sa tentative et notre banque lui impose un solde minimum plus eleve dans son compte:\n";
	static_cast<comptCheq*>(*transaction)->setSoldeMinimum(10000);
	(*transaction)->afficher();

	cout << "\n\n\nI'll tell you what I want, what I really, really want\n"
		<< "So tell me what you want, what you really, really want\n"
		<< "I wanna, (ha)I wanna, (ha)I wanna, (ha)I wanna, (ha)\n"
		<< "I wanna really, really, really wanna zigazig ah\n\n";
	
	return 0;
}
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
