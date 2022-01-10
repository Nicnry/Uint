/*
-----------------------------------------------------------------------------------
Nom du fichier :    	henry_labo30.cpp
Auteur(s)      :    	Nicolas Henry
Date creation  :    	14.12.2021
Laboratoire n° :    	30
Description    :
-----------------------------------------------------------------------------------
*/

#include <iostream>
#include "Uint.hpp"
#include <string>
#include <random>

using namespace std;

const uint32_t GRAINE = 34032;
mt19937 mt_rand(GRAINE);
uniform_int_distribution<int32_t> distribution(0, 9);
Uint gen_random(int nombre);
uint32_t exponentiation_modulaire(uint64_t base, uint32_t exposant, uint32_t modulo);
bool test_rapide_primalite(uint32_t nombre);

int main() {
	string nombre;
	cout << "Introduire un nombre entier: ";
	cin >> nombre;
	size_t nb = stoul(nombre);
	Uint n;           // Vérification constructeur vide
	n = Uint(nombre); // Vérification constructeur par string

	cout << "Nombre lu " << n << endl; // Vérification opérateur <<

	Uint factorielle(1); // Vérification constructeur par entier (explicite)
	for (size_t i = 2; i <= nb; ++i) {
		factorielle *= i; // Vérification *= size_t
		cout << i << "! = " << factorielle << endl;
	}

	factorielle = 1;              // Vérification constructeur par entier implicite
	for (Uint i = 2; i <= n; ++i) // Vérification <= et ++
	{
		factorielle *= i; // Vérification *= Uint
		cout << i << "! = " << factorielle << endl;

	}

	Uint fibo_m2(0), fibo_m1(1), fibonacci;

	for (Uint i = 2; i <= n; ++i) {
		fibonacci = fibo_m2 + fibo_m1; // Vérification Uint + Uint
		cout << "fibonacci(" << i << ") = " << fibonacci << endl;
		fibo_m2 = fibo_m1;
		fibo_m1 = fibonacci;
	}

	// Vérification -, > et -=
	for (Uint i = n - 1; i > 0; i -= 1) {
		cout << "fibonacci(" << i << ") = " << fibo_m2 << endl;
		fibonacci = fibo_m1;
		fibo_m1 = fibo_m2;
		fibo_m2 = fibonacci - fibo_m2; // Vérification -
	}
	/*
	for (Uint i = n; i > 0; i -= 1) {
		cout << i << "! = " << factorielle << endl;
		factorielle = factorielle / i; // Vérification Uint/Uint
	}
	/*
	Uint p;
	Uint t = 10000;
	cout << t-- << endl;
	cout << t;
	//Uint w = 872360;
	//cout << --w << endl;
	//do
	//{
	//	p = gen_random(nb); // Vérification gen_random
	//	cout << p << endl;
	//} while (/*!prime(p) 1); // Vérification exponentiation modulaire, prime
*/
}
/*
Uint gen_random(int nombre) {
	string random_string;
	Uint random_number;
	for (size_t i = 0; i < nombre; i++) {
		random_string += to_string(distribution(mt_rand));
	}
	random_number = random_string;
	return random_number;
}

uint32_t exponentiation_modulaire(Uint base, Uint exposant, Uint modulo) {
	uint64_t resultat = 1;
	while (exposant > 0) {
		if (!(exposant % 2)) {
			base = base * base % modulo;
			exposant /= 2;
		} else {
			resultat = resultat * base % modulo;
			exposant--;
		}
	}
	return uint32_t(resultat);
}

bool test_rapide_primalite(Uint nombre) {
	//Utilisation d'une variable, car souvent répété dans la fonction.
	Uint nombre_moins_1 = nombre - 1;
	//1 et 0 ne sont pas premier,
	if (nombre < 2) {
		return false;
	}
	/**
	 * 2 est le premier nombre premier et empêche tous les nombres paires d'être
	 * premier. Tester si l'utilisateur rentre 3 (car generateur_aleatoire
	 * retournera 2 et ça ferra modulo 2 donc boucle infinie plus tard dans la
	 * fonction). */
/*
	if (nombre == 2 || nombre == 3) {
		return true;
	}

	uint32_t nombre_aleatoire;
	//Tester 10 fois pour s'assurer de la primalité
	for (int i = 1; i <= 10; i++) {
		//Generation d'un nombre aléatoire, on vérifie avec % si le nombre dépasse nombre-1
		do {
			nombre_aleatoire = 2;//generateur_aleatoire() % nombre_moins_1;
		} while(nombre_aleatoire < 2);
		/**
		 * Si l'exponentiation modulaire retourne autre chose que 1, c'est que le
		 * nombre n'est pas premier (le PGDC d'un nombre premier ne peut être que
		 * lui même et 1, donc si on trouve autre chose que 1...)
		 */
/*
		if(exponentiation_modulaire(uint64_t(nombre_aleatoire), nombre_moins_1, nombre) != 1) {
			return false;
		}
		/**
		 * les noms de variables q et u viennent de la formule mathématique fournie
		 * ici : https://fr.wikipedia.org/wiki/Algorithme_d%27Euclide_%C3%A9tendu,
		 * mais pour résumer, ce sont des variables temporaires qu'on doit utiliser
		 * en informatique et qui ne sont pas expliquée mathématiquement, c'est une
		 * contrainte du language C++ qui ne permet pas d'affecter plusieurs
		 * variables en une seule fois.
		 */
/*
		Uint q = 1;
		Uint u = nombre_moins_1;
		//Tant que u n'est pas pair (divisible par 2) il est candidat.
		while (!(u % 2) && q == 1) {
			u /= 2;
			q = exponentiation_modulaire(nombre_aleatoire, u, nombre);
			//Si q n'est pas premier et (nombre - 1), c'est qu'il n'est pas premier...
			if (q != 1 && q != nombre_moins_1) {
				return false;
			}
		}
	}
	return true;
}
*/