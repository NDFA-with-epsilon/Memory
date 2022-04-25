#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mem.h"

bin* CreateBucket(int nBins) //Bucket == collection of bins
{
    if(!nBins)
    {
        printf("\nInvalid bucket size\n");
        return NULL;
    }

    bin* tmp = (bin*) malloc(nBins * sizeof(bin));
    if(!tmp)
    {
        printf("\nFailed to create bucket\nExiting");
        return NULL;
    }

    for(int i = 0; i < nBins; i++) //setting the size of all bins
    {
        printf("\nEnter size of bin %d\n", i+1);
        scanf("%d", &((&tmp[i])->bin_size));
        (&tmp[i])->bound = 0; //unbound state at initialization
    }

    for(int i = 0; i < nBins; i++)
    {
        printf("\nBin %d:\tSize: %d bytes at %p\tUnbound\n", i+1, (&tmp[i])->bin_size, &tmp[i]);
    }

    return tmp;
}

void FreeBucket(bin* ptr)    //Frees the bucket
{
    if(!ptr)
    {
        return;
    }

    free(ptr);
    printf("\nBucket freed\n");
}

/* void ProcessQueue(process* ptr)
{
    if(!queue)
    {
        CreateQueue(5);
    }
} */

process* CreateProcess(int size /* Memory required by the process */)
{
    process* tmp = (process*) malloc(sizeof(process));
    tmp->proc_size = (size != 0) ? size : DEFAULT_SIZE; //allocates 8 bytes by default
    tmp->ptr = NULL;
    tmp->allocated = 0; 
    /* bool res = CreateQueue(tmp);
    if(!res)
    {
        printf("\nProcess created but failed to queue\n");
        return tmp;
    } */

    printf("\nProcess created & queued\nProcess Size: %d bytes\n", tmp->proc_size);
    return tmp;
}

void ExitProcess(process* ptr)
{
    if(!ptr)
    {
        return;
    }

    free(ptr);
    printf("\nProcess terminated\n");
}

void CheckProcessStatus(process* ptr)
{
    if(!ptr)
    {
        printf("\nInvalid handle to process\n");
        return;
    }

    printf("\nProcess at %p\tSize:\t%d bytes\tMemory bin bound to:\t%p\n", ptr, ptr->proc_size, ptr->ptr);
}

void FirstFit(process* parray[], bin* barray)
{
    if(!parray || !barray)
    {
        printf("\nINVALID\n");
        return;
    }

    for(int i = 0; i < SAMPLE_SIZE; i++)
    {
        for(int j = 0; j < SAMPLE_SIZE; j++)
        {
            if(parray[i]->proc_size <= (&barray[j])->bin_size && (&barray[j])->bound == false)
            {
                printf("\nMatch found for process %d\n", i+1);
                parray[i]->ptr = (&barray[j]);
                parray[i]->allocated = true;
                (&barray[j])->bound = true;

                (&barray[j])->residue = (&barray[j])->bin_size - parray[i]->proc_size;
                printf("\nProcess %d has allocated bin %d located at %p and residue of bin %d is %d\n", i+1, j+1, (&barray[j]), j+1, (&barray[j])->residue);
                break;
            }
        }
    }
    //display which process number got allocated which bin ( bin number )
}

process** queue = NULL;

int main(void)
{
    bin* bin1 = CreateBucket(5);
    process* proc_list[SAMPLE_SIZE];
    for(int i = 0; i < SAMPLE_SIZE; i++)
    {
        proc_list[i] = CreateProcess(i+10);
    }
    
    FirstFit(proc_list, bin1); 

    for(int i = 0; i < SAMPLE_SIZE; i++)
    {
        CheckProcessStatus(proc_list[i]);
    }

    FreeBucket(bin1);
    for(int i = 0; i < SAMPLE_SIZE; i++)
    {
        ExitProcess(proc_list[i]);
    }

}