//
//  main.cpp
//  GreatWall
//
//  Created by Atte Kotiranta on 5/20/13.
//  Copyright (c) 2013 Atte Kotiranta. All rights reserved.
//

#include <iostream>
#include <list>
#include <time.h>

using namespace std;

struct tribe {
    int attackDay;
    int numberOfAttacks;
    int westBorder;
    int eastBorder;
    int strength;
    int deltaDays;
    int deltaDistance;
    int deltaStrength;
};

struct attack {
    int west;
    int east;
    int strength;
};

#define WALL (1<<30)
#define MIDDLE (1<<29)
int* wall;
list<tribe*> tribes;
list<attack*> attacks;

bool compare_attack(tribe* t1, tribe* t2) {
    if (t1->attackDay < t2->attackDay) return true;
    return false;
}

int getHeight(int w, int e) {
    int lowest = INT32_MAX;
    for (int i = (w + MIDDLE); i < (e + MIDDLE); i++) {
        if (wall[i] < lowest) {
            lowest = wall[i];
        }
    }
    return lowest;
}

bool addAttack(int w, int e, int s)
{
    int height = getHeight(w, e);
    if (height >= s) return false;
    
    attack* a = new attack();
    a->west = w;
    a->east = e;
    a->strength = s;
    attacks.push_back(a);
    return true;
}

void buildWall() {
    
    list<attack*>::iterator it = attacks.begin();
    
    while (it != attacks.end()) {
        int strength = (*it)->strength;
        for (int i = ((*it)->west + MIDDLE); i < ((*it)->east + MIDDLE); i++) {
            if (wall[i] < strength) {
                wall[i] = strength;
            }
        }
        delete (*it);
        it = attacks.erase(it);
    }
}

int main(int argc, const char * argv[])
{
    clock_t t_start, t_end;
    
    int cases;
    cin >> cases;
    
    wall = new int[WALL];
    
    for (int i = 1; i <= cases; i++) {
        t_start = clock();
        
        memset(wall, 0, (WALL)*sizeof(int));
        int count = 0;
        int attacks = 0;
        int day = -1;
        
        cin >> count;
        for (int j = 0; j < count; j++) {
            tribe* t = new tribe();
            cin >> t->attackDay;
            cin >> t->numberOfAttacks;
            cin >> t->westBorder;
            cin >> t->eastBorder;
            cin >> t->strength;
            cin >> t->deltaDays;
            cin >> t->deltaDistance;
            cin >> t->deltaStrength;
            tribes.push_back(t);
        }
        
        tribes.sort(compare_attack);
        
        while (tribes.size() > 0) {
            day++;
            list<tribe*>::iterator it = tribes.begin();
            list<tribe*>::iterator temp;
            while (it != tribes.end() && (*it)->attackDay == day) {
                if (addAttack((*it)->westBorder, (*it)->eastBorder, (*it)->strength)) {
                    attacks++;
                }
                (*it)->attackDay += (*it)->deltaDays;
                (*it)->strength += (*it)->deltaStrength;
                (*it)->westBorder += (*it)->deltaDistance;
                (*it)->eastBorder += (*it)->deltaDistance;
                (*it)->numberOfAttacks--;
                if ((*it)->numberOfAttacks == 0) {
                    delete (*it);
                    it = tribes.erase(it);
                } else {
                    //tribes.sort(compare_attack);
                    //it = tribes.begin();
                    temp = it;
                    temp++;
                    while (temp != tribes.end() && (*temp)->attackDay <= (*it)->attackDay) {
                        temp++;
                    }
                    tribes.insert(temp, (*it));
                    tribes.erase(it);
                    it = tribes.begin();
                }
            }
            buildWall();
        }
        tribes.clear();

        cout << "Case #" << i << ": " << attacks << endl;
        t_end = clock();
        cerr << "Case #" << i << ": " << ((long double) t_end - t_start) / CLOCKS_PER_SEC << " s" << endl;
                
    }
    delete wall;
    return 0;
}

