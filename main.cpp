#include "includes/inp_out.h"
#include "includes/menu.h"

using namespace std;

int main() {
    menu();
    return 0;
}
/*
int main()
{
    unsigned int width = 20;
    unsigned int height = 10;

    vector<vector<char>> coordinates(height, vector<char>(width, 10));

    //printing the 2D vector
    cout << "printing the 2D vector\n";
    for (auto it : coordinates) {
        //it is now an 1D vector
        for (auto ij : it) {
            cout << ij << " ";
        }
        cout << endl;
    }

    return 0;
}
*/
