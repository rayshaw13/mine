#ifndef MINE_MAP
#define MINE_MAP
#include <vector>
#include <set>
using namespace std;

class MineMap
{
private:
    // 'M' 代表一个未挖出的地雷，'E' 代表一个未挖出的空方块，
    // 'B' 代表没有相邻（上，下，左，右，和所有4个对角线）地雷的已挖出的空白方块，
    // 数字（'1' 到 '8'）表示有多少地雷与这块已挖出的方块相邻，
    // 'X' 则表示一个已挖出的地雷。
    vector<vector<char>> mineMap;
    int mineNum;
    int height;
    int width;
    set<pair<int,int>> recovered;

    bool IsValid(const vector<vector<char>> &board, const vector<int>& point)
    {
        if(point.size()<2){
            return false;
        }
        if(point[0]>=0&&point[0]<board.size()&&point[1]>=0&&point[1]<board[0].size()) {
            return true;
        }
        return false;
    }
    int Arround(vector<vector<char>> &board, const vector<int>& point, char target)
    {
        int res=0;
        for(auto& dirc:directions) {
            auto nextPoint=point;
            nextPoint[0]=point[0]+dirc[0];
            nextPoint[1]=point[1]+dirc[1];
            if (IsValid(board,  nextPoint) && board[nextPoint[0]][nextPoint[1]]==target)
            {
                res++;
            }
            
        }
        return res;
    }
    vector<vector<int>> directions{{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
public:
    explicit MineMap(int height, int width, int num);
    ~MineMap();

    void GenerateMap();
    // 一次点击后揭示的地雷地图
    // 返回值
    // 0 正常
    // -1 触雷
    int RecoverOnClick(const vector<int> &click);
    // 插红旗标记
    void SetRedFlag(const vector<int> &click);

    void PrintMap();

    void PrintMapAll();

    int GetRecovered();
    int GetHeight();
    int GetWidth();
    int GetMineNum();
};
#endif
