#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
ifstream ifs;



void converttotext(vector<int> asciival)
{
    ofstream ofs("outputtext.txt", ios::trunc);
    for (int i = 0; i < asciival.size(); i++)
    {
        char x = asciival.at(i);
        ofs << char(x);
    }
}




int modInverse(int a, int m){ 
    a=a%m; 
    for(int x=-m;x<m;x++) 
       if((a*x)%m==1) 
          return x; 
} 

void getCofactor(vector<vector<int> > &a, vector<vector<int> > &temp, int p, int q, int n){ 
    int i=0,j=0; 
    for(int row=0;row<n;row++){ 
        for(int col=0;col<n;col++){ 
            if(row!=p&&col!=q){ 
                temp[i][j++] = a[row][col]; 
                if (j==n-1){ 
                    j=0; 
                    i++; 
                } 
            } 
        } 
    } 
}

int determinant(vector<vector<int> > &a, int n, int N){ 
    int D = 0;
    if(n==1) 
        return a[0][0]; 
    vector<vector<int> > temp(N, vector<int>(N));
    int sign = 1;
    for(int f=0;f<n;f++){ 
        getCofactor(a, temp, 0, f, n); 
        D += sign * a[0][f] * determinant(temp, n - 1, N); 
        sign = -sign; 
    }
    return D; 
} 

void adjoint(vector<vector<int> > &a,vector<vector<int> > &adj,int N){ 
    if(N == 1){ 
        adj[0][0] = 1; 
        return; 
    } 
    int sign = 1;
    vector<vector<int> > temp(N, vector<int>(N));
    for(int i=0;i<N;i++){ 
        for(int j=0;j<N;j++){ 
            getCofactor(a, temp, i, j, N); 
            sign = ((i+j)%2==0)? 1: -1; 
            adj[j][i] = (sign)*(determinant(temp, N-1 , N)); 
        } 
    } 
} 

bool inverse(vector<vector<int> > &a, vector<vector<int> > &inv, int N){ 
    int det = determinant(a, N, N); 
    if(det == 0){ 
        cout << "Inverse does not exist"; 
        return false; 
    } 
    int invDet = modInverse(det,91);
    cout<<det%91<<' '<<invDet<<'\n';
    vector<vector<int> > adj(N, vector<int>(N));
    adjoint(a, adj, N);  
    for(int i=0;i<N;i++) 
        for(int j=0;j<N;j++) 
            inv[i][j] = (adj[i][j]*invDet)%91; 
    return true; 
} 


int main(){
    ofstream ofs("decryptedascii.txt", ios::trunc);
    int x,y,i,j,k,n;
    cout<<"Enter the size of key matrix\n";
    cin>>n;
    cout<<"Enter the key matrix\n";
    vector<vector<int> > a(n, vector<int>(n));
    vector<vector<int> > adj(n, vector<int>(n));
    vector<vector<int> > inv(n, vector<int>(n));

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            cin>>a[i][j];
        }
    }
    if(inverse(a,inv,n)){
        cout<<"Inverse exist\n";
    }

    string s;
    ifs.open("encrypted.txt", ios::in);
    while (ifs.peek() != EOF) {
        getline(ifs, s);
    }

    k=0;
    string ans;
    while(k<s.size()){
        for(i=0;i<n;i++){
            int sum = 0;
            int temp = k;
            for(j=0;j<n;j++){
                sum += ((inv[i][j] + 91)%91*(s[temp++]-' ')%91)%91;
                sum = sum%91;
                
            }
            ans+=(sum+' ');
        }
        k+=n;
    }
    //ans+='\0';
    int f=ans.size()-1;
    while(ans[f]=='?'){
        f--;
    }

    for(i=0;i<=f;i++){
        ofs<<ans[i];
    }
    cout<<'\n';
    ofs.close();
    ifs.close();
    




   vector<int> asciival;
    
    //cout << "Enter text to convert to ASCII: ";

    ifs.open("decryptedascii.txt", ios::in);

    while (ifs.peek() != EOF) {
        int temp;
        ifs>>temp;
        asciival.push_back(temp);     
    }
    converttotext(asciival);

    return 0;    
}









