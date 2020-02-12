#include "stdlib.h"
#include "time.h"
#include <iostream>
#include <stack>
#include "MineMap.h"


MineMap::MineMap(int height, int width, int num):
    mineNum(num)
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
        int ranHeight = ran / mineMap.size();
        int ranWidth = ran % mineMap[0].size();
        mineMap[ranHeight][ranWidth] = 'M';
    }
    
}

void MineMap::PrintMap()
{
    for (size_t i = 0; i < mineMap.size(); i++)
    {
        for (size_t j = 0; j < mineMap[i].size(); j++)
        {
            std::cout<<mineMap[i][j]<<" ";
        }
        std::cout<<std::endl;  
    }
    
}
int MineMap::RecoverOnClick(const vector<int>& click)
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
        return 0;
    }
    stack<vector<int>> st;
    if (arr == 0)
    {
        mineMap[click[0]][click[1]] = 'B';
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
                    }
                    else if (arrtmp == 0)
                    {
                        mineMap[nextClick[0]][nextClick[1]] = 'B';
                        st.push(nextClick);
                    }
                }
            }
        }
    }
    return 0;
}