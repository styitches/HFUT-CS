#include<iostream>
using namespace std;
#define max 100


//定位函数
int locates(char *g, char ch,int number)
{
    int i;
    for(i = 0; i <number; i++)
    {
        if(g[i] == ch)
        {
            break;
        }
    }
    if(i >= number)
    {
        return-1;
    }

    return i;
}

//输入函数
void inputc(char *c,int number){
    for(int i=0;i<number;i++){
        cin>>c[i];
    }
}


//输出函数
void inputl(int ling[max][max],int number){

    for(int i=0;i<number;i++){
        for(int j=0;j<number;j++){
            cout<<ling[i][j]<<"\t";
        }
        cout<<endl;
    }
}


//判断是否为等价关系
bool judge(int ling[max][max],int number){
    bool zifan,duichen=true,chuandi=true;;
//判断自反性
    int total=0;
    for(int i=0;i<number;i++){
        if(ling[i][i]==1){
            total++;
        }
    }
    zifan=(number==total);

//判断对称性
    for(int m=0;m<number;m++){
        for(int n=0;n<number;n++){
            if(ling[m][n]==1 && ling[n][m]!=1){
                duichen=false;
            }
        }
    }

//判断传递性
    for(int p=0;p<number;p++){
        for(int q=0;q<number;q++){
            for(int s=0;s<number;s++){
                if(ling[p][q]==1 && ling[q][s]==1&& ling[p][s]!=1){
                    chuandi=false;
                }
            }
        }
    }

    return(zifan&duichen)&chuandi;


}

//求商集

void shangji(int ling[max][max],int number,char c[max]){
    bool visited[max];
    for(int p=0;p<number;p++){
        visited[p]=false;
    }

    for(int i=0;i<number;i++){
        if(visited[i]==false){
            visited[i]=true;
            cout<<"{";
            cout<<c[i]<<",";
            for(int j=0;j<number;j++){
                if(ling[i][j]==1&& visited[j]==false){
                    visited[j]=true;
                    cout<<c[j]<<",";
                }
            }
            cout<<"\b"<<"}";
            cout<<"  ";
        }
    }

}

int main(){
    char c[max],a,b;
    int ling[max][max];
    int number,edge;
    cout<<"请输入元素个数以及关系个数:";
    cin>>number>>edge;
    cout<<"请输入元素:";
    inputc(c,number);

    for(int i=0;i<number;i++){
        for(int j=0;j<number;j++){
            ling[i][j]=0;
        }
    }

    //输入二元关系
    cout<<"请输入二元关系: "<<endl;
    for(int p=0;p<edge;p++){
        cin>>a>>b;
        ling[locates(c,a,number)][locates(c,b,number)]=1;
    }

//输出二元关系
    inputl(ling,number);
    if(judge(ling,number)){
        cout<<"它是满足等价关系"<<endl;
        shangji(ling,number,c);
    }
    else cout<<"它不满足等价关系"<<endl;

    return 0;
}
