//
//  main.cpp
//  StoreCredit
//
//  Created by Atte Kotiranta on 4/20/13.
//  Copyright (c) 2013 Atte Kotiranta. All rights reserved.
//

#include <iostream>

using namespace std;

void solve(int credit, int length, int offset, int p[]) {
    
    for (int i = 1; i < length; i++) {
        if (p[0] + p[i] == credit) {
            cout << offset + 1 << " " << i + offset + 1;
            return;
        }
    }
    solve(credit, length - 1, ++offset, ++p);
}

int main(int argc, const char * argv[])
{
    int n = 0;
    cin >> n;
    cout << endl;
    
    for (int i = 0; i < n; i++) {
        int c, l;
        int *p;
        cin >> c;
        cin >> l;
        p = new int[l];
        
        for (int j = 0; j < l; j++) {
            cin >> p[j];
        }
        
        cout << "Case #" << i+1 << ": ";
        
        solve(c, l, 0, p);
        
        cout << endl;
        
        free(p);
    }
    return 0;
}

