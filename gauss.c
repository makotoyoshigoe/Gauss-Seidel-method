#include<stdio.h>
#include<math.h>

int N; //行列の大きさ

double get_x(int l, double arr[l][N], double res[N], double ans[N]){
    double x = 0;
    for(int i = 0; i < N; i++) if(i != l) x += arr[l][i] * res[i]; //対角成分でない場合, 係数行列と解を掛け, それらの総和を求める. 

    x = ans[l] - x;  //右辺から上で求めた値を引く. 
    x /= arr[l][l];  //上で求めた値を対角成分で割る. 
    return x; //xを返す. 
}

int main(void){
    FILE *fp;  //ファイルポインタを宣言.
    char file_name[] = "sample.txt";  //読み込みファイル指定.
    fp = fopen(file_name, "r");  //読み込みモードでファイルを開く.
    if(fp==NULL){
        printf("Can't open the file. \n");  //ファイルが開けない場合, エラーメッセージを出力.
        return -1;  //プログラム終了.
    }

    fscanf(fp, "%d", &N);  //行列数読み込み. 
    double k[N][N];  //係数行列を格納する配列を宣言.
    double ans[N];  //式の右辺の列ベクトルを宣言.
    double res[N];  //解の列ベクトルを宣言.
    for(int i = 0; i < N; i++) for(int j = 0; j < N; j++) fscanf(fp, "%lf, ", &k[i][j]);  //係数行列の読み込み.

    for(int i = 0; i < N; i++) fscanf(fp, "%lf,", &ans[i]);  //右辺の列ベクトルの読み込み.

    for(int i = 0; i < N; i++) fscanf(fp, "%lf,", &res[i]);   //解の初期値の読み込み.

    fclose(fp);  //ファイルを閉じる. 
    double esp = 1e-11; //許容誤差範囲を宣言. 
    int cnt = 0; //計算した回数を代入する.
    double e = 1; //誤差を代入する変数を定義. 初期値はespよりも大きいものにする. 
    //右辺と左辺の差がesp未満になるまで繰り返す. 
    while(fabs(e) >= esp){
        double sum = 0;
        for(int i = 0; i < N; i++) res[i] = get_x(i, k, res, ans); //xの値の更新. 
        for(int i = 0; i < N; i++) sum += k[0][i] * res[i]; //1行目のxに解を代入し, 総和を求める. 
        e = ans[0] - sum;  //誤差を計算する. 
        cnt++;  //計算回数を更新する. 

        for(int i = 0; i < N; i++) printf("x%d = %.10lf, ", i+1, res[i]); //xの値の表示. 
        printf("cnt = %d\n", cnt); //計算回数の表示. 
    }
    return 0;
}