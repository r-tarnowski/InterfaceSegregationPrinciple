#include <iostream>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>


using std::cout;
using std::endl;

void printHeader() {
   cout << endl;
   cout << "================================================" << endl;
   cout << "Design Patterns in Modern C++ by Dmitri Nesteruk" << endl;
   cout << "SOLID, Interface Segregation Principle" << endl;
   cout << "================================================" << endl;
   cout << endl;
}

struct Document {
    std::string title;

    explicit Document( std::string title )
                     : title( title ) {}
};

struct IPrinter {
    virtual void print( std::vector< Document * > docs ) = 0;
};

struct IScanner {
    virtual void scan( std::vector< Document * > docs ) = 0;
};

struct IMachine : IPrinter, IScanner {
};

struct Printer : IPrinter {
    void print( std::vector< Document * > docs ) override {
        if ( 0 == docs.size() ) {
            cout << "Nothing to print" << endl;
        }
        else {
            for ( auto & ptrDoc : docs ) {
                cout << "Printing " << ptrDoc->title << endl;
            }
        }
    }
};

struct Scanner : IScanner {
    void scan( std::vector< Document * > docs ) override {
        if ( 0 == docs.size() ) {
            cout << "Nothing to scan" << endl;
        }
        else {
            for ( auto & ptrDoc : docs ) {
                cout << "Scanning " << ptrDoc->title << endl;
            }
        }
    }
};

struct Machine : IMachine {
    IScanner & scanner;
    IPrinter & printer;

    Machine( IScanner & scanner, IPrinter & printer )
            : scanner( scanner ),
              printer( printer ) {}

    void print( std::vector< Document * > docs ) override {
        printer.print( docs );
    }

    void scan( std::vector< Document * > docs ) override {
        scanner.scan( docs );
    }

};

int main(int argc, char *argv[]) {
   printHeader();

   Scanner scanner;
   Printer printer;
   Machine machine( scanner, printer );

   Document doc1( "doc1" );
   Document doc2( "doc2" );
   Document doc3( "doc3" );
   std::vector< Document * > docs = { & doc1, & doc2 };

   cout << "Printing docs:" << endl;
   machine.print( docs );

   cout << endl;

   docs.push_back( & doc3 );
   cout << "Scanning docs:" << endl;
   machine.scan( docs );

   cout << endl;
   return 0;
}
