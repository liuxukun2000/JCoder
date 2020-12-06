#ifndef Matrix_H
#define Matrix_H
#include<iostream>
#include<cstring>
#include <atomic>

class Matrix
{
private:
    int x = 0, y = 0;
    float *matrix = nullptr;
    int *num = nullptr;

public:
    Matrix();

    Matrix(int x, int y);

    Matrix(const Matrix &b);

    bool clone(const Matrix &b);

    ~Matrix();

    void operator=(const Matrix &b);

    void oo();

    Matrix operator+(const Matrix &b);

    Matrix operator-(const Matrix &b);

    Matrix operator*(const Matrix &b);

    Matrix operator^(const long long &b);

    friend Matrix operator*(const float &x, const Matrix &b);

    friend Matrix operator*(const Matrix &b, const float &x);

    friend std::ostream& operator <<(std::ostream& os,const Matrix& b);

    bool operator==(const Matrix &b);

    bool operator!=(const Matrix &b);

    void resize(int X, int Y);

    void set(int v);

    std::string out();

    std::string to_string(float Num);

    void operator*=(const Matrix &b);

    void operator+=(const Matrix &b);

    void operator-=(const Matrix &b);
};
#endif