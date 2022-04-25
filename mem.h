/* first fit */
/* ########################################################################################################################## */
#define DEFAULT_SIZE 8
#define SAMPLE_SIZE 5

typedef struct _bin
{
    int bin_size; //size of the bin
    bool bound;   //memory bin is bound to some process or not
    //char proc_data[10];
    int residue; // bin_size - proc_size for first fit
}bin;

typedef struct _process
{
    int proc_size; //amount of memory required by a process
    bin* ptr;       //pointer to a memory bin that can be allocated to this process
    bool allocated; //memory bin allocated to this process or not
}process;
/* ########################################################################################################################### */

bin* CreateBucket(int nBins);
void FreeBucket(bin* ptr);

process* CreateProcess(int size /* Memory required by the process */);
void CheckProcessStatus(process* ptr);
void ExitProcess(process* ptr);

void FirstFit(process* parray[], bin* barray);
