// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if(len > 0){
		BitLen = len;
		MemLen = (int)(len/(sizeof(TELEM)*8));
		if((len%(sizeof(TELEM)*8)) > 0){
			MemLen++;
		}
		pMem =  new TELEM[MemLen];
		for(int i = 0; i < MemLen; i++){
			pMem[i] = 0;
		}
	}
	else{
		throw"Error";
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	for(int i = 0; i < MemLen; i++){
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	int index = (int)(n/((sizeof(TELEM))*8));
	if((n%(sizeof(TELEM))*8) > 0){
		index++;
	}
	return index;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM mask = 1;
	int position = (n%(sizeof(TELEM) * 8));
	mask = mask << position;                        //может быть -1
	return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
//return 0;
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	int index = GetMemIndex(n);
	int mask = GetMemMask(n);
	pMem[index] = pMem[index] | mask;     //логическое ИЛИ
}

void TBitField::ClrBit(const int n) // очистить бит
{
	int index = GetMemIndex(n);
	int mask = GetMemMask(n);
	pMem[index] = pMem[index] & (~mask); 
}

int TBitField::GetBit(const int n) const // получить значение бита
{
//return 0;
	int index = GetMemIndex(n);
	int mask = GetMemMask(n);
	return pMem[index] & mask;   //логическое И
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = bf.pMem;
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
//return 0;
	if(MemLen != bf.MemLen){
		return 0;
	}
	else
	{
		for(int i = 0; i < MemLen; i++){
			if(pMem[i] != bf.pMem[i]){
				return 0;
			}
		}
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
//return 0;
	if(MemLen == bf.MemLen){
		return 0;
	}
	else
	{
		for(int i = 0; i < MemLen; i++){
			if(pMem[i] == bf.pMem[i]){
				return 0;
			}
		}
	}
	return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField tmp(bf);
	for(int i = 0; i < MemLen; i++){
		tmp.pMem[i] = pMem[i] | bf.pMem[i];
	}
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField tmp(bf);
	for(int i = 0; i < MemLen; i++){
		tmp.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	//TBitField tmp(this);
	for(int i = 0; i < MemLen; i++){
		this->pMem[i] = ~pMem[i];
	}
	return *this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	char* tmp;
	//string str;
	cin >> tmp;
	//const char* tmp = .c_str();
	for(int i = 0; i < strlen(tmp); i++){
		if(tmp[i] == '1'){
			bf.SetBit(i);
		}
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for(int i = 0; i < bf.BitLen; i++){
		ostr << bf.GetBit(i);
	}
	return ostr;
}
