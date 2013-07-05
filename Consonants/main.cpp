//
//  main.cpp
//  Consonants
//
//  Created by Atte Kotiranta on 5/18/13.
//  Copyright (c) 2013 Atte Kotiranta. All rights reserved.
//

#include <iostream>

using namespace std;

int hasConsecutiveConsonants(string* str, int offset, int length)
{
    int n = 0;
    int j = (int)str->length() - offset;
    for (int i = 0; i < j; i++) {
        char c = str->at(i+offset);
        if (c != 'a' &&
            c != 'e' &&
            c != 'i' &&
            c != 'o' &&
            c != 'u')
        {
            n++;
            if (n == length) return i+offset;
        } else n = 0;
    }
    return -1;
}

long findSubstrings(string* name, int length, int& offset)
{
    int end = hasConsecutiveConsonants(name, offset, length);
    if (end == -1) return 0;
    
    long substrings = ((end - length + 2) - offset) * (name->length() - end);
    
    offset = end - length + 2;
    
    return substrings;
    
//    for (int i = offset + length; i <= name->length(); i++) {
//        if (hasConsecutiveConsonants(name, offset, i - offset, length)) {
//            substrings++;
//        }
//    }
//    return substrings;
}

int main(int argc, const char * argv[])
{
    int cases;
    cin >> cases;
    string name;
    int length;

    for (int i = 1; i <= cases; i++)
    {
        long substrings = 0;
        // read string in piece by piece
        // fails on the 1000000 character string
        cin >> name;
        cin >> length;
        
        for (int j = 0; j <= name.length() - length;) {
            long n = findSubstrings(&name, length, j);
            if (n == 0) break;
            substrings += n;
        }
        
        cout << "Case #" << i << ": " << substrings << endl;
    }
    
    return 0;
}

