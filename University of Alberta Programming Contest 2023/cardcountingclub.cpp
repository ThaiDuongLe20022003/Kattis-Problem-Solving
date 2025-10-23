#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// This is the storage type for the simulation.
unordered_map< int, priority_queue< int, vector< int >, greater< int > > > simulation;
// This is where the result will end up.
vector< int > result;
vector< string > nameList;
int numPlayers, lenLists, punishFactor;

void readInput() {
    cin >> numPlayers >> lenLists >> punishFactor;

    // Will just read the input into a buffer so I can do some precomputation
    // on it to make it less compute intensive during actual simulation.
    unordered_map< string, vector< int > > inpBuf;
    nameList.reserve( numPlayers );
    result.reserve( numPlayers );

    // O( n*m )
    for ( int i = 0; i < numPlayers; i++ ) {
        string pName;
        cin >> pName;
        inpBuf[ pName ] = vector< int >();
        inpBuf[ pName ].reserve( lenLists );
        nameList.push_back( pName );
        for ( int j = 0; j < lenLists; j++ ) {
            int t;
            cin >> t;
            inpBuf[ pName ].push_back( t );
        }
    }

    // At this point, the input should be fully read.
    // In order to not constantly re-compare the keys down the road, convert
    // the names to a "number" space by sorting the list of names.
    // O( nlogn )
    sort( nameList.begin(), nameList.end() );

    // O( nm )
    // nm because apparently the priority_queue construction is linear.
    for ( int i = 0; i < numPlayers; i++ ) {
        simulation[ i ] = priority_queue< int, vector< int >, greater< int > >(
            inpBuf[ nameList[ i ] ].begin(),
            inpBuf[ nameList[ i ] ].end() );
    }
}

void simulate() {
    // Keep the simulation running while there are still some players left in
    // the simulation.
    int numCurrPlayers = numPlayers;
    // O( nm )
    while ( numCurrPlayers ) {
        // Step 1: Set up the single iteration state.
        // Cannot set minVal to maxRand as during simulation we will reach
        // numbers much higher than maxRand
        int minVal = -1;
        int minIdx = numPlayers;

        // Step 2: Iterate through all the players to figure out who has the
        // smallest value in their hand.
        // O( n )
        for ( const auto & p : simulation ) {
            int v = p.second.top();
            int idx = p.first;
            if ( v < minVal || minVal == -1 ) {
                minVal = v;
                minIdx = idx;
            } else if ( v == minVal && idx < minIdx ) {
                minIdx = idx;
            }
        }

        // Step 3: Let winning player progress.
        // O( logm )
        simulation[ minIdx ].pop();
        if ( simulation[ minIdx ].empty() ) {
            // This player "won". Put them in the result list, clean up map.
            result.push_back( minIdx );
            simulation.erase( minIdx );
            numCurrPlayers--;
        }

        // Step 4: Iterate through all the losing players and do the "punish"
        // logic. Note, non-const iter due to mutation of heap in map.
        // O( nlogm )
        // This is the main factor to really optimize. Could probably 
        for ( auto & p : simulation ) {
            int v = p.second.top();
            int idx = p.first;
            // In the interim, we will see this rounds winner in the simulation,
            // so make sure not to punish them by accident.
            if ( idx == minIdx ) {
                continue;
            }
            p.second.pop();
            p.second.push( v + punishFactor );
        }
    }
}

void generateOutput() {
    for ( int i = 0; i < numPlayers; i++ ) {
        cout << nameList[ result[ i ] ];
        if ( i < numPlayers - 1 ) {
            cout << " ";
        }
    }
    cout << endl;
}

int main() {
    // O( nm )
    readInput();
    // O( n^2*m*logm )
    simulate();
    // O( n )
    generateOutput();

    return 0;
}