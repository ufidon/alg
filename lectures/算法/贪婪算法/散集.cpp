#include <stdexcept>
#include <cstdlib>
#include "散集.h"

散列集::散列集(int 夵)
{
    集夵 = 夵;
    元列 = new int[集夵 + 1];
    for (号 i = 1; i <= 集夵; i++)
    {
        元列[i] = i; // 倒树者根指己
    }
}

散列集::散列集(const 散列集 &某)
{
    集夵 = 某.集夵;
    元列 = new int[集夵 + 1];
    for (int i = 1; i <= 集夵; i++)
    {
        元列[i] = 某.元列[i];
    }
}

散列集::~散列集()
{
    if (元列 != 0)
    {
        delete[] 元列;
        元列 = 0;
    }
}

集手 散列集::寻(号 i)
{
    号 j;
    j = i;
    while (元列[j] != j)
    {
        j = 元列[j];
    }
    return j;
}

void 散列集::并(集手 p, 集手 q)
{
    if (p < q)
        元列[q] = p; // 倒树者子指父,小者为父
    else
        元列[p] = q;
}
bool 散列集::同(集手 p, 集手 q)
{
    return p == q;
}

const 散列集 &散列集::operator=(const 散列集 &某)
{
    if (this != &某)
    {
        集夵 = 某.集夵;
        delete[] this->元列;

        元列 = new int[集夵 + 1];
        for (int i = 1; i <= 集夵; i++)
        {
            元列[i] = 某.元列[i];
        }
    }
    return *this;
}
号 &散列集::operator[](号 i)
{
    if (i < 1 || i > 集夵)
    {
        throw std::out_of_range("号无效");
        std::exit(-1);
    }
    else
    {
        return 元列[i];
    }
}

//======================================================

散树集::散树集(int 夵)
{
    集夵 = 夵;
    元列 = new 树节[集夵 + 1];
    for (号 i = 1; i <= 集夵; i++)
    {
        元列[i].父 = i; // // 倒树者根指己
        元列[i].深度 = 0;
    }
}

散树集::散树集(const 散树集 &某)
{
    集夵 = 某.集夵;
    元列 = new 树节[集夵 + 1];
    for (int i = 1; i <= 集夵; i++)
    {
        元列[i] = 某.元列[i];
    }
}

散树集::~散树集()
{
    if (元列 != 0)
    {
        delete[] 元列;
        元列 = 0;
    }
}

集手 散树集::寻(号 i)
{
    号 j;
    j = i;
    while (元列[j].父 != j)
    {
        j = 元列[j].父;
    }
    return j;
}

void 散树集::并(集手 p, 集手 q)
{
    if (元列[p].深度 == 元列[q].深度)
    {
        元列[p].深度++; // 任取p为父，深度增一
        元列[q].父 = p;
    }
    else if (元列[p].深度 < 元列[q].深度)
        元列[p].父 = q; // 深者为父，浅者为子
    else
        元列[q].父 = p;
}

bool 散树集::同(集手 p, 集手 q)
{
    return p == q;
}

const 散树集 &散树集::operator=(const 散树集 &某)
{
    if (this != &某)
    {
        集夵 = 某.集夵;
        delete[] this->元列;

        元列 = new 树节[集夵 + 1];
        for (int i = 1; i <= 集夵; i++)
        {
            元列[i] = 某.元列[i];
        }
    }
    return *this;
}

号 &散树集::operator[](号 i)
{
    if (i < 1 || i > 集夵)
    {
        throw std::out_of_range("号无效");
        std::exit(-1);
    }
    else
    {
        return 元列[i].父;
    }
}

//======================================================

散木集::散木集(int 夵)
{
    集夵 = 夵;
    元列 = new 木节[集夵 + 1];
    for (号 i = 1; i <= 集夵; i++)
    {
        元列[i].父 = i; // // 倒树者根指己
        元列[i].深度 = 0;
        元列[i].最小号 = i;
    }
}

散木集::散木集(const 散木集 &某)
{
    集夵 = 某.集夵;
    元列 = new 木节[集夵 + 1];
    for (int i = 1; i <= 集夵; i++)
    {
        元列[i] = 某.元列[i];
    }
}

散木集::~散木集()
{
    if (元列 != 0)
    {
        delete[] 元列;
        元列 = 0;
    }
}

集手 散木集::寻(号 i)
{
    号 j;
    j = i;
    while (元列[j].父 != j)
    {
        j = 元列[j].父;
    }
    return j;
}

void 散木集::并(集手 p, 集手 q)
{
    if (元列[p].深度 == 元列[q].深度)
    {
        元列[p].深度++; // 任取p为父，深度增一
        元列[q].父 = p;
    }
    else if (元列[p].深度 < 元列[q].深度)
    {

        元列[p].父 = q; // 深者为父，浅者为子
        if (元列[p].最小号 < 元列[q].最小号)
        {
            元列[q].最小号 = 元列[p].最小号; // 最小号存于根
        }
    }
    else
    {
        元列[q].父 = p;
        if (元列[q].最小号 < 元列[p].最小号)
        {
            元列[p].最小号 = 元列[q].最小号;
        }
    }
}

bool 散木集::同(集手 p, 集手 q)
{
    return p == q;
}

const 散木集 &散木集::operator=(const 散木集 &某)
{
    if (this != &某)
    {
        集夵 = 某.集夵;
        delete[] this->元列;

        元列 = new 木节[集夵 + 1];
        for (int i = 1; i <= 集夵; i++)
        {
            元列[i] = 某.元列[i];
        }
    }
    return *this;
}

号 &散木集::operator[](号 i)
{
    if (i < 1 || i > 集夵)
    {
        throw std::out_of_range("号无效");
        std::exit(-1);
    }
    else
    {
        return 元列[i].父;
    }
}

号& 散木集::取最小号(集手 p) const
{
    return 元列[p].最小号;
}