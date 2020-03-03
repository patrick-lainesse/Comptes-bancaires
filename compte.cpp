/*
* Auteur: Patrick Lainesse
* Cours: IFT1166 - A19 - Mardi 16h30
*
* compte.cpp
* Classes et methodes implementant une classe abstraite pour gerer
* des operations bancaires.
*/

#include "compte.h"

// On declare globalement l'iteration des numeros de comptes pour qu'ils soient modifies a l'exterieur des classes
// afin d'eviter d'attribuer le meme numero a deux comptes differents. On debute a 1001 pour faire plus serieux.
// J'ai d'abord essaye avec le mot-cle "static" a l'interieur de comptBanq, tel que suggére, par Audrey, mais cela
// n'accomplissait pas l'effet désire (tous les comptes se retrouvaient alors avec le meme numero), et il fallait tout
// de même initialiser globalement pour que cela fonctionne, donc c'est la solution que j'ai privilégiee.
int iteration = 1001;

comptBanq::comptBanq()
{
	numero = iteration;
	iteration++;
}

comptBanq::comptBanq(double montant):solde(montant)
{
	numero = iteration;
	iteration++;
}

int comptBanq::getNumero() const
{
	return numero;
}

double comptBanq::getSolde() const
{
	return solde;
}

void comptBanq::depot(double montant)
{
	solde += montant;
}

void comptBanq::retrait(double montant)
{
	double test = 0;
	test = solde - montant;

	if(test < 0)
	{
		cout << "\nCher client, votre compte #" << getNumero() << " n'a pas suffisamment de fonds. Impossible d'effectuer un retrait. "
			<< "Allez directement en prison et si vous passez Go, NE RECLAMEZ PAS 200$.\n";
	}
	else
		solde -= montant;

	return;
}

comptCheq::comptCheq(double montant) : comptBanq(montant)
{
	fraisService();		// eh oui, nos radins de patrons chargent des frais meme a l'ouverture des comptes
}

comptCheq::comptCheq(double montant, double minimum): comptBanq(montant), soldeMinimum(minimum)
{
	fraisService();
}

comptCheq::comptCheq() : comptBanq() {}		// constructeur avec valeurs par defaut

void comptCheq::setSoldeMinimum(double minimum)
{
	soldeMinimum = minimum;
	fraisService();
}

double comptCheq::getSoldeMinimum() const
{
	return soldeMinimum;
}

/* Il me semble necessaire de definir une methode pour les frais de service a appliquer a chaque transaction
dans le cas ou le client a un solde inferieur au solde minimum */
void comptCheq::fraisService()
{
	if (getSolde() - soldeMinimum <= 0)
	{
		cout << "Cher client, votre compte #" << getNumero() << " contient moins que le solde minimum prevu a votre contrat. "
			<< "Des frais de 50 sous ont ete debites a votre compte pour cette transaction. Veuillez agreer de nos sentiments les plus distingues.\n";
		comptBanq::retrait(0.50);		// utilise le retrait de la classe mere pour eviter une boulce infinie avec le retrait de comptCheq
	}
}

double comptCheq::fraisMensuels() const	// ces frais seront appliques a toute transaction autre que les interrogations de compte
{
	if (getSolde() - getSoldeMinimum() <= 0)
		return (getSoldeMinimum() - getSolde()) * 0.0025;
	else return 0;			// si le compte a un solde superieur au minimum, pas de frais
}

void comptCheq::retrait(double montant)
{
	fraisService();
	comptBanq::retrait(montant);
}

void comptCheq::depot(double montant)
{
	fraisService();
	comptBanq::depot(montant);
}

void comptCheq::afficher() const
{
	cout << "Compte cheque #" << comptBanq::getNumero() << ":\n";
	cout << "Solde: " << getSolde() << "$\n";
	cout << "Solde minimum a respecter: " << getSoldeMinimum() << "$\n";
	cout << "Frais mensuels: " << fraisMensuels() << "$\n";
	cout << "Frais de service: 0.50$\n";
}

comptEpargn::comptEpargn(): comptBanq() {}

comptEpargn::comptEpargn(double montant, double tauxInteret): comptBanq(montant)
{
	taux = tauxInteret;
}

comptEpargn::comptEpargn(double montant): comptBanq(montant) {}

void comptEpargn::setTaux(double tauxInteret)
{
	taux = tauxInteret;
}

double comptEpargn::getTaux() const
{
	return taux;
}

void comptEpargn::afficher() const
{
	cout << "Compte epargne #" << comptBanq::getNumero() << ":\n";
	cout << "Solde: " << getSolde() << "$\n";
	cout << "Taux d'interet: " << getTaux() * 100 << "%\n";
	cout << "A la fin du mois, vous recolterez " << getSolde() * taux / 12 << "$\n";
}
/*
int main()
{
	comptEpargn test1;
	comptCheq test2(300);
	comptCheq test3(3);
	comptCheq test4(200.672, 850);
	comptEpargn test5(2000);

	cout << fixed << setprecision(2);		// montants s'affichent avec format usuel pour l'argent

	test1.afficher();
	//cout << test1.getTaux() << endl << endl;
	test2.afficher();
	//cout << test2.getSoldeMinimum() << endl << endl;
	test3.afficher();
	//cout << test3.getSoldeMinimum() << endl << endl;
	
	test4.afficher();
	//cout << test4.getSoldeMinimum();
	//cout << "\n";

	cout << "getSolde test3: " << test3.getSolde() << endl;

	test3.retrait(35);
	cout << "getSolde test3 apres retrait: " << test3.getSolde() << endl;

	cout << "frais mensuels test2: " << test2.fraisMensuels() << endl;
	cout << "frais mensuels test3: " << test3.fraisMensuels() << endl;
	cout << "frais mensuels test4: " << test4.fraisMensuels() << endl;
	test5.afficher();
}*/
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
