//
//  main.cpp
//  FallingDiamonds
//
//  Created by Atte Kotiranta on 5/15/13.
//  Copyright (c) 2013 Atte Kotiranta. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

// triangle base is 2x height
// diamond count is now negative

int triangleHeight(int& diamonds) {
    int height = 0;
    while (diamonds >= 0) {
        diamonds -= (height * 4 + 1);
        height++;
    }
    return height;
}

int main(int argc, const char * argv[])
{
    // 0 x 2 + 1 = 1
    // 2 x 2 + 1 = 5
    // 4 x 2 + 1 = 9
    // 6 x 2 + 1 = 13
    // 8 x 2 + 1 = 17
    
    // Propability is 1 always when pyramid is complete
    // Propability is number of edge pieces that can land the area divided by the number of pieces available

    int cases = 0;
    cin >> cases;
    
    for (int i = 1; i <= cases; i++) {
        int height = 0;
        int diamonds = 0;
        int x = 0, y = 0;
        float propability = 1.0f;

        cin >> diamonds;
        cin >> x;
        cin >> y;
        x = abs(x);
        
        height = triangleHeight(diamonds);
        if (height*2 < x+y) {
            propability = 0.0;
        } else if ((height-1)*2 > x+y) {
            propability = 1.0;
        } else {
            int side = height * 2 - 2;
            diamonds += (height - 1) * 4 + 1;
            if (side >= diamonds) {
                if (y >= diamonds) {
                    propability = 0.0;
                } else {
                    propability = 1.0;
                    for (int j = 0; j <= y; j++) {
                        propability *= (float)(1 - pow(0.5, diamonds - j));
                    }
                }
            } else {
                diamonds -= side;
                if (y < diamonds) {
                    propability = 1.0;
                } else {
                    diamonds += side;
                    propability = 1.0;
                    for (int j = 1; j <= y; j++) {
                        propability *= (float)(1 - pow(0.5, diamonds - j));
                    }
                }
            }
        }
        
        cout << "Case #" << i << ": " << propability << endl;
    }
    
    return 0;
}

