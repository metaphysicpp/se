#ifndef __YL_KEYRECOMMANDER_H__
#define __YL_KEYRECOMMANDER_H__

#include "Dictionary.h"
#include "../../Reactor/TcpServer.h"
#include "../../Reactor/ThreadPool.h"
#include <queue>

using std::priority_queue;

struct MyResult {
    string _word;
    int _dist;
    int _freq;
};

struct MyCompare {
    bool operator()(MyResult lhs, MyResult rhs)
    {
        if(lhs._dist != rhs._dist)
        {
            return lhs._dist < rhs._dist;
        } else {
            return lhs._freq < rhs._freq;
        }
    }
};

class KeyRecommander
{
public:
    //构造函数
    //KeyRecommander(const string &query, const TcpConnectionPtr& conn);
    //构造函数
    KeyRecommander();
    //执行查询
    void execute(const string &query);
    //查询索引
    void queryIndexTable(const string &query);
    //进行计算
    void statistic(set<int> &iset, const string &query);
    //计算最小编辑距离
    int distance(const string &rhs, const string &query);
    //响应客户端请求
    vector<string> response();
private:
    //string _queryWord;  //查询词
    TcpConnectionPtr _conn; //与客户端进行连接的文件描述符
    //保存候选结果集的优先级队列    
    priority_queue<MyResult, vector<MyResult>, MyCompare> _resultQue;   
};

#endif
