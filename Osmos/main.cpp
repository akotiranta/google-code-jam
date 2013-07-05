//
//  main.cpp
//  Osmos
//
//  Created by Atte Kotiranta on 5/12/13.
//  Copyright (c) 2013 Atte Kotiranta. All rights reserved.
//

#include <iostream>

using namespace std;

int trim(int& armin, int* motes, int& count, int& offset)
{
    int c = count;
    int o = offset;
    for (int i = 0; i < c; i++) {
        if (armin > motes[i + o]) {
            armin += motes[i + o];
            offset++; count--;
        }
    }
    return c - count;
}

void solve(int& armin, int* motes, int &count, int& offset, int& moves) {
    int max = count; // remove all
    while (count > 0 && moves < max) {
        armin += armin - 1;
        moves++;
        if (trim(armin, motes, count, offset) != 0) {
            max = max > (moves + count) ? moves + count : max;
        }
    }
}

int main(int argc, const char * argv[])
{
    int cases = 0;

    cin >> cases;
    
    for (int i = 0; i < cases; i++) {
        int armin = 0;
        int count = 0;
        int mote = 0;
        int moves = 0;
        int offset = 0;
        int motes[100];

        cin >> armin;
        cin >> count;
        for (int j = 0; j < count; j++) {
            cin >> mote;
            motes[j] = mote;
        }
        sort(motes, motes + count);
        trim(armin, motes, count, offset);
        solve(armin, motes, count, offset, moves);
        
        cout << "Case #" << i + 1 << ": " << moves << endl;
    }
    
    return 0;
}

