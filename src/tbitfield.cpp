// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len>0)
	{
		BitLen=len;
		MemLen=1+BitLen/(sizeof(TELEM)*8);
		pMem=new TELEM [MemLen];
		for (int i=0; i<MemLen; i++)
			pMem[i]=0;
	}
	else
	{
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen=bf.MemLen;
	BitLen=bf.BitLen;
	pMem=new TELEM [MemLen];
	for(int i=0; i<MemLen; i++)
		pMem[i]=bf.pMem[i];
}

TBitField::~TBitField()
{
	delete [] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n/(sizeof(TELEM)*8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM mask=1;
	return mask<<=n;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	pMem[GetMemIndex(n)]|= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	pMem[GetMemIndex(n)]&=~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	TELEM tmp=pMem[GetMemIndex(n)];
	tmp|= GetMemMask(n);
	if(tmp==pMem[GetMemIndex(n)])
		return 1;
	else
		return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen=bf.BitLen;
	MemLen=bf.MemLen;
	pMem=new TELEM [MemLen];
	for (int i=0; i<MemLen; i++)
			pMem[i]=bf.pMem[i];
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int flag=0;
	if (BitLen==bf.BitLen && MemLen==bf.MemLen)
	{
		for (int i=0; i<MemLen; i++)
			if(pMem[i]==bf.pMem[i])
			{
				flag=1;
			}
			else
			{
				flag=0;
				break;
			}
	}
  return flag;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int flag=1;
	if (BitLen==bf.BitLen && MemLen==bf.MemLen)
	{
		for (int i=0; i<MemLen; i++)
			if(pMem[i]==bf.pMem[i])
			{
				flag=0;
			}
			else
			{
				flag=1;
				break;
			}
	}
  return flag;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField tmp(BitLen);
	for (int i=0; i<MemLen; i++)
	{
		tmp.pMem[i]=pMem[i]|bf.pMem[i];
	}
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField tmp(BitLen);
	for (int i=0; i<MemLen; i++)
	{
		tmp.pMem[i]=pMem[i]&bf.pMem[i];
	}
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for (int i=0; i<MemLen; i++)
	{
		tmp.pMem[i]=~pMem[i];
	}
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
}

