//
//  main.cpp
//  GreatWall
//
//  Created by Atte Kotiranta on 5/20/13.
//  Copyright (c) 2013 Atte Kotiranta. All rights reserved.
//

#include <iostream>
#include <list>
#include <set>

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

struct wall {
    int w;
    int e;
    int h;
};

bool compare_west(wall* w1, wall* w2) {
    if (w1->w < w2->w) return true;
    return false;
}

bool compare_east(wall* w1, wall* w2) {
    if (w1->e < w2->e) return true;
    return false;
}

list<tribe*> tribes;
set<wall*, bool(*)(wall*,wall*)> greatwall (compare_west);
list<wall*> unresolved;

bool compare_attack(tribe* t1, tribe* t2) {
    if (t1->attackDay < t2->attackDay) return true;
    return false;
}

void addWall(list<wall*>::iterator it, int w, int e, int h)
{
    wall* wa = new struct wall();
    wa->w = w;
    wa->e = e;
    wa->h = h;
    greatwall.insert(wa);
}

void addWall(wall* wa)
{
    greatwall.insert(wa);
}

set<wall*>::iterator find_start(wall* wa) {
    set<wall*>::iterator it = greatwall.lower_bound(wa);
    while (it != greatwall.begin()) {
        if ((*it)->e > wa->w) it--;
        else break;
    }
    return it;
}

bool addAttack(int w, int e, int s)
{
    wall* wa = new struct wall();
    wa->w = w;
    wa->e = e;
    wa->h = s;
    
    set<wall*>::iterator it;
    it = find_start(wa);
    
    while (it != greatwall.end() && wa->w < wa->e) {
        if ((*it)->w <= wa->w)
        if ((*it)->h < wa->h) {
            unresolved.push_back(wa);
            return true;
        } else {
            wa->w = (*start)->e;
            it++;
        }
    }
    
    delete wa;
    return false;
}

void buildWall() {
    if (unresolved.size() == 0) return;
    
    while (unresolved.size() > 0) {
        wall* wa = (*unresolved.begin());
        unresolved.erase(unresolved.begin());
        
        
    }
    
    while (it != greatwall.end()) {
        list<wall*>::iterator next = it;
        next++;
        if ((*it)->w >= (*it)->e) {
            delete (*it);
            it = greatwall.erase(it);
        } else {
            if (next == greatwall.end()) {
                break;
            }
            if ((*next)->w >= (*next)->e) {
                delete (*next);
                greatwall.erase(next);
            } else {
                if ((*it)->e > (*next)->w) {
                    list<wall*>::iterator temp;
                    if ((*it)->h >= (*next)->h) {
                        (*next)->w = (*it)->e;
                        temp = next;
                        while (temp != greatwall.end() && (*temp)->w <= (*next)->w) {
                            temp++;
                        }
                        greatwall.insert(temp, (*next));
                        greatwall.erase(next);
                    } else {
                        addWall(it, (*it)->w, (*next)->w, (*it)->h);
                        (*it)->w = (*next)->e;
                        temp = next;
                        while (temp != greatwall.end() && (*temp)->w <= (*it)->w) {
                            temp++;
                        }
                        greatwall.insert(temp, (*it));
                        it = greatwall.erase(it);
                    }
                } else {
                    it++;
                }
            }
        }
    }
}

int main(int argc, const char * argv[])
{
    int cases;
    cin >> cases;
    
    for (int i = 1; i <= cases; i++) {
        int count = 0;
        int attacks = 0;
        int day = -1;
        
        cin >> count;
        for (int j = 0; j < count; j++) {
            tribe* t = new tribe;
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
                    temp = it;
                    temp++;
                    while (temp != tribes.end() && (*temp)->attackDay <= (*it)->attackDay) {
                        temp++;
                    }
                    tribes.insert(temp, (*it));
                    it = tribes.erase(it);
                }
            }
            if ((day % 10000) == 0) {
                cerr << "Case #" << i << " : " << "Day " << day << " : attacks = " << attacks << endl;
            }
            buildWall();
        }
        
        cout << "Case #" << i << ": " << attacks << endl;
        list<wall*>::iterator it = greatwall.begin();
        while (it != greatwall.end()) {
            delete (*it);
            it = greatwall.erase(it);
        }
    }
    return 0;
}

