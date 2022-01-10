//
// Created by Nicolas Henry on 08.01.22.
//

#include "Uint.hpp"


#include "Uint.hpp"

Uint::Uint() = default;

Uint::Uint(std::string nombre) {
	//Inverser le nombre afin de faire des push_back et ne pas devoir tout re-trier.
	for(size_t i = nombre.length() + 1; i > 0; --i) {
		if(i != nombre.length() + 1) {
			this->nombre.push_back(nombre[i - 1] - 48);
		}
	}

}

Uint::Uint(u_int64_t nombre) {
	//Simple copie
	std::string nombre_string = std::to_string(nombre);
	*this = Uint(nombre_string);
}

Uint operator+(Uint lhs, const Uint& rhs) {
	//Appel à +=
	lhs += rhs;
	return lhs;
}

Uint& Uint::operator+=(const Uint& rhs) {
	Uint tutu = rhs;
	//Définir le plus petit pour éviter les overflows
	size_t difference_de_taille = 0;
	if(this->nombre.size() > rhs.nombre.size()) {
		difference_de_taille = this->nombre.size() - rhs.nombre.size();
		for(size_t i = 0; i < difference_de_taille; ++i) {
			tutu.nombre.push_back(0);
		}
	} else {
		difference_de_taille = rhs.nombre.size() - this->nombre.size();
		for(size_t i = 0; i < difference_de_taille; ++i) {
			this->nombre.push_back(0);
		}
	}
	int report = 0;
	for(size_t i = 0; i < this->nombre.size(); ++i) {
		int somme = this->nombre.at(i) + tutu.nombre.at(i) + report;
		this->nombre.at(i) = somme % 10;
		report = somme / 10;
	}
	if(report) {
		this->nombre.push_back(report);
	}
	return *this;
}

Uint operator-(Uint lhs, Uint &rhs) {
	//Appel à -=
	lhs -= rhs;
	return lhs;
}

Uint operator-(Uint lhs, const size_t &rhs) {
	//Appel à -=
	Uint temp = rhs;
	lhs -= temp;
	return lhs;
}

Uint& Uint::operator-=(Uint& rhs) {
	// Check for underflow.
	if(this->nombre.size() < rhs.nombre.size()) {
		std::cerr << "Underflow";
		*this = 0;
		return *this;
	}

	for(size_t i = 0; i < rhs.nombre.size(); ++i) {
		//
		if (this->nombre.at(i) >= rhs.nombre.at(i)) {
			this->nombre.at(i) = this->nombre.at(i) - rhs.nombre.at(i);
		} else {
			this->nombre.at(i) = this->nombre.at(i) + 10 - rhs.nombre.at(i);
			this->nombre.at(i + 1) = this->nombre.at(i + 1) - 1;
		}
	}
	if (!this->nombre.back()) {
		this->nombre.pop_back();
	}
	return *this;
}

Uint& Uint::operator-=(const size_t& rhs) {
	Uint temp = rhs;
	*this -= temp;
	return *this;
}

Uint operator/(Uint lhs, const Uint &rhs) {
	lhs /= rhs;
	return lhs;
}

Uint& Uint::operator/=(const Uint &rhs) {
	*this = this->division_reste(rhs);
	return *this;
}

Uint& Uint::division_par2() {
	for(size_t i = 0; i < this->nombre.size(); ++i) {
		if(i && this->nombre.at(i) % 2) {
			this->nombre.at(i - 1) += 5;
		}
		this->nombre.at(i) /= 2;
	}
	if(!this->nombre.back()) {this->nombre.pop_back();}
	return *this;
}

std::ostream& operator<<(std::ostream& lhs, const Uint& rhs) {
	for (size_t i = rhs.nombre.size(); i > 0; --i) {
		lhs << rhs.nombre.at(i - 1);
	}
	return lhs;
}

Uint operator*(Uint lhs, const size_t& rhs) {
	return lhs *= rhs;
}

Uint &Uint::operator*=(const Uint &rhs) {
	Uint resultat = 0;
	Uint manipulations;
	int report = 0;
	for(size_t i = 0; i < this->nombre.size(); ++i) {
		manipulations.nombre.clear();
		//*10 en fonction de l'avancée du calcul
		for(size_t k = 0; k < i; ++k) {
			manipulations.nombre.push_back(0);
		}
		//Multiplication basique
		for(int j : rhs.nombre) {
			manipulations.nombre.push_back(this->nombre.at(i) * j);
		}
		//Recalculer chaque cellule
		for(size_t l = 0; l < manipulations.nombre.size(); ++l) {
			int temp = manipulations.nombre.at(l) + report;
			manipulations.nombre.at(l) = temp % 10;
			report = temp / 10;
		}

		//Si il y a un dernier report
		if(report) {
			manipulations.nombre.push_back(report);
		}
		report = 0;
		resultat = manipulations + resultat;
	}

	*this = resultat;
	return *this;
}

/*Uint& Uint::operator*=(int& rhs) {
	Uint facteur = rhs;
	*this *= facteur;
	return *this;
}*/

Uint& Uint::operator++() {
	//++n
	const int MAX_DIGIT = 9;
	const int MIN_DIGIT = 0;
	if(this->nombre.at(0) < MAX_DIGIT) {
		++this->nombre.at(0);
	} else {
		for(size_t i = 1; i < this->nombre.size(); ++i) {
			this->nombre.at(i - 1) = MIN_DIGIT;
			if(this->nombre.at(i) < MAX_DIGIT) {
				++this->nombre.at(i);
				return *this;
			}
		}
		this->nombre.back() = MIN_DIGIT;
		this->nombre.push_back(1);
	}
	return *this;
}

const Uint Uint::operator++(int) {
	//n++
	Uint temp = *this;
	++*this;
	return temp;
}

bool operator<(const Uint& lhs, const Uint& rhs) {
	if(lhs.nombre.size() != rhs.nombre.size()) {
		return lhs.nombre.size() < rhs.nombre.size();
	}
	for (size_t i = lhs.nombre.size(); i > 0; --i) {
		if(lhs.nombre.at(i - 1) != rhs.nombre.at(i - 1)) {
			return lhs.nombre.at(i - 1) < rhs.nombre.at(i - 1);
		}
	}
	return false;
}
bool operator>(const Uint& lhs, const Uint& rhs) {return rhs < lhs;}
bool operator<=(const Uint& lhs, const Uint& rhs) {return !(rhs < lhs);}
bool operator>=(const Uint& lhs, const Uint& rhs) {return !(lhs < rhs);}
bool operator==(const Uint& lhs, const Uint& rhs) {
	return lhs.nombre == rhs.nombre;
}
bool operator!=(const Uint& lhs, const Uint& rhs) {return !(lhs == rhs);}

/*
void Uint::division_par2() {
	int report = 0;
	int resultat;
	if (!(this->nombre.size() == 1 && this->nombre.at(0) == 1))
	{
		for (size_t i = 0; i < this->nombre.size(); i++) {
			resultat = (this->nombre.at(i) + report) / 2;

			if (this->nombre.at(i) % 2) {
				report = 10;
			} else {
				report = 0;
			}

			this->nombre.at(i) = resultat;
		}
		if (this->nombre.at(0) == 0) {
			this->nombre.erase(this->nombre.begin(), this->nombre.begin() + 1);
		}
	}
}
*/

Uint Uint::division_reste(Uint diviseur) {
	Uint p2 = 1;
	Uint b = diviseur;
	Uint quotient = 0;
	Uint reste = *this;
	while (b <= *this) {
		p2 *= 2;
		b *= 2;
	}
	while (reste >= diviseur) {
		b.division_par2();
		p2.division_par2();

		if (reste >= b) {
			quotient = quotient + p2;
			reste = reste - b;
		}
	}
	return quotient;
}
/*
Uint operator+(Uint lhs, Uint rhs) {
	int report = 0;
	int somme;

	if (rhs.nombre.size() > lhs.nombre.size()) {
		lhs.nombre.insert(lhs.nombre.begin(), rhs.nombre.size() - lhs.nombre.size(), 0);
	}
	if (lhs.nombre.size() > rhs.nombre.size()) {
		rhs.nombre.insert(rhs.nombre.begin(), lhs.nombre.size() - rhs.nombre.size(), 0);
	}
	for (size_t i = rhs.nombre.size(); i > 0; i--) {
		//Si l'avant dernière valeur de la suite est plus petite on ajuste le vecteur pour qu'ils soient de la même taille

		somme = lhs.nombre.at(i - 1) + rhs.nombre.at(i - 1) + report;
		report = somme / 10;
		somme = somme % 10;
		lhs.nombre.at(i - 1) = somme;
	}
	//Si au moment d'arriver à la valeur la plus grande il reste un carry, on l'ajoute au début du vecteur.
	if (report) {
		lhs.nombre.insert(lhs.nombre.begin(), report);
	}
	return lhs;
}
*/
/*
Uint::Uint() {
	this->nombre = {};
}

Uint::Uint(std::string nombre) {
	for (size_t i = 0; i < nombre.size(); i++) {
		int char_to_int = nombre.at(i) - 48;
		this->nombre.push_back(char_to_int);
	}
}

Uint::Uint(uint64_t nombre) {
	std::string nombre_string = std::to_string(nombre);
	*this = Uint(nombre_string);
}

Uint operator*(Uint lhs, const int &rhs) {
	lhs *= rhs;
	return lhs;
}

bool operator<(const Uint &lhs, const Uint &rhs) {
	if (lhs.nombre.size() != rhs.nombre.size()) {
		return lhs.nombre.size() < rhs.nombre.size();
	}
	else {
		for (size_t i = 0; i < lhs.nombre.size(); i++) {
			if (lhs.nombre.at(i) > rhs.nombre.at(i)) {
				return false;
			} else if (lhs.nombre.at(i) < rhs.nombre.at(i)) {
				return true;
			}
			if ((i == lhs.nombre.size() - 1) && (lhs.nombre.at(i) == rhs.nombre.at(i) )) {
				return false;
			}
		}
		return true;
	}
	// if (lhs.nombre < rhs.nombre)
	// {
	//     return true;
	// }
	// else
	// {
	//     return false;
	// }
}

bool operator<=(const Uint &lhs, const Uint &rhs) {
	return !(rhs < lhs);
}

bool operator>(const Uint &lhs, const Uint &rhs) {
	return (rhs < lhs);
}

bool operator>=(const Uint &lhs, const Uint &rhs) {
	return !(lhs < rhs);
}

bool operator==(const Uint& lhs, const int rhs) {
	Uint comparateur = rhs;
	if (lhs.nombre.size() != comparateur.nombre.size()) {
		return false;
	}
	for (size_t i = 0; i < lhs.nombre.size(); ++i) {
		if (lhs.nombre.at(i) != comparateur.nombre.at(i)) {
			return false;
		}
	}
	return true;
}

bool operator==(const Uint& lhs, const Uint rhs) {
	if (lhs.nombre.size() != rhs.nombre.size()) {
		return false;
	}
	for (size_t i = 0; i < lhs.nombre.size(); ++i) {
		if (lhs.nombre.at(i) != rhs.nombre.at(i)) {
			return false;
		}
	}
	return true;
}

bool operator!=(const Uint& lhs, const int rhs) {
	return !(lhs == rhs);
}

bool operator!=(const Uint& lhs, const Uint rhs) {
	return !(lhs == rhs);
}

Uint &Uint::operator*=(const int rhs) {
	int report = 0;
	for (size_t i = nombre.size(); i > 0; --i) {
		nombre.at(i - 1) = nombre.at(i - 1) * rhs;
	}
	for (size_t i = nombre.size(); i > 0; --i) {
		int valeur = nombre.at(i - 1) + report;

		nombre.at(i - 1) = valeur % 10;
		report = valeur / 10;
	}
	if (report) {
		nombre.insert(nombre.begin(), report);
	}
	return *this;
}

Uint &Uint::operator*=(const Uint &rhs) {
	Uint resultat = 0;
	Uint temp = 0;
	int multiplicateur;
	for (size_t i = rhs.nombre.size(); i > 0; --i) {
		multiplicateur = rhs.nombre.at(i - 1) * std::pow(10, rhs.nombre.size() - i);
		temp = *this * multiplicateur;
		resultat = temp + resultat;
	}
	*this = resultat;

	return *this;
}

Uint operator*(Uint lhs, const Uint &rhs) {
	lhs *= rhs;
	return lhs;
}

Uint operator+(Uint lhs, Uint rhs) {
	int report = 0;
	int somme;

	if (rhs.nombre.size() > lhs.nombre.size()) {
		lhs.nombre.insert(lhs.nombre.begin(), rhs.nombre.size() - lhs.nombre.size(), 0);
	}
	if (lhs.nombre.size() > rhs.nombre.size()) {
		rhs.nombre.insert(rhs.nombre.begin(), lhs.nombre.size() - rhs.nombre.size(), 0);
	}
	for (size_t i = rhs.nombre.size(); i > 0; i--) {
		//Si l'avant dernière valeur de la suite est plus petite on ajuste le vecteur pour qu'ils soient de la même taille

		somme = lhs.nombre.at(i - 1) + rhs.nombre.at(i - 1) + report;
		report = somme / 10;
		somme = somme % 10;
		lhs.nombre.at(i - 1) = somme;
	}
	//Si au moment d'arriver à la valeur la plus grande il reste un carry, on l'ajoute au début du vecteur.
	if (report) {
		lhs.nombre.insert(lhs.nombre.begin(), report);
	}
	return lhs;
}

Uint operator-(Uint lhs, const Uint &rhs) {
	lhs -= rhs;
	return lhs;
}
Uint &Uint::operator-=(Uint rhs) {
	int difference;
	int report = 0;
	//Si l'avant dernière valeur de la suite est plus petite on ajuste le vecteur pour qu'ils soient de la même taille

	if (this->nombre.size() > rhs.nombre.size()) {
		rhs.nombre.insert(rhs.nombre.begin(), this->nombre.size() - rhs.nombre.size(), 0);
	}
	for (size_t i = rhs.nombre.size(); i > 0; i--) {
		if (this->nombre.at(i - 1) < rhs.nombre.at(i - 1)) {
			this->nombre.at(i - 1) += 10;
			difference = this->nombre.at(i - 1) - rhs.nombre.at(i - 1) - report;
			report = 1;
		} else {
			difference = this->nombre.at(i - 1) - rhs.nombre.at(i - 1) - report;
			report = 0;
		}

		this->nombre.at(i - 1) = difference;
	}
	if (!this->nombre.at(0) && this->nombre.size() > 1) {
		this->nombre.erase(this->nombre.begin(), this->nombre.begin() + 1);
	}
	return *this;
}

Uint operator/(Uint lhs, const Uint &rhs) {
	lhs /= rhs;
	return lhs;
}

Uint &Uint::operator/=(const Uint &rhs) {
	*this = this->division_reste(rhs);
	return *this;
}

std::ostream &operator<<(std::ostream &lhs, const Uint &rhs) {
	for (size_t i = 0; i < rhs.nombre.size(); ++i) {
		lhs << rhs.nombre.at(i);
	}
	return lhs;
}

Uint &Uint::operator++() {
	nombre.back() = nombre.back() + 1;
	for (size_t i = nombre.size() - 1; i > 0; i--) {
		if (nombre.at(i) == 10) {
			nombre.at(i) = 0;
			nombre.at(i - 1)++;
		}
	}
	if (nombre.at(0) == 10) {
		nombre.at(0) = 0;
		nombre.insert(nombre.begin(), 1);
	}
	return *this;
}

Uint &Uint::operator--() {
	if(this->nombre.back() > 0) {
		//Décrementer c'est facile si le dernier nombre != 0
		this->nombre.back() -= 1;
	} else {
		//Sinon, il faut s'assurer que le nombre n'est pas 0
		if (this->nombre.size() == 1) {
			//La convention Uint définie aujourd'hui retourne 0 si on fait --0
			return *this;
		}
		for (size_t i = this->nombre.size() - 2; i >= 0; --i) {
			//Si je peux retirer 1 à ma cellule
			if(this->nombre.at(i) != 0) {
				//On retire de la cellule
				this->nombre.at(i) -= 1;
				//On rajoute 9 aux suivantes
				for(size_t j = i; j < this->nombre.size() - 1; ++j) {
					this->nombre.at(j + 1) = 9;
				}
				this->fit();
				return *this;
			}
		}
	}
	return *this;
}

Uint Uint::operator--(int) {
	Uint temp = *this;
	--*this;
	return temp;
}

bool operator%(const Uint& lhs, const int rhs) {

}

bool operator%(const Uint& lhs, const Uint rhs) {

}

void Uint::division_par2() {
	int report = 0;
	int resultat;
	if (!(this->nombre.size() == 1 && this->nombre.at(0) == 1))
	{
		for (size_t i = 0; i < this->nombre.size(); i++) {
			resultat = (this->nombre.at(i) + report) / 2;

			if (this->nombre.at(i) % 2) {
				report = 10;
			} else {
				report = 0;
			}

			this->nombre.at(i) = resultat;
		}
		if (this->nombre.at(0) == 0) {
			this->nombre.erase(this->nombre.begin(), this->nombre.begin() + 1);
		}
	}
}

Uint Uint::division_reste(Uint diviseur) {
	Uint p2 = 1;
	Uint b = diviseur;
	Uint quotient = 0;
	Uint reste = *this;
	while (b <= *this) {
		p2 *= 2;
		b *= 2;
	}
	while (reste >= diviseur) {
		b.division_par2();
		p2.division_par2();

		if (reste >= b) {
			quotient = quotient + p2;
			reste = reste - b;
		}
	}
	return quotient;
}

void Uint::fit() {
	if(!this->nombre.at(0)) {
		size_t nbr_de_0 = 0;
		size_t i = 1;
		do {
			nbr_de_0++;
			if(this->nombre.at(i) != 0) {
				i = this->nombre.size();
			} else {
				i++;
			}
		} while(i < this->nombre.size());

		for(size_t j = nbr_de_0; j < this->nombre.size(); ++j) {
			this->nombre.at(j - nbr_de_0) = this->nombre.at(j);
		}
		this->nombre.resize(this->nombre.size() - nbr_de_0);
	}
}
 */