// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля
// 
#include "tset.h"

TSet::TSet(int mp) : BitField(-1)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(-1)
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(-1)
{
	BitField = bf;
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
  //  return 0;
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
   // return 0;
	if(MaxPower != s.MaxPower){
		return 0;
	}
	else{
		if(BitField != s.BitField){
			return 0;
		}
	}
	return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if(MaxPower == s.MaxPower){
		return 0;
	}
	else{
			if(BitField == s.BitField){
				return 0;
			}
		}
		return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet tmp(s.MaxPower);
	tmp = BitField | s.BitField;
	return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet tmp(MaxPower);
	if(Elem > MaxPower){
		throw "Error";
	}
	else{
	    BitField.SetBit(Elem);
		tmp = BitField;
	}
	return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet tmp(MaxPower);
	if(Elem > MaxPower){
		throw "Error";
	}
	else{
		BitField.ClrBit(Elem);
		tmp = BitField;
	}
	return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet tmp(s.MaxPower);
	tmp = BitField & s.BitField;
	return tmp;
}

TSet TSet::operator~(void) // дополнение
{
	BitField = ~BitField;
	return BitField;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	istr >> s.BitField;
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.BitField;
	return ostr;
}
