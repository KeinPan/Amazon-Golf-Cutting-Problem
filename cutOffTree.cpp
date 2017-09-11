class Solution {
public:
    // idea : 扫一遍，用hash存树的高度与坐标，然后按照顺序进行BFS，计算从目前高度到下一个高度最短步数，累加
    vector<int> dir = {1,0,-1,0,1};
    
    int bfs(vector<vector<int>>& forest, unordered_map<int, pair<int,int>> &hash, int &h1, int &h2){
        int m = forest.size(), n = forest[0].size();
        int i = hash[h1].first, j = hash[h1].second;    // starting point
        if(hash[h2].first == i && hash[h2].second == j) return 0;
        int steps = 0;
        vector<vector<int>> visited(m, vector<int> (n, 0));
        queue<pair<int,int>> q;
        q.push({i, j});
        visited[i][j] = 1;
        while(!q.empty()){
            int sz = q.size();
            steps++;
            while(sz-->0){
                // get top, pop, check 4, update sth
                int x = q.front().first, y = q.front().second;
                q.pop();
                for(int index = 0; index < 4; ++index){
                    int x1 = x + dir[index], y1 = y + dir[index+1];
                    if(x1< 0||x1>=m||y1<0||y1>=n||forest[x1][y1] == 0||visited[x1][y1]) continue;         
                    // inside, not visited, and not 0
                    if(forest[x1][y1] == h2) return steps;
                    visited[x1][y1] = 1;
                    q.push({x1,y1}); 
                }// for index
            }// while
        }
        return -1;
    }
    
    int cutOffTree(vector<vector<int>>& forest) {
        int m = forest.size(), n = forest[0].size(), res = 0;
        vector<int> height = {1};
        unordered_map< int, pair<int, int> > hash = {{1,{0,0}}};
        // step1. scan and record
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(forest[i][j] > 1){
                    height.push_back(forest[i][j]);
                    hash[forest[i][j]] = {i, j};
                }
            }
        }
        
        // 2. sort height
        int pos = 0;
        sort(height.begin(), height.end());
        if(forest[0][0] == height[1]){
            pos = 2;
        }
        else pos = 1;
        
        // 3. bfs for every neighborhood pairs
        for(int i = pos; i < height.size(); ++i){
            int tmp = bfs(forest, hash, height[i-1], height[i]);
            if(tmp > 0)  res += tmp;
            else return -1;
        }
        return res;
    }
};
