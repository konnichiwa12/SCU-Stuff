typedef struct st STRUCT;

STRUCT *createDataSet(int MaxElts);

void destroyDataSet(STRUCT *sp);

bool search(STRUCT *sp, int searchage, int searchid, int *returnindex);

void insertDataSet(STRUCT *sp, int searchage, int searchid);

bool searchBoundary(STRUCT *sp, int searchage, int searchid, int *low, int *high);

void deleteAge(STRUCT *sp, int lobound, int hibound);

int maxAgeGap(STRUCT *sp);

void printArray(STRUCT *sp);

bool search2(STRUCT *sp, int lo, int hi, int searchID, int *returnindex);
