#include <iostream>

using namespace std;

struct Sparse
{
    int row=0;
    int col=0;
    int val=0;
};

void print(struct Sparse *S)
{
    int temp=1;

    for(int i=0; i<S[0].row; i++)
    {
        for(int j=0; j<S[0].col; j++)
        {
            if(S[temp].row==i && S[temp].col==j)
            {
                cout<<S[temp].val<<" ";
                temp++;
            }
            else
                cout<<"0 ";
        }
        cout<<"\n";
    }
}

void getdata(struct Sparse S[])
{
    cin>>S[0].row>>S[0].col>>S[0].val;
    for(int i=1; i<=S[0].val; i++)
        cin>>S[i].row>>S[i].col>>S[i].val;
}

void putdata(struct Sparse S[])
{
    for(int i=0; i<=S[0].val; i++)
        cout<<S[i].row<<" "<<S[i].col<<" "<<S[i].val<<"\n";
}

int notzero(struct Sparse *A, int Row, int Col)
{
    int Val=0;
    for(int temp=1; temp<=A[0].val; temp++)
        if(A[temp].row==Row && A[temp].col==Col)
            Val=A[temp].val;
    return Val;
}

void transpose(struct Sparse *S, struct Sparse *T)
{
    int n=S[0].val;
    int count[10]={0};
    int temp[10]={0};

    for(int i=1; i<=n; i++)
        count[S[i].col]++;

    temp[0]=1;

    for(int i=1; i<S[0].col; i++)
        temp[i]=temp[i-1]+count[i-1];

    T[0].col=S[0].row;
    T[0].row=S[0].col;
    T[0].val=S[0].val;

    for(int i=1; i<=n; i++)
    {
        T[temp[S[i].col]].row=S[i].col;
        T[temp[S[i].col]].col=S[i].row;
        T[temp[S[i].col]].val=S[i].val;
        temp[S[i].col]++;
    }
}

int multiply(struct Sparse *A, struct Sparse *B, struct Sparse *C)
{
    if(A[0].col==B[0].col)
    {
    int temp=1;
        int sum=0;
    for(int i=0; i<A[0].row; i++)
    {
            for(int j=0; j<B[0].row; j++)
            {
                for(int k=0; k<A[0].col; k++)
                {
                    sum+=notzero(A, i, k)*notzero(B, j, k);
                }
                if(sum!=0)
                {
                    C[temp].row=i;
                    C[temp].col=j;
                    C[temp++].val=sum;
                }
                sum=0;
            }
       }
       C[0].row=A[0].row;
       C[0].col=B[0].row;
       C[0].val=temp;
       return 1;
    }
    else
    return 0;
}

int main()
{
    struct Sparse A[20], B[20], BT[20], C[40];
    cout<<"Multiplication of Sparse Matrices\n";
    cout<<"Enter the elements of Sparse Matrix A\n";
    getdata(A);
    cout<<"Enter the elements of Sparse Matrix B\n";
    getdata(B);

    transpose(B, BT);
    multiply(A, BT, C);
    if(multiply(A, BT, C)==1)
    {
        cout<<"Elements of Matrix A: \n";
        print(A);
        cout<<"\nElements of Matrix B: \n";
        print(B);
        cout<<"\nSparse Matrix C= AxB: \n";
        putdata(C);
        cout<<"\nElements of Matrix C: \n";
        print(C);
        cout<<endl;
    }
    else
        cout<<"Incompatible Matrices entered";

    return 0;
}
