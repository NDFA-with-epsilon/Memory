/* Best Fit algorithm for allocation */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common.h"

/* ################################################################################ */
void swap(int* x, int* y)
{
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}
/* ################################################################################ */

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
        printf("\nFailed to create bucket\nExiting...");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < nBins; i++) //setting the size of all bins
    {
        printf("\nEnter size of bin %d\n", i+1);
        scanf("%d", &((&tmp[i])->bin_size));
        (&tmp[i])->bound = 0; //unbound state at initialization
        (&tmp[i])->bound_proc = NULL; //unbound state at initialization
    }

    for(int i = 0; i < nBins; i++)
    {
        printf("\nBin %d:\tSize: %d bytes at %p\tUnbound\n", i+1, (&tmp[i])->bin_size, &tmp[i]);
    }

    SortBins(&tmp, nBins);
    return tmp;
}

void SortBins(bin** ptr, int size)
{
    if(!ptr || !size)
    {
        printf("\nInvalid bucket\n");
        return;
    }

    for(int i = 0; i < size-1; i++)
    {
        for(int j = i+1; j < size; j++)
        {
            if( ((*ptr)+i)->bin_size > ((*ptr)+j)->bin_size)
            {
                swap(&(((*ptr)+i)->bin_size), &(((*ptr)+j)->bin_size));
            }
        }
    }
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
/* ################################################################################ */
/* ################################################################################ */

process* CreateProcess(int size /* Memory required by the process */)
{
    process* tmp = (process*) malloc(sizeof(process));
    tmp->proc_size = (size != 0) ? size : DEFAULT_SIZE; //allocates 8 bytes by default
    tmp->ptr = NULL;
    tmp->allocated = 0; 

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

void CheckProcessStatus(process** ptr)
{
    if(!ptr)
    {
        printf("\nInvalid handle to process\n");
        return;
    }

    printf("\n************************************************************************************\n");
    for(int i = 0; i < SAMPLE_SIZE; i++)
    {
        printf("\nProcess %d at %p\tRequested size:\t%d bytes\tMemory bin bound to:\t%p\n", i+1, ptr[i], (ptr[i])->proc_size, (ptr[i])->ptr);
    }
    printf("\n************************************************************************************\n");
}
/* ################################################################################ */
/* ################################################################################ */


void BestFit(process** proc_ptr, bin* bin_ptr)
{
    if(!proc_ptr || !bin_ptr)
    {
        printf("\nInvalid request to allocator\n");
        return;
    }
    
    for(int i = 0; i < SAMPLE_SIZE; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(proc_ptr[i]->proc_size <= (&bin_ptr[j])->bin_size && (&bin_ptr[j])->bound == false)
            {
                proc_ptr[i]->ptr = (&bin_ptr[j]);
                proc_ptr[i]->allocated = true;
                (&bin_ptr[j])->bound = true;
                (&bin_ptr[j])->bound_proc = proc_ptr[i];

                printf("\nBest fit found for process %d at bin %d!!!\n", i+1, j+1);
                break;
            }        
        }
    }
}

void CheckInternalFragmentation(bin* ptr)
{
    if(!ptr)
    {
        printf("\nInvalid pointer\n");
    }
    
    printf("\n************************************************************************************\n");
    
    int i_frag = 0;
    for(int i = 0; i < SAMPLE_SIZE; i++)
    {
        if((&ptr[i])->bound == true)
        {
            i_frag = (&ptr[i])->bin_size - ((process*)((&ptr[i])->bound_proc))->proc_size;
            printf("\nInternal fragmentation in bin %d:\t%d", i+1, i_frag);
        }        
        
        else
        {
            printf("\nInternal fragmentation in bin %d:\t--NA--", i+1);
        }
    }

    printf("\n************************************************************************************\n");
}
/* ################################################################################ */

int main(void)
{
    bin* b_ptr = CreateBucket(5);
    process* proc_list[SAMPLE_SIZE];

    for(int i = 0; i < SAMPLE_SIZE; i++)
    {
        proc_list[i] = CreateProcess(i+10);
    }

    BestFit(proc_list, b_ptr);

    CheckProcessStatus(proc_list);
    CheckInternalFragmentation(b_ptr);
    
    FreeBucket(b_ptr);
    for(int i = 0; i < SAMPLE_SIZE; i++)
    {
        ExitProcess(proc_list[i]);
    }
}