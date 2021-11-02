#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

ifstream ifs;
ofstream ofs("encrypted.txt",ios::trunc);

void convertToASCII(string letter)
{
    ofstream ofs("inputascii.txt",ios::trunc);
    for (int i = 0; i < letter.length(); i++)
    {
        char x = letter.at(i);
        ofs << int(x) <<" ";
    }
}

int main() {


    string plainText;
    string plainTextcopy;
    //cout << "Enter text to convert to ASCII: ";

    ifs.open("inputtext.txt", ios::in);

    while (ifs.peek() != EOF) {
        getline(ifs, plainTextcopy);
        plainText+=plainTextcopy;      
        plainText+="\n";      
    }
    convertToASCII(plainText);
    
    ifs.close();
    
    int x, y, i, j, k, n;
    cout << "Enter the size of key matrix\n";
    cin >> n;
    cout << "Enter the key matrix\n";
    int a[n][n];
    for (i = 0;i < n;i++) {
        for (j = 0;j < n;j++) {
            cin >> a[i][j];
        }
    }
    
    string s;
    ifs.open("inputascii.txt", ios::in);

    while (ifs.peek() != EOF) {
        getline(ifs, s);
        
    }
    int temp = (n - s.size() % n) % n;
    for (i = 0;i < temp;i++) {
        s += '?';/*to comonsate for
        incomplete matrix*/
    }
    k = 0;
    string ans = "";
    while (k < s.size()) {
        for (i = 0;i < n;i++) {
            int sum = 0;
            int temp = k;
            for (j = 0;j < n;j++) {

                sum += (a[i][j] % 91 * (s[temp++] - ' ') % 91) % 91;
                
                sum = sum % 91;
            }
            ans += (sum + ' ');
        }
        k += n;
    }
    ofs << ans;
    return 0;
}