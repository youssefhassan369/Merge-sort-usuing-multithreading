
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


int array[100];
int size=0;




void merge(int left,int middle,int right){
    int i,j,k;
    int leftSize= middle - left + 1;
    int rightSize= right-middle ;
    int leftArray[leftSize];
    int rightArray[rightSize];
    for (int i=0;i<leftSize; i++) {
        leftArray[i]=array[left+i];
        
    }
    
    
    for (int j=0; j<rightSize; j++) {
        rightArray[j]=array[middle+1+j];
    }
    
    i= 0;
    j= 0;
    k=left;
    while (i< leftSize && j< rightSize)
    {
    if (leftArray[i]<=rightArray[j]) {
    array[k] = leftArray[i];
        i++;
        k++;
    }
    else {
        array[k]=rightArray[j];
        k++;
        j++;
        
        
    }
}
while (i< leftSize)   {
array[k] =leftArray[i];
    i++;
    k++;
}
 while (j< rightSize)
    {
        array[k]=rightArray[j];
        j++;
        k++;
}
    
}


void* merge_sort(void *args)
{
    int *tempo=malloc(sizeof(int)*2);
    tempo[0]=((int*)args)[0];
        tempo[1]=((int*)args)[1];
    
    int low=tempo[0];
    int high=tempo[1];

    
    int middle = (low + high) / 2;
    
    if (low < high) {
    pthread_t thread1;
        int *tempo2=malloc(sizeof(int)*2);
        tempo2[0]=low;
        tempo2[1]=middle;
        pthread_create(&thread1,NULL,merge_sort,tempo2);

        
        int *tempo3=malloc(sizeof(int)*2);
        pthread_t thread2;
        tempo3[0]=middle+1;
        tempo3[1]=high;
        pthread_create(&thread2,NULL,merge_sort,tempo3);

         
        pthread_join(thread1,NULL);
        pthread_join(thread2,NULL);
        merge(low, middle, high);
        
        
        
        
    }
}

void load(char *filename){
    //printf("Enter file name\n");
    //char filename[100];
    //fgets(filename,sizeof(filename),stdin);
    
    
    
        FILE* fp;
        fp=fopen(filename,"r");
        if (!fp)
            {
            printf("Error opening file\n");
                return ;
            }
             else
        {
            printf("Loaded Successfully..!\n");
            printf(".................................\n");
            fseek(fp, 0, SEEK_SET);
            fscanf(fp,"%d",&size);
            int i=0;
            while (!feof(fp))
            {
                int *element=(int*)malloc(sizeof(int));
                fscanf(fp,"%d",element);
                array[i]=*element;
                i++;
                
            }

        }
    
    fclose(fp);


    }
    
    
void printArray(int size){
    int i=0;
    while (i<size) {
        printf("%d\t",array[i]);
        i++;
    }
    printf("\n");
    
    
}


    
    


int main(int argc,char * argv[]) {
    load(argv[1]);
    int *array1=malloc(sizeof(int)*2);
    array1[0]=0;
    array1[1]=size-1;
    pthread_t threadx;
    pthread_create(&threadx,NULL,merge_sort, array1);

    pthread_join(threadx,NULL);
    
    printArray(size);
    
  
    
    
   
    
    
    return 0;
}
