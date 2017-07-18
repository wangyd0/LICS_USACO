/*
ID: lic92031
LANG: C
TASK: comehome
*/
#include<stdio.h>
#include<string.h>
#define MAX_POINT_NUM 26*2
#define MAX_PATH_LENGTH 1000000
typedef struct{
  int p;
  int Mat[MAX_POINT_NUM][MAX_POINT_NUM];
} InputData;
typedef struct{
  char p;
  int dist;
} OutputData;
int EncodeChar(char a){
  if(a<='z'&&a>='a') return (int)(a-'a');
  if(a<='Z'&&a>='A') return (int)(a-'A'+26);
  return 0;
}
char DecodeNum(int a){
  if(a<26&&a>=0) return (char)a+'a';
  if(a<52&&a>=26) return (char)a+'A'-26;
  return '\0';
}
void ReadIn(FILE *f, InputData *data){
  int index = 0, i = 0, j = 0;
  char lp = '\0', rp = '\0';
  int tmp = 0;
  fscanf(f,"%d\n",&(data->p));
  for (i = 0; i < MAX_POINT_NUM; i++)
    for (j  = 0; j <MAX_POINT_NUM; j++)
    {
      data->Mat[i][j] = i==j?0:MAX_PATH_LENGTH;
    }
  for (index = 0; index < (data->p); index++)
  {
    fscanf(f,"%c %c %d\n",&lp,&rp,&tmp);
    data->Mat[EncodeChar(lp)][EncodeChar(rp)] = data->Mat[EncodeChar(lp)][EncodeChar(rp)]>tmp?tmp:data->Mat[EncodeChar(lp)][EncodeChar(rp)];
    data->Mat[EncodeChar(rp)][EncodeChar(lp)] = data->Mat[EncodeChar(lp)][EncodeChar(rp)];
  }
}
int GetDistBetween(InputData *data,int l, int r){
  return (data->Mat[l][r]<data->Mat[r][l]?data->Mat[l][r]:data->Mat[r][l]);
}
void UpdateResult(OutputData *data, int lp, int rp, int dist){
  int tmp = 0;
  if(DecodeNum(rp) == 'Z'){tmp = lp; lp = rp; rp = tmp;}
  if(DecodeNum(lp) == 'Z' && DecodeNum(rp)<='Y' && DecodeNum(rp)>='A'){
    if(dist<data->dist||data->dist == 0){
      data->p = DecodeNum(rp);
      data->dist = dist;
    }
  }
}
void ResolveProblem(InputData *inputdata, OutputData *outputdata){
  int f[MAX_POINT_NUM][MAX_POINT_NUM]={0};
  int i = 0, j = 0, k = 0;
  for(j = 0; j < MAX_POINT_NUM; j++)
    for(i = 0; i < MAX_POINT_NUM; i++){
      f[i][j] = GetDistBetween(inputdata,i,j);
      UpdateResult(outputdata,i,j,f[i][j]);
    }
  for(k = 0; k < MAX_POINT_NUM; k++)
    for(j = 0; j < MAX_POINT_NUM; j++)
      for(i = 0; i < MAX_POINT_NUM; i++){
        if(f[i][j]>f[i][k]+f[k][j]){
          f[j][i] = f[i][j] = f[i][k]+f[k][j];
          UpdateResult(outputdata,i,j,f[i][j]);
        }
      }

}
void WriteOut(FILE *f, OutputData *data){
  fprintf(f,"%c %d\n",data->p,data->dist);
}
int main(){
  FILE *fin=fopen("comehome.in","r");
  FILE *fout=fopen("comehome.out","w");
  InputData inputdata;
  OutputData outputdata={0,0};
  ReadIn(fin,&inputdata);
  ResolveProblem(&inputdata,&outputdata);
  WriteOut(fout,&outputdata);
  fclose(fin);
  fclose(fout);
  return 0;
}
