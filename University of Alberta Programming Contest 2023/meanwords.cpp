#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector< string > vs;
    vs.reserve( n );
    int maxlen = 0;
    for ( int i = 0; i < n; i++ ) {
        string temp;
        cin >> temp;
        vs.push_back( temp );
        maxlen = temp.length() > maxlen ? temp.length() : maxlen;
    }
    vector< int > sum( maxlen, 0 );
    vector< int > count( maxlen, 0 );

    for ( string & t : vs ) {
        for ( int i = 0; i < t.length(); i++ ) {
            sum[ i ] += int( char( t[ i ] ) );
            count[ i ]++;
        }
    }

    for ( int i = 0; i < maxlen; i++ ) {
        cout << char( sum[ i ] / count[ i ] );
    }
    cout << endl;


    return 0;
}