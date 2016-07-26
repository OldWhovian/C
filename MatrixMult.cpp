#include <iostream>

using namespace std;



int main(int argc, char** argv) {
    char mat1[3][3], mat2[3][3];
    char input;
    cout << "Please input two matrices: ";
    
    int x = 0;
    int y = 0;
    for(x; y < 3; x++){
        cin >> input;
        mat1[y][x] = input;
        if (x == 2){
            x = -1;
            y++;
        }
    }
    
    x = 0;
    y = 0;
    for(x; y < 3; x++){
        cin >> input;
        mat2[y][x] = input;
        if (x == 2){
            x = -1;
            y++;
        }
    }
    
    int finalMat[3][3];
    finalMat[0][0] = ((mat1[0][0]-'0')*(mat2[0][0]-'0'))+((mat1[0][1]-'0')*(mat2[1][0]-'0'))+((mat1[0][2]-'0')*(mat2[2][0]-'0'));
    finalMat[1][0] = ((mat1[1][0]-'0')*(mat2[0][0]-'0'))+((mat1[1][1]-'0')*(mat2[1][0]-'0'))+((mat1[1][2]-'0')*(mat2[2][0]-'0'));
    finalMat[2][0] = ((mat1[2][0]-'0')*(mat2[0][0]-'0'))+((mat1[2][1]-'0')*(mat2[1][0]-'0'))+((mat1[2][2]-'0')*(mat2[2][0]-'0'));
    finalMat[0][1] = ((mat1[0][0]-'0')*(mat2[0][1]-'0'))+((mat1[0][1]-'0')*(mat2[1][1]-'0'))+((mat1[0][2]-'0')*(mat2[2][1]-'0'));
    finalMat[1][1] = ((mat1[1][0]-'0')*(mat2[0][1]-'0'))+((mat1[1][1]-'0')*(mat2[1][1]-'0'))+((mat1[1][2]-'0')*(mat2[2][1]-'0'));
    finalMat[2][1] = ((mat1[2][0]-'0')*(mat2[0][1]-'0'))+((mat1[2][1]-'0')*(mat2[1][1]-'0'))+((mat1[2][2]-'0')*(mat2[2][1]-'0'));
    finalMat[0][2] = ((mat1[0][0]-'0')*(mat2[0][2]-'0'))+((mat1[0][1]-'0')*(mat2[1][2]-'0'))+((mat1[0][2]-'0')*(mat2[2][2]-'0'));
    finalMat[1][2] = ((mat1[1][0]-'0')*(mat2[0][2]-'0'))+((mat1[1][1]-'0')*(mat2[1][2]-'0'))+((mat1[1][2]-'0')*(mat2[2][2]-'0'));
    finalMat[2][2] = ((mat1[2][0]-'0')*(mat2[0][2]-'0'))+((mat1[2][1]-'0')*(mat2[1][2]-'0'))+((mat1[2][2]-'0')*(mat2[2][2]-'0'));
    
    int output = 0;
    x = 0;
    y = 0;
    for (x; y < 3; x++) {
        output = finalMat[y][x];
        cout << output << ' ';
        if (x == 2){
            cout << '\n';
            x = -1;
            y++;
        }
    }
    return 0;
}

