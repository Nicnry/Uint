//
// Created by Nicolas Henry on 08.01.22.
//

#ifndef LABO30_UINT_HPP
#define LABO30_UINT_HPP

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using Nombre = std::vector<int>;

class Uint {
	friend std::ostream& operator<<(std::ostream& lhs, const Uint& rhs);
	friend Uint operator*(Uint lhs, const size_t& rhs);
	friend Uint operator+(Uint lhs, const Uint& rhs);
	friend Uint operator-(Uint lhs, Uint &rhs);
	friend Uint operator-(Uint lhs, const size_t &rhs);
	friend bool operator<(const Uint& lhs, const Uint& rhs);
	friend bool operator>(const Uint& lhs, const Uint& rhs);
	friend bool operator<=(const Uint& lhs, const Uint& rhs);
	friend bool operator>=(const Uint& lhs, const Uint& rhs);
	friend bool operator==(const Uint& lhs, const Uint& rhs);
	friend bool operator!=(const Uint& lhs, const Uint& rhs);
	friend Uint operator/(Uint lhs, const Uint &rhs);
public:
	Uint();
	Uint(std::string);
	Uint(size_t);
	Uint division_reste(Uint diviseur);

	Uint& operator+=(const Uint& rhs);
	Uint& operator-=(Uint& rhs);
	Uint& operator-=(const size_t& rhs);
	Uint& operator*=(int& rhs);
	Uint& operator++();
	const Uint operator++(int);
	Uint &operator/=(const Uint &rhs);

	Uint &operator*=(const Uint &rhs);
	Uint& division_par2();
private:
	Nombre nombre;
	//void division_par2();

};
/*
class Uint {
	friend std::ostream &operator<<(std::ostream &lhs, const Uint &rhs);
	friend Uint operator*(Uint lhs, const int &rhs);
	friend Uint operator*(Uint lhs, const Uint &rhs);
	friend Uint operator+(Uint lhs, Uint rhs);
	friend Uint operator-(Uint lhs, const Uint &rhs);
	friend Uint operator/(Uint lhs, const Uint &rhs);
	friend bool operator<(const Uint &lhs, const Uint &rhs);
	friend bool operator>(const Uint &lhs, const Uint &rhs);
	friend bool operator<=(const Uint &lhs, const Uint &rhs);
	friend bool operator>=(const Uint &lhs, const Uint &rhs);
	friend bool operator==(const Uint& lhs, const int rhs);
	friend bool operator==(const Uint& lhs, const Uint rhs);
	friend bool operator!=(const Uint& lhs, const int rhs);
	friend bool operator!=(const Uint& lhs, const Uint rhs);
	friend bool operator%(const Uint& lhs, const int rhs);
	friend bool operator%(const Uint& lhs, const Uint rhs);


private:
	std::vector<int> nombre;
	void division_par2();
	//bool taille_identique(Uint nombre);
	void fit();
public:
	Uint();
	Uint(std::string nombre);
	Uint(uint64_t nombre);
	Uint &operator*=(const int rhs);
	Uint &operator*=(const Uint &rhs);
	Uint &operator-=(Uint rhs);
	Uint &operator/=(const Uint &rhs);
	Uint division_reste(Uint diviseur);

	Uint &operator++();
	Uint &operator--();
	Uint operator--(int);
	std::string get_valeur();
};

*/

#endif //LABO30_UINT_HPP
