//
//  main.cpp
//  ReverseWords
//
//  Created by Atte Kotiranta on 5/10/13.
//  Copyright (c) 2013 Atte Kotiranta. All rights reserved.
//

#include <iostream>

using namespace std;

void reverse()
{
    string str;
    cin >> str;
    if (cin.peek() != '\n' || cin.eof()) {
        str = " " + str;
        reverse();
    }
    cout << str;
}

int main(int argc, const char * argv[])
{
    int count = 0;
    cin >> count;
    for (int i = 0; i < count; i++) {
        cout << "Case #" << (i + 1) << ": ";
        reverse();
        cout << endl;
    }
    return 0;
}

