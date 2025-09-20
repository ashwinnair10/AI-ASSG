#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

bool isZero(vector<int> &heaps)
{
    for (auto i : heaps)
    {
        if (i != 0)
            return false;
    }
    return true;
}

string convert(vector<int> heaps)
{
    string str = "";
    for (auto i : heaps)
    {
        str += to_string(i) + ".";
    }
    return str;
}

int minimax(vector<int> &heaps, int m, bool flag, unordered_map<string, int> &map, unordered_map<string, pair<int, int>> &moves, int alpha, int beta)
{
    if (isZero(heaps))
    {
        return flag ? 1 : -1;
    }
    string state = convert(heaps) + (flag ? "1" : "0");
    if (map.find(state) != map.end())
    {
        return map[state];
    }
    pair<int, int> move = {-1, -1};
    bool prune = false;
    int curr;
    if (flag)
    {
        int maxi = INT_MIN;
        for (int i = 0; i < m; i++)
        {
            for (int j = 1; j <= heaps[i]; j++)
            {
                heaps[i] -= j;
                curr = minimax(heaps, m, !flag, map, moves, alpha, beta);
                if (curr > maxi)
                {
                    maxi = curr;
                    move = {i, j};
                    moves[state] = move;
                    alpha = max(alpha, maxi);
                    if (alpha >= beta)
                        prune = true;
                }
                heaps[i] += j;
                if (prune)
                    break;
            }
            if (prune)
                break;
        }
        return map[state] = maxi;
    }
    else
    {
        int mini = INT_MAX;
        for (int i = 0; i < m; i++)
        {
            for (int j = 1; j <= heaps[i]; j++)
            {
                heaps[i] -= j;
                curr = minimax(heaps, m, !flag, map, moves, alpha, beta);
                if (curr < mini)
                {
                    mini = curr;
                    move = {i, j};
                    moves[state] = move;
                    beta = min(beta, mini);
                    if (alpha >= beta)
                        prune = true;
                }
                heaps[i] += j;
                if (prune)
                    break;
            }
            if (prune)
                break;
        }
        return map[state] = mini;
    }
}

int main()
{
    int m;
    cin >> m;
    int j;
    vector<int> heaps;
    unordered_map<string, int> map;
    unordered_map<string, pair<int, int>> moves;
    for (int i = 0; i < m; i++)
    {
        cin >> j;
        heaps.push_back(j);
    }
    auto start = high_resolution_clock::now();
    int val = minimax(heaps, m, true, map, moves, INT_MIN, INT_MAX);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    if (val == 1)
        cout << "Player 1 wins\n"
             << '\n';
    else
        cout << "Player 2 wins\n"
             << '\n';
    string state = convert(heaps);
    bool flag = true;
    while (!isZero(heaps))
    {
        string st = state + (flag ? "1" : "0");
        pair<int, int> p = moves[st];
        cout << "Player " << (flag ? "1" : "2") << " takes " << p.second << " sticks from heap " << p.first + 1 << '\n';
        cout << state << " --> ";
        heaps[p.first] -= p.second;
        state = convert(heaps);
        cout << state << "\n\n";
        flag = !flag;
    }
    cout << "\nTime taken : " << duration.count() << " ms\n";
    return 0;
}
