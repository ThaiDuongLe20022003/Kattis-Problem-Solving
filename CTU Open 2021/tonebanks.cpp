#include <bits/stdc++.h>

using namespace std;

#define FOR(a, b, c) for(int a = b; a < c; a++)

const int N = 102;

bool mapa[N][N];
int id[N][N];

const int DX[] = {0, 0, 1, -1};
const int DY[] = {1, - 1, 0 ,0};


map<int, vector<pair<int,int> > > idToPos;

void flood(int sy, int sx, int idx, bool val) {
    queue<pair<int,int> > kol;
    
    kol.push({sy, sx});
    id[sy][sx] = idx;
    idToPos[idx] = {};
    
    
    while(kol.size()) {
        int y = kol.front().first;
        int x = kol.front().second;
        idToPos[idx].push_back({y, x});
        kol.pop();
        
        for(int d = 0; d < 4; ++d) {
            int ny = y + DY[d];
            int nx = x + DX[d];
            
            if(mapa[ny][nx] != val) continue;
            if(id[ny][nx] != 0) continue;
            
            id[ny][nx] = idx;
            kol.push({ny, nx});
        
        }
    }
    sort(idToPos[idx].begin(), idToPos[idx].end());
}

void print(int h, int w) {
    for(int y = 1; y <= h; ++y) {
        for(int x = 1; x <= w; ++x) {
            cout << setw(3) << id[y][x] << ' ';
        }
        cout << '\n';
    }
}

string s;
void decode(int sy, int sx) {
    int idx = id[sy][sx];
    
    set<int> visited;
    vector<pair<int,int> > order;
    
    for(auto pos : idToPos[idx]) {
        int y = pos.first;
        int x = pos.second;
        
        for(int d = 0; d < 4; ++d) {
            int nx = x + DX[d];
            int ny = y + DY[d];
            
            if(id[ny][nx] <= idx) continue;
            
            if (visited.count(id[ny][nx]) == 0) {
                visited.insert(id[ny][nx]);
                order.push_back({ny, nx});
            }
        }
    }
    
    if(visited.size())
        s += 'a' + visited.size() - 1;

    for(auto pos : order) decode(pos.first, pos.second);
    
}

int sx = 2000;
int sy = 2000;
int ex = 2000;
int ey = 2060;

char mapka[3000][3000];

void create(char let, bool isHash) {
    char c = '.';
    char oth = '#';
    if (isHash) {
        c = '#';
        oth = '.';
    }
    
    if (let == 'a') {
        for(int i = sx - 1; i <= ex + 1; ++i) {
                mapka[sy - 1][i] = c;
                mapka[ey + 1][i] = c;
        }
        
        for(int i = sy - 3; i <= ey + 1; ++i) {
            mapka[i][ex + 1] = c;
            mapka[i][sx - 1] = c;
        }
        sx--;
        sy--;
        ex++;
        ey++;
        return;
        
    }
    
    for(int i = sx - 3; i <= ex + 1; ++i) {
            mapka[sy - 1][i] = c;
            mapka[ey + 1][i] = c;
    }
        
    
    for(int i = sy; i <= ey; ++i) {
        mapka[i][ex + 1] = c;
        mapka[i][sx - 1] = c;
        mapka[i][sx - 3] = c;
        mapka[i][sx - 2] = oth;
    }
    
    
    int cnt = let - 'a' - 1;
    for(int i = 0; i < cnt; ++i) {
        mapka[sy + 2 * i + 1][sx - 2] = c;
    }
    
    sx -= 3;
    sy--;
    ex++;
    ey++;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    
    int height, width;
    cin >> height >> width;
    
    for(int i = 0; i < height; ++i) {
        string s;
        cin >> s;
        for(int j = 0; j < width; ++j) {
            mapa[i + 1][j + 1] = (s[j] == '#');
        }
    }
    int cnt = 0;
    for(int i = 1; i <= height; ++i) {
            for(int j = 1; j <= width; ++j) {
                if(id[i][j] != 0) continue;
                
                cnt++;
                flood(i, j, cnt, mapa[i][j]);
            }
    }
    
    //print(height, width);
    
    decode(1, 1);
    bool type = s.size() % 2;
    
    char c = '#';
    if (type) c = '.';
    
    for(int i = 0; i < 3000; ++i) fill(mapka[i], mapka[i] + 3000, c);
    
    
    for(auto u : s) {
        create(u, type);
        type = (type + 1) % 2;
    
    }
    
    cout << ey - sy + 1 << ' ' << ex - sx + 1 << '\n';
    for(int i = sy; i <= ey; ++i) {
        for(int j = sx; j <= ex; ++j) {
            cout << mapka[i][j];
        }
        cout << '\n';
        
    }
}