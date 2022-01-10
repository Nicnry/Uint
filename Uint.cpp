//
// Created by Nicolas Henry on 08.01.22.
//

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
	Uint temp = rhs;
	//Définir le plus petit pour éviter les overflows
	size_t difference_de_taille = 0;
	if(this->nombre.size() > rhs.nombre.size()) {
		difference_de_taille = this->nombre.size() - rhs.nombre.size();
		for(size_t i = 0; i < difference_de_taille; ++i) {
			temp.nombre.push_back(0);
		}
	} else {
		difference_de_taille = rhs.nombre.size() - this->nombre.size();
		for(size_t i = 0; i < difference_de_taille; ++i) {
			this->nombre.push_back(0);
		}
	}
	int report = 0;
	for(size_t i = 0; i < this->nombre.size(); ++i) {
		int somme = this->nombre.at(i) + temp.nombre.at(i) + report;
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
