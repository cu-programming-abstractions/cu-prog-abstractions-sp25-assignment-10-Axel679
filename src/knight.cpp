#include "knight.h"
#include <algorithm>
#include <cmath>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/* -------- minKnightMoves -------- */
int minKnightMoves(const Pos& start, const Pos& target) {
    if (start == target) return 0;

    vector<pair<int, int>> directions = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };

    unordered_set<Pos, PosHash> visited;
    queue<pair<Pos, int>> q;

    q.push({start, 0});
    visited.insert(start);

    while (!q.empty()) {
        auto [current, dist] = q.front();
        q.pop();

        for (auto [dr, dc] : directions) {
            Pos next = {current.row + dr, current.col + dc};
            if (next == target) return dist + 1;

            if (visited.count(next) == 0) {
                visited.insert(next);
                q.push({next, dist + 1});
            }
        }
    }
    return -1;
}

/* -------- getKnightPath -------- */
vector<Pos> getKnightPath(const Pos& start, const Pos& target) {
    if (start == target) return {start};

    vector<pair<int, int>> directions = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };

    unordered_map<Pos, Pos, PosHash> parent;
    unordered_set<Pos, PosHash> visited;
    queue<Pos> q;

    q.push(start);
    visited.insert(start);

    bool found = false;

    while (!q.empty() && !found) {
        Pos current = q.front();
        q.pop();

        for (auto [dr, dc] : directions) {
            Pos next = {current.row + dr, current.col + dc};
            if (visited.count(next)) continue;

            parent[next] = current;

            if (next == target) {
                found = true;
                break;
            }

            visited.insert(next);
            q.push(next);
        }
    }

    vector<Pos> path;
    if (!found) return path;

    for (Pos p = target; p != start; p = parent[p]) {
        path.push_back(p);
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

/* -------- isValidPosition -------- */
bool isValidPosition(const Pos& pos, int boardSize) {
    if (boardSize == -1) {
        return true;
    }
    
    return pos.row >= 0 && pos.row < boardSize && 
           pos.col >= 0 && pos.col < boardSize;
}
