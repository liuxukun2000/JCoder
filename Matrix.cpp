//
// Created by 32678 on 2020/12/6.
//


#include <iostream>
#include <cstdio>
#include<cstring>
#include <atomic>
#include "Matrix.h"
#include<cstdlib>
#include<cstdio>
#include<sstream>
using namespace std;

string Matrix::to_string(float Num)
{
    ostringstream oss;
    oss<<Num;
    string str(oss.str());
    return str;
}

Matrix::Matrix()
    {
        //cout<<"new: "<<num<<endl;
    }
Matrix::Matrix(int x, int y)
    {
        this->x = x;
        this->y = y;
        this->matrix = new float[x * y];
        //cout<<"pre:"<<&num<<endl;
        memset(matrix, 0, sizeof(float)*x*y);
        num = new int;
        *num = 1;
        //cout<<"new: "<<num<<endl;
    }
Matrix::Matrix(const Matrix &b)
    {
        this->x = x;
        this->y = y;
        this->matrix = new float[x * y];
        num = new int;
        *num = 1;
        int l=x*y;
        for(int i=0;i<l;i++)
        {
            matrix[i]=b.matrix[i];
        }
    }
bool Matrix:: clone(const Matrix &b)
    {
        if(x!=b.x||y!=b.y) return false;
        num = new int;
        *num = 1;
        int l=x*y;
        for(int i=0;i<l;i++)
        {
            matrix[i]=b.matrix[i];
        }
        return true;
    }
Matrix::~Matrix()
    {
        //*num = *num - 1;
        //_MT_DECR(*num);
        __sync_fetch_and_sub(num,1);
        if (*num <= 0)
        {
            cout << "del:" << endl;
            cout << matrix << endl;
            cout << num << endl;
            delete[] matrix;
        }
    }
    void Matrix::operator=(const Matrix &b)
    {

        if (num == b.num)
        {
            return;
        }

        x = b.x;
        y = b.y;
        //*num = *num - 1;
        //_MT_DECR(*num);
        __sync_fetch_and_sub(num,1);
        if (*num == 0)
        {

            delete[] matrix;
            delete num;
        }
        num = b.num;
        //_MT_INCR(*num);
        __sync_fetch_and_add(num,1);
        matrix = b.matrix;
        //*num += 1;
    }
    void Matrix::oo()
    {
        cout << "m: " << matrix << endl;
        cout << "n: " << num << endl;
    }
void Matrix::operator*=(const Matrix &b)
{
    *this = *this * b;
}
void Matrix::operator+=(const Matrix &b)
{
    *this = *this + b;
}
void Matrix::operator-=(const Matrix &b)
{
    *this = *this - b;
}
    Matrix Matrix::operator+(const Matrix &b)
    {
        Matrix ans(x, y);
        if (this->x != b.x || this->y != b.y)
        {
            return ans;
        }

        int l = x * y;
        for (int i = 0; i < l; i++)
        {
            ans.matrix[i] = matrix[i] + b.matrix[i];
        }
        return ans;
    }
    Matrix Matrix::operator-(const Matrix &b)
    {
        Matrix ans(x, y);
        if (this->x != b.x || this->y != b.y)
        {
            return ans;
        }

        int l = x * y;
        for (int i = 0; i < l; i++)
        {
            ans.matrix[i] = matrix[i] - b.matrix[i];
        }
        return ans;
    }
    Matrix Matrix::operator*(const Matrix &b)
    {
        Matrix ans(this->x, b.y);
        if (this->y != b.x)
            return ans;
        for (int i = 0; i < x; i++)
        {
            for (int k = 0; k < x; k++)
            {
                for (int j = 0; j < b.y; j++)
                {
                    ans.matrix[i * b.y + j] += (this->matrix[i * y + k] * b.matrix[k * b.y + j]);
                }
            }
        }
        return ans;
    }
    Matrix Matrix::operator^(const long long &b)
    {
        Matrix ans(x, y), B(x, y);
        B.clone(*this);
        if (x != y)
        {
            return ans;
        }
        long long a = b;
        for (int i = 0; i < x; i++)
        {
            ans.matrix[i * y + i] = 1;
        }
        //ans.out();
        while (a)
        {
            if (a & 1)
            {
                //ans.out();
                ans = ans * B;
                ans.out();
            }
            B = B * B;
            //B.out();
            a >>= 1;
        }
        return ans;
    }
    Matrix operator*(const float &x, const Matrix &b)
    {
        Matrix ans(b.x, b.y);
        for (int i = 0; i < b.x; i++)
        {
            for (int j = 0; j < b.y; j++)
            {
                ans.matrix[i * b.y + j] = b.matrix[i * b.y + j] * x;
            }
        }
        return ans;
    }
    Matrix operator*(const Matrix &b, const float &x)
    {
        Matrix ans(b.x, b.y);
        //cout << "ans: " << ans.matrix << endl;
        for (int i = 0; i < b.x; i++)
        {
            for (int j = 0; j < b.y; j++)
            {
                ans.matrix[i * b.y + j] = b.matrix[i * b.y + j] * x;
            }
        }
        return ans;
    }
    std::ostream& operator<< (std::ostream& os,const Matrix& b)
    {
        string ans;
        for (int i = 0; i < b.x; i++)
        {
            for (int j = 0; j < b.y; j++)
            {
                ans+=to_string(b.matrix[i * b.y + j]);
                ans+=' ';
            }
            ans+='\n';
        }
        os<<ans<<endl;
        return os;
    }
    bool Matrix::operator==(const Matrix &b)
    {
        if (x != b.y || y != b.y)
            return false;
        int l = x * y;
        for (int i = 0; i < l; i++)
        {
            if (matrix[i] != b.matrix[i])
                return false;
        }
        return true;
    }
    bool Matrix::operator!=(const Matrix &b)
    {
        return !(*this == b);
    }
    void Matrix::resize(int X, int Y)
    {
        if (X <= 0 || Y <= 0)
            return;
        float *tmp = new float[X * Y];
        for (int i = 0; i < min(x, X); i++)
        {
            for (int j = 0; j < min(Y, y); j++)
            {
                tmp[i * Y + j] = matrix[i * min(y, Y) + j];
            }
        }
        delete[] matrix;
        matrix = new float[X * Y];
        memcpy(matrix, tmp, sizeof(float) * X * Y);
        x = X;
        y = Y;
        delete[] tmp;
    }
    void Matrix::set(int v)
    {

        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {
                matrix[i * y + j] = v;
            }
        }
    }
    string Matrix::out()
    {
        string ans;
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {
                ans+=to_string(matrix[i * y + j]);
                ans+=' ';
            }
            ans+='\n';
        }
        return ans;
    }
