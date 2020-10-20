#define SET struct set

#define ELT struct elt

SET* createSet(int MaxElts);

bool search(SET* sp, int searchage, int searchid);

void insertID(SET* sp, int searchage, int searchid);

void deleteID(SET *sp, int insertage, int insertid);

void printArray(SET* sp);

void destroySet(SET *sp);
