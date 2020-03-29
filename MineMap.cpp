#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>
#include <stack>
#include "MineMap.h"
#include "wchar.h"
#include <map>

vector<vector<int>> MineMap::directions={{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};


MineMap::MineMap(int h, int w, int num):
    height(h),width(w),mineNum(num)
{
    vector<char> tmp(width,'E');
    mineMap.assign(height, tmp);
    GenerateMap();
}

MineMap::~MineMap()
{
}

void MineMap::GenerateMap()
{
    int len=mineMap.size()*mineMap[0].size();
    srand((int)time(nullptr));
    for (size_t i = 0; i < mineNum; i++)
    {
        int ran = rand()%len;
        int ranHeight = ran / mineMap[0].size();
        int ranWidth = ran % mineMap.size();
        mineMap[ranHeight][ranWidth] = 'M';
    }
    
}

int GetPosNum(int num)
{
    int posnum=0;
    while (num)
    {
        num/=10;
        posnum++;
    }
    return posnum;

}
void MineMap::PrintMap()
{
    std::cout<<"_|";
    for(size_t i = 0; i < mineMap[0].size(); i++)
    {
       wprintf(L"%2d",i);
    }
    std::cout<<std::endl;
    int posnum = GetPosNum(mineMap.size());
    for (size_t i = 0; i < mineMap.size(); i++)
    {
        printf("%*d|",posnum,i);
        for (size_t j = 0; j < mineMap[i].size(); j++)
        {
            char str;
            if(mineMap[i][j]=='M'||mineMap[i][j]=='E') {
                str='E';
            }else if(mineMap[i][j]=='B') {
                str='B';
            }else
            {
                str=mineMap[i][j];
            }
            
            printf("%2c",str);
        }
        std::cout << std::endl;
    }
}
void MineMap::PrintMapAll()
{
    for (size_t i = 0; i < mineMap.size(); i++)
    {
        for (size_t j = 0; j < mineMap[i].size(); j++)
        {
            char tmp = mineMap[i][j];
            std::cout << tmp << " ";
        }
        std::cout << std::endl;
    }
}

int MineMap::RecoverOnClick(const vector<int> &click)
{
    if(!IsValid(mineMap,click)) {
        return 1;
    }
    if (mineMap[click[0]][click[1]] == 'M')
    {
        mineMap[click[0]][click[1]] = 'X';
        return -1;
    }
    int arr = Arround(mineMap, click, 'M');
    if (arr > 0)
    {
        mineMap[click[0]][click[1]] = arr + '0';
        recovered.insert(make_pair(click[0],click[1]));
        return 0;
    }
    stack<vector<int>> st;
    if (arr == 0)
    {
        mineMap[click[0]][click[1]] = 'B';
        recovered.insert(make_pair(click[0], click[1]));
        st.push(click);
        while (!st.empty())
        {
            auto p = st.top();
            st.pop();
            for (auto &dirc : directions)
            {
                auto nextClick = p;
                nextClick[0] = p[0] + dirc[0];
                nextClick[1] = p[1] + dirc[1];
                if (IsValid(mineMap, nextClick) && mineMap[nextClick[0]][nextClick[1]] == 'E')
                {
                    int arrtmp = Arround(mineMap, nextClick, 'M');
                    if (arrtmp > 0)
                    {
                        mineMap[nextClick[0]][nextClick[1]] = arrtmp + '0';
                        recovered.insert(make_pair(nextClick[0], nextClick[1]));
                    }
                    else if (arrtmp == 0)
                    {
                        mineMap[nextClick[0]][nextClick[1]] = 'B';
                        recovered.insert(make_pair(nextClick[0], nextClick[1]));
                        st.push(nextClick);
                    }
                }
            }
        }
    }
    return 0;
}

int MineMap::GetRecovered()
{
    return recovered.size();
}
int MineMap::GetHeight()
{
    return height;
}
int MineMap::GetWidth()
{
    return width;
}
int MineMap::GetMineNum()
{
    return mineNum;
}

inline bool MineMap::IsValid(const vector<vector<char>> &board, const vector<int> &point)
{
    if (point.size() < 2)
    {
        return false;
    }
    if (point[0] >= 0 && point[0] < board.size() && point[1] >= 0 && point[1] < board[0].size())
    {
        return true;
    }
    return false;
}

inline int MineMap::Arround(vector<vector<char>> &board, const vector<int> &point, char target)
{
    int res = 0;
    for (auto &dirc : directions)
    {
        auto nextPoint = point;
        nextPoint[0] = point[0] + dirc[0];
        nextPoint[1] = point[1] + dirc[1];
        if (IsValid(board, nextPoint) && board[nextPoint[0]][nextPoint[1]] == target)
        {
            res++;
        }
    }
    return res;
}