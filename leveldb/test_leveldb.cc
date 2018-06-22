#include <iostream>
#include <string>
#include <sys/time.h>
#include "leveldb/db.h"

using namespace std;
using namespace leveldb;

#define TEST_DATA_NUM 100000
#define TEST_DATA_LEN 100
#define MAX_LEN       10000

struct timeval start, current;

int main()
{
    DB *db;
    Options options;
    options.create_if_missing = true;

    Status s = DB::Open(options, "/tmp/lvd.db", &db);
    if (!s.ok()) {
        cerr << s.ToString() << endl;
        exit(-1);
    }

    int i;
    char k[100], v[MAX_LEN+1];
    string key, val;

    

    return 0;
}
