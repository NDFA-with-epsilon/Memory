#define DEFAULT_SIZE 8 /*default memory request by a process*/
#define SAMPLE_SIZE 5 /*number of processes */

typedef struct _bin
{
    int bin_size; //size of the bin
    bool bound;   //memory bin is bound to some process or not
    //char proc_data[10];
    void* bound_proc;
}bin;

typedef struct _process
{
    int proc_size; //amount of memory requested by a process
    bin* ptr;       //pointer to a memory bin that can be allocated to this process
    bool allocated; //memory bin allocated to this process or not
}process;


void swap(int* x, int* y);
bin* CreateBucket(int nBins);
void SortBins(bin** ptr, int size);
void FreeBucket(bin* ptr);
process* CreateProcess(int size /* Memory required by the process */);
void ExitProcess(process* ptr);
void CheckProcessStatus(process** ptr);
void CheckInternalFragmentation(bin* ptr);