// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#define TELEMSIZE sizeof(TELEM) * 8

TBitField::TBitField(int len)
{
	if (len > 0)
	{
		BitLen = len;
		MemLen = 1 + BitLen / (TELEMSIZE);
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else
	{
		throw len;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n >= 0 && n<BitLen)
	{
		return n / (TELEMSIZE);
	}
	else
	{
		throw n;
	}
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n >= 0)
	{
		TELEM mask = 1;
		return mask << n;
	}
	else
	{
		throw n;
	}

}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= 0 && n < BitLen)
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	else
		throw n;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= 0 && n < BitLen)
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	else
		throw n;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= 0 && n<BitLen)
	{
		TELEM tmp = pMem[GetMemIndex(n)];
		if (pMem[GetMemIndex(n)] == (tmp |= GetMemMask(n)))
			return 1;
		else
			return 0;
	}
	else
	{
		throw n;
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	delete[] pMem;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (MemLen == bf.MemLen && BitLen == bf.BitLen)
	{
		int flag = 1;
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] == bf.pMem[i])
			{
				flag = 1;
			}
			else
			{
				flag = 0;
				break;
			}
		return flag;
	}
	else
	{
		return 0;
	}
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (MemLen == bf.MemLen && BitLen == bf.BitLen)
	{
		int flag = 0;
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] == bf.pMem[i])
			{
				flag = 0;
			}
			else
			{
				flag = 1;
				break;
			}
		return flag;
	}
	else
	{
		return 1;
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int tmpsize;
	if (BitLen >= bf.BitLen)
	{
		tmpsize = BitLen;
	}
	else
	{
		tmpsize = bf.BitLen;
	}
	TBitField tmp1(tmpsize), tmp2(tmpsize);
	for (int i = 0; i < MemLen; i++)
		tmp1.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		tmp2.pMem[i] = bf.pMem[i];
	for (int i = 0; i < tmp1.MemLen; i++)
		tmp1.pMem[i] |= tmp2.pMem[i];
	return tmp1;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int tmpsize;
	if (BitLen >= bf.BitLen)
	{
		tmpsize = BitLen;
	}
	else
	{
		tmpsize = bf.BitLen;
	}
	TBitField tmp1(tmpsize), tmp2(tmpsize);
	for (int i = 0; i < MemLen; i++)
		tmp1.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		tmp2.pMem[i] = bf.pMem[i];
	for (int i = 0; i < tmp1.MemLen; i++)
		tmp1.pMem[i] &= tmp2.pMem[i];
	return tmp1;

}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for (int i = 0; i < MemLen; i++)
		tmp.pMem[i] = ~pMem[i];
	for (int i = TELEMSIZE - ( ( MemLen*TELEMSIZE ) - BitLen ); i < TELEMSIZE; i++)
	{
		tmp.pMem[MemLen - 1] &= (~(1 << i));
	}
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int bit;
	cout << "Enter a set of bits" << endl;
	for (int i = 0; i < bf.BitLen; i++)
	{
		cout << "Enter " << i << " bit" << endl;
		do
		{
			cin >> bit;
			if (bit != 0 || bit != 1)
			{
				cout << "Wrong bit value! Re-enter " << i << " bit!" << endl;
			}
		} while (bit != 0 || bit != 1);
		if (bit == 1)
		{
			bf.SetBit(i);
		}
		else
		{
			bf.ClrBit(i);
		}
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		cout << bf.GetBit(i);
	}
	return ostr;
}
