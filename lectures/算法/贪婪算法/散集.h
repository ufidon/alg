#ifndef _散集_H_
#define _散集_H_

typedef int 号;
typedef 号 集手;

struct 树节
{
    号 父;
    int 深度;
};

struct 木节
{
    号 父;
    int 深度;
    int 最小号;
};


class 散列集
{
private:
    int 集夵;
    号 *元列; // 元列[1..集夵]

public:
    散列集(int);
    散列集(const 散列集 &);
    ~散列集();

    集手 寻(号);
    void 并(集手, 集手);
    bool 同(集手, 集手);

    const 散列集 &operator=(const 散列集 &);
    号& operator[](号);
};

class 散树集
{
private:
    int 集夵;
    树节 *元列; // 元列[1..集夵]

public:
    散树集(int);
    散树集(const 散树集 &);
    ~散树集();

    集手 寻(号);
    void 并(集手, 集手);
    bool 同(集手, 集手);

    const 散树集 &operator=(const 散树集 &);
    号& operator[](号);
};

class 散木集
{
private:
    int 集夵;
    木节 *元列; // 元列[1..集夵]

public:
    散木集(int);
    散木集(const 散木集 &);
    ~散木集();

    集手 寻(号);
    void 并(集手, 集手);
    bool 同(集手, 集手);
    号& 取最小号(集手) const;

    const 散木集 &operator=(const 散木集 &);
    号& operator[](号);
};

#endif // _散集_H_