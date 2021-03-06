// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength())
{
	MaxPower = bf.GetLength();
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
	if (MaxPower == s.MaxPower && BitField == s.BitField)
		return 1;
	else
		return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (MaxPower == s.MaxPower && BitField == s.BitField)
		return 0;
	else
		return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int tmpsize;
	if (MaxPower >= s.MaxPower)
		tmpsize = MaxPower;
	else
		tmpsize = s.MaxPower;
	TSet tmp(tmpsize);
	tmp.BitField = BitField | s.BitField;
	return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet tmp(MaxPower);
	tmp.BitField = BitField;
	tmp.BitField.SetBit(Elem);
	return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet tmp(MaxPower);
	tmp.BitField = BitField;
	tmp.BitField.ClrBit(Elem);
	return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	int tmpsize;
	if (MaxPower >= s.MaxPower)
		tmpsize = MaxPower;
	else
		tmpsize = s.MaxPower;
	TSet tmp(tmpsize);
	tmp.BitField = BitField & s.BitField;
	return tmp;
}

TSet TSet::operator~(void) // дополнение
{
	TSet tmp(MaxPower);
	tmp.BitField = ~BitField;
	return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int tmpElem;
	do
	{
		cout << "Enter Set Elem" << endl;
		cin >> tmpElem;
		if (tmpElem >= 0 && tmpElem < s.MaxPower)
			s.InsElem(tmpElem);
		else
			cout << "wrong elem value";
	} while (tmpElem >= 0 && tmpElem < 0);
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	cout << "Set Power: " << s.MaxPower<<endl;
	cout << "Set: ";
	for (int i = 0; i < s.MaxPower; i++)
	{
		if(s.BitField.GetBit(i)==1)
			cout << i <<" ";
		else
		{
		}
	}
	return ostr;
}
