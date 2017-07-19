/*
ID: lic92031
LANG: C
TASK: fracdec
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_RESULT_NUM 100000
typedef struct{
  int num;
  int den;
}InputData;
typedef char* OutputData;
void ReadIn(FILE *f, InputData *data){
  fscanf(f,"%d%d",&data->num,&data->den);
}
int GetDotPos(OutputData *outputdata){
  int index = 0;
  for (index = 0; index < strlen(*outputdata); index++)
    if((*outputdata)[index] == '.') return index;
  return 0;
}
void ResolveProblem(InputData *inputdata,OutputData *outputdata){
  int *dec_num = (int *)malloc(inputdata->den*sizeof(int));
  char tmp[2]={0};
  int val = 0;
  int total_count = 0;
  int i = 0, j = 0, flag = 0;
  memset(dec_num,0,inputdata->den*sizeof(int));
  memset(*outputdata,0,MAX_RESULT_NUM*sizeof(char));
  val = inputdata->num / inputdata->den;
  inputdata->num = inputdata->num % inputdata->den;
  sprintf(*outputdata,"%d",val);
  if(inputdata->num > 0) strcat(*outputdata,".");
  else{
    strcat(*outputdata,".0");
    return;
  }
  while(inputdata->num > 0){
    total_count++;
    if(dec_num[inputdata->num] == 0){
      dec_num[inputdata->num] = total_count;
    }else{
      i = GetDotPos(outputdata);
      (*outputdata)[i+total_count+1] = ')';
      for(j = i + total_count; j >= i + dec_num[inputdata->num]+1; j--){
        (*outputdata)[j] = (*outputdata)[j-1];
      }
      (*outputdata)[i+dec_num[inputdata->num]] = '(';
      break;
    }
    inputdata->num *= 10;
    val = inputdata->num / inputdata->den;
    inputdata->num = inputdata->num % inputdata->den;
    sprintf(tmp,"%d",val);
    strcat(*outputdata,tmp);
  }
  free(dec_num);
}
void WriteOut(FILE *f, OutputData *outputdata){
  int i = 0;
  for(i = 0; i < strlen(*outputdata); i++){
    fprintf(f,"%c",(*outputdata)[i]);
    if((i+1)%76 == 0) fprintf(f,"\n");
  }
  if((i+1)%76 != 0) fprintf(f,"\n");
}
int main(){
  FILE *fin=fopen("fracdec.in","r");
  FILE *fout=fopen("fracdec.out","w");
  InputData inputdata;
  OutputData outputdata = (OutputData)malloc(MAX_RESULT_NUM*sizeof(char));
  ReadIn(fin,&inputdata);
  ResolveProblem(&inputdata,&outputdata);
  WriteOut(fout,&outputdata);
  free(outputdata);
  fclose(fin);
  fclose(fout);
  return 0;
}
