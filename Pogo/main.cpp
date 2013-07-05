//
//  main.cpp
//  Pogo
//
//  Created by Atte Kotiranta on 5/18/13.
//  Copyright (c) 2013 Atte Kotiranta. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

typedef struct {
    int x, y;
    string jumps;
} jumper;

vector<jumper*> jumping;
vector<jumper*> visited;
vector<jumper*> newJumpers;

void cleanup() {
    // iterate and delete jumpers
    newJumpers.clear();
    jumping.clear();
    for (int i = 0; i < visited.size(); i++) {
        delete visited.at(i);
    }
    visited.clear();
}

bool hasVisited(jumper* n) {
    for (int i = 0; i < visited.size(); i++) {
        if (n->x == visited.at(i)->x && n->y == visited.at(i)->y) return true;
    }
    visited.push_back(n);
    return false;
}

void createJumpers() {
    newJumpers.clear();    
    for (int i = 0; i < jumping.size(); i++) {
        jumper* j = jumping.at(i);

        jumper* n = new jumper;
        n->x = 0;
        n->y = 0;
        n->jumps = "";
        
        n->x = j->x + ((int)j->jumps.length() + 1);
        n->y = j->y;
        n->jumps = j->jumps + 'E';
        if (hasVisited(n)) {
            delete n;
        } else newJumpers.push_back(n);
        
        n = new jumper;
        n->x = 0;
        n->y = 0;
        n->jumps = "";
        n->x = j->x - ((int)j->jumps.length() + 1);
        n->y = j->y;
        n->jumps = j->jumps + 'W';
        if (hasVisited(n)) {
            delete n;
        } else newJumpers.push_back(n);

        n = new jumper;
        n->x = 0;
        n->y = 0;
        n->jumps = "";
        n->x = j->x;
        n->y = j->y - ((int)j->jumps.length() + 1);
        n->jumps = j->jumps + 'S';
        if (hasVisited(n)) {
            delete n;
        } else newJumpers.push_back(n);

        n = new jumper;
        n->x = 0;
        n->y = 0;
        n->jumps = "";
        n->x = j->x;
        n->y = j->y + ((int)j->jumps.length() + 1);
        n->jumps = j->jumps + 'N';
        if (hasVisited(n)) {
            delete n;
        } else newJumpers.push_back(n);
    }
    jumping.clear();
    jumping = newJumpers;
    cerr << jumping.size() << endl;
}

string jump(int x, int y) {
    while (true) {
        createJumpers();
        for (int i = 0; i < jumping.size(); i++) {
            if (jumping.at(i)->x == x && jumping.at(i)->y == y) {
                return jumping.at(i)->jumps;
            }
        }
    }
}

int main(int argc, const char * argv[])
{
    int cases;
    cin >> cases;
    
    for (int i = 1; i <= cases; i++) {
        int x,y;
        cin >> x;
        cin >> y;
        jumper* j = new jumper();
        j->x = 0;
        j->y = 0;
        j->jumps = "";
        jumping.push_back(j);
        cout << "Case #" << i << ": " << jump(x, y) << endl;
        cleanup();
    }
    
    return 0;
}

