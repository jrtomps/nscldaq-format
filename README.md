NSCLDAQ Format Package
=========================

The NSCLDAQ format package addresses the need for users to operate on data
taken with NSCLDAQ without requiring the entirety of NSCLDAQ. The goal of this
is to simplify the task of the experimenter. We provide:

1. Classes that encapsulate version 8, 10, 11, and 12 data.
2. I/O tools for extracting these data from event files. For example, users can
   write things like a dumper program: 
```

using namespace DAQ::V12;
using namespace std;

CRawRingItem item; 

ifstream file("run-0012-00.evt", ios::binary);

file >> item;
while (file) {
  auto pItem = RingItemFactory::createRingItem(item);
  cout << item.toString();
  cout << "----------------------------------" << endl;
}

```
3. A filter framework to quickly develop programs that process version 11
   data in event files.
4. A dumper program to inspect the data in your event file.
5. A tool to convert between all data formats. Note that there are limitations and 
   consequences of transforming between data formats.

## How to build?


The NSCLDAQ format package leverages the GNU autotools build system that generates
./configure style builds. To build from a cloned repository:

```
autoreconf -i
./configure --prefix=/path/to/install
make all 
make install 
make check
```

If you are building from a distribution tarball, then you skip the first step and just do:

```
./configure --prefix=/path/to/install
make all install check
```

## Documentation

There is doxygen style documentation that documents all of the code. We aim to provide useful
documentation that includes not only descriptions of what classes and methods generally do, but
also code snippets to demonstrate basic usage patterns. That documentation is in process.
